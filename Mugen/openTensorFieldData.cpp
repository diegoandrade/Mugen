//
//  openTensorFieldData.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/12/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include "openTensorFieldData.h"

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


openTensorFieldData::openTensorFieldData()
{
    numberOfElements = 0;
    
    //Initializing values
    r=s=t=0;
    R=S=T=0;

}

openTensorFieldData::~openTensorFieldData()
{
    

}

int openTensorFieldData::numberOfElementsInFile(const char *file)
{
    
  
    int lineCounter = 0;
    
    
    string tempValue = "";


    try
    {
        string line;
        string str = "/Users/diegoandrade/Documents/Mugen/Mugen/data/";
        str.append(file);
        str.append("/meshanid.nt3m");
        
        ifstream myfile (str); //AQUI this is a hardcoded direction change this
        
        if (myfile.is_open())
        {
            
            while ( getline (myfile,line))
            {
                
                D(cout << "lineCounter: " << lineCounter << endl;)
                lineCounter++;
            }
            
            myfile.close();
            
            
        }
        
        else cout << "Unable to open file";
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
    
    }
    
    return lineCounter;
}

Tensor3D* openTensorFieldData::ReadNt3mFile(const char *file)
{
    
    numberOfElements = numberOfElementsInFile(file);
    
    
    TFD = (Tensor3D *)malloc(numberOfElements*sizeof(Tensor3D));
    
    int lineCounter = 0;
    
    string tempValue[6];
    double tnVal[6];
    std::string::size_type sz;   // alias of size_t
    
    try
    {
        string line;
        
        string str = "/Users/diegoandrade/Documents/Mugen/Mugen/data/";
        str.append(file);
        str.append("/meshanid.nt3m");
        
        ifstream myfile (str); //AQUI this is a hardcoded direction change this
    
        if (myfile.is_open())
        {
            
            while ( getline (myfile,line))
            {
                
                istringstream iss(line);
                
                vector<string> tokens;
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter(tokens));
            
                
                
                for(int k=0; k < 6; k++){
                    tempValue[k] = tokens[k+2];
                    tnVal[k] = stod(tempValue[k], &sz);
                }
                
                
                TFD[lineCounter].m0 = tnVal[0];
                TFD[lineCounter].m1 = tnVal[1];
                TFD[lineCounter].m2 = tnVal[2];
                TFD[lineCounter].m3 = tnVal[3];
                TFD[lineCounter].m4 = tnVal[4];
                TFD[lineCounter].m5 = tnVal[5];
                
                
                D(cout <<  "TFD[" << lineCounter << "].m0 : " << setprecision(9) << TFD[lineCounter].m0 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m1 : " << TFD[lineCounter].m1 << fixed << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m2 : " << TFD[lineCounter].m2 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m3 : " << TFD[lineCounter].m3 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m4 : " << TFD[lineCounter].m4 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m5 : " << TFD[lineCounter].m5 << endl;)
                D(cout <<" -----------------------------------------------------------" << endl;)
                
                //FIND A MORE ELEGANT WAY OF ASSIGNING VALUES SUCH AS INLIN
                
                TFD[lineCounter].L[0][0] = tnVal[0];
                TFD[lineCounter].L[0][1] = tnVal[1];
                TFD[lineCounter].L[0][2] = tnVal[2];
                TFD[lineCounter].L[1][0] = tnVal[1];
                TFD[lineCounter].L[1][1] = tnVal[3];
                TFD[lineCounter].L[1][2] = tnVal[4];
                TFD[lineCounter].L[2][0] = tnVal[2];
                TFD[lineCounter].L[2][1] = tnVal[4];
                TFD[lineCounter].L[2][2] = tnVal[5];
                
                for(int i=0;i<3; i++) {
                    for(int j=0;j<3; j++) {
                        TFD[lineCounter].R[i][j] = 0.0;
                    }
                }
                
                
                D(cout <<  "A[0][0]: " << setprecision(9) << TFD[lineCounter].A[0][0] << endl;)
                D(cout <<  "A[0][1]: " << TFD[lineCounter].A[0][1] << fixed << endl;)
                D(cout <<  "A[0][2]: " << TFD[lineCounter].A[0][2] << endl;)
                D(cout <<  "A[1][1]: " << TFD[lineCounter].A[1][1] << endl;)
                D(cout <<  "A[1][2]: " << TFD[lineCounter].A[1][2]  << endl;)
                D(cout <<  "A[2][2]: " << TFD[lineCounter].A[2][2]  << endl;)
                D(cout <<" -----------------------------------------------------------" << endl;)
                
                
                
                lineCounter++;
                
                
            }
            
          
            myfile.close();
            
            
            for (int k=0;k<lineCounter;k++)
            {
                objM.jacrot(TFD[k].L, TFD[k].R);
            }
            
            
        }
        else cout << "Unable to open file";
        
        
        for (int k=0;k<lineCounter;k++)
        {
            sortSmallToLarge(TFD[k]);
        }
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
    
    return TFD;
}

Tensor3D openTensorFieldData::sortSmallToLarge(Tensor3D &tnsr)
{
    double l0 = tnsr.L[0][0];
    double l1 = tnsr.L[1][1];
    double l2 = tnsr.L[2][2];
    
    //tnsr.printTensor();
    
    D(cout << "l1: " << l0 <<" l2: " << l1 <<" l3: " << l2 << endl;);
    
    if (l0>=l1)
    {
        if(l0>=l2)
        {
            D(cout << "Largest number :" << l0 << endl;);
        }
        else
            D(cout << "Largest number :" << l2 << endl;);
    }
    else
    {
        if(l1>=l2)
        {
            D(cout << "Largest number :" << l1 << endl;);
        }
        else
            D(cout << "Largest number :" << l2 << endl;);
    }
    
    if (tnsr.L[0][0] > tnsr.L[1][1])
    {
        switchColumns(0, 1, tnsr);
        switchRows(0, 1, tnsr);
    }
    if (tnsr.L[0][0] > tnsr.L[2][2])
    {
        switchColumns(0, 2, tnsr);
        switchRows(0, 2, tnsr);
        
    }
    if (tnsr.L[1][1] > tnsr.L[2][2])
    {
        switchColumns(1, 2, tnsr);
        switchRows(1, 2, tnsr);
    }
    
    
    //tnsr.printTensor();
    
    return tnsr;
    
}

Tensor3D openTensorFieldData::switchColumns(int column1 , int column2, Tensor3D &tnsr)
{
    r = tnsr.R[0][column1];
    s = tnsr.R[1][column1];
    t = tnsr.R[2][column1];
    
    //  tnsr.printTensor();
    
    tnsr.R[0][column1] = tnsr.R[0][column2];
    tnsr.R[1][column1] = tnsr.R[1][column2];
    tnsr.R[2][column1] = tnsr.R[2][column2];
    
    tnsr.R[0][column2] = r;
    tnsr.R[1][column2] = s;
    tnsr.R[2][column2] = t;
    
    R = tnsr.L[0][column1];
    S = tnsr.L[1][column1];
    T = tnsr.L[2][column1];
    
    tnsr.L[0][column1] = tnsr.L[0][column2];
    tnsr.L[1][column1] = tnsr.L[1][column2];
    tnsr.L[2][column1] = tnsr.L[2][column2];
    
    tnsr.L[0][column2] = R;
    tnsr.L[1][column2] = S;
    tnsr.L[2][column2] = T;
    
    //   tnsr.printTensor();
    
    return tnsr;
}


Tensor3D openTensorFieldData::switchRows(int row1 , int row2, Tensor3D &tnsr)
{
    r = tnsr.R[row1][0];
    s = tnsr.R[row1][1];
    t = tnsr.R[row1][2];
    
    //  tnsr.printTensor();
    
    tnsr.R[row1][0] = tnsr.R[row2][0];
    tnsr.R[row1][1] = tnsr.R[row2][1];
    tnsr.R[row1][2] = tnsr.R[row2][2];
    
    tnsr.R[row2][0] = r;
    tnsr.R[row2][1] = s;
    tnsr.R[row2][2] = t;
    
    R = tnsr.L[row1][0];
    S = tnsr.L[row1][1];
    T = tnsr.L[row1][2];
    
    tnsr.L[row1][0] = tnsr.L[row2][0];
    tnsr.L[row1][1] = tnsr.L[row2][1];
    tnsr.L[row1][2] = tnsr.L[row2][2];
    
    tnsr.L[row2][0] = R;
    tnsr.L[row2][1] = S;
    tnsr.L[row2][2] = T;
    
    // tnsr.printTensor();
    
    return tnsr;
}
