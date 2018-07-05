#ifndef _MAKE_SHADERS_H_
#define _MAKE_SHADERS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// parse the shader from file
char* parseShader(const char* shaderFileName);

// read a shader file and create a shader object
GLuint makeShader(const char* shaderFileName, GLenum shaderType);

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

// log err for shader link
void printShaderLinkError (GLuint shader_programme);

#endif
