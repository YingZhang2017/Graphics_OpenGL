/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * 09/24/2013 rdb
 *            Some code taken from Can Xiong 770 assignment Fall 2012
 */

#include <iostream>
#include "ControlPanel.h"
#include "Scene.h"

//#include <math.h>
using namespace std;

//------------------ Constructors ------------------------------------
/** Initialize any values, register callbacks
 */
Scene::Scene( GLuint shaderProg )
{
    resetView();
    drawAxes = true;
}
//-------------- resetView -----------------------------------------
/**
 *  restore the view to default settings
 */
void Scene::resetView()
{
    setLookat( 10, 3, 10, // eye
               0, 0, 0,   // at
               0, 1, 0 ); // up

    setPerspective( 10, 1.33, 0.1, 100.0 ); //should calc windowWid / windowHt
}

//--------------------------------------------------------------------
void Scene::addObject( Shape3D *newObject )
{
    objects.push_back( newObject );
}
//--------------------------------------------------------------------
void Scene::clear()
{
    objects.clear();
    redraw();
}

//---------------------------------------------------------------------
/**
 *  set lookat parameters
 */
void Scene::setLookat( float eyeX, float eyeY, float eyeZ,
                    float lookX, float lookY, float lookZ,
                    float upX, float upY, float upZ )
{
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    this->lookX = lookX;
    this->lookY = lookY;
    this->lookZ = lookZ;
    this->upX = upX;
    this->upY = upY;
    this->upZ = upZ;
}
//---------------------------------------------------------------------
/**
 *  set perspective parameters
 */
void Scene::setPerspective ( float angle, float ratio, float near, float far )
{
    this->viewAngle = angle;
    this->aspectRatio = ratio;
    this->near = near;
    this->far = far;
}

//---------------------------------------------------------------------
/**
 * This method assumes that the lighting specification has been established
 *   and that the Modelview and Projection matrices have been initialized.
 *   This assumption is based on the idea that the lights are independent
 *   of the scene.
 * It would be feasible to want the lights to be IN the scene.
 */
void Scene::redraw( void )
{
	glEnable( GL_DEPTH_TEST );
    glClearDepth( 1.0 );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    /////////////////////////////////////////////////////////////////////
    // The code below uses deprecated OpenGL functionality to specify
    // the viewing parameters and do the matrix multiplications.
    //
    //////////////////////////////////////////////////////////////////////
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // Only do perspective for now
    gluPerspective( viewAngle, aspectRatio, near, far );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt( eyeX, eyeY, eyeZ, 
              lookX, lookY, lookZ, 
              upX, upY, upZ );
    //////////////////////////////////////////////////////////////////////

    //-- now draw the shapes in the scene with the ModelView matrix containing
    //   the current transformation needed for current view and projection.
    std::vector<Shape3D*>::iterator it;
    for ( it = objects.begin(); it != objects.end(); it++ )
    {
    	( *it )->redraw();
    }
    glFlush();                         // send all output to display 
}
/**
 * Send the current Projection * ModelView to the shader programs.
 *
 * This is copied from Shape3D.
 * It should probably be part of a SceneManager class.
 */
void Scene::sendXformToShader( GLuint shaderProg,
		                              const char* uniformVar )
{
	//---- need to get Proj * ModelView matrix into the shader for
	//  transforming all vertices.
	//
	// Do that by getting the MV matrix and multiplying it in the
	//   Proj matrix stack (after pushing)
    
	float pXmv[ 16 ];
	glGetFloatv( GL_MODELVIEW_MATRIX, pXmv );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	{
		glMultMatrixf( pXmv );   // P = P*MV
		glGetFloatv( GL_PROJECTION_MATRIX, pXmv );
	}
	glPopMatrix();   // and clean up Proj matrix stack
    /**************
    std::cerr << "pXmv: ";
    for ( int i = 0; i < 16; i++ ) std::cerr << pXmv[ i ] << ", ";
    std::cerr << "\n";
    ******************************/

	glMatrixMode( GL_MODELVIEW ); // restore to MV mode

	//--- now push the composite into a uniform var in vertex shader
	int matLoc = glGetUniformLocation( shaderProg, uniformVar );
	glUniformMatrix4fv( matLoc, 1, false, pXmv );
}
//---------------- setDrawAxes( int )  -----------------------
/**
 *  0 means don't draw the axes
 * non-zero means draw them
 */
//-------------------------------------------
void Scene::setDrawAxes( int yesno )
{
    drawAxes = yesno;
}

// ----------------- retCurObjNum  -----------------
/**
 *  return current object num in the vectors in current scene
 */
int Scene::retCurObjNum(){
   return objects.size();	
}


// ----------------- retCurObj  -----------------
/**
 *  return current object in the vectors in current scene
 */
Shape3D* Scene::retCurObj( int i ){
	if(objects.size() > 0 && i < objects.size() )
		return objects[i];
	else 
		return nullptr;	
}


