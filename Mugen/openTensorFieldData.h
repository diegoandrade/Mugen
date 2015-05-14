//
//  openTensorFieldData.h
//  Mugen
//
//  Created by Diego Andrade on 5/12/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__openTensorFieldData__
#define __Mugen__openTensorFieldData__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <iomanip>

#include "Tensor3D.h"

using namespace std;

class openTensorFieldData
{
public:
    openTensorFieldData();		//Constructor
    ~openTensorFieldData();     //Destructor
    
    int numberOfElementsInFile(const char* file);
    
    Tensor3D * ReadNt3mFile(const char* file);
    
    Tensor3D * TFD; //= new Tensor3D();
    
    int numberOfElements;
    
};

#endif /* defined(__Mugen__openTensorFieldData__) */
