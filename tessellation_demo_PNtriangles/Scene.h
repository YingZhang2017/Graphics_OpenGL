/**
 * Scene.h - a class represent a scene: its objects and its view
 * 
 * 09/24/2013 rdb
 *            Some code taken from Can Xiong 770 assignment Fall 2012
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>
#include "Shape3D.h"

class Scene 
{
public:
    Scene( GLuint shaderProgram );

    void addObject( Shape3D* object );
    void clear();

    void resetView();
    
    void setLookat( float eyeX, float eyeY, float eyeZ,
                    float lookX, float lookY, float lookZ,
                    float upX, float upY, float upZ );
    void setPerspective( float angle, float ratio, float near, float far );

    void setDrawAxes( int yesno );
    void drawCoordinateAxes( void );
    void redraw( void );
    static void sendXformToShader( GLuint prgrm, const char* unifVar );

    // return current objects in the vectors in current scene;
    Shape3D* retCurObj( int );
    // return current object number in the vectors in current scene;
    int retCurObjNum();

protected:
    //---- objects collection -------
    std::vector<Shape3D*> objects;

    //----gluLookat parameters -------
    float eyeX, eyeY, eyeZ; // gluLookat eye position
    float lookX, lookY, lookZ; // gluLookat look position
    float upX, upY, upZ; // up vector

    //----gluPerspective parameters ----
    float viewAngle, aspectRatio, near, far; 

    //---- draw Axes data ------------------------
    bool   drawAxes;
};

#endif /*SCENE_H_*/
