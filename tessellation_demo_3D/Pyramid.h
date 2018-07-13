/* Pyramid.h - a class implementation representing
 *              a Pryamid object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #ifndef PYRAMID_H_
 #define PYRAMID_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class Pyramid: public Shape3D
 {
 public:
   Pyramid(string colorName);
   Pyramid(Color c);
   Pyramid(float r, float g, float b, float a = 1.0);
   virtual ~Pyramid();

   virtual void createBuffer();
   virtual void draw();
 };

 #endif
