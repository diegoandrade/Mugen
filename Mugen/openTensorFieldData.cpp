//
//  openTensorFieldData.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/12/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include "openTensorFieldData.h"

//#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


openTensorFieldData::openTensorFieldData()
{
    
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
                
                D(cout << "lineCounter: " << lineCounter++ << endl;)
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

void openTensorFieldData::ReadNt3mFile(const char *file)
{
    
    int numberOfElemInFile = numberOfElementsInFile(file);
    
    TFD = (Tensor3D *)malloc(numberOfElemInFile*sizeof(Tensor3D));
    
    int lineCounter = 0;
    
    string tempValue = "";
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
                
                //tempValue = tokens[0];
                //TFD[lineCounter].m0 = stoi(tempValue, &sz);
                tempValue = tokens[2];
                TFD[lineCounter].m0 = stod(tempValue, &sz);
                tempValue = tokens[3];
                TFD[lineCounter].m1 = stod(tempValue, &sz);
                tempValue = tokens[4];
                TFD[lineCounter].m2 = stod(tempValue, &sz);
                tempValue = tokens[5];
                TFD[lineCounter].m3 = stod(tempValue, &sz);
                tempValue = tokens[6];
                TFD[lineCounter].m4 = stod(tempValue, &sz);
                tempValue = tokens[7];
                TFD[lineCounter].m5 = stod(tempValue, &sz);
                
                //FIND A MORE ELEGANT WAY OF ASSIGNING VALUES SUCH AS INLINE
                TFD[lineCounter].A[0][0] = TFD[lineCounter].m0;
                TFD[lineCounter].A[0][1] = TFD[lineCounter].m1;
                TFD[lineCounter].A[0][2] = TFD[lineCounter].m2;
                TFD[lineCounter].A[1][0] = TFD[lineCounter].m1;
                TFD[lineCounter].A[1][1] = TFD[lineCounter].m3;
                TFD[lineCounter].A[1][2] = TFD[lineCounter].m4;
                TFD[lineCounter].A[2][0] = TFD[lineCounter].m2;
                TFD[lineCounter].A[2][1] = TFD[lineCounter].m3;
                TFD[lineCounter].A[2][2] = TFD[lineCounter].m5;
                
                
                D(cout <<  "TFD[" << lineCounter << "].m0 : " << setprecision(9) << TFD[lineCounter].m0 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m1 : " << TFD[lineCounter].m1 << fixed << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m2 : " << TFD[lineCounter].m2 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m3 : " << TFD[lineCounter].m3 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m4 : " << TFD[lineCounter].m4 << endl;)
                D(cout <<  "TFD[" << lineCounter << "].m5 : " << TFD[lineCounter].m5 << endl;)
                
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
}