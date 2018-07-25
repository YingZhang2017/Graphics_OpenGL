/*
 * Shader.h is an class representing an OpenGL shader prgram
 *
 * Author: Ying Zhang,
 * July, 2018
 *
 * reference sources:
 * 1. UNH cs770 base code of demos, R.Daniel.Bergeron
 *
 * 2. opengl-tutorial
 *    Tutorial 8: Basic Shading
 *    http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
 */

#ifndef _SHADER_H_
#define _SHADER_H_

#include <gl_yz.h>        // self-defined library
#include "gl_utils.h"     // helper functions for check info/error

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
using namespace glm;

class Shader {
public:
  GLuint shaderProgramID;
  // ======= Constructor ======
  // make shader programs by input shader file order as following:
  // vertex shader
  // tessellation control shader
  // tessellation evaluation shader
  // geometry shader
  // fragment shader
  // if Not such shader file, pass NULL
  Shader(const char* v_shader, const char* tc_shader, const char* te_shader,
        const char* g_shader,  const char* f_shader);
  // use the shader program
  void use();
  // set unfiform of different types <unfiorm var name in shader, value>
  void setInt(const char* name, int value);
  void setFloat(const char* name, float value);

  void setVec2 (const char* name, float x, float y);
  void setVec2 (const char* name, const vec2 &value);

  void setVec3 (const char* name, float x, float y, float z);
  void setVec3 (const char* name, const vec3 &value);

  void setVec4 (const char* name, float x, float y, float z, float w);
  void setVec4 (const char* name, const vec4 &value);

  void setMat4 (const char* name, const mat4 &value);

private:
  // parse the shader from file
  char* parseShader(const char* shaderFileName);
  // read a shader file and create a shader object
  GLuint makeShader(const char* shaderFileName, GLenum shaderType);
  // check err for shader compile
  void checkShaderCompileError(const char* shaderFileName, GLuint shaderId);
  // check err for shader link
  void checkShaderLinkError();
};



#endif
