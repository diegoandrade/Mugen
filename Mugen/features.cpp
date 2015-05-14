//
//  features.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/13/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

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