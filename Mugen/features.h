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



class features
{
public:
    features();		//Constructor
    ~features();     //Destructor
    
    const float DEG2RAD = 3.14159/180.0;
    
    void drawOval();
    void drawEllipse(float xradius, float yradius);
    void drawEllipse(float xradius, float yradius, GLuint index);
    
    void drawTriangleList( GLuint index);
    
    
};

#endif /* defined(__Mugen__features__) */
