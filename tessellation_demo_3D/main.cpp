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
#include "Shape3D.h"
#include "Color.h"

#include <iostream>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

// struct for shader uniform variables
struct ShaderUniformVars {
  float tess_fac_inner;
  float tess_fac_outer;
};

// define the original window size
int window_width = 1280;
int window_height = 720;

static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window, Shader shader, ShaderUniformVars& suv);


// ======================= main ===========================
int main () {
  // init glfw, glew, create window
  GLFWwindow* window = init();

  //=========================
  // set triangle coordinates
  GLfloat tri_points [] = {
    0.0f, 0.8f, 0.0f,
    0.4f, 0.0f, 0.0f,
    -0.4f, 0.0f, 0.0f
  };

  int nVertices = sizeof(tri_points)/sizeof(GLfloat)/3;

  // create and active vao
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // create and active vbo
  GLuint tri_points_vbo;
  glGenBuffers(1, &tri_points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, tri_points_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri_points), tri_points, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // index of vao. if only 1, use 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // create shader program
  Shader shader_programme("shader_vs.glsl",
                          "shader_tcs.glsl",
                          "shader_tes.glsl",
                          NULL,
                          "shader_fs.glsl");
  // init shader uniform variables
  ShaderUniformVars suv;
  suv.tess_fac_outer = 1.0;
  suv.tess_fac_inner = 1.0;
  // set shader uniform variables
  shader_programme.setFloat("tess_fac_outer", suv.tess_fac_outer);
  shader_programme.setFloat("tess_fac_inner", suv.tess_fac_inner);

  glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPatchParameteri (GL_PATCH_VERTICES, 3);


  // start loop
  while (!glfwWindowShouldClose(window)) {
    // clear the buff first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // handle key controls as input
    handleKeyboard(window, shader_programme, suv);

    // use shader program
    shader_programme.use();

    // draw triangle
    glBindVertexArray(vao);
    glDrawArrays(GL_PATCHES, 0, nVertices);

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
static void handleKeyboard (GLFWwindow* window, Shader shader, ShaderUniformVars& suv)
{
  glfwPollEvents();
  // handle key controls for controlling tessellation factors
  static bool o_was_down = false;
  static bool k_was_down = false;
  static bool p_was_down = false;
  static bool l_was_down = false;

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_O)) {
    if (!o_was_down) {
      suv.tess_fac_inner += 1.0f;
      cout << "inner tess. factor = " << suv.tess_fac_inner << endl;
      o_was_down = true;
      shader.setFloat("tess_fac_inner", suv.tess_fac_inner);
    }
  } else {
    o_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_K)) {
    if (!k_was_down && suv.tess_fac_inner > 1.0f) {
      suv.tess_fac_inner -= 1.0f;
      cout << "inner tess. factor = " << suv.tess_fac_inner << endl;
      k_was_down = true;
      shader.setFloat("tess_fac_inner", suv.tess_fac_inner);
    }
  } else {
    k_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P)) {
    if (!p_was_down) {
      suv.tess_fac_outer += 1.0f;
      cout << "outer tess. factor = " << suv.tess_fac_outer << endl;
      p_was_down = true;
      shader.setFloat("tess_fac_outer", suv.tess_fac_outer);
    }
  } else {
    p_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_L)) {
    if (!l_was_down && suv.tess_fac_outer > 1.0f) {
      suv.tess_fac_outer -= 1.0f;
      cout << "outer tess. factor = " << suv.tess_fac_outer << endl;
      l_was_down = true;
      shader.setFloat("tess_fac_outer", suv.tess_fac_outer);
    }
  } else {
    l_was_down = false;
  }
}
