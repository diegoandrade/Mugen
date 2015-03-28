//
//  VerticesOutput.cpp
//  Yui
//
//  Created by Diego Andrade on 3/26/15.
//  Copyright (c) 2015 Carnegie Mellon University. All rights reserved.
//

#include "VerticesOutput.h"

VerticesOutput::~VerticesOutput()
{
    
    
}

VerticesOutput::VerticesOutput(string V, int v1, int v2, int v3)
{
    this->idSV = V;
    this->int_value1 = v1;
    this->int_value2 = v2;
    this->int_value3 = v3;
    
    this->vertexconn.V1 = v1;
    this->vertexconn.V2 = v2;
    this->vertexconn.V3 = v3;
    
}


VerticesOutput::VerticesOutput(string V, double v1, double v2, double v3)
{
    this->idS = V;
    this->x = v1;
    this->y = v2;
    this->z = v3;
    
    this->origen.X = v1;
    this->origen.Y = v2;
    this->origen.Z = v3;
    
}

