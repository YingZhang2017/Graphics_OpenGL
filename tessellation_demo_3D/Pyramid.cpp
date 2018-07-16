/* Pyramid.cpp - a class implementation representing
 *              a Pyramid object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #include "Pyramid.h"

 // vertices

 int pnVertices = 18;  // 6 triangles * 3
 float pverts [] = {
    // front face:
    0.0f, 0.0f, 0.5f,
    0.0f, 0.5f, 0.0f,
    0.5f, 0.0f, 0.0f,

    // left face:
    -0.5f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.0f, 0.5f,

    // back face:
    -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, -0.5f,
    0.0f, 0.5f, 0.0f,

    // right face :
    0.5f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.0f, -0.5f,

    // bottom face:  lbf, rbn, lbn
    -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f,  0.5f,
    0.5f, 0.0f,  0.0f,

    // bottom face: lbf, rbf, rbn
    0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, -0.5f,
    -0.5f, 0.0f, 0.0f
 };
 float pnormals [] = {

        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, -0.25f,
        0.25f, -0.25f, -0.25f,
        0.25f, -0.25f, -0.25f,

        0.25f, -0.25f, 0.25f,
        0.25f, -0.25f, 0.25f,
        0.25f, -0.25f, 0.25f,

        -0.25f, -0.25f, 0.25f,
        -0.25f, -0.25f, 0.25f,
        -0.25f, -0.25f, 0.25f,

        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f

  };

 // ==== Constructor ====
 Pyramid::Pyramid(string colorName) {
   setColor(colorName);
   // create buffer
   createBuffer();
 }

 Pyramid::Pyramid(Color c) {
   color = c;
   // create buffer
   createBuffer();
 }

 Pyramid::Pyramid(float r, float g, float b, float a) {
   color.set(r, g, b, a);
   // create buffer
   createBuffer();
 }

 // ==== Destructor =====
 Pyramid::~Pyramid(){
 }

 // ====== create buffer =======
 void Pyramid::createBuffer() {
    // vbo for pverts
    glGenBuffers(1, &vboId_vert);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_vert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pverts), pverts, GL_STATIC_DRAW);

    // vbo for normal
    glGenBuffers(1, &vboId_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pnormals), pnormals, GL_STATIC_DRAW);

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
 void Pyramid::draw() {
   // init mode
   if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glPatchParameteri (GL_PATCH_VERTICES, 3);

   // use shader program
   shaderProgram->use();
   // send modelmatrix and object color to shaderProgram
   sendUniformToShader();
   // bind vao
   glBindVertexArray(vaoId);
   // draw as tessellation patch
   // glDrawArrays(GL_TRIANGLES, 0, pnVertices);
   glDrawArrays(GL_PATCHES, 0, pnVertices);
 }
