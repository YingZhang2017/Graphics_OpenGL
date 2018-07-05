/***
This is a opengl program that demostrate 3D objects
with lighting, transformation, tessellation shader
and geometry shader. It supports interaction through
keyboard to show the effective of above functionalities.

Author: Ying Zhang
==========
Controller:
Raise/Lower "inner" tessellation factor: O/K keys
Raise/Lower "outter" tessellation factor: P/L keys
***/

#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info, check error
#include "make_shaders.h" // helper functions for make shader programs

#include "Shape3D.h"
#include "Color.h"

#include <iostream>
#include <string>
#include <vector>

// enable glm/gxt/transforme.hpp
#define GLM_ENABLE_EXPERIMENTAL
using namespace glm;
using namespace std;

// struct for saving shader uniform vars
struct ShaderUniformVars{
  int inner_tess_fac_loc;
  int outer_tess_fac_loc;
};

// define the original window size
int window_width = 1280;
int window_height = 720;
// set default max patch vertices number
GLuint max_patch_vert = 1;
// define the initial inner/outter tessellation factor
static float inner_tess_fac = 1.0;
static float outer_tess_fac = 1.0;
// define the shader file names. If NA, set it as NULL
const char* vertex_shader_file = "shader_vs.glsl";
const char* tess_ctrl_shader_file = "shader_tcs.glsl";
const char* tess_eval_shader_file = "shader_tes.glsl";
const char* geometry_shader_file = NULL;
const char* fragment_shader_file = "shader_fs.glsl";

static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window, ShaderUniformVars suv);


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

  // set shader program
  GLuint shader_programme = makeShaders(vertex_shader_file,
                                        tess_ctrl_shader_file,
                                        tess_eval_shader_file,
                                        geometry_shader_file,
                                        fragment_shader_file);
  // shader uniform variables
  ShaderUniformVars suv;
  suv.outer_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_outer");
	suv.inner_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_inner");

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
    handleKeyboard(window, suv);

    // use shader program
    glUseProgram(shader_programme);

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
  // print out some major info
  cout << glfwGetVersionString() << endl;

  // init glfw
  if (!glfwInit()) {
    cerr << "ERROR: can not start GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  // specify openGL3.2 for MAC OS
  #ifdef APPLE
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif

  // create window
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
  max_patch_vert = get_max_patch();
  if(max_patch_vert <= 1) {
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
static void handleKeyboard (GLFWwindow* window, ShaderUniformVars suv)
{
  glfwPollEvents();
  // handle key controls for controlling tessellation factors
  static bool o_was_down = false;
  static bool k_was_down = false;
  static bool p_was_down = false;
  static bool l_was_down = false;

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_O)) {
    if (!o_was_down) {
      inner_tess_fac += 1.0f;
      cout << "inner tess. factor = " << inner_tess_fac << endl;
      o_was_down = true;
      glUniform1f (suv.inner_tess_fac_loc, inner_tess_fac);
    }
  } else {
    o_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_K)) {
    if (!k_was_down && inner_tess_fac > 1.0f) {
      inner_tess_fac -= 1.0f;
      cout << "inner tess. factor = " << inner_tess_fac << endl;
      k_was_down = true;
      glUniform1f (suv.inner_tess_fac_loc, inner_tess_fac);
    }
  } else {
    k_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P)) {
    if (!p_was_down) {
      outer_tess_fac += 1.0f;
      cout << "outer tess. factor = " << outer_tess_fac << endl;
      p_was_down = true;
      glUniform1f (suv.outer_tess_fac_loc, outer_tess_fac);
    }
  } else {
    p_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_L)) {
    if (!l_was_down && outer_tess_fac > 1.0f) {
      outer_tess_fac -= 1.0f;
      cout << "outer tess. factor = " << outer_tess_fac << endl;
      l_was_down = true;
      glUniform1f (suv.outer_tess_fac_loc, outer_tess_fac);
    }
  } else {
    l_was_down = false;
  }
}
