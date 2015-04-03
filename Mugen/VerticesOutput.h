//
//  VerticesOutput.h
//  Yui
//
//  Created by Diego Andrade on 3/26/15.
//  Copyright (c) 2015 Carnegie Mellon University. All rights reserved.
//

#ifndef __Yui__VerticesOutput__
#define __Yui__VerticesOutput__

#include <stdio.h>
#include <iostream>
using namespace std;

class VerticesOutput
{
   
public:
    double x , y, z ;
    double nx, ny, nz;
    int id1, id2, id3;
       
public:
    
    VerticesOutput();
    ~VerticesOutput();
    
    VerticesOutput(string V, int v1, int v2, int v3);
    VerticesOutput(string V, double v1, double v2, double v3);
    VerticesOutput(double v1, double v2, double v3);
    
    union{
        struct{
            double a, b, c;
        };
        //struct{
            //double x, y, z;
        //};
    };  double elements[3];

    
};

//retrieves and clasifies the vertices from SRF and faces, I am storing both values here maybe a problem in the future for now verry compact.




#endif /* defined(__Yui__VerticesOutput__) */
