/* CubeQuad.cpp - a class implementation representing
 *              a Cube object draw by quad in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #include "CubeQuad.h"

 // vertices
 float a = 0.5;
 int cqVertices = 36;
 float cqVerts [] = {
   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,

   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f

/*
      // top
      -a, a, a,
      -a, a, -a,
      a, a, -a,
      a, a, a,

      // right
      a, a, a,
      a, a, -a,
      a, -a, -a,
      a, -a, a,

      // back
      -a, a, -a,
      a, a, -a,
      a, -a, -a,
      -a, -a, -a,

      // left
      -a, a, a,
      -a, a, -a,
      -a, -a, -a,
      -a, -a, a,

      // bottom
      -a, -a, a,
      -a, -a, -a,
      a, -a, -a,
      a, -a, a,

      //front
      -a, a, a,
      a, a, a,
      a, -a, a,
      -a, -a, a
      */

 };

 float cqNormals [] = {

   0.0f,  0.0f, -1.0f,
   0.0f,  0.0f, -1.0f,
   0.0f,  0.0f, -1.0f,
   0.0f,  0.0f, -1.0f,
   0.0f,  0.0f, -1.0f,
   0.0f,  0.0f, -1.0f,

   0.0f,  0.0f,  1.0f,
   0.0f,  0.0f,  1.0f,
   0.0f,  0.0f,  1.0f,
   0.0f,  0.0f,  1.0f,
   0.0f,  0.0f,  1.0f,
   0.0f,  0.0f,  1.0f,

  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,

   1.0f,  0.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   1.0f,  0.0f,  0.0f,

   0.0f, -1.0f,  0.0f,
   0.0f, -1.0f,  0.0f,
   0.0f, -1.0f,  0.0f,
   0.0f, -1.0f,  0.0f,
   0.0f, -1.0f,  0.0f,
   0.0f, -1.0f,  0.0f,

   0.0f,  1.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  1.0f,  0.0f
/*
        // top
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        // right
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,

        //back
        0, 0, -1,
        0, 0, -1,
        0, 0, -1,
        0, 0, -1,

        // left
        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,

        //bottom
        0, -1, 0,
        0, -1, 0,
        0, -1, 0,
        0, -1, 0,

        // front
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
*/
  };

 // ==== Constructor ====
 CubeQuad::CubeQuad(string colorName) {
   setColor(colorName);

   // create buffer
   createBuffer();
 }

 CubeQuad::CubeQuad(Color c) {
   color = c;
   // create buffer
   createBuffer();
 }

 CubeQuad::CubeQuad(float r, float g, float b, float a) {
   color.set(r, g, b, a);
   // create buffer
   createBuffer();
 }

 // ==== Destructor =====
 CubeQuad::~CubeQuad(){
 }

 // ====== create buffer =======
 void CubeQuad::createBuffer() {
    // vbo for cqVerts
    glGenBuffers(1, &vboId_vert);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_vert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cqVerts), cqVerts, GL_STATIC_DRAW);

    // vbo for normal
    glGenBuffers(1, &vboId_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cqNormals), cqNormals, GL_STATIC_DRAW);

    // vao
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId_vert);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboId_normal);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
 }


 // ==== draw object ======
 void CubeQuad::draw() {
   // init mode
   if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glPatchParameteri (GL_PATCH_VERTICES, 4);

   // use shader program
   shaderProgram->use();
   // send modelmatrix and object color to shaderProgram
   sendUniformToShader();
   // bind vao
   glBindVertexArray(vaoId);
   // draw as tessellation patch
   glDrawArrays(GL_PATCHES, 0, cqVertices);
 }
