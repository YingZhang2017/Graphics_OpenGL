/*
 * Shader.h is an class representing an OpenGL shader prgram
 *
 * Ying Zhang, Jul 2018
 */
#include "Shader.h"
#include "gl_utils.h"

using namespace std;
#define DEBUG 0      // switch to turn on DEBUG

// ======================== Constructor =======================
// make shader programs by input shader file order as following:
// vertex shader
// tessellation control shader
// tessellation evaluation shader
// geometry shader
// fragment shader
// if Not such shader file, pass NULL
Shader::Shader(const char* v_shader,
               const char* tc_shader, const char* te_shader,
               const char* g_shader,  const char* f_shader)
{
    // set shder id
    shaderProgramID = glCreateProgram();
    GLuint vs, tcs, tes, gs, fs;

    if (v_shader) {
      vs = makeShader(v_shader, GL_VERTEX_SHADER);
      glAttachShader(shaderProgramID, vs);
    }
    if (tc_shader) {
      tcs = makeShader(tc_shader, GL_TESS_CONTROL_SHADER);
      glAttachShader(shaderProgramID, tcs);
    }
    if (te_shader) {
      tes = makeShader(te_shader, GL_TESS_EVALUATION_SHADER);
      glAttachShader(shaderProgramID, tes);
    }
    if (g_shader) {
      gs = makeShader(g_shader, GL_GEOMETRY_SHADER);
      glAttachShader(shaderProgramID, gs);
    }
    if (f_shader) {
      fs = makeShader(f_shader, GL_FRAGMENT_SHADER);
      glAttachShader(shaderProgramID, fs);
    }

    // link program
    glLinkProgram(shaderProgramID);
    // check shader program link error
    checkShaderLinkError();

    // detach and delete shaders after link successfully
    if (v_shader) {
      glDetachShader(shaderProgramID, vs);
      glDeleteShader(vs);
    }
    if (tc_shader) {
      glDetachShader(shaderProgramID, tcs);
      glDeleteShader(tcs);
    }
    if (te_shader) {
      glDetachShader(shaderProgramID, tes);
      glDeleteShader(tes);
    }
    if (g_shader) {
      glDetachShader(shaderProgramID, gs);
      glDeleteShader(gs);
    }
    if (f_shader) {
      glDetachShader(shaderProgramID, fs);
      glDeleteShader(fs);
    }
}

// ===============================================================
// use shader programs
void Shader::use()
{
  glUseProgram(shaderProgramID);
}

// ===============================================================
// set unfiform of different types <unfiorm var name in shader, value>
void Shader::setInt(const char* name, int value)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform1i(loc, value);
}

void Shader::setFloat(const char* name, float value)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform1f(loc, value);
}

void Shader::setVec2 (const char* name, float x, float y)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform2f(loc, x, y);
}

void Shader::setVec2 (const char* name, const vec2& value)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform2f(loc, value.x, value.y);
}

void Shader::setVec3 (const char* name, float x, float y, float z)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform3f(loc, x, y, z);
}

void Shader::setVec3 (const char* name, const vec3& value)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setVec4 (const char* name, float x, float y, float z, float w)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform4f(loc, x, y, z, w);
}

void Shader::setVec4 (const char* name, const vec4& value) {
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setMat4 (const char* name, const mat4 &value)
{
  int loc = glGetUniformLocation(shaderProgramID, name);
  glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

// ===============================================================
// ====== parse shader content by file name ========
char* Shader::parseShader(const char* shaderFileName)
{
    ifstream shaderfile(shaderFileName);
    string contents((istreambuf_iterator<char>(shaderfile)),
                    istreambuf_iterator<char>());
    char* buff = new char[contents.length() + 1];
    strcpy (buff, contents.c_str());

    // print shader content
    if (DEBUG) print_shader_file(shaderFileName, buff);
    return buff;
}

// ===============================================================
// read a shader file and create a shader object
GLuint Shader::makeShader(const char* shaderFileName, GLenum shaderType)
{
    char* shaderSource = parseShader(shaderFileName);
    const GLchar* p = (const GLchar*)shaderSource;

    GLuint shader = glCreateShader (shaderType);
    glShaderSource (shader, 1, &p, NULL);
    glCompileShader (shader);

    // check for compile errors
    checkShaderCompileError(shaderFileName, shader);

    return shader;
}

// ===============================================================
// check err for shader compile
void Shader::checkShaderCompileError(const char* shaderFileName, GLuint shaderID)
{
  int compiled = - 1;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

  if (compiled != GL_TRUE) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(shaderID, 1024, &log_length, message);
    cerr << "ERROR: compile failed for shader: " << shaderFileName << endl;
    cerr << message << endl;
    exit(EXIT_FAILURE);
  }
}

// ===============================================================
// check err for shader link
void Shader::checkShaderLinkError()
{
  int linked = -1;
  glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linked);
  if (linked != GL_TRUE) {
    cerr << "ERROR: cannot link shader program, index:" << shaderProgramID << endl;
    GLint maxLength = 0;
    glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(shaderProgramID, maxLength, &maxLength, &infoLog[0]);
    for (int i = 0; i < infoLog.size(); i++) cout << infoLog[i];
    cout << endl;
    // delete program before exit
    glDeleteProgram(shaderProgramID);
    exit(EXIT_FAILURE);
  }
}
