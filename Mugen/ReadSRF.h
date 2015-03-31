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
       
    void ReadSRFFile(char* file);
    void init();
      
    int numberOfVerticesInFile;
    int numberOfFacesInFile;
    
    int* boundary;
    int* interior;
    
    int boundaryPicesCounter;
    
    int interiorCounter;
    int boundaryCounter;
    int boundarySize;
    
    int tokenSize;
    
    int* getVerticesConnectedTo (int idx, VerticesOutput* vert);
    int numberOfVerticesConnectedTo;

};



#endif /* defined(__Yui__ReadSRF__) */
