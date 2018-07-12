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
  setRotate( 0, 0, 0, 1);
  color.set_DogerBlue();

  // init shader program point as NULL
  shaderProgram = NULL;
}

// ====== Destructor ==========
Shape3D::~Shape3D(){}

// get modelMatrix after transformed
mat4 Shape3D::getModelMatrix() {
  modelMatrix = T * R * S;
  return modelMatrix;
}

// ======= set shader program =====
void Shape3D::setShaderProgram(Shader* sp) {
  shaderProgram = sp;
}

// ======= send shader uniform ro bound shader ====
void Shape3D::sendUniformToShader() {
  // check shader program set or not;
  if (!shaderProgram) {
    cerr << "ERROR: Shape3D object not bind shader program and cannot send uniform vars\n";
    exit(EXIT_FAILURE);
  }
  shaderProgram->use();
  // send modelMatrix and object_color;
  shaderProgram->setMat4("modelMatrix", getModelMatrix());
  shaderProgram->setVec3("object_color", vec3(color.r, color.g, color.b));
}


void Shape3D::sendObjectCorlorToShader() {
  // check shader program set or not;
  if (!shaderProgram) {
    cerr << "ERROR: Shape3D object not bind shader program and cannot send uniform vars\n";
    exit(EXIT_FAILURE);
  }
  shaderProgram->use();
  shaderProgram->setVec3("object_color", vec3(color.r, color.g, color.b));
}

void Shape3D::sendModelMatrixToShader() {
  // check shader program set or not;
  if (!shaderProgram) {
    cerr << "ERROR: Shape3D object not bind shader program and cannot send uniform vars\n";
    exit(EXIT_FAILURE);
  }
  shaderProgram->use();
  shaderProgram->setMat4("modelMatrix", getModelMatrix());
}

// ======= set object location ========
void Shape3D::setLocation(float x, float y, float z) {
  xLoc = x;
  yLoc = y;
  zLoc = z;
  T = translate(mat4(1.0f), vec3(x, y, z));
}

// ======= set object size =======
void Shape3D::setSize(float x, float y, float z) {
  xSize = x;
  ySize = y;
  zSize = z;
  S = scale(mat4(1.0f), vec3(x, y, z));
}

// ==========  setRotate ==============
// set the rotation parameters: angle, and axis specification
void Shape3D::setRotate( float a, float dx, float dy, float dz )
{
    angle = a;
    dxRot = dx;
    dyRot = dy;
    dzRot = dz;

    R = rotate(R, a, vec3(dx, dy, dz));
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
