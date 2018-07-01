#ifndef _GL_UTILS_H_
#define _GL_UTILS_H_

#include <gl_yz.h>

// keep track of window size
extern int window_width;
extern int window_height;

// a call-back function to notify when window is resized
void windowResizedCallback (GLFWwindow* window, int width, int height);

// a call-back function when a GLFW function fails
void errorCallback (int error, const char* description);

// a call-back function for key event
void keyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);

// print version info
void print_version_info ();

// get max patch number that supported
GLuint get_max_patch ();

// print shader file
void print_shader_file (const char* fileName, char* buff);

#endif
