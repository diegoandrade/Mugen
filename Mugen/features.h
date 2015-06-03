//
//  features.h
//  Mugen
//
//  Created by Diego Andrade on 5/13/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__features__
#define __Mugen__features__

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <math.h>
#include "Vector3D.h"
#include "VerticesOutput.h"
#include "Tensor3D.h"


#include <iomanip>
#include <limits>

#include "Common.h"

class features
{
public:
    features();		//Constructor
    ~features();     //Destructor
    
    const float DEG2RAD = PI/180.0;
    const float RAD2DEG = 180/PI;
    
    void drawOval();
    void drawEllipse(float xradius, float yradius);
    void drawEllipse(float xradius, float yradius, Vector3D vec, GLuint index);
    void drawEllipse(float xradius, float yradius, GLuint index);
    
    void drawUDCS(GLuint index);
    void drawGLobalCoordinateSystem();
    
    double rotateCoordinatSystem(VerticesOutput vert, Tensor3D tnsr, AXIS axis);
    Tensor3D sortSmallToLarge (Tensor3D &tnsr);
    Tensor3D switchColumns (int column1, int column2, Tensor3D &tnsr);
    Tensor3D switchRows (int row1, int row2, Tensor3D &tnsr);
    
    void drawLocalCoordinateSystem ( Tensor3D &tnsr, VerticesOutput vert);

    
    void drawTriangleList( GLuint index);
    
    void normalize(Tensor3D &v) ;
    double length (const Vector3D &v);
    void normalize (Vector3D &v);
    
   

    //temporal values to switch columns, this can be more elegant someday!
    double r, s, t;
    double R, S, T;
    Tensor3D tensorTemp;
    
    void printVertice (VerticesOutput vert);
    
};



#endif /* defined(__Mugen__features__) */
