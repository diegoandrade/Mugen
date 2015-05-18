//
//  features.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/13/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG

#include "features.h"


features::features()
{
    
}

features::~features()
{
    
}

void features::drawEllipse(float xradius, float yradius)
{
    glBegin(GL_LINE_LOOP);
    for(int i=0; i < 360; i++)
    {
        //convert degrees into radians
        float degInRad = i*DEG2RAD;
        glVertex2f(cos(degInRad)*xradius,sin(degInRad)*yradius);
    } 
    glEnd();
}

void features::drawEllipse(float xradius, float yradius, GLuint index)
{
    glNewList(index, GL_COMPILE);
        glBegin(GL_LINE_LOOP);
        for(int i=0; i < 360; i++)
        {
            if(i%12==0)
            {
                 //convert degrees into radians
                float degInRad = i*DEG2RAD;
                glVertex2f(cos(degInRad)*xradius,sin(degInRad)*yradius);
            }
           
        }
        glEnd();
    glEndList();
}

void features::drawEllipse(float xradius, float yradius, Vector3D vect, GLuint index)
{
    glNewList(index, GL_COMPILE);
    //glPushMatrix ();
    //glTranslatef(vect.a,  vect.b, vect.c); // this translations is done after a world rotation so we are looking at x-z and then translation
    glBegin(GL_LINE_LOOP);
    for(int i=0; i < 360; i++)
    {
        if(i%12==0)
        {
            //convert degrees into radians
            float degInRad = i*DEG2RAD;
            glVertex2f(cos(degInRad)*xradius,sin(degInRad)*yradius);
        }
        
    }
    //glPushMatrix();
    glEnd();
    glEndList();
}


void features::drawTriangleList(GLuint index)
{
    glNewList(index, GL_COMPILE);
        glBegin(GL_TRIANGLES);
            glVertex3f(0,3,2);
            glVertex3f(0,1,3);
            glVertex3f(2,3,4);
        glEnd();
    glEndList();
}

double features::rotateCoordinatSystem(VerticesOutput vert, Tensor3D tnsr, AXIS axis)
{
    
    Vector3D v, w;
    
    if (axis==XAXIS)
    {
        v.x1 = tnsr.R[0][0];
        v.y1 = tnsr.R[0][1];
        v.z1 = tnsr.R[0][2];
        
        w.x1 = 1;
        w.y1 = 0;
        w.z1 = 0;
    }
    else if ( axis == YAXIS)
    {
        v.x1 = tnsr.R[1][0];
        v.y1 = tnsr.R[1][1];
        v.z1 = tnsr.R[1][2];
        
        w.x1 = 0;
        w.y1 = 1;
        w.z1 = 0;
    }
    else if (axis == ZAXIS)
    {
        v.x1 = tnsr.R[2][0];
        v.y1 = tnsr.R[2][1];
        v.z1 = tnsr.R[2][2];
        
        w.x1 = 0;
        w.y1 = 0;
        w.z1 = 1;
    }
    
    D(cout << setprecision(8) << fixed << "v.x: " << v.x1 << setw(8) << "\tv.y: " << v.y1 << setw(8) << "\tv.z: " << v.z1 << endl;
      cout << setprecision(8) << "w.x: " << w.x1 << setw(8) << "\tw.y: " << w.y1 << setw(8) << "\tw.z: " << w.z1 << endl;);

    
    double angle = acos(dot(v, w)/(length(v)*length(w))) * RAD2DEG;
  
    return  (angle);
}
