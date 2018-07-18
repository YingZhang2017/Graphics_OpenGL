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

// scene
static int currentSceneIndex;
vector<Scene*> allScenes;

// define the original window size
int window_width = 1280;
int window_height = 720;

static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window);

// create scenes
Scene* createScene1(Shader* shader);
Scene* createScene2(Shader* shader);
Scene* createScene3(Shader* shader);
Scene* createScene4(Shader* shader);


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

  // create scenes
  currentSceneIndex = 0;
  // add first scene
  Scene * scene1 = createScene1(&shader_tess);
  Scene * scene2 = createScene2(&shader_tess_2);
  Scene * scene3 = createScene3(&shader_tess_3);

  allScenes.push_back(scene1);
  allScenes.push_back(scene2);
  allScenes.push_back(scene3);


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
 */
static void handleKeyboard (GLFWwindow* window)
{
    Scene* currentScene = allScenes[currentSceneIndex];
    glfwPollEvents();
    // handle key controls for controlling tessellation factors
    static bool o_was_down = false;
    static bool k_was_down = false;
    static bool p_was_down = false;
    static bool l_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_O)) {
      if (!o_was_down) {
        currentScene->sceneTessllate(1.0, 0);
        cout << "inner tess. factor = " << currentScene->suv.tess_fac_inner << endl;
        o_was_down = true;

      }
    } else {
      o_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_K)) {
      if (!k_was_down) {
        currentScene->sceneTessllate(-1.0, 0);
        cout << "inner tess. factor = " << currentScene->suv.tess_fac_inner << endl;
        k_was_down = true;
      }
    } else {
      k_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P)) {
      if (!p_was_down) {
        currentScene->sceneTessllate(0, 1.0);
        cout << "outer tess. factor = " << currentScene->suv.tess_fac_outer << endl;
        p_was_down = true;
      }
    } else {
      p_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_L)) {
      if (!l_was_down) {
        currentScene->sceneTessllate(0, -1.0);
        cout << "outer tess. factor = " << currentScene->suv.tess_fac_outer << endl;
        l_was_down = true;
      }
    } else {
      l_was_down = false;
    }


    // move obj by key left/right, up/down
    static bool up_was_down = false;
    static bool down_was_down = false;
    static bool left_was_down = false;
    static bool right_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_LEFT)) {
      if (!left_was_down) {
        left_was_down = true;
        currentScene->sceneTranslate(-0.1, 0, 0);
      }
    } else {
      left_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_RIGHT)) {
      if (!right_was_down) {
        right_was_down = true;
        currentScene->sceneTranslate(0.1, 0, 0);
      }
    } else {
      right_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_UP)) {
      if (!up_was_down) {
        up_was_down = true;
        currentScene->sceneTranslate(0, 0.1, 0);
      }
    } else {
      up_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_DOWN)) {
      if (!down_was_down) {
        down_was_down = true;
        currentScene->sceneTranslate(0, -0.1, 0);
      }
    } else {
      down_was_down = false;
    }

    // move obj in z directeion and control in/out tess factor by keyborad A/Z
    static bool a_was_down = false;
    static bool z_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {
      if (!a_was_down) {
        a_was_down = true;
        currentScene->sceneTranslate(0, 0, 0.1);
        currentScene->sceneTessllate(1.0, 1.0);
        cout << "inner tess = " << currentScene->suv.tess_fac_inner;
        cout << ", outer tess = " << currentScene->suv.tess_fac_outer << endl;
      }
    } else {
      a_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_Z)) {
      if (!z_was_down) {
        z_was_down = true;
        currentScene->sceneTranslate(0, 0, -0.1);
        currentScene->sceneTessllate(-1.0, -1.0);
        cout << "inner tess = " << currentScene->suv.tess_fac_inner;
        cout << ", outer tess = " << currentScene->suv.tess_fac_outer << endl;
      }
    } else {
      z_was_down = false;
    }

    // use w, e, r to set rotateion for x, y, z axis
    static bool w_was_down = false;
    static bool e_was_down = false;
    static bool r_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W)) {
      if (!w_was_down) {
        w_was_down = true;
        currentScene->sceneRotate(25, 1, 0, 0);
        cout << "rotate by x axis for 25 degree" << endl;
      }
    } else {
      w_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_E)) {
      if (!e_was_down) {
        e_was_down = true;
        currentScene->sceneRotate(25, 0, 1, 0);
        cout << "rotate by y axis for 25 degree" << endl;
      }
    } else {
      e_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_R)) {
      if (!r_was_down) {
        r_was_down = true;
        currentScene->sceneRotate(25, 0, 0, 1);
        cout << "rotate by z axis for 25 degree" << endl;
      }
    } else {
      r_was_down = false;
    }

    // use N/M to go to prev/next scene
    static bool n_was_down = false;
    static bool m_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_N)) {
      if (!n_was_down) {
        n_was_down = true;
        if (currentSceneIndex == allScenes.size() - 1) currentSceneIndex = 0;
        else currentSceneIndex++;
        cout << "current scene: " << currentSceneIndex << endl;
      }
    } else {
      n_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_M)) {
      if (!m_was_down) {
        m_was_down = true;
        if (currentSceneIndex == 0) currentSceneIndex = allScenes.size() - 1;
        else currentSceneIndex--;
        cout << "current scene: " << currentSceneIndex << endl;
      }
    } else {
      m_was_down = false;
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
  d2->setSize(5, 5, 5);
  d3->setLocation(-4,-2,2);
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
  d2->setSize(1, 1, 1.5);
  d2->setRotate(45, 1, 1, 0);
  d2->setLocation(0, 2, 2);
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();

  Dodecahedron* d3 = new Dodecahedron("ForestGreen");
  d3->setSize(1.2, 1.2, 0.8);
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
  Pyramid* d1 = new Pyramid("ForestGreen");
  d1->setSize(2, 2, 2);
  d1->setRotate(30, 0, 1, 0);
  d1->setLocation(-3, 1, 0);
  d1->setDrawingMode(0);  // 0: fill, 1:line(default)
  d1->setShaderProgram(shader);
  d1->sendUniformToShader();


  Cube* d2 = new Cube("Orange");
  d2->setSize(2, 2, 3);
  d2->setRotate(78, 1, 1, 1);
  d2->setLocation(3, 1, 0);
  d2->setDrawingMode(0);  // 0: fill, 1:line(default)
  d2->setShaderProgram(shader);
  d2->sendUniformToShader();


  Dodecahedron* d3 = new Dodecahedron(0.4, 0.3, 0.6, 1.0);
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
