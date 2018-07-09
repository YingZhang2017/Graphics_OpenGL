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

#include <iostream>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

// struct for shader uniform variables
struct ShaderUniformVars {
  // tessellation
  float tess_fac_inner;
  float tess_fac_outer;
  // transformation matrix
  mat4 modelMatrix;
  mat4 viewMatrix;
  mat4 projectionMatrix;

  vec3 camera_position;
  vec3 view_position;
  vec3 head_up;

  float view_angle;
  float aspec_ratio;
  float near;
  float far;

  // lighting
  vec3 light_position;
  vec3 light_color;
  vec3 diffuse_material;
  vec3 ambient_material;
  vec3 object_color;
};

// test
static Cube* d1;

// define the original window size
int window_width = 1280;
int window_height = 720;

static GLFWwindow* init();
static void handleKeyboard(GLFWwindow* window, Shader shader, ShaderUniformVars& suv);

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
  /*
  Shader shader_programme("shader_vs_light.glsl",
                           NULL, NULL, NULL,
                          "shader_fs_light.glsl");
  */
  // ----------------------------------------
  // create object
  d1 = new Cube("SteelBlue");
  d1->setRotateX(45.0, 0.2);
  // set shader program for the object
  d1->setShaderProgram(&shader_programme);

  //----------------------------------------
  // init shader uniform variables
  ShaderUniformVars suv;
  suv.tess_fac_outer = 1.0;
  suv.tess_fac_inner = 1.0;

  suv.view_angle = 45.0f;
  suv.aspec_ratio = (float)window_width / (float)window_height;
  suv.near = 1.0f;
  suv.far = 100.f;
  suv.camera_position = vec3(0.0f, 0.0f, 3.0f);
  suv.view_position = vec3(0.0f, 0.0f, 0.0f);
  suv.head_up = vec3(0.0f, 1.0f, 0.0f);

  suv.modelMatrix = d1->getModelMatrix();
  suv.viewMatrix = lookAt(suv.camera_position, suv.view_position,  suv.head_up);
  suv.projectionMatrix = perspective(suv.view_angle,
                                     suv.aspec_ratio,
                                     suv.near,
                                     suv.far);
  suv.light_position = vec3(1.2f, 1.0f, 2.0f);
  suv.light_color = vec3(1.0f, 1.0f, 1.0f);
  Color c = d1->getColor();
  suv.object_color = vec3(c.r, c.g, c.b);

  // set shader uniforms
  // be sure to activate shader when setting uniforms/drawing objects
  shader_programme.use();

  // set shader uniform variables
  shader_programme.setFloat("tess_fac_outer", suv.tess_fac_outer);
  shader_programme.setFloat("tess_fac_inner", suv.tess_fac_inner);
  shader_programme.setMat4("modelMatrix", suv.modelMatrix);
  shader_programme.setMat4("projectionMatrix", suv.projectionMatrix);
  shader_programme.setMat4("viewMatrix", suv.viewMatrix);

  shader_programme.setVec3("light_position", suv.light_position);
  shader_programme.setVec3("view_position", suv.view_position);
  shader_programme.setVec3("light_color", suv.light_color);
  shader_programme.setVec3("object_color", suv.object_color);
  // ----------------------------------------

  // switch between draw line and surface
  glEnable(GL_DEPTH_TEST);
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
    // draw object
    d1->draw();

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
static void handleKeyboard (GLFWwindow* window,
                            Shader shader,
                            ShaderUniformVars& suv)
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


  // move obj by key left/right, up/down
  static bool up_was_down = false;
  static bool down_was_down = false;
  static bool left_was_down = false;
  static bool right_was_down = false;

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_LEFT)) {
    if (!left_was_down) {
      left_was_down = true;
      suv.modelMatrix[3].x -= 0.1;
      shader.setMat4("modelMatrix", suv.modelMatrix);
    }
  } else {
    left_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_RIGHT)) {
    if (!right_was_down) {
      right_was_down = true;
      suv.modelMatrix[3].x += 0.1;
      shader.setMat4("modelMatrix", suv.modelMatrix);
    }
  } else {
    right_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_UP)) {
    if (!up_was_down) {
      up_was_down = true;
      suv.modelMatrix[3].y += 0.1;
      shader.setMat4("modelMatrix", suv.modelMatrix);
    }
  } else {
    up_was_down = false;
  }

  if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_DOWN)) {
    if (!down_was_down) {
      down_was_down = true;
      suv.modelMatrix[3].y -= 0.1;
      shader.setMat4("modelMatrix", suv.modelMatrix);
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
        suv.modelMatrix[3].z += 0.1;
        shader.setMat4("modelMatrix", suv.modelMatrix);

        suv.tess_fac_inner += 1.0;
        suv.tess_fac_outer += 1.0;
        shader.setFloat("tess_fac_inner", suv.tess_fac_inner);
        shader.setFloat("tess_fac_outer", suv.tess_fac_outer);
        cout << "inner tess = " << suv.tess_fac_inner << ", outer tess = " << suv.tess_fac_outer << endl;
      }
    } else {
      a_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_Z)) {
      if (!z_was_down) {
        z_was_down = true;
        suv.modelMatrix[3].z -= 0.1;
        shader.setMat4("modelMatrix", suv.modelMatrix);

        suv.tess_fac_inner = suv.tess_fac_inner > 1.0 ? suv.tess_fac_inner - 1.0 : 1.0;
        suv.tess_fac_outer = suv.tess_fac_outer > 1.0 ? suv.tess_fac_outer - 1.0: 1.0;
        shader.setFloat("tess_fac_inner", suv.tess_fac_inner);
        shader.setFloat("tess_fac_outer", suv.tess_fac_outer);
        cout << "inner tess = " << suv.tess_fac_inner << ", outer tess = " << suv.tess_fac_outer << endl;
      }
    } else {
      z_was_down = false;
    }

    // use w, e, r to set rotateion for x, y, z axis
    static bool w_was_down = false;
    //static bool e_was_down = false;
    //static bool r_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_W)) {
      if (!w_was_down) {
        w_was_down = true;
        // suv.modelMatrix[3].z += 0.1;


        // shader.setMat4("modelMatrix", suv.modelMatrix);
        cout << "rotate by x axis" << endl;
      }
    } else {
      w_was_down = false;
    }
}
