#ifndef _MAKE_SHADERS_H_
#define _MAKE_SHADERS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// make shader programs by input shader file order as following:
// vertex shader
// tessellation control shader
// tessellation evaluation shader
// geometry shader
// fragment shader
GLuint makeShaders(const char* v_shader,
                   const char* tc_shader,
                   const char* te_shader,
                   const char* g_shader,
                   const char* f_shader);


#endif
