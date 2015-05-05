//
//  PickingObject.cpp
//  Mugen
//
//  Created by Diego Andrade on 4/22/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG

#include "PickingObject.h"

PickingObject::PickingObject()
{
    isInThisTriangleFlag = false;

}

PickingObject::~PickingObject()
{
    
}

bool PickingObject::isInThisTriangle(Vector3D A, Vector3D B, Vector3D C, Vector3D P)
{
    bool isInThisTriangle = false;
    
    
    //Compute vectors
    v0 = C - A;
    v1 = B - A;
    v2 = P - A;
    
    // Compute dot products
    double dot00 = dot(v0, v0);
    double dot01 = dot(v0, v1);
    double dot02 = dot(v0, v2);
    double dot11 = dot(v1, v1);
    double dot12 = dot(v1, v2);
    
    // Compute barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    
    // Check if point is in triangle
    if((u >= 0) && (v >= 0) && (u + v < 1))
    {
        isInThisTriangle = true;
        return isInThisTriangle;
    }
    else
        return isInThisTriangle;
}

//Euclidena Distance
double PickingObject::distanceToPoint(Vector3D A, Vector3D P)
{

    double distance = sqrt((A.x1-P.x1)*(A.x1-P.x1)+(A.y1-P.y1)*(A.y1-P.y1)+(A.z1-P.z1)*(A.z1-P.z1));
    
    return distance;
}

int PickingObject::idxVertex (int id0, int id1, int id2, VerticesOutput* VertexLocation, Vector3D P)
{
    int idForVertex = 0;
    
    V0.a = VertexLocation[id0].x; V0.b = VertexLocation[id0].y; V0.c = VertexLocation[id0].z;
    v1.a = VertexLocation[id1].x; V1.b = VertexLocation[id1].y; V1.c = VertexLocation[id1].z;
    V2.a = VertexLocation[id2].x; V2.b = VertexLocation[id2].y; V2.c = VertexLocation[id2].z;
    
    isInThisTriangleFlag = isInThisTriangle(V0, V1, V2, P);
    
    return idForVertex;
}

int PickingObject::idxClosestVertex(int idTriangle, VerticesOutput *VertexLocation, Vector3D P)
{
    int idV = 0;
    int id0 = VertexLocation[idTriangle].id0;
    int id1 = VertexLocation[idTriangle].id0;
    int id2 = VertexLocation[idTriangle].id2;
    
    V0.a = VertexLocation[id0].x;
    V0.b = VertexLocation[id0].y;
    V0.c = VertexLocation[id0].z;
    
    V1.a = VertexLocation[id1].x;
    V1.b = VertexLocation[id1].y;
    V1.c = VertexLocation[id1].z;
    
    V2.a = VertexLocation[id2].x;
    V2.b = VertexLocation[id2].y;
    V2.c = VertexLocation[id2].z;
    
    double d0 = distanceToPoint(V0,P);
    double d1 = distanceToPoint(V1,P);
    double d2 = distanceToPoint(V2,P);
    
    if(d0<d1)
        idV = id0;
    else if (d1<d2)
        idV = id1;
    else
        idV = id2;
    
    return idV;
}

bool PickingObject::ConvertScreenCoordTo3DCoord(Vector3D &org,Vector3D &vec,int mx,int my)
{
    bool DFbool = true;
    
    int viewport[4];
    double modelMat[16],projMat[16];
    double x1,y1,z1,x2,y2,z2;
    
    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,modelMat);
    glGetDoublev(GL_PROJECTION_MATRIX,projMat);
    
    my=viewport[3]-my;  // Why? I don't know.
    
    gluUnProject((double)mx,(double)my, 0.5,modelMat,projMat,viewport,&x1,&y1,&z1);
    gluUnProject((double)mx,(double)my, 0.7,modelMat,projMat,viewport,&x2,&y2,&z2);
    
    org.a = x1;
    org.b = y1;
    org.c = z1;
    
    vec.a = x2;
    vec.b = y2;
    vec.c = z2;
    
    vec=vec-org;
    
    normalize(vec);
    
    D(cout << "V x: " << vec.a << " y: " << vec.b << " z: " << vec.c <<'\n');

    
    
    /*
    YsVec3 itsc,viewPos,viewDir;
    GetViewPosition(viewPos);
    GetViewDirection(viewDir);
    YsPlane pln;
    pln.Set(viewPos,viewDir);
    
    if(pln.GetIntersection(itsc,org,vec)==YSOK)
    {
        org=itsc;
    }*/
    
    
    //return YSOK;
    
    
    return DFbool;
}

const Vector3D &PickingObject::GetViewPosition(Vector3D &pos) const
{
   // pos::Vector3D.Set(0.0,0.0,viewDistance);
   // pos::Vector3D.viewAttitude.Mul(pos,pos);
   // pos=viewTarget+pos;
    return pos;
}

