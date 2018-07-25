/*
 * gl_utils.h - a class implementation help funtions for information check and print
 *
 * Author: Ying Zhang
 * July, 2018
 *
 * reference sources:
 * 1. UNH cs770 base code of demos, R.Daniel.Bergeron
 *
 * 2. Accompanies written series "Anton's OpenGL 4 Tutorials"
 *    Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.
 *    https://github.com/capnramses/antons_opengl_tutorials_book
 */

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

// a call-back function for key event. only define exit key event
void exitKeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);

// print version info
void print_version_info ();

// get max patch number that supported
GLuint get_max_patch ();

// print shader file
void print_shader_file (const char* fileName, char* buff);

#endif
