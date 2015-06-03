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
    //Initializing values
    r=s=t=0;
    R=S=T=0;
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

void features::drawGLobalCoordinateSystem()
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

double features::rotateCoordinatSystem(VerticesOutput vert, Tensor3D tnsr, AXIS axis)
{
    
    Vector3D u, v, w;
    
    sortSmallToLarge(tnsr);
    
   // tnsr.printTensor();

    if (axis==XAXIS)
    {
        v.x1 = tnsr.R[0][0];
        v.y1 = tnsr.R[1][0];
        v.z1 = tnsr.R[2][0];
        
        w.x1 = 1;
        w.y1 = 0;
        w.z1 = 0;
    }
    else if ( axis == YAXIS)
    {
        v.x1 = tnsr.R[0][1];
        v.y1 = tnsr.R[1][1];
        v.z1 = tnsr.R[2][1];
        
        w.x1 = 0;
        w.y1 = 1;
        w.z1 = 0;
    }
    else if (axis == ZAXIS)
    {
        v.x1 = tnsr.R[0][2];
        v.y1 = tnsr.R[1][2];
        v.z1 = tnsr.R[2][2];
        
        w.x1 = 0;
        w.y1 = 0;
        w.z1 = 1;
    }
    
   //  tnsr.printTensor();
    
    D(cout << setprecision(8) << fixed << "v.x: " << v.x1 << setw(8) << "\tv.y: " << v.y1 << setw(8) << "\tv.z: " << v.z1 << endl;
      cout << setprecision(8) << "w.x: " << w.x1 << setw(8) << "\tw.y: " << w.y1 << setw(8) << "\tw.z: " << w.z1 << endl;);

    
    double angle = acos(dot(v, w)/(length(v)*length(w))) * RAD2DEG;
    //cout<< "] angle : " << angle << endl;
  
    return  (angle);
}

void features::drawLocalCoordinateSystem(Tensor3D &tnsr, VerticesOutput vert)
{
    tnsr.printTensor();
    
    tensorTemp.R[0][0] = vert.x+tnsr.R[0][0];
    tensorTemp.R[1][0] = vert.y+tnsr.R[1][0];
    tensorTemp.R[2][0] = vert.z+tnsr.R[2][0];
    
    tensorTemp.R[0][1] = vert.x+tnsr.R[0][1];
    tensorTemp.R[1][1] = vert.y+tnsr.R[1][1];
    tensorTemp.R[2][1] = vert.z+tnsr.R[2][1];

    tensorTemp.R[0][2] = vert.x+1.0;
    tensorTemp.R[1][2] = vert.y+1.0;
    tensorTemp.R[2][2] = vert.z+1.0;
    
    printVertice(vert);

    normalize(tensorTemp);
    
}

void features::normalize(Tensor3D &v)
{
    Vector3D v0,v1,v2;
    
     v.printTensor();
    
    v0.a = v.R[0][0];
    v0.b = v.R[1][0];
    v0.c = v.R[2][0];
    
    v1.a = v.R[0][1];
    v1.b = v.R[1][1];
    v1.c = v.R[2][1];
    
    v2.a = v.R[0][2];
    v2.b = v.R[1][2];
    v2.c = v.R[2][2];
    
    normalize(v0);
    normalize(v1);
    normalize(v2);
    
    v.R[0][0] = v0.a;
    v.R[1][0] = v0.b;
    v.R[2][0] = v0.c;
    
    v.R[0][1] = v1.a;
    v.R[1][1] = v1.b;
    v.R[2][1] = v1.c;
    
    v.R[0][2] = v2.a;
    v.R[1][2] = v2.b;
    v.R[2][2] = v2.c;
    
    v.printTensor();

}

double features::length(const Vector3D &v)
{
    return sqrt(v.a * v.a + v.b * v.b + v.c * v.c);
}

void features::normalize(Vector3D &v)
{
    double m = length(v);
    if (m != 0.0) v *= (1/m);
}

void features::drawUDCS(GLuint index)
{
    glNewList(index, GL_COMPILE);
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.5f);
    glEnd();
    glEndList();
    
    //D(cout << setprecision(8) << "vec.a: " << vec.a << setw(8) << "\tvec.b: " << vec.b << setw(8) << endl;);

    
}


Tensor3D features::sortSmallToLarge(Tensor3D &tnsr)
{
    double l0 = tnsr.L[0][0];
    double l1 = tnsr.L[1][1];
    double l2 = tnsr.L[2][2];
    
   //tnsr.printTensor();
    
    D(cout << "l1: " << l0 <<" l2: " << l1 <<" l3: " << l2 << endl;);

    if (l0>=l1)
    {
        if(l0>=l2)
        {
            D(cout << "Largest number :" << l0 << endl;);
        }
        else
            D(cout << "Largest number :" << l2 << endl;);
    }
    else
    {
        if(l1>=l2)
        {
            D(cout << "Largest number :" << l1 << endl;);
        }
        else
            D(cout << "Largest number :" << l2 << endl;);
    }
    
    if (tnsr.L[0][0] > tnsr.L[1][1])
    {
        switchColumns(0, 1, tnsr);
         switchRows(0, 1, tnsr);
    }
    if (tnsr.L[0][0] > tnsr.L[2][2])
    {
        switchColumns(0, 2, tnsr);
        switchRows(0, 2, tnsr);

    }
    if (tnsr.L[1][1] > tnsr.L[2][2])
    {
        switchColumns(1, 2, tnsr);
        switchRows(1, 2, tnsr);
    }
    
    
    //tnsr.printTensor();
    
    return tnsr;
    
}

Tensor3D features::switchColumns(int column1 , int column2, Tensor3D &tnsr)
{
    r = tnsr.R[0][column1];
    s = tnsr.R[1][column1];
    t = tnsr.R[2][column1];
    
  //  tnsr.printTensor();
    
    tnsr.R[0][column1] = tnsr.R[0][column2];
    tnsr.R[1][column1] = tnsr.R[1][column2];
    tnsr.R[2][column1] = tnsr.R[2][column2];
    
    tnsr.R[0][column2] = r;
    tnsr.R[1][column2] = s;
    tnsr.R[2][column2] = t;
    
    R = tnsr.L[0][column1];
    S = tnsr.L[1][column1];
    T = tnsr.L[2][column1];
    
    tnsr.L[0][column1] = tnsr.L[0][column2];
    tnsr.L[1][column1] = tnsr.L[1][column2];
    tnsr.L[2][column1] = tnsr.L[2][column2];
    
    tnsr.L[0][column2] = R;
    tnsr.L[1][column2] = S;
    tnsr.L[2][column2] = T;
    
 //   tnsr.printTensor();
    
    return tnsr;
}


Tensor3D features::switchRows(int row1 , int row2, Tensor3D &tnsr)
{
    r = tnsr.R[row1][0];
    s = tnsr.R[row1][1];
    t = tnsr.R[row1][2];
    
  //  tnsr.printTensor();
    
    tnsr.R[row1][0] = tnsr.R[row2][0];
    tnsr.R[row1][1] = tnsr.R[row2][1];
    tnsr.R[row1][2] = tnsr.R[row2][2];

    tnsr.R[row2][0] = r;
    tnsr.R[row2][1] = s;
    tnsr.R[row2][2] = t;
    
    R = tnsr.L[row1][0];
    S = tnsr.L[row1][1];
    T = tnsr.L[row1][2];
    
    tnsr.L[row1][0] = tnsr.L[row2][0];
    tnsr.L[row1][1] = tnsr.L[row2][1];
    tnsr.L[row1][2] = tnsr.L[row2][2];
    
    tnsr.L[row2][0] = R;
    tnsr.L[row2][1] = S;
    tnsr.L[row2][2] = T;
    
   // tnsr.printTensor();
    
    return tnsr;
}

void features::printVertice(VerticesOutput vert)
{
    cout << "vert.x : " << vert.x << "\tvert.y: " << vert.y << "\tvert.z : " << vert.z << endl  ;
}

