/***
This is a opengl program that demostrate 3D objects
with lighting, transformation, tessellation shader
and geometry shader. It supports interaction through
keyboard to show the effective of above functionalities.

Author: Ying Zhang
==========
Controller:
Raise/Lower "inner" tessellation factor: O/K keys
Raise/Lower "outer" tessellation factor: P/L keys
***/

#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info/error

#include "Shader.h"       // Shader class for shader program
#include "Cube.h"
#include "Color.h"

#include "Scene.h"

#include <iostream>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

// test
static Scene* currentScene;

// define the original window size
int window_width = 1280;
int window_height = 720;

static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window);

// ======================= main ===========================
int main () {
  // init glfw, glew, create window
  GLFWwindow* window = init();

  // create shader program
  Shader shader_programme("shader_vs.glsl",
                          "shader_tcs.glsl",
                          "shader_tes.glsl",
                          NULL,
                          "shader_fs.glsl");

  // create objects
  Cube* d1 = new Cube("Coral");
  d1->setSize(2, 2, 2);
  d1->setRotate(45, 0, 1, 0);
  // set shader program for the object
  d1->setShaderProgram(&shader_programme);
  d1->sendUniformToShader();

  Cube* d2 = new Cube("ForestGreen");
  d2->setSize(1, 2, 1);
  d2->setRotate(-45, 1, 0, 0);
  d2->setLocation(1.6, 0.8, 0.8);
  // set shader program for object
  d2->setShaderProgram(&shader_programme);
  d2->sendUniformToShader();

  // create Scene
  currentScene = new Scene(window_width, window_height);
  currentScene->addObject(d1);
  currentScene->addObject(d2);
  currentScene->addShader(&shader_programme);
  currentScene->sendAllUniformToShaders();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // start loop
  while (!glfwWindowShouldClose(window)) {
    // clear the buff first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // handle key controls as input
    handleKeyboard(window);

    // draw secne
    currentScene->drawScene();

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
 * UP/DOWN/LEFT/RIGHT: move scene in XY coords
 *
 */
static void handleKeyboard (GLFWwindow* window)
{
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

}
