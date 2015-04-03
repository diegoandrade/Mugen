//
//  VectorRepresentationOGL.h
//  Mugen
//
//  Created by Diego Andrade on 4/2/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__VectorRepresentationOGL__
#define __Mugen__VectorRepresentationOGL__

#include <stdio.h>
#include <iostream>

#include "Vector3D.h"

using namespace std;

class VectorRepresentationOGL
{
    
public:
    double x , y, z ;
    double nx, ny, nz;
    int id1, id2, id3;
    
public:
    
    VectorRepresentationOGL();
    ~VectorRepresentationOGL();
    
    Vector3D* getVectors(char* file);
    Vector3D* getPoints(char* file);
    
    
    
    
};


#endif /* defined(__Mugen__VectorRepresentationOGL__) */
