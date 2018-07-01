#include "make_shaders.h"
#include <iostream>
#include <fstream>

using namespace std;

// parse the shader from file
char* parseShader(const char* shaderFileName) {



}

// read a shader file and create a shader object
GLuint makeShader(const char* shaderFileName, GLenum shaderType) {
    //Lchar* shaderSource = readShaderSource
    return 0;
}

// create a GLSL program object by following order:
// vertex shader
// tessellation control shader
// tessellation evaluation shader
// geometry shader
// fragment shader
GLuint makeShaders(const char* v_shader,
                   const char* tc_shader,
                   const char* te_shader,
                   const char* g_shader,
                   const char* f_shader) {

  return 0;
}
