/***
This is a opengl program that demostrate 3D objects
with lighting, transformation, tessellation shader
and geometry shader. It supports interaction through
keyboard to show the effective of above functionalities.

Author: Ying Zhang
==========
Controller:
  Quit program: Q/ESC key
  prev/next scene: N/M key
  Raise/Lower "inner" tessellation factor: O/K keys
  Raise/Lower "outer" tessellation factor: P/L keys
  roteate object in x/y/z in model coords: W/E/R keys
  move object in x direction: LEFT/RIGHT keys
  move object in y direction: UP/DOWN keys
  move obejct in z direction & raise/lower both inner/outer tess factor: A/Z keys
  scale object: S/X keys
  switch between drawing mode(GL_LINE, GL_FILL) : D key (* only for scene 1 & 2)
***/

#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info/error

#include "Shader.h"       // Shader class for build shader program
#include "Cube.h"         // class for build a 3D cube
#include "Pyramid.h"      // class for build a 3D Pryamid
#include "Dodecahedron.h" // class for build a Dodecahedron


#include "Scene.h"        // class for build Scene

#include <iostream>
#include <string>
#include <vector>

using namespace glm;
using namespace std;


// global variables

// static bool draw_line_mode = true;
/* ---- draw solid line ---
 * For: scene 4 & 5
 * draw surface solid lines or not
 * 1: draw line, else not
 */
static int draw_solid_line = 0;


// scene
static int currentSceneIndex;
vector<Scene*> allScenes;

// define the original window size
int window_width = 1280;
int window_height = 720;

// static function declarations
static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window);
Scene* createScene1(Shader* shader);
Scene* createScene2(Shader* shader);
Scene* createScene3(Shader* shader);
Scene* createScene4(Shader* shader);
Scene* createScene5(Shader* shader);


// ======================= main ===========================
int main () {
  // init glfw, glew, create window
  GLFWwindow* window = init();

  // create shader program
  Shader shader_tess("shader_vs.glsl",
                     "shader_tcs.glsl",
                     "shader_tes.glsl",
                     NULL,
                     "shader_fs.glsl");

  Shader shader_tess_2("shader2_vs.glsl",
                        "shader2_tcs.glsl",
                        "shader2_tes.glsl",
                        NULL,
                        "shader2_fs.glsl");
  Shader shader_tess_3("shader3_vs.glsl",
                        "shader3_tcs.glsl",
                        "shader3_tes.glsl",
                        "shader3_gs.glsl",
                        "shader3_fs.glsl");

  Shader shader_tess_4("shader3_vs.glsl",
                        "shader3_tcs.glsl",
                        "shader3_tes.glsl",
                        "shader4_gs.glsl",
                        "shader4_fs.glsl");

  Shader shader_tess_5("shader3_vs.glsl",
                        "shader3_tcs.glsl",
                        "shader3_tes.glsl",
                        "shader4_gs.glsl",
                        "shader4_fs.glsl");
  // create scenes
  currentSceneIndex = 0;
  // add first scene
  Scene * scene1 = createScene1(&shader_tess);
  Scene * scene2 = createScene2(&shader_tess_2);
  Scene * scene3 = createScene3(&shader_tess_3);
  Scene * scene4 = createScene4(&shader_tess_4);
  Scene * scene5 = createScene5(&shader_tess_5);

  allScenes.push_back(scene1);
  allScenes.push_back(scene2);
  allScenes.push_back(scene3);
  allScenes.push_back(scene4);
  allScenes.push_back(scene5);


  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // start loop
  while (!glfwWindowShouldClose(window)) {
    // clear the buff first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // handle key controls as input
    handleKeyboard(window);

    // draw currentsecne
    allScenes[currentSceneIndex]->drawScene();

    // display buffer stuff on screen
    glfwSwapBuffers(window);
  }

  // exit
  glfwTerminate();
  return 0;
}

// ====================================================
/*
* init glfw, glew, create window
*/
static GLFWwindow* init ()
{
  // init glfw
  cout << glfwGetVersionString() << endl;
  if (!glfwInit()) {
    cerr << "ERROR: can not start GLFW" << endl;
    exit(EXIT_FAILURE);
  }
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef APPLE
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // create glfw window
  GLFWwindow* window = glfwCreateWindow(window_width,
                                        window_height,
                                        "OpenGL Tessellation Shader Demo_1",
                                        NULL,
                                        NULL);
  if (!window) {
    cerr << "ERROR: cannot open window with GLFW" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // keep track of window resize
  glfwSetWindowSizeCallback(window, windowResizedCallback);
  // set key event call back function for exit event
  glfwSetKeyCallback(window, exitKeyCallback);
  // set error call back function
  glfwSetErrorCallback(errorCallback);
  // set as current window before us it
  glfwMakeContextCurrent(window);
  // enable multisampling. set 4 * MSAA in app
  glfwWindowHint(GLFW_SAMPLES, 4);

  // init glew
  glewExperimental = GL_TRUE;
  GLenum initOK = glewInit();
  if (initOK != GLEW_OK) {
    cerr << "ERROR: cannot start GLEW" << endl;
    exit(EXIT_FAILURE);
  }

  // print out version info
  print_version_info();

  // check max patch supported
  if(get_max_patch() <= 1) {
    cerr << "ERROR: incorrect max patch vertices number." << endl;
    exit(EXIT_FAILURE);
  }

  // retrieve the current size of framebuffer of a window
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);

  return window;
}

/*
 * handle key board input
 * o/k: inner tessellation factor
 * p/l: outer tessellation factor
 * UP/DOWN/LEFT/RIGHT: move obj in XY axis
 * W/E/R: rotate x, y. z
 * A/Z: move obj in z axis and tess
 * M/N: prev/next scene
 * X: for scene 4, change draw line or not
 */
static void handleKeyboard (GLFWwindow* window)
{
    Scene* currentScene = allScenes[currentSceneIndex];
    glfwPollEvents();
    // handle key controls for controlling tessellation factors
    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_O)) {
      currentScene->sceneTessllate(1.0, 0);
      cout << "inner tess. factor = " << currentScene->suv.tess_fac_inner << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_K)) {
      currentScene->sceneTessllate(-1.0, 0);
      cout << "inner tess. factor = " << currentScene->suv.tess_fac_inner << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P)) {
      currentScene->sceneTessllate(0, 1.0);
      cout << "outer tess. factor = " << currentScene->suv.tess_fac_outer << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_L)) {
      currentScene->sceneTessllate(0, -1.0);
      cout << "outer tess. factor = " << currentScene->suv.tess_fac_outer << endl;
    }


    // move obj by key left/right, up/down
    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_LEFT)) {
      currentScene->sceneTranslate(-0.1, 0, 0);
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_RIGHT)) {
      currentScene->sceneTranslate(0.1, 0, 0);
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_UP)) {
      currentScene->sceneTranslate(0, 0.1, 0);
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_DOWN)) {
      currentScene->sceneTranslate(0, -0.1, 0);
    }

    // move obj in z directeion and control in/out tess factor by keyborad A/Z
    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {
      currentScene->sceneTranslate(0, 0, 0.1);
      currentScene->sceneTessllate(1.0, 1.0);
      cout << "inner tess = " << currentScene->suv.tess_fac_inner;
      cout << ", outer tess = " << currentScene->suv.tess_fac_outer << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_Z)) {
      currentScene->sceneTranslate(0, 0, -0.1);
      currentScene->sceneTessllate(-1.0, -1.0);
      cout << "inner tess = " << currentScene->suv.tess_fac_inner;
      cout << ", outer tess = " << currentScene->suv.tess_fac_outer << endl;
    }

    // use w, e, r to set rotateion for x, y, z axis
    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W)) {
      currentScene->sceneRotate(25, 1, 0, 0);
      cout << "rotate by x axis" << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_E)) {
      currentScene->sceneRotate(25, 0, 1, 0);
      cout << "rotate by y axis" << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_R)) {
      currentScene->sceneRotate(25, 0, 0, 1);
      cout << "rotate by z axis" << endl;
    }

    // use s, x to set scale for objects
    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_S)) {
      currentScene->sceneScale(1.01, 1.01, 1.01);
      cout << "scale: enlarger the object" << endl;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_X)) {
      currentScene->sceneScale(0.99, 0.99, 0.99);
      cout << "scale: reduce the object" << endl;
    }


    // use N/M to go to prev/next scene
    static bool n_was_down = false;
    static bool m_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_N)) {
      if (!n_was_down) {
        n_was_down = true;
        if (currentSceneIndex == 0) currentSceneIndex = allScenes.size() - 1;
        else currentSceneIndex--;
        cout << "current scene: " << currentSceneIndex + 1 << endl;
      }
    } else {
      n_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_M)) {
      if (!m_was_down) {
        m_was_down = true;
        if (currentSceneIndex == allScenes.size() - 1) currentSceneIndex = 0;
        else currentSceneIndex++;
        cout << "current scene: " << currentSceneIndex + 1 << endl;
      }
    } else {
      m_was_down = false;
    }


    // change drawing mode with key D
    // switch between in line mode or surface mode(GL_LINE or GL_FILL)
    // only works for scene 1, 2
    static bool d_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D) && currentSceneIndex < 2) {
      if (!d_was_down) {
        d_was_down = true;
        allScenes[currentSceneIndex]->changeDrawingMode();
      }
    } else {
      d_was_down = false;
    }

}

/*
* create scene 1: contains 2 3D objects with surface tessellation
*/
Scene* createScene1(Shader * shader) {
  // create objects
  Cube* d1 = new Cube("Coral");
  d1->setSize(2, 2, 2);
  d1->setRotate(45, 0, 1, 0);
  d1->setLocation(0, 0, 0);
  // set shader program for the object
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();

  Pyramid* d2 = new Pyramid("Violet");
  d2->setSize(4, 5, 4);
  d2->setLocation(4,2,0);
  // set shader program for object
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();

  Dodecahedron* d3 = new Dodecahedron("SteelBlue");
  d3->setSize(1.6, 1.6, 1.6);
  d3->setLocation(-4,-2,0);
  // set shader program for the object
  d3->setShaderProgram(shader);
  d3->sendUniformToShader();

  // create Scene
  Scene * currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addObject(d3);
  currentScene->addShader(shader);
  currentScene->sendAllUniformToShaders();

  return currentScene;
}

/*
* create scene 2: contains 2 3D objects with tessellation and normalization
* draw in line
*/
Scene* createScene2(Shader * shader) {
  // create objects
  Cube* d1 = new Cube("Orange");
  d1->setSize(2, 2, 2);
  d1->setRotate(45, 0, 1, 0);
  d1->setLocation(-4, -2, 0);
  // set shader program for the object
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();


  Pyramid* d2 = new Pyramid("Salmon");
  d2->setSize(1.5, 1.5, 2);
  d2->setRotate(45, 1, 1, 0);
  d2->setLocation(0, 2, 2);
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();

  Dodecahedron* d3 = new Dodecahedron("ForestGreen");
  d3->setSize(1.5, 1.5, 1.5);
  d3->setLocation(4, -2, 0);
  d3->setShaderProgram(shader);
  d3->sendUniformToShader();

  // create Scene
  Scene * currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addObject(d3);
  currentScene->addShader(shader);
  currentScene->sendAllUniformToShaders();

  return currentScene;
}


/*
* create scene 3: contains 2 3D objects with tessellation and normalization d
* draw in surface
*/
Scene* createScene3(Shader * shader) {
  // create objects
  Pyramid* d1 = new Pyramid("IndiaRed");
  d1->setSize(2, 2, 2);
  d1->setRotate(30, 0, 1, 0);
  d1->setLocation(-4, 0.5, 0);
  d1->setDrawingMode(0);  // 0: fill, 1:line(default)
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();


  Cube* d2 = new Cube("SteelBlue");
  d2->setSize(2, 2, 3);
  d2->setRotate(78, 1, 1, 1);
  d2->setLocation(4, 1.5, 0);
  d2->setDrawingMode(0);  // 0: fill, 1:line(default)
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();


  Dodecahedron* d3 = new Dodecahedron(0.2, 0.8, 0.3, 1.0);
  d3->setSize(1.5, 1.5, 1.5);
  d3->setRotate(60, 0, 1, 0);
  d3->setLocation(0, -2, 0);
  d3->setDrawingMode(0);  // 0: fill, 1:line(default)
  d3->setShaderProgram(shader);
  d3->sendUniformToShader();

  // create Scene
  Scene * currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addObject(d3);
  currentScene->addShader(shader);
  currentScene->sendAllUniformToShaders();

  return currentScene;
}


/*
* create scene 4: contains 3 3D dode with tess & geo shaders
* draw in surface, with line show tess
*/
Scene* createScene4(Shader * shader) {
  // set shader draw with line
  shader->use();
  shader->setInt("draw_solid_line", draw_solid_line);

  // create objects
  Dodecahedron* d1 = new Dodecahedron("Orange");
  d1->setSize(3, 3, 3);
  d1->setRotate(45, 1, 0, 0);
  d1->setLocation(4, 2, -2);
  d1->setDrawingMode(0);  // 0: fill, 1:line(default)
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();


  Dodecahedron* d2 = new Dodecahedron("DogerBlue");
  d2->setSize(2, 2, 2);
  d2->setRotate(70, 0, 1, 1);
  d2->setLocation(-1, 1, 0);
  d2->setDrawingMode(0);  // 0: fill, 1:line(default)
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();


  Dodecahedron* d3 = new Dodecahedron(1.000, 0.412, 0.706, 1.0);
  d3->setSize(1.5, 1.5, 1.5);
  d3->setRotate(60, 0, 1, 0);
  d3->setLocation(0, -2, -1);
  d3->setDrawingMode(0);  // 0: fill, 1:line(default)
  d3->setShaderProgram(shader);
  d3->sendUniformToShader();

  // create Scene
  Scene * currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addObject(d3);
  currentScene->addShader(shader);
  currentScene->sendAllUniformToShaders();

  return currentScene;
}

/*
* create scene 5: contains 3 3D dode with tess & geo shaders
* draw in surface
*/
Scene* createScene5(Shader * shader) {
  // set shader draw without line
  shader->use();
  shader->setInt("draw_solid_line", draw_solid_line);

  // create objects
  Cube* d1 = new Cube(0.832, 0.223, 0.456, 1.0);
  d1->setSize(0.8, 1.6, 2.2);
  d1->setRotate(50, 0, 0, 1);
  d1->setLocation(-3, 0, 2);
  d1->setDrawingMode(0);  // 0: fill, 1:line(default)
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();


  Pyramid* d2 = new Pyramid("DogerBlue");
  d2->setSize(2, 2, 1);
  d2->setRotate(45, 0, 1, 0);
  d2->setLocation(3, 1.5, 0.5);
  d2->setDrawingMode(0);  // 0: fill, 1:line(default)
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();


  Dodecahedron* d3 = new Dodecahedron(0.223, 0.861, 0.145, 1.0);
  d3->setSize(2, 2, 2);
  d3->setRotate(60, 0, 1, 0);
  d3->setLocation(0, -2, 0);
  d3->setDrawingMode(0);  // 0: fill, 1:line(default)
  d3->setShaderProgram(shader);
  d3->sendUniformToShader();

  // create Scene
  Scene * currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addObject(d3);
  currentScene->addShader(shader);
  currentScene->sendAllUniformToShaders();

  return currentScene;
}
