/* Diamond.h - a class implementation representing
 *              a diamond object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #include "Diamond.h"

 // vertices
 int nVertices = 24;  // 8 triangles * 3
 float verts =
 {
   // top 4 triangles
   0, 0.5, 0, 1,   0, 0, -0.5, 1,    0.5, 0, 0,  1,
   0, 0.5, 0, 1,   0.5, 0, 0,  1,    0, 0, -0,5, 1,
   0, 0.5, 0, 1,   0, 0, -0,5, 1,    -0,5, 0, 0, 1,
   0, 0.5, 0, 1,   -0,5, 0, 0, 1,    0, 0, -0.5, 1,
   // bottom 4 triangles
   0, -0.5, 0, 1,   0, 0, -0.5, 1,   0.5, 0, 0,  1,
   0, -0.5, 0, 1,   0.5, 0, 0,  1,   0, 0, -0,5, 1,
   0, -0.5, 0, 1,   0, 0, -0,5, 1,   -0,5, 0, 0, 1,
   0, -0.5, 0, 1,   -0,5, 0, 0, 1,   0, 0, -0.5, 1
 };

 int nBytes  = sizeof(verts);
 int nFloats = nBytes / sizeof(float);
 int nCoords   = nFloats / 4; // 4 coordinates per vertex (and color)

 // ==== Constructor ====
 Diamond::Diamond() {
   // init colors[]
   for (int i = 0; i < nCoords)

 }

 // ==== Destructor =====
 Diamond::~Diamond(){
 }

 // ==== redrawGLSL ======
 void Diamond::redrawGLSL() {


 }
 // ==== set color =======
 void Diamond::setColor(Color c) {
   Shape3D::setColor(c);
   // bind vert color array

 }


 void Diamond::setColor(float r, float g, float b, float a){
   Shape3D::setColor(r, g, b, a);
   // bind vert color array
 }
