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
#include "VerticesOutput.h"
#include "matrix3x3.h"

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
    
    Tensor3D sortSmallToLarge (Tensor3D &tnsr);
    Tensor3D switchColumns (int column1, int column2, Tensor3D &tnsr);
    Tensor3D switchRows (int row1, int row2, Tensor3D &tnsr);
    
    void normalize(Tensor3D &v) ;
    double length (const Vector3D &v);
    void normalize (Vector3D &v);
    

    
    //temporal values to switch columns, this can be more elegant someday!
    double r, s, t;
    double R, S, T;
    Tensor3D tensorTemp;
    
    void printVertice (VerticesOutput vert);
    
    matrix3x3 objM;
    
};

#endif /* defined(__Mugen__openTensorFieldData__) */
