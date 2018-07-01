/***
This is a demo programm for tessellation shader in OpenGL
for a traiangle with tesslation.

Author: Ying Zhang
==========
Controller:
Raise/Lower "inner" tessellation factor: O/K keys
Raise/Lower "outter" tessellation factor: P/L keys
***/

#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info, check error
#include "make_shaders.h" // helper functions for make shader programs

#include <iostream>
#include <string>

using namespace std;

// define the original window size
int window_width = 1280;
int window_height = 720;

// set default max patch vertices number
GLuint max_patch_vert = 4;

// define the shader file names. If NA, set it as NULL
const char* vertex_shader_file = "shader_vs.glsl";
const char* tess_ctrl_shader_file = "shader_tcs.glsl";
const char* tess_eval_shader_file = "shader_tes.glsl";
const char* geometry_shader_file = NULL;
const char* fragment_shader_file = "shader_fs.glsl";


// define the initial inner/outter tessellation factor
float inner_tess_fac = 1.0;
float outer_tess_fac = 1.0;


int main () {
  // print out some major info
  cout << glfwGetVersionString() << endl;

  // init glfw
  if (!glfwInit()) {
    cerr << "ERROR: can not start GLFW" << endl;
    return -1;
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
    return -1;
  }

  // keep track of window resize
  glfwSetWindowSizeCallback(window, windowResizedCallback);
  // set key event call back function
  glfwSetKeyCallback(window, keyCallback);
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
    return -1;
  }

  // print out version info
  print_version_info();

  // check max patch supported
  max_patch_vert = get_max_patch();

  // retrieve the current size of framebuffer of a window
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);

  // set triangle coordinates
  GLfloat tri_points [] = {
    0.0f, 0.8f, 0.0f,
    0.4f, -0.4f, 0.0f,
    -0.4f, -0.4f, 0.0f,
  };

  // vbo
  GLuint tri_points_vbo;
  glGenBuffers(1, &tri_points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, tri_points_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri_points), tri_points, GL_STATIC_DRAW);

  // vao
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, tri_points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);


  // set shader program
  GLuint shader_programme = makeShaders(vertex_shader_file,
                                        tess_ctrl_shader_file,
                                        tess_eval_shader_file,
                                        geometry_shader_file,
                                        fragment_shader_file);

	int outer_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_outer");
	int inner_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_inner");

  glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPatchParameteri (GL_PATCH_VERTICES, 3);

  // start loop
  while (!glfwWindowShouldClose(window)) {
    // handle key controls as input
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
				glUniform1f (inner_tess_fac_loc, inner_tess_fac);
			}
		} else {
			o_was_down = false;
		}

		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_K)) {
			if (!k_was_down) {
				inner_tess_fac -= 1.0f;
				cout << "inner tess. factor = " << inner_tess_fac << endl;
				k_was_down = true;
				glUniform1f (inner_tess_fac_loc, inner_tess_fac);
			}
		} else {
			k_was_down = false;
		}

		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_P)) {
			if (!p_was_down) {
				outer_tess_fac += 1.0f;
				cout << "outer tess. factor = " << outer_tess_fac << endl;
				p_was_down = true;
				glUniform1f (outer_tess_fac_loc, outer_tess_fac);
			}
		} else {
			p_was_down = false;
		}

		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_L)) {
			if (!l_was_down) {
				outer_tess_fac -= 1.0f;
        cout << "outer tess. factor = " << outer_tess_fac << endl;
				l_was_down = true;
				glUniform1f (outer_tess_fac_loc, outer_tess_fac);
			}
		} else {
			l_was_down = false;
		}

    //======================

    // clear the buff first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use shader program
    glUseProgram(shader_programme);
    // draw triangle
    glBindVertexArray(vao);
    glDrawArrays(GL_PATCHES, 0, 3);

    // display buffer stuff on screen
    glfwSwapBuffers(window);
  }

  // exit
  glfwTerminate();
  return 0;
}
