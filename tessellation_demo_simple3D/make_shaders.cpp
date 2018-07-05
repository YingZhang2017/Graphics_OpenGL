#include "make_shaders.h"
#include "gl_utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

// parse the shader from file
char* parseShader(const char* shaderFileName)
{
    ifstream shaderfile(shaderFileName);
    string contents((istreambuf_iterator<char>(shaderfile)),
                    istreambuf_iterator<char>());
    char* buff = new char[contents.length() + 1];
    strcpy (buff, contents.c_str());
    return buff;
}

// read a shader file and create a shader object
GLuint makeShader(const char* shaderFileName, GLenum shaderType)
{
    char* shaderSource = parseShader(shaderFileName);
    const GLchar* p = (const GLchar*)shaderSource;

    GLuint shader = glCreateShader (shaderType);
    glShaderSource (shader, 1, &p, NULL);
    glCompileShader (shader);

    // check for compile errors
    int compiled = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
      GLsizei log_length = 0;
      GLchar message[1024];
      glGetShaderInfoLog(shader, 1024, &log_length, message);
      cerr << "ERROR: compile failed for shader: " << shaderFileName << endl;
      cerr << message << endl;
      exit(EXIT_FAILURE);
    }

    return shader;
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
                   const char* f_shader)
{
    GLuint shader_programme = glCreateProgram();
    GLuint vs, tcs, tes, gs, fs;

    if (v_shader) {
      vs = makeShader(v_shader, GL_VERTEX_SHADER);
      glAttachShader(shader_programme, vs);
    }
    if (tc_shader) {
      tcs = makeShader(tc_shader, GL_TESS_CONTROL_SHADER);
      glAttachShader(shader_programme, tcs);
    }
    if (te_shader) {
      tes = makeShader(te_shader, GL_TESS_EVALUATION_SHADER);
      glAttachShader(shader_programme, tes);
    }
    if (g_shader) {
      gs = makeShader(g_shader, GL_GEOMETRY_SHADER);
      glAttachShader(shader_programme, gs);
    }
    if (f_shader) {
      fs = makeShader(f_shader, GL_FRAGMENT_SHADER);
      glAttachShader(shader_programme, fs);
    }

    // link program
    glLinkProgram(shader_programme);
    int linked = -1;
    glGetProgramiv(shader_programme, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
      cerr << "ERROR: cannot link shader program, index:" << shader_programme << endl;
      printShaderLinkError(shader_programme);
      // delete program before exit
      glDeleteProgram(shader_programme);
      exit(EXIT_FAILURE);
    }

    // detach shaders after link successfully
    if (v_shader) glDetachShader(shader_programme, vs);
    if (tc_shader) glDetachShader(shader_programme, tcs);
    if (te_shader) glDetachShader(shader_programme, tes);
    if (g_shader) glDetachShader(shader_programme, gs);
    if (f_shader) glDetachShader(shader_programme, fs);

    return shader_programme;
}

void printShaderLinkError (GLuint shader_programme) {
  GLint maxLength = 0;
  glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &maxLength);
  // The maxLength includes the NULL character
  std::vector<GLchar> infoLog(maxLength);
  glGetProgramInfoLog(shader_programme, maxLength, &maxLength, &infoLog[0]);
  for (int i = 0; i < infoLog.size(); i++) cout << infoLog[i];
  cout << endl;
}
