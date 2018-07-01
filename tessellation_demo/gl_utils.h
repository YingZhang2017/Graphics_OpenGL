#ifndef _GL_UTILS_H_
#define _GL_UTILS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// keep track of window size
extern int window_width;
extern int window_height;

// a call-back function to notify whrn window is resized
void windowResizedCallback (GLFWwindow* window, int width, int height);

// print version info
void print_version_info ();

// print max patch number that supported 
void print_max_patch ();

// print shader file
void print_shader_file (const char* fileName, char* buff);

#endif
