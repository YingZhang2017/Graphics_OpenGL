/* Sphere.cpp - a class implementation representing
 *              a Sphere object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #include "Sphere.h"

 // vertices
 const int faces[] = {
        2, 1, 0,
        3, 2, 0,
        4, 3, 0,
        5, 4, 0,
        1, 5, 0,

        11, 6,  7,
        11, 7,  8,
        11, 8,  9,
        11, 9,  10,
        11, 10, 6,

        1, 2, 6,
        2, 3, 7,
        3, 4, 8,
        4, 5, 9,
        5, 1, 10,

        2,  7, 6,
        3,  8, 7,
        4,  9, 8,
        5, 10, 9,
        1, 6, 10 };

const float verts[] = {
        0.000f,  0.000f,  1.000f,
        0.894f,  0.000f,  0.447f,
        0.276f,  0.851f,  0.447f,
       -0.724f,  0.526f,  0.447f,
       -0.724f, -0.526f,  0.447f,
        0.276f, -0.851f,  0.447f,
        0.724f,  0.526f, -0.447f,
       -0.276f,  0.851f, -0.447f,
        -0.894f,  0.000f, -0.447f,
       -0.276f, -0.851f, -0.447f,
        0.724f, -0.526f, -0.447f,
        0.000f,  0.000f, -1.000f };
 int idxCount = sizeof(faces) / sizeof(faces[0]);
 // ==== Constructor ====
 Sphere::Sphere(string colorName) {
   setColor(colorName);

   // create buffer
   createBuffer();
 }

 Sphere::Sphere(Color c) {
   color = c;
   // create buffer
   createBuffer();
 }

 Sphere::Sphere(float r, float g, float b, float a) {
   color.set(r, g, b, a);
   // create buffer
   createBuffer();
 }

 // ==== Destructor =====
 Sphere::~Sphere(){
 }

 // ====== create buffer =======
 void Sphere::createBuffer() {
   // vao
   glGenVertexArrays(1, &vaoId);
   glBindVertexArray(vaoId);

    // vbo for verts
    glGenBuffers(1, &vboId_vert);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_vert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // vbo for indices
    glGenBuffers(1, &vboId_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
 }


 // ==== draw object ======
 void Sphere::draw() {
   glPatchParameteri (GL_PATCH_VERTICES, 3);
   // use shader program
   shaderProgram->use();
   // send modelmatrix and object color to shaderProgram
   sendUniformToShader();
   // bind vao
   glBindVertexArray(vaoId);
   // draw as tessellation patch
   glDrawElements(GL_PATCHES, idxCount, GL_UNSIGNED_INT, 0);
 }
