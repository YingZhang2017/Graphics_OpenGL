/*
 * Shape3D is an abstract class representing an OpenGL graphical object
 * Edited base on cs770's Shape3D.cpp
 *
 * Ying Zhang, Jul 2018
 */

#include "Shape3D.h"
#include "Color.h"

// ====== Constructor ========
// create a new Shape3D object
// position (0,0,0,), size (1,1,1), color: DogerBlue
Shape3D::Shape3D() {
  // init TRS and modelMatrix
  R = mat4(1.0f);
  S = mat4(1.0f);
  T = mat4(1.0f);

  modelMatrix = mat4(1.0);

  setLocation(0, 0, 0);
  setSize(1, 1, 1);
  setRotateX(0, 0);
  setRotateY(0, 0);
  setRotateZ(0, 0);
  color.set_DogerBlue();
}

// ====== Destructor ==========
Shape3D::~Shape3D(){}

// get modelMatrix after transformed
mat4 Shape3D::getModelMatrix() {
  modelMatrix = modelMatrix * T * R * S;
  return modelMatrix;
}

// ======= set shader program =====
void Shape3D::setShaderProgram(Shader* sp) {
  shaderProgram = sp;
}

// ======= set object location ========
void Shape3D::setLocation(float x, float y, float z) {
  xLoc = x;
  yLoc = y;
  zLoc = z;
  T = translate(T, vec3(x, y, z));
}

// ======= set object size =======
void Shape3D::setSize(float x, float y, float z) {
  xSize = x;
  ySize = y;
  zSize = z;
  S = scale(S, vec3(x, y, z));
}

// ======= set rotation X =======
void Shape3D::setRotateX(float an, float dx) {
  angle = an;
  dxRot = dx;
  R = rotate(angle, vec3(1, 0, 0));
}

// ======= set rotation Y =======
void Shape3D::setRotateY(float an, float dy) {
  angle = an;
  dyRot = dy;
  R = rotate(angle, vec3(0, 1, 0));
}

// ======= set rotation Z =======
void Shape3D::setRotateZ(float an, float dz) {
  angle = an;
  dzRot = dz;
  R = rotate(angle, vec3(0, 0, 1));
}

// ===== set colort for object =======
void Shape3D::setColor(float r, float g, float b, float a) {
  color.set(r, g, b, a);
}

void Shape3D::setColor(Color c) {
  color = c;
}

void Shape3D::setColor(string colorName) {
  color.set(colorName);
}

// ====== create vbo and vao =======
void Shape3D::createBuffer() {
  cerr << "ERROR: Shape3D createBuffer() is called. It must be implemented in derived class." << '\n';
}

// ====== draw of object =======
void Shape3D::draw() {
  cerr << "ERROR: Shape3D draw() is called. It must be implemented in derived class." << '\n';
}
