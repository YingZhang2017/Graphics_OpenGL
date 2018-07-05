/*
 * Shape3D is an abstract class representing an OpenGL graphical object
 * Edited base on cs770's Shape3D.h
 *
 * Ying Zhang, Jul 2018
 */

#ifndef Shape3D_H_
#define Shape3D_H_

#include <gl_yz.h>
#include "Color.h"
#include <iostream>

using namespace glm;

struct VBOInfo {
  // vbo buffer id for this object
  GLuint vertId;      // 0: vertices buffer id
  GLuint colorId;     // 1: colors buffer id
  int    vboBytes;    // size of vbo buffer in bytes
  int    vboSize;     // number of vertices/colors/etc... in vbo buffer
};

class Shape3D {
protected:
  // object attributes
  float xLoc, yLoc, zLoc;           // original location of object(translation)
  float xSize, ySize, zSize;        // original size of object(scale)
  float angle, dxRot, dyRot, dzRot; // original rotation angle and axis(rotate)
  Color color;                      // original color
  // matrix fotr translation, rotation and scalation
  mat4 T, R, S;
  // model matrix
  mat4 modelMatrix;

  // shader program name used for object
  GLuint shaderProgram;
  bool hasSetShader;

  // VBO information
  VBOInfo vbo;
  // vao id
  GLuint vaoId;

  // for redrawObject() steps
  virtual void sendUniformToShader();
  virtual GLuint createVBO(float* coords, int size, int index);
  virtual void redrawGLSL() = 0;

public:
  Shape3D();
  virtual ~Shape3D();

  // set shader program for object
  void setShaderProgram(GLuint sp);
  // check shader program is set already
  void checkShaderProgram();
  // set object location
  void setLocation(float x, float y, float z);
  // set object size
  void setSize(float x, float y, float z);
  // set rotation
  void setRotateX(float an, float dx);
  void setRotateY(float an, float dy);
  void setRotateZ(float an, float dz);
  // set colort for object
  void setColor(Color c);
  void setColor(float r, float g, float b, float a = 1.0);

  virtual void redrawObject();
};

#endif
