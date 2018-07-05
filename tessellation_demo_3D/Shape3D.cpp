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
  R = mat4();
  S = mat4();
  T = mat4();
  modelMatrix = mat4();

  setLocation(0, 0, 0);
  setSize(1, 1, 1);
  setRotateX(0, 0);
  setRotateY(0, 0);
  setRotateZ(0, 0);
  color.set_DogerBlue();

  // vbo = new VBOInfo();

  // shaderProgram must be set before redraw object
  hasSetShader = false;
}

// ====== Destructor ==========
Shape3D::~Shape3D(){}

// ======= set shader program =====
void Shape3D::setShaderProgram(GLuint sp) {
  shaderProgram = sp;
  hasSetShader = true;
}

// ======= check shader program =====
void Shape3D::checkShaderProgram() {
  if (!hasSetShader) {
    cerr << "ERROR: shader program not set when redraw program\n";
    return;
  }
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

// ==========================
// ====== redraw method =====
void Shape3D::redrawObject() {
  // check shader program
  checkShaderProgram();
  // specify current matrix as model view matrix
  glMatrixMode(GL_MODELVIEW);
  // push and duplicate the the current matrix in matrix stack to make it on top
  glPushMatrix();
  // update the uniform veariables to the shader program
  sendUniformToShader();
  // redraw shader program
  redrawGLSL(); // this is a pure virtual function in Shape3D
  // specify current matrix as model view matrix
  glMatrixMode(GL_MODELVIEW);
  // pop the current matrix in stack
  glPopMatrix();
}



// ===== protected methods ==========
// ===== set uniform variables to shader program
void Shape3D::sendUniformToShader() {
    // get MVP matrix and send to shader proigram to do transformation
    // first get current modelMatrix
    float pXmv[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, pXmv);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMultMatrixf(pXmv);
    glGetFloatv( GL_PROJECTION_MATRIX, pXmv);
    glPopMatrix();

    mat4 tmpPxmv;
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        tmpPxmv[i][j] = pXmv[j*4+i];
      }
    }
    tmpPxmv = tmpPxmv * modelMatrix * T * R * S;

    for(int i = 0; i < 4; i++){
  		for(int j =0; j < 4; j++)
  			pXmv[j*4+i] = tmpPxmv[i][j];
  	}
    glMatrixMode( GL_MODELVIEW );

    int matLoc = glGetUniformLocation( shaderProgram, "MVPMatrix" );
  	glUniformMatrix4fv( matLoc, 1, false, pXmv );

    // later also need to get tessellation uniform to shaderr program to do tessellation
}


// ====== createVBO=====
// index: 0: verts, 1: colors
GLuint Shape3D::createVBO(float* coords, int size, int index)
{
    // set
    vbo.vboBytes = sizeof(coords);
    vbo.vboSize = size;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    // set in paramters in shaderProgram
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index , 4, GL_FLOAT, GL_FALSE,0, (GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );  // unbind this buffer
    return vbo;
}

// ====== redraw GLSL=====
void Shape3D::redrawGLSL() {
  cerr << "ERROR: Shape3D redrawGLSL() is called. It must be implemented in derived class." << '\n';
}
