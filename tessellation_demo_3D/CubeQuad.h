/* CubeQuad.h - a class implementation representing
 *              a Cube object draw by quad in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #ifndef CUBEQUAD_H_
 #define CUBEQUAD_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class CubeQuad: public Shape3D
 {
 public:
   CubeQuad(string colorName);
   CubeQuad(Color c);
   CubeQuad(float r, float g, float b, float a = 1.0);
   virtual ~CubeQuad();

   virtual void createBuffer();
   virtual void draw();
 };

 #endif
