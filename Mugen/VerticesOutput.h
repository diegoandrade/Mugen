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
    double value1,  value2 , value3;
    
public:
    
    int idd;
    char idC ;
    string idS ;


    
    string idSV ;
    string idSF ;
    int int_value1 ;
    int int_value2 ;
    int int_value3 ;
    
    VerticesOutput();
    ~VerticesOutput();
    
    VerticesOutput(string V, int v1, int v2, int v3);
    VerticesOutput(string V, double v1, double v2, double v3);

    struct orim
    {
        double X, Y , Z;
        
    };
    
    orim origen;
    
    struct vc
    {
        double V1, V2, V3;
    };
    
    vc vertexconn;
    
    
};  //retrieves and clasifies the vertices from SRF




#endif /* defined(__Yui__VerticesOutput__) */
