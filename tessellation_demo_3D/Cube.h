/* Cube.h - a class implementation representing
 *              a Cube object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #ifndef CUBE_H_
 #define CUBE_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class Cube: public Shape3D
 {
 public:
   Cube(string colorName);
   Cube(Color c);
   Cube(float r, float g, float b, float a = 1.0);
   virtual ~Cube();

   virtual void createBuffer();
   virtual void draw();
 };

 #endif
