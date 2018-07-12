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
#include "Shader.h"
#include <iostream>

using namespace glm;

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
  Shader* shaderProgram;

  // VBO information
  GLuint vboId_vert;
  GLuint vboId_normal;
  int vboBytes;    // size of vbo buffer in bytes
  int vboSize;     // number of vertices/colors/etc... in vbo buffer
  // vao id
  GLuint vaoId;

public:
  Shape3D();
  virtual ~Shape3D();

  // retrun transformed model matrix
  mat4 getModelMatrix();

  // return color
  inline Color getColor() { return color; }
  // return position
  inline vec3 getLocation() { return vec3(xLoc, yLoc, zLoc); }
  // return rotate angle
  inline float getRotateAngle () { return angle; }

  // set shader program for object
  void setShaderProgram(Shader* sp);
  // set object location
  void setLocation(float x, float y, float z);
  // set object size
  void setSize(float x, float y, float z);
  // set rotation
  void setRotate( float angle, float dx, float dy, float dz );
  // set colort for object
  void setColor(string colorName);
  void setColor(Color c);
  void setColor(float r, float g, float b, float a = 1.0);

  virtual void createBuffer() = 0;
  virtual void draw() = 0;
};

#endif
