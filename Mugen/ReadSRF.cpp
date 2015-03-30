//
//  ReadSRF.cpp
//  Yui
//
//  Created by Diego Andrade on 3/26/15.
//  Copyright (c) 2015 Carnegie Mellon University. All rights reserved.
//


#include "ReadSRF.h"


ReadSRF::ReadSRF()
{
    //VertexConnectivityList[100]=new *VerticesOutput();
    numberOfVerticesInFile=0;
    numberOfFacesInFile=0;
}

ReadSRF::~ReadSRF()
{
   // float *dist = (float *)malloc(100 * sizeof(float)); //format to initialize a pointer
   VertexLocation = (VerticesOutput *)malloc(1000*sizeof(VerticesOutput));
    //init();
}

void ReadSRF::init()
{
    /*
    for(int j=0;j<100;j++){
        VertexLocation[j].x= 0.0;
        VertexLocation[j].y= 0.0;
        VertexLocation[j].z= 0.0;
        
        VertexLocation[j].value1 = 0.0;
        VertexLocation[j].value2 = 0.0;
        VertexLocation[j].value3 = 0.0;
    }*/
}


void ReadSRF::ReadSRFFile(char* file)
{
   VerticesOutput* vert = (VerticesOutput *)malloc(10000*sizeof(VerticesOutput)); //AQUI majke sure the size is correct
    int vertexCounter = 0;
    int faceCounter = 0;
    
    string tempValue = "";
    
    std::string::size_type sz;   // alias of size_t
  
    try
    {
        string line;
        ifstream myfile ("/Users/diegoandrade/Box Sync/Mugen/Mugen/data/meshd_sq.srf"); //AQUI this is a hardcoded direction change this
        if (myfile.is_open())
        {
            bool foundGE = false;
            bool foundF = false;
            
            
            while ( getline (myfile,line) && foundGE ==false)
            {
                 istringstream iss(line);
                
                vector<string> tokens;
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter(tokens));
                
                              
                if (tokens[0] ==  "Surf")
                {
                    //cout << "FOUND SURFACE" << '\n';
                    
                }
                else if (tokens[0] == "F")
                {
                    //cout << "FOUND FACE" << '\n';
                    foundF = true;
                }
                else if (tokens[0] == "GE")
                {
                    //cout << "FOUND GE" << '\n';
                    foundGE = true;
                }
                else if (tokens[0] == "E")
                {
                    //cout << "FOUND EDGE" << '\n';

                }
                else if (tokens[0]== "V" && foundF == true)
                {
                    //cout << "FOUND VERTEX when foundf=true" << '\n';
                    foundF = false;
                    tempValue = tokens[1];
                    vert[faceCounter].id1 = stoi(tempValue, &sz);
                    tempValue = tokens[2];
                    vert[faceCounter].id2 = stoi(tempValue, &sz);
                    tempValue = tokens[3];
                    vert[faceCounter].id3 = stoi(tempValue, &sz);
                    faceCounter++;
                    
                    
                    
                }
                else if (tokens[0] == "N")
                {
                    //cout << "FOUND NORMAL" << '\n';
                    vert[vertexCounter].nx = stod(tokens[4]);
                    vert[vertexCounter].ny = stod(tokens[5]);
                    vert[vertexCounter].nz = stod(tokens[6]);
                    
                }
                else if (tokens[0] == "V" && foundF == false)
                {
                    //cout << "FOUND VERTEX when foundf=false" << '\n';
                    vert[vertexCounter].x = stod(tokens[1]);
                    vert[vertexCounter].y = stod(tokens[2]);
                    vert[vertexCounter].z = stod(tokens[3]);
                    vertexCounter++;
                    
                }

             
            }
            myfile.close();
            
           
        }
            
        else cout << "Unable to open file";
        
        cout << "vertexCounter : " << vertexCounter << '\n';
        
        
        VertexLocation = vert;
        numberOfVerticesInFile = vertexCounter;
        numberOfFacesInFile = faceCounter;
        
         cout << "numberOfVerticesInFile: " << numberOfVerticesInFile << '\n';
         cout << "numberOfFacesInFile: " << numberOfFacesInFile << '\n';
        
        /*for(int i =0; i<vertexCounter ; i++)
        {
            cout << "values on x: " << vert[i].x << '\n';
            cout << "values on X: " << VertexLocation[i].x << '\n';
            
        }*/
        
        
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
    
    
    
}