//
//  PickingObject.h
//  Mugen
//
//  Created by Diego Andrade on 4/22/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__PickingObject__
#define __Mugen__PickingObject__

#include <stdio.h>
#include <iostream>
#include "Vector3D.h"
#include "VerticesOutput.h"

using namespace std;

class PickingObject
{
    
public:
    double x , y, z ;
    double nx, ny, nz;
    int id1, id2, id3;
    
    bool isInThisTriangleFlag;
    
public:
    
    PickingObject();
    ~PickingObject();
    
    Vector3D v0;
    Vector3D v1;
    Vector3D v2;
    
    Vector3D V0;
    Vector3D V1;
    Vector3D V2;
    
    // returns true if point is inside the triangle using barycentric coordinates
    bool isInThisTriangle (Vector3D A, Vector3D B, Vector3D C, Vector3D P);
    
    // what distance between two points
    double distanceToPoint (Vector3D A, Vector3D P);
    
    // what is triangle where this point lies ?
    int idxVertex (int id0, int id1, int id2, VerticesOutput* VertexLocation, Vector3D P);
    
    // what is the closest vertex to that point ?
    int idxClosestVertex ( int idTriangle, VerticesOutput* VertexLocation, Vector3D P);
    
};


#endif /* defined(__Mugen__PickingObject__) */
