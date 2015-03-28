//
//  ReadSRF.h
//  Yui
//
//  Created by Diego Andrade on 3/26/15.
//  Copyright (c) 2015 Carnegie Mellon University. All rights reserved.
//

#ifndef __Yui__ReadSRF__
#define __Yui__ReadSRF__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "VerticesOutput.h"

using namespace std;

class ReadSRF
{
public:
    ReadSRF();		//Constructor
    ~ReadSRF();     //Destructor
    
    //Vertex and Location Output from SRF files
    VerticesOutput* VertexLocation;
    vector <VerticesOutput> VertexConnectivity;
    vector <VerticesOutput> VertexConnectivityList;
    
    void ReadSRFFile(char* file);
    void init();

    
};



#endif /* defined(__Yui__ReadSRF__) */
