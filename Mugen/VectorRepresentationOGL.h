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
#include "ReadSRF.h"
#include "VerticesOutput.h"

using namespace std;

class VectorRepresentationOGL
{
    
public:
    VerticesOutput*  vertexLocation; //initialize in a different way
    
    
public:
    
    VectorRepresentationOGL();
    ~VectorRepresentationOGL();
    
    void getVectors(const char* file);
    void getPoints(const char* file);
    
    ReadSRF* objRSRF = new ReadSRF();
    VerticesOutput*  objNRoSyVer = new VerticesOutput(); //vector info for NRosy
    
   
    
    
    
};


#endif /* defined(__Mugen__VectorRepresentationOGL__) */
