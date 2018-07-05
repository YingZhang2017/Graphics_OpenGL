/* Diamond.h - a class implementation representing
 *              a diamond object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #ifndef DIAMOND_H_
 #define DIAMOND_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class Diamond: class Shape3D
 {
 private:
   float colors[96]; // 8 triangle * 3 verts/tro * 4 cords/vert
 protected:
   virtual void redrawGLSL();
 public:
   Diamond();
   virtual ~Diamond();
   void setColor(Color c);
   void setColor(float r, float g, float b, float a = 1.0);
 };

 #endif
