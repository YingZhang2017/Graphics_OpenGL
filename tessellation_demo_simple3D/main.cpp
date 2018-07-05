/***
This is a demo programm for tessellation shader in OpenGL
for a PNtraiangles (Point Normal Triangles) with tesslation.

"maths_funcs.h": source:  "Anton's OpenGL 4 Tutorials"

Author: Ying Zhang
==========
Controller:
Raise/Lower "inner" tessellation factor: O/K keys
Raise/Lower "outter" tessellation factor: P/L keys
Move object position: LEFT/RIGHT/UP/DOWN keys
***/
#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info, check error
#include "make_shaders.h" // helper functions for make shader programs
#include "maths_funcs.h"  // math function.

#include <iostream>
#include <string>

using namespace std;

// define the original window size
int window_width = 1280;
int window_height = 720;

// set default max patch vertices number
GLuint max_patch_vert = 1;

// define the shader file names. If NA, set it as NULL
const char* vertex_shader_file = "shader_vs.glsl";
const char* tess_ctrl_shader_file = "shader_tcs.glsl";
const char* tess_eval_shader_file = "shader_tes.glsl";
const char* geometry_shader_file = NULL;
const char* fragment_shader_file = "shader_fs.glsl";

// inner/outer tess factor
float inner_tess_fac = 1.0; // inner tess factor
float outer_tess_fac = 1.0; // outer tess factor

static GLFWwindow* init();
static GLuint GeneraterObjectVAO();
// ======================= main ===========================

int main () {
  // init glfw, glew, create window
  GLFWwindow* window = init();

  // generate object and return vao
  GLuint vao = GeneraterObjectVAO();

  // set shader program
  GLuint shader_programme = makeShaders(vertex_shader_file,
                                        tess_ctrl_shader_file,
                                        tess_eval_shader_file,
                                        geometry_shader_file,
                                        fragment_shader_file);

	// input variables
	float near = 0.1f; // clipping plane
	float far = 100.0f; // clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)window_width / (float)window_height; // aspect ratio
	// matrix components
	float range = tan (fov * 0.5f) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);
  GLfloat projection_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};

  float cam_pos[] = {0.0f, 0.0f, 2.0f};
	float cam_yaw = 0.0f; // y-rotation in degrees
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);

	mat4 model_mat = identity_mat4 ();
	model_mat.m[12] = 1.0;
	mat4 view_mat = R * T;

  glUseProgram (shader_programme);
	int view_mat_location = glGetUniformLocation (shader_programme, "view_mat");
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	int proj_mat_location = glGetUniformLocation (shader_programme, "projection_mat");
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, projection_mat);
	int model_mat_location = glGetUniformLocation (shader_programme, "model_mat");
	glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);

  int outer_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_outer");
	int inner_tess_fac_loc = glGetUniformLocation(shader_programme, "tess_fac_inner");

  // init states
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
        inner_tess_fac = inner_tess_fac > 0 ? inner_tess_fac - 1.0 : 0.0;
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
        outer_tess_fac = outer_tess_fac > 0 ? inner_tess_fac - 1.0 : 0.0;
        cout << "outer tess. factor = " << outer_tess_fac << endl;
				l_was_down = true;
				glUniform1f (outer_tess_fac_loc, outer_tess_fac);
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
        model_mat.m[12] -= 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
      }
    } else {
      left_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_RIGHT)) {
      if (!right_was_down) {
        right_was_down = true;
        model_mat.m[12] += 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
      }
    } else {
      right_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_UP)) {
      if (!up_was_down) {
        up_was_down = true;
        model_mat.m[13] += 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
      }
    } else {
      up_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_DOWN)) {
      if (!down_was_down) {
        down_was_down = true;
        model_mat.m[13] -= 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);
      }
    } else {
      down_was_down = false;
    }

    // scale obj by keyborad A/Z
    static bool a_was_down = false;
    static bool z_was_down = false;

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {
      if (!a_was_down) {
        a_was_down = true;
        model_mat.m[14] += 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);

        inner_tess_fac += 1.0;
        outer_tess_fac += 1.0;
        glUniform1f (inner_tess_fac_loc, inner_tess_fac);
        glUniform1f (outer_tess_fac_loc, outer_tess_fac);
        cout << "inner tess = " << inner_tess_fac << ", outer tess = " << outer_tess_fac << endl;
      }
    } else {
      a_was_down = false;
    }

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_Z)) {
      if (!z_was_down) {
        z_was_down = true;
        model_mat.m[14] -= 0.1;
        glUniformMatrix4fv (model_mat_location, 1, GL_FALSE, model_mat.m);

        inner_tess_fac = inner_tess_fac > 0 ? inner_tess_fac - 1.0 : 0.0;
        outer_tess_fac = outer_tess_fac > 0 ? inner_tess_fac - 1.0: 0.0;
        glUniform1f (inner_tess_fac_loc, inner_tess_fac);
        glUniform1f (outer_tess_fac_loc, outer_tess_fac);
        cout << "inner tess = " << inner_tess_fac << ", outer tess = " << outer_tess_fac << endl;
      }
    } else {
      z_was_down = false;
    }


    // clear the buff first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use shader program
    glUseProgram(shader_programme);

    // render the object
    glBindVertexArray(vao);
    glDrawArrays(GL_PATCHES, 0, 12);

    // display buffer stuff on screen
    glfwSwapBuffers(window);
  }

  // exit
  glfwTerminate();
  return 0;
}

// ==========================================

/*
* init glfw, glew, create window
*/
static GLFWwindow* init () {
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
 * generate object and return vao
 */
static GLuint GeneraterObjectVAO () {
    // set triangle coordinates.
    GLfloat tri_points [] = {
      // -0.7f, -0.8f, 0.0f,   -0.1f, 0.7f, 0.0f,   0.8f, -0.2f, 0.0f,
      0.0f, 0.5f, 0.0f,    -0.5f, -0.5f, 0.0f,     0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.5f,
      0.0f, 0.5f, 0.0f,     0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.5f,
      -0.5f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.5f
    };

    GLfloat tri_normals [] = {
      0.0f, 0.0f,  1.0f,   0.0f, 0.0f,  1.0f,    0.0f, 0.0f,  1.0f,
      0.0f, 0.0f,  1.0f,   0.0f, 0.0f,  1.0f,    0.0f, 0.0f,  1.0f,
      0.0f, 0.0f,  1.0f,   0.0f, 0.0f,  1.0f,    0.0f, 0.0f,  1.0f,
      0.0f, 0.0f,  1.0f,   0.0f, 0.0f,  1.0f,    0.0f, 0.0f,  1.0f

    };

    GLfloat tri_textCords [] = {
      0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,
      0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,
      0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,
      0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f
    };

    // vbo
    GLuint tri_points_vbo;
    glGenBuffers(1, &tri_points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tri_points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_points), tri_points, GL_STATIC_DRAW);

    GLuint tri_normals_vbo;
    glGenBuffers(1, &tri_normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tri_normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_normals), tri_normals, GL_STATIC_DRAW);

    GLuint tri_textCords_vbo;
    glGenBuffers(1, &tri_textCords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tri_textCords_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_textCords), tri_textCords, GL_STATIC_DRAW);

    // vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, tri_points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, tri_normals_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, tri_textCords_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    return vao;
}
