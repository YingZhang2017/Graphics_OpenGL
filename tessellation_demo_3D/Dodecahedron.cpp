/* Dodecahedron.cpp - a class implementation representing
 *              a grest stellated Dodecahedron object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #include "Dodecahedron.h"

 // vertices
 int dnVertices = 72;  // 4 * 6 triangle = 24 triangles * 3 = 72
 float dverts [] = {
   // top
   0, 1, 0,      -0.5, 0.5, 0.5,      -0.5, 0.5, -0.5,
   0, 1, 0,      -0.5, 0.5, -0.5,      0.5, 0.5, -0.5,
   0, 1, 0,      0.5, 0.5, -0.5,       0.5, 0.5, 0.5,
   0, 1, 0,      0.5, 0.5, 0.5,        -0.5, 0.5, 0.5,
   // bottom
   0, -1, 0,      -0.5, -0.5, 0.5,      -0.5, -0.5, -0.5,
   0, -1, 0,      -0.5, -0.5, -0.5,      0.5, -0.5, -0.5,
   0, -1, 0,      0.5, -0.5, -0.5,       0.5, -0.5, 0.5,
   0, -1, 0,      0.5, -0.5, 0.5,        -0.5, -0.5, 0.5,
   // left
   -1, 0, 0,      -0.5, 0.5, 0.5,     -0.5, -0.5, 0.5,
   -1, 0, 0,      -0.5, -0.5, 0.5,    -0.5, -0.5, -0.5,
   -1, 0, 0,      -0.5, -0.5, -0.5,   -0.5, 0.5, -0.5,
   -1, 0, 0,      -0.5, 0.5, -0.5,    -0.5, 0.5, 0.5,
   // right
   1, 0, 0,      0.5, 0.5, 0.5,     0.5, 0.5, -0.5,
   1, 0, 0,      0.5, 0.5, -0.5,    0.5, -0.5, -0.5,
   1, 0, 0,      0.5, -0.5, -0.5,   0.5, -0.5, 0.5,
   1, 0, 0,      0.5, -0.5, 0.5,    0.5, 0.5, 0.5,

   // front
   0, 0, 1,      -0.5, 0.5, 0.5,    0.5, 0.5, 0.5,
   0, 0, 1,      0.5, 0.5, 0.5,     0.5, -0.5, 0.5,
   0, 0, 1,      0.5, -0.5, 0.5,    -0.5, -0.5, 0.5,
   0, 0, 1,      -0.5, -0.5, 0.5,   -0.5, 0.5, 0.5,

   // back
   0, 0, -1,      -0.5, 0.5, -0.5,    0.5, 0.5, -0.5,
   0, 0, -1,      0.5, 0.5, -0.5,     0.5, -0.5, -0.5,
   0, 0, -1,      0.5, -0.5, -0.5,    -0.5, -0.5, -0.5,
   0, 0, -1,      -0.5, -0.5, -0.5,   -0.5, 0.5, -0.5
 };

 float dnormals [] = {
   0.5, -0.5, 0,    0.5, -0.5, 0,     0.5, -0.5, 0,
   0, -0.5, 0.5,    0, -0.5, 0.5,     0, -0.5, 0.5,
   -0.5, -0.5, 0,   -0.5, -0.5, 0,    -0.5, -0.5, 0,
   0, -0.5, -0.5,   0, -0.5, -0.5,    0, -0.5, -0.5,

   -0.5, -0.5, 0,   -0.5, -0.5, 0,    -0.5, -0.5, 0,
   0, -0.5, -0.5,   0, -0.5, -0.5,    0, -0.5, -0.5,
   0.5, -0.5, 0,    0.5, -0.5, 0,      0.5, -0.5, 0,
   0, -0.5, 0.5,    0, -0.5, 0.5,    0, -0.5, 0.5,

   0.5, 0, -0.5,    0.5, 0, -0.5,    0.5, 0, -0.5,
   0.5, 0.5, 0,    0.5, 0.5, 0,    0.5, 0.5, 0,
   0.5, 0, 0.5,    0.5, 0, 0.5,    0.5, 0, 0.5,
   0.5, -0.5, 0,    0.5, -0.5, 0,    0.5, -0.5, 0,

   -0.5, -0.5, 0,    -0.5, -0.5, 0,    -0.5, -0.5, 0,
   -0.5, 0, 0.5,    -0.5, 0, 0.5,    -0.5, 0, 0.5,
   -0.5, 0.5, 0,    -0.5, 0.5, 0,    -0.5, 0.5, 0,
   -0.5, 0, -0.5,    -0.5, 0, -0.5,    -0.5, 0, -0.5,

   0, -0.5, -0.5,    0, -0.5, -0.5,    0, -0.5, -0.5,
   -0.5, 0, -0.5,    -0.5, 0, -0.5,    -0.5, 0, -0.5,
   0, 0.5, -0.5,    0, 0.5, -0.5,    0, 0.5, -0.5,
   0.5, 0, -0.5,    0.5, 0, -0.5,    0.5, 0, -0.5,

   0, 0.5, -0.5,    0, 0.5, -0.5,    0, 0.5, -0.5,
   0.5, 0, -0.5,    0.5, 0, -0.5,    0.5, 0, -0.5,
   0, -0.5, -0.5,    0, -0.5, -0.5,    0, -0.5, -0.5,
   -0.5, 0, -0.5,    -0.5, 0, -0.5,    -0.5, 0, -0.5
  };

vec3 get_Normal(vec3 p1,vec3 p2,vec3 p3) {

      float a = ( (p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y) );

      float b = ( (p2.z-p1.z)*(p3.x-p1.x)-(p2.x-p1.x)*(p3.z-p1.z) );

      float c = ( (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x) );

      return vec3(a,b,c);

  }


 // ==== Constructor ====
 Dodecahedron::Dodecahedron(string colorName) {
   setColor(colorName);

   // create buffer
   createBuffer();
 }

 Dodecahedron::Dodecahedron(Color c) {
   color = c;
   // create buffer
   createBuffer();
 }

 Dodecahedron::Dodecahedron(float r, float g, float b, float a) {
   color.set(r, g, b, a);
   // create buffer
   createBuffer();
 }

 // ==== Destructor =====
 Dodecahedron::~Dodecahedron(){
 }

 // ====== create buffer =======
 void Dodecahedron::createBuffer() {
    // vbo for pverts
    glGenBuffers(1, &vboId_vert);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_vert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dverts), dverts, GL_STATIC_DRAW);

    // vbo for normal
    glGenBuffers(1, &vboId_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dnormals), dnormals, GL_STATIC_DRAW);

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
 void Dodecahedron::draw() {
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
   glDrawArrays(GL_PATCHES, 0, dnVertices);
 }
