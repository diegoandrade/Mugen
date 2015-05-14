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
        ifstream myfile ("/Users/diegoandrade/Documents/Mugen/Mugen/data/meshanid.nt3m"); //AQUI this is a hardcoded direction change this
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
        ifstream myfile ("/Users/diegoandrade/Documents/Mugen/Mugen/data/meshanid.nt3m"); //AQUI this is a hardcoded direction change this
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
                
                TFD[lineCounter].A[0][0] = tnVal[0];
                TFD[lineCounter].A[0][1] = tnVal[1];
                TFD[lineCounter].A[0][2] = tnVal[2];
                TFD[lineCounter].A[1][0] = tnVal[1];
                TFD[lineCounter].A[1][1] = tnVal[3];
                TFD[lineCounter].A[1][2] = tnVal[4];
                TFD[lineCounter].A[2][0] = tnVal[2];
                TFD[lineCounter].A[2][1] = tnVal[4];
                TFD[lineCounter].A[2][2] = tnVal[5];
                
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
            
            
        }
        
        else cout << "Unable to open file";
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
    
    return TFD;
}