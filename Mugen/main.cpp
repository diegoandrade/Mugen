
// ----------------------------------------------------------------------------
/**
 File: main.cpp
 
 System:         YUI
 Component Name: Carnegie Mellon University
 Status:         Version 1.0 Release 1
 Language: C++
 
 License: GNU Public License
 Licensed Material - Property of CERLAB (Carnegie Mellon Univerisity)
 
 (c) Copyright Carnegie Mellon Univerisity 2012
 
 Address:
 Carnegie Mellon University
 5000 Forbes Avenue Pittsburgh, PA 15213
 
 Author: Diego F Andrade
 E-Mail: diegoandrade@gmail.com
 
 Description: Header file for Project X
 Bubblepacking For Aesthetic Design in Manufacturing
 
 This file contains the defined types for Project X
 This is sometimes called the "Abstract" and may be
 followed by a section called "Notes".
 
 Limitations: bla bla bla
 
 Function:
 1) bla bla bla
 2) bla bla bla
 3) bla bla bla
 
 Thread Safe: No
 
 Extendable: No
 
 Platform Dependencies: OSX
 
 Compiler Options: No
 
 */
// ----------------------------------------------------------------------------

//
//  main.cpp
//  Yui
//
//  Created by Diego Andrade on 6/13/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//


#undef DEBUG
//define DEBUG

#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


#include <stdio.h>



//Includes for system classes
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include "AllColor.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Includes for costume classes
#include "Common.h"
#include "trackball.h"


//GEOMETRY CLASSES
#include "ReadSRF.h"
#include "VectorRepresentationOGL.h"

//Picking obejct class
#include "PickingObject.h"

/*
 Costume #define pre-processor directives
 */

#define DTOR 0.017453925
#define CROSSPROD(p1,p2,p3) \
p3.x = p1.y*p2.z - p1.z*p2.y; \
p3.y = p1.z*p2.x - p1.x*p2.z; \
p3.z = p1.x*p2.y - p1.y*p2.x


#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define HEIGHT 666
#define WIDTH 999

/*
 Open Gl Variables
 */
GLint gDollyPanStartPoint[2] = {0, 0};
//static GLint snowman_display_list;

GLuint gPointList = NULL;
GLuint gWireList = NULL;
GLuint gSolidList = NULL;

GLfloat gfDeltaX = .01;
GLfloat gfPosX = 0.0;
GLfloat gShapeSize = 11.0f;
GLfloat gTrackBallRotation [4] = {0.0, 0.0, 0.0, 0.0};
GLfloat gWorldRotation [4] = {180, 0.0, 1.0, 0.0}; //{155.0, 0.0, -1.0, 0.0};

GLboolean gDolly = GL_FALSE;
GLboolean gPan = GL_FALSE;

GLboolean gShowHelp = GL_TRUE;
GLboolean gShowInfo = GL_TRUE;
GLboolean gShowSplineControlPoints = GL_TRUE;
GLboolean gTrackBall = GL_FALSE;

GLboolean gDrawNumberOnVertex = GL_FALSE;
GLboolean gDrawTriangles = GL_FALSE;
GLboolean gDrawPoints = GL_FALSE;
GLboolean gDrawBoundary = GL_FALSE;
GLboolean gInit = GL_FALSE;

static GLboolean WIRE=0;		// draw mesh in wireframe?

int gLastKey = ' ';
int gMainWindow = 0;

float a=HEIGHT;
float b=WIDTH;

GLboolean isInsideTriangle = GL_TRUE;
bool wasTheVertexFound = false;

int ii = 0;
int idForTriangle = 0;
int idForClosestVertex = 0;

int mx,my; // variable to hold mouse location

/*
 Costume Structures
 */
typedef struct {
    GLdouble x,y,z;
} recVec;

typedef struct {
    recVec viewPos; // View position
    recVec viewDir; // View direction vector
    recVec viewUp; // View up direction
    recVec rotPoint; // Point to rotate about
    GLdouble focalLength; // Focal Length along view direction
    GLdouble aperture; // gCamera aperture
    GLdouble eyeSep; // Eye separation
    GLint screenWidth,screenHeight; // current window/screen height and width
} recCamera;


recCamera gCamera;
recVec gOrigin = {0.0, 0.0, 0.0};



#pragma mark ---- User's Objects ----
ReadSRF objReadSRF;
VectorRepresentationOGL objVRep; //Vectors used for NRoSy representation
PickingObject objPicking;

//used for picking
Vector3D org;
Vector3D vec;

// Menu items
enum MENU_TYPE
{
    MENU_FRONT,
    MENU_SPOT,
    MENU_BACK,
    MENU_BACK_FRONT,
};

// Assign a default value
MENU_TYPE show = MENU_BACK_FRONT;

// Menu handling function declaration
void menu(int);


#pragma mark ---- gCamera control ----


// ----------------------------------------------------------------------------
/**
 Routine: gCameraReset()
 Inputs: none
 Arguments: void
 Externals: gCamera struct
 Others: none
 
 Outputs: gCamera struct
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 **/
// ----------------------------------------------------------------------------
void gCameraReset(void)
{
    gCamera.aperture = 25;
    gCamera.focalLength = 50; //THIS IS THE DEFAULT ZOOM
    gCamera.rotPoint = gOrigin;
    
    gCamera.viewPos.x = 0.0;
    gCamera.viewPos.y = 0.0;
    gCamera.viewPos.z = -gCamera.focalLength;
    
    gCamera.viewDir.x = -gCamera.viewPos.x;
    gCamera.viewDir.y = -gCamera.viewPos.y;
    gCamera.viewDir.z = -gCamera.viewPos.z;
    
    gCamera.viewUp.x = 0;
    gCamera.viewUp.y = 1;
    gCamera.viewUp.z = 0;
}



#pragma mark ---- Geometries  ----

// ----------------------------------------------------------------------------
/**
 Routine: drawBubble()
 Inputs: none
 Arguments: none
 Externals:none
 Others: none
 
 Outputs: gCamera struct
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void drawBubble ()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_POLYGON);
    glColor3f(   0.2,  0.39812096,  .0918263 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
    
    
    glBegin(GL_LINES);
    glColor3f(   0.23,  1.0,  0.23 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(   0.23,  1.0,  0.23 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glEnd();
    glBegin(GL_LINES);
    glColor3f(   0.23,  1.0,  0.23 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
    glBegin(GL_LINES);
    glColor3f(   0.23,  1.0,  0.23 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glEnd();
    
    
}


#pragma mark ---- Utilities ----

// ----------------------------------------------------------------------------
/**
 Routine: drawGLString()
 Inputs: GLfloat x, GLfloat y, char* string
 Arguments: none
 Externals: glRasterPos2f(x, y), glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i])
 Others: strlen(len)
 
 Outputs:
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void
drawGLString(GLfloat x, GLfloat y, char *string)
{
    int len, i;
    
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
    }
}


#pragma mark ---- Drawing ----


void SetLighting(unsigned int mode)
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {90.0};
    
    GLfloat position[4] = {7.0,-7.0,12.0,0.0};
    GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
    GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
    GLfloat specular[4] = {1.0,1.0,1.0,1.0};
    
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    
    switch (mode) {
        case 0:
            break;
        case 1:
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
            break;
        case 2:
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            break;
        case 3:
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
            break;
        case 4:
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
            break;
    }
    
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glEnable(GL_LIGHT0);
}

// ----------------------------------------------------------------------------
/**
 Routine: drawGLText ()
 Inputs: GLint window_width, GLint window_height
 Arguments: none
 Externals: drawGLString()
 Others:
 
 Outputs:
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void drawGLText (GLint window_width, GLint window_height)
{
    char outString [256] = "";
    GLint matrixMode;
    GLint vp[4];
    GLint lineSpacing = 13;
    GLint line = 0;
    GLint startOffest = 7;
    
    glGetIntegerv(GL_VIEWPORT, vp);
    glViewport(0, 0, window_width, window_height);
    
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(2.0f / window_width, -2.0f / window_height, 1.0f);
    glTranslatef(-window_width / 2.0f, -window_height / 2.0f, 0.0f);
    
    int temp3 = NUMBER_OF_BUBBLES_IN_SIMULATION - NUMBER_OF_BUBBLES_L0 - NUMBER_OF_BUBBLES_L1 - NUMBER_OF_BUBBLES_L2 - NUMBER_OF_BUBBLES_L3 -3; //MAL
    
    // draw
    glDisable(GL_LIGHTING);
    glColor3f (1.0, 1.0, 1.0);
    if (gShowInfo) {
        
        sprintf (outString, "Camera Position: (%0.1f, %0.1f, %0.1f)", gCamera.viewPos.x, gCamera.viewPos.y, gCamera.viewPos.z);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        sprintf (outString, "Trackball Rotation: (%0.1f, %0.2f, %0.2f, %0.2f)", gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        sprintf (outString, "World Rotation: (%0.1f, %0.2f, %0.2f, %0.2f)", gWorldRotation[0], gWorldRotation[1], gWorldRotation[2], gWorldRotation[3]);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        sprintf (outString, "Aperture: %0.1f", gCamera.aperture);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        sprintf (outString, "Focus Distance: %0.1f", gCamera.focalLength);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Number in the surface: %0.1d",temp3);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Max Number of Iterations for Runge Kutta: %0.1d", NUM_ITERATIONS);
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Carnegie Mellon University 2015 : Diego Andrade");
        drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        
        
    }
    
    if (gShowHelp) {
        line = 1;
        sprintf (outString, "Controls:\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "left button drag: rotate camera\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "right (or crtl-left) button drag: dolly (zoom) camera\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "arrows: aperture & focal length\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "H: toggle help\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "I: toggle info\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "W: toggle wire frame\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "R: rungge kutta simulation\n");
        drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(matrixMode);
    
    glViewport(vp[0], vp[1], vp[2], vp[3]);
}

#pragma mark ---- GLUT callbacks ----


// ----------------------------------------------------------------------------
/**
 Routine: init()
 Inputs: bubble * l0, float newradius, int numBubbles
 Arguments: none
 Externals: objBB.createPoints() , objMainBSPline.InitializeControlPoints() ,
 subdivisionHardCode() , findBoundariesLengths() , MatPointInitial(),
 objBP2D.bubbleBoundaries() ,  VectPointInitial();
 
 Others:
 
 Outputs:  many
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function initializes all the properties and the needed data for the YUI
 to work needs to be run before any other.
 */
// ----------------------------------------------------------------------------



void init (void)
{
    glEnable(GL_DEPTH_TEST);
    
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CCW);
    
    glColor3f(1.0,1.0,1.0);
    
    
    glClearColor(0.0,0.0,0.0,0.0);         /* Background recColor */
    
    
    if (!gInit)
    {
        objReadSRF.ReadSRFFile("hola");
    
        //int* temp = objReadSRF.getVerticesConnectedTo(27, objReadSRF.VertexLocation);
        //objReadSRF.getVerticesConnectedInOrder(temp);
    
        /*const char* myFile = "/Users/diegoandrade/Documents/Mugen/Mugen/data/sq3.rosy";
        objVRep.getVectors(myFile);*/
        
        gInit =!gInit;
    }
    
    

    
    gCameraReset ();
    
    
  
    
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    
  
    
    
    glPolygonOffset (1.0, 1.0);
    SetLighting(1); //Lighting function
    
    glEnable(GL_LIGHTING);

    
    
    
}

void reshape (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    gCamera.screenWidth = w;
    gCamera.screenHeight = h;
    glutPostRedisplay();
    
}


Vector3D GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    
    return Vector3D (posX, posY, posZ);
}

#pragma mark <F> main display function

//FTOIO :  function to be on its owned
void outputTexto(double x, double y, double z, char *string)
{
    glColor3fv(Green2);
    glRasterPos3f(x, y, z);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
}

//FTOIO :  function to be on its owned
void trianglesInFile(int id1, int id2, int id3, VerticesOutput* vertex )
{
        glLineWidth(1.0);
   // glColor3fv(Ivory4);
    glBegin( GL_TRIANGLES ); // Draw a triangle
    glColor4f(1.0, 1.0, 0.0, 0.6);
    glVertex3f(  vertex[id1].x,  vertex[id1].y,  vertex[id1].z );
    glVertex3f(  vertex[id2].x,  vertex[id2].y,  vertex[id2].z );
    glVertex3f(  vertex[id3].x,  vertex[id3].y,  vertex[id3].z );
    glEnd();
    
    glLineWidth(2.0);
    glColor3fv(DarkOrchid);
    glBegin( GL_LINES); // Draw a triangle
    glVertex3f(  vertex[id1].x,  vertex[id1].y,  vertex[id1].z );
    glVertex3f(  vertex[id2].x,  vertex[id2].y,  vertex[id2].z );
    glEnd();
    
    glBegin( GL_LINES);
    glVertex3f(  vertex[id2].x,  vertex[id2].y,  vertex[id2].z );
    glVertex3f(  vertex[id3].x,  vertex[id3].y,  vertex[id3].z );
    glEnd();
    
    glBegin( GL_LINES);
    glVertex3f(  vertex[id3].x,  vertex[id3].y,  vertex[id3].z );
    glVertex3f(  vertex[id1].x,  vertex[id1].y,  vertex[id1].z );
    glEnd();
    
    char buffer [100];
    
    if (gDrawNumberOnVertex) {
    
    sprintf(buffer, "%d", id1);
    outputTexto(vertex[id1].x, vertex[id1].y, vertex[id1].z, buffer);
    
    sprintf(buffer, "%d", id2);
    outputTexto(vertex[id2].x, vertex[id2].y, vertex[id2].z, buffer);
    
    sprintf(buffer, "%d", id3);
        outputTexto(vertex[id3].x, vertex[id3].y, vertex[id3].z, buffer);
        
    }
    
}

//FTOIO :  function to be on its owned
//void perimtrLines(int id1, int id2, int id3, VerticesOutput* vertex )
void DrawNRoSyField(int idx, VerticesOutput* vertex, VerticesOutput* unitVec)
{
    glLineWidth(3.0);
    glColor3fv(Cornsilk2);
    glBegin( GL_LINES ); // Draw a triangle
    glVertex3f(  vertex[idx].x,   vertex[idx].y,   vertex[idx].z );
    glVertex3f(  vertex[idx].x-unitVec[idx].x,  vertex[idx].y-unitVec[idx].y,  vertex[idx].z-unitVec[idx].z );
    glEnd();

}

void maindisplay(void)
{
    GLdouble xmin, xmax, ymin, ymax;
    // far frustum plane
    GLdouble zFar = 100 ; //-gCamera.viewPos.z + gShapeSize * 0.5;
    // near frustum plane clamped at 1.0
    GLdouble zNear = MIN (-gCamera.viewPos.z - gShapeSize * 0.5, 1.0);
    // window aspect ratio
    GLdouble aspect = gCamera.screenWidth / (GLdouble)gCamera.screenHeight;
    
    glEnable(GL_LIGHTING); //not really used just put here to remind me to use it... CHANGE
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    
    //char file[] = "/Users/Serenity/Dropbox/CMU 2012/export_coor.txt";
    

    
   
    
    if (aspect > 1.0) {
        ymax = zNear * tan (gCamera.aperture * 0.5 * DTOR);
        ymin = -ymax;
        xmin = ymin * aspect;
        xmax = ymax * aspect;
    } else {
        xmax = zNear * tan (gCamera.aperture * 0.5 * DTOR);
        xmin = -xmax;
        ymin = xmin / aspect;
        ymax = xmax / aspect;
    }
        
    
    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar); // changes the projection to perpective
    
    
    gluLookAt (gCamera.viewPos.x, gCamera.viewPos.y, gCamera.viewPos.z,
               gCamera.viewPos.x + gCamera.viewDir.x,
               gCamera.viewPos.y + gCamera.viewDir.y,
               gCamera.viewPos.z + gCamera.viewDir.z,
               gCamera.viewUp.x, gCamera.viewUp.y ,gCamera.viewUp.z);
    
    // track ball rotation
    glRotatef (gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
    glRotatef (gWorldRotation[0], gWorldRotation[1], gWorldRotation[2], gWorldRotation[3]);
    
    glTranslatef(-1.0, 0.0, -1.0); // this translations is done after a world rotation so we are looking at x-z and then translation
    
    glClearColor (0.2f, 0.2f, 0.4f, 1.0f);	// clear the surface
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawGLText (gCamera.screenWidth, gCamera.screenHeight);
    
    glColor3fv(LightGoldenrod1);
    
    glPointSize(4.0);
    
    if(gDrawPoints)
    {
        glBegin( GL_POINTS );
        glColor3f( 0.95f, 0.207, 0.031f );
        for ( int i = 0; i < objReadSRF.numberOfVerticesInFile; i++ )
        {
            glVertex3f( objReadSRF.VertexLocation[i].x, objReadSRF.VertexLocation[i].y, objReadSRF.VertexLocation[i].z);
            //cout << objReadSRF.VertexLocation[i].x << "\n";
        }
        glEnd();
    }
    
   
    if(gDrawTriangles)
    {
        for ( int i = 0; i < objReadSRF.numberOfFacesInFile; i++ )
        {
            trianglesInFile(objReadSRF.VertexLocation[i].id0,
                            objReadSRF.VertexLocation[i].id1,
                            objReadSRF.VertexLocation[i].id2,
                            objReadSRF.VertexLocation);
            
        }
    }
    
    if(gDrawBoundary)
    {
        for (int i=0;i<objReadSRF.boundarySize-1; i++)
        {
            glLineWidth(5.0);
            glColor3fv(Black);
            glBegin( GL_LINES); // Draw a triangle
            glVertex3f(  objReadSRF.VertexLocation[objReadSRF.boundary[i]].x,
                       objReadSRF.VertexLocation[objReadSRF.boundary[i]].y,
                       objReadSRF.VertexLocation[objReadSRF.boundary[i]].z);
            
            glVertex3f(  objReadSRF.VertexLocation[objReadSRF.boundary[i+1]].x,
                       objReadSRF.VertexLocation[objReadSRF.boundary[i+1]].y,
                       objReadSRF.VertexLocation[objReadSRF.boundary[i+1]].z);
            glEnd();
            
        }
    }
     /*
    
   for ( int i = 0; i < objReadSRF.numberOfVerticesInFile; i++ )
    {
        DrawNRoSyField(i, objReadSRF.VertexLocation, objVRep.objNRoSyVer);
    }*/
    
    //Test to see if a point is inside a triangle
    
    Vector3D A (objReadSRF.VertexLocation[2].x, objReadSRF.VertexLocation[2].y, objReadSRF.VertexLocation[2].z);
    Vector3D B (objReadSRF.VertexLocation[4].x, objReadSRF.VertexLocation[4].y, objReadSRF.VertexLocation[4].z);
    Vector3D C (objReadSRF.VertexLocation[39].x, objReadSRF.VertexLocation[39].y, objReadSRF.VertexLocation[39].z);
    Vector3D P ((A.x1+B.x1+C.x1)/3,(A.y1+B.y1+C.y1)/3, (A.z1+B.z1+C.z1)/3);
    //Vector3D P (,(A.y+B.y+C.y)/3, (A.z+B.z+C.z)/3);
    
    //int idxForVertexSelected;

    // Replace with pick function to select the point from the mouse to the surface
    if (isInsideTriangle == GL_TRUE)
    {
        
        D(cout << "Triangle Idx 2, 4, 39" <<'\n');
        D(cout << "P x: " << P.x << " y: " << P.y << " z: " << P.z <<'\n');
        D(cout << "A x: " << A.x << " y: " << A.y << " z: " << A.z <<'\n');
        D(cout << "B x: " << B.x << " y: " << B.y << " z: " << B.z <<'\n');
        D(cout << "C x: " << C.x << " y: " << C.y << " z: " << C.z <<'\n');
        
        glPointSize(6);
        glBegin( GL_POINTS );
        glColor3f( 1.0f, 0.207, 0.41f );
        glVertex3f( P.x1, P.y1, P.z1);
        glEnd();
        
      
       // bool isInThisTriangle = objPicking.isInThisTriangle(A, B, C, P);
       // double distanceAP = objPicking.distanceToPoint(A,P);
       // double distanceBP = objPicking.distanceToPoint(B,P);
        //double distanceCP = objPicking.distanceToPoint(C,P);

        
        
        D(cout << "Is the point in the triangle ? " << isInThisTriangle <<'\n');
        D(cout << "Distance A P ? " << distanceAP <<'\n');
        D(cout << "Distance B P ? " << distanceBP <<'\n');
        D(cout << "Distance C P ? " << distanceCP <<'\n');
    }
    
    //to find inside of what triangle the point P is located
    /*while (wasTheVertexFound!=true)
    {
        idForTriangle = objPicking.idxVertex(objReadSRF.VertexLocation[ii].id0,
                                                  objReadSRF.VertexLocation[ii].id1,
                                                  objReadSRF.VertexLocation[ii].id2,
                                                  objReadSRF.VertexLocation,
                                                  P);
        
        wasTheVertexFound=objPicking.isInThisTriangleFlag;
        
        ++ii; //It could go overflow be careful here if P is not inside the surface!!!! Make sure always to have the point on top of the surface it is a condition necessary
        
        D(cout << ii << " wasTheVertexFound ? " << wasTheVertexFound <<'\n');
        
        D(cout << " id0 " << objReadSRF.VertexLocation[ii].id0 << " id1 " << objReadSRF.VertexLocation[ii].id1 << " id2 " << objReadSRF.VertexLocation[ii].id2<< '\n');

        
    }
    
    idForClosestVertex = objPicking.idxClosestVertex(ii, objReadSRF.VertexLocation, P);
    


    
    D(cout << " The Closest vertex is ? " << idForClosestVertex << " in triangle :" << ii << '\n');
    
  
    
   // isInsideTriangle = GL_FALSE;

    
    /* clear window */
    //glClear(GL_COLOR_BUFFER_BIT);
    
    /* draw scene */
    //glutSolidTeapot(.5);
    
    /* flush drawing routines to the window */
    glFlush();
    glutSwapBuffers();
    
}


void special(int key, int px, int py)
{
    gLastKey = key;
    switch (key) {
        case GLUT_KEY_UP: // arrow forward, close in on world
            gCamera.focalLength -= 1.5f;
            if (gCamera.focalLength < 0.0f)
                gCamera.focalLength = 0.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: // arrow back, back away from world
            gCamera.focalLength += 1.5f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // arrow left, smaller aperture
            gCamera.aperture -= 1.5f;
            if (gCamera.aperture < 0.0f)
                gCamera.aperture = 0.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: // arrow right, larger aperture
            gCamera.aperture += 1.5f;
            glutPostRedisplay();
            break;
    }
}

void mouseDolly (int x, int y)
{
    if (gDolly) {
        GLfloat dolly = (gDollyPanStartPoint[1] - y) * -gCamera.viewPos.z / 200.0f;
        GLfloat eyeRelative = gCamera.eyeSep / gCamera.focalLength;
        gCamera.focalLength += gCamera.focalLength / gCamera.viewPos.z * dolly;
        if (gCamera.focalLength < 1.0)
            gCamera.focalLength = 1.0;
        gCamera.eyeSep = gCamera.focalLength * eyeRelative;
        gCamera.viewPos.z += dolly;
        if (gCamera.viewPos.z == 0.0) // do not let z = 0.0
            gCamera.viewPos.z = 0.0001;
        gDollyPanStartPoint[0] = x;
        gDollyPanStartPoint[1] = y;
        glutPostRedisplay();
    }
}

void mousePan (int x, int y)
{
    if (gPan) {
        GLfloat panX = (gDollyPanStartPoint[0] - x) / (900.0f / -gCamera.viewPos.z);
        GLfloat panY = (gDollyPanStartPoint[1] - y) / (900.0f / -gCamera.viewPos.z);
        gCamera.viewPos.x -= panX;
        gCamera.viewPos.y -= panY;
        gDollyPanStartPoint[0] = x;
        gDollyPanStartPoint[1] = y;
        glutPostRedisplay();
    }
}

void drag(int x, int y)
{
    a = x/1.0;
    b = 300.0 - (y/1.0);
    glutPostRedisplay();
}

void mouseTrackball (int x, int y)
{
    if (gTrackBall) {
        rollToTrackball (x, y, gTrackBallRotation);
        glutPostRedisplay();
    }
}


void mouse (int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        if (gDolly) { // if we are currently dollying, end dolly
            mouseDolly (x, y);
            gDolly = GL_FALSE;
            glutMotionFunc (NULL);
            gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
            glutMotionFunc (NULL);
        }
        else if (gPan)
        {
            mousePan (x, y);
            gPan = GL_FALSE;
            glutMotionFunc (NULL);
            gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
            glutMotionFunc (NULL);
        }
        startTrackball (x, y, 0, 0, gCamera.screenWidth, gCamera.screenHeight);
        glutMotionFunc (mouseTrackball);
        gTrackBall = GL_TRUE;
        
        objPicking.ConvertScreenCoordTo3DCoord(org, vec, x, y);
        D(cout << "mx: " << x << " my: " << y <<'\n');
        
        
    }
    else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        gTrackBall = GL_FALSE;
        glutMotionFunc (NULL);
        rollToTrackball (x, y, gTrackBallRotation);
        if (gTrackBallRotation[0] != 0.0)
            addToRotationTrackball (gTrackBallRotation, gWorldRotation);
        gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
    }
    
    
    else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
    {
        if (gTrackBall)
        {
            // if we are currently trackballing, end trackball
            gTrackBall = GL_FALSE;
            glutMotionFunc (NULL);
            rollToTrackball (x, y, gTrackBallRotation);
            if (gTrackBallRotation[0] != 0.0)
                addToRotationTrackball (gTrackBallRotation, gWorldRotation);
            gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
        }
        else if (gDolly)
        {
            mouseDolly (x, y);
            gDolly = GL_FALSE;
            glutMotionFunc (NULL);
            gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
            glutMotionFunc (NULL);
        }
        gDollyPanStartPoint[0] = x;
        gDollyPanStartPoint[1] = y;
        glutMotionFunc (mousePan);
        gPan = GL_TRUE;
    }
    

    
    

    
}

void key(unsigned char inkey, int px, int py)
{
    gLastKey = inkey;
    switch (inkey) {
        case 27:
            exit(0);
            break;
        case 'h': // help
        case 'H':
            gShowHelp =  1 - gShowHelp;
            glutPostRedisplay();
            break;
        case 'i': // info
        case 'I':
            gShowInfo =  1 - gShowInfo;
            glutPostRedisplay();
            break;
        case 'n': // info
        case 'N':
            gDrawNumberOnVertex =  1 - gDrawNumberOnVertex;
            glutPostRedisplay();
            break;
        case 't': // info
        case 'T':
            gDrawTriangles =  1 - gDrawTriangles;
            glutPostRedisplay();
            break;
        case 'p': // info
        case 'P':
            gDrawPoints =  1 - gDrawPoints;
            glutPostRedisplay();
            break;
        case 'b': // info
        case 'B':
            gDrawBoundary =  1 - gDrawBoundary;
            glutPostRedisplay();
            break;
        case 'r':
        case 'R': //Read SRF
            //objReadSRF.ReadSRFFile((char*) "meshd.srf");
            glutPostRedisplay();
            //glutPostRedisplay();
            break; // print point spline
            
        default:   break;
            
    }
}

void spaceballmotion (int x, int y, int z)
{
    long deadZone = 105;
    float scale = -gCamera.viewPos.z * 0.00000001f;
    if (abs (x) > deadZone) {
        GLfloat panX = abs (x) * x * scale;
        gCamera.viewPos.x += panX;
    }
    if (abs (y) > deadZone) {
        GLfloat panY = abs (y) * y * scale;
        gCamera.viewPos.y -= panY;
    }
    if (abs (z) > deadZone) {
        GLfloat dolly = abs (z) * z * scale;
        gCamera.viewPos.z += dolly;
        if (gCamera.viewPos.z == 0.0) // do not let z = 0.0
            gCamera.viewPos.z = 0.0001;
    }
    glutPostRedisplay();
}

void spaceballrotate (int rx, int ry, int rz)
{
    long deadZone = 60;
    float rotation[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    // handle rotations about each respective axis
    if (abs (rx) > deadZone) {
        rotation[0] = abs (rx) * -rx * 0.0000008f;
        rotation[1] = 1.0f;
        rotation[2] = 0.0f;
        rotation[3] = 0.0f;
        addToRotationTrackball (rotation, gWorldRotation);
    }
    if (abs (ry) > deadZone) {
        rotation[0] = abs (ry) * ry * 0.0000008f;
        rotation[1] = 0.0f;
        rotation[2] = 1.0f;
        rotation[3] = 0.0f;
        addToRotationTrackball (rotation, gWorldRotation);
    }
    if (abs(rz) > deadZone) {
        rotation[0] = abs (rz) * -rz * 0.0000008f;
        rotation[1] = 0.0f;
        rotation[2] = 0.0f;
        rotation[3] = 1.0f;
        addToRotationTrackball (rotation, gWorldRotation);
    }
    glutPostRedisplay();
}

#pragma mark ---- menu ----

void menuOb (int value)
{
    switch (value) {
        case 0:  WIRE = !WIRE;		break;
        default:   				break;
    }
    glutPostRedisplay();
}

#pragma mark ---- timer for animation ----

void Timer(int iUnused)
{
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

#pragma mark ---- menu handling ----

// Menu handling function definition
void menu(int item)
{
    switch (item)
    {
        case MENU_FRONT:
        case MENU_SPOT:
        case MENU_BACK:
        case MENU_BACK_FRONT:
        {
            show = (MENU_TYPE) item;
        }
            break;
        default:
        {       /* Nothing */       }
            break;
    }
    
    glutPostRedisplay();
    
    return;
}

#pragma mark ---- main ----

int main (int argc, const char * argv[])
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // non-stereo for main window
    glutInitWindowPosition (100, 50);
    glutInitWindowSize (WIDTH, HEIGHT);
    gMainWindow = glutCreateWindow("N-RoSy IMPLEMENTATION CMU");
    
    init(); // standard GL init
    
    glutReshapeFunc (reshape);
    glutDisplayFunc (maindisplay);
    
    Timer(0);
    
    glutKeyboardFunc (key);
    glutSpecialFunc (special);
    
    glutMouseFunc (mouse);
    glutMotionFunc(drag);
    //glutSpaceballMotionFunc(spaceballmotion);
    //glutSpaceballRotateFunc(spaceballrotate);
    
    // Create a menu
    glutCreateMenu(menu);
    
    // Add menu items
    glutAddMenuEntry("Show Front", MENU_FRONT);
    glutAddMenuEntry("Show Back", MENU_BACK);
    glutAddMenuEntry("Spotlight", MENU_SPOT);
    glutAddMenuEntry("Blend 'em all", MENU_BACK_FRONT);
    
    // Associate a mouse button with menu
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    
    glutMainLoop();
    return 0;
}





