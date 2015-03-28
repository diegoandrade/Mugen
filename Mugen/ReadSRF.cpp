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
}

ReadSRF::~ReadSRF()
{
   // float *dist = (float *)malloc(100 * sizeof(float)); //format to initialize a pointer
   // VertexLocation = (VerticesOutput *)malloc(100*sizeof(VerticesOutput));
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


template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

void ReadSRF::ReadSRFFile(char* file)
{
   VerticesOutput* vert = (VerticesOutput *)malloc(100*sizeof(VerticesOutput));
  
    try
    {
        string line;
        ifstream myfile ("/Users/diegoandrade/Desktop/meshd.srf"); //AQUI this is a hardcoded direction change this
        if (myfile.is_open())
        {
            bool foundGE = false;
            bool foundF = false;
            
            int vertexCounter = 0;
            int faceCounter = 0;
            
            while ( getline (myfile,line) && foundGE ==false)
            {
                 istringstream iss(line);
                
                vector<string> tokens;
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter(tokens));
                
                              
                if (tokens[0] ==  "Surf")
                {
                    cout << "FOUND SURFACE" << '\n';
                    
                }
                else if (tokens[0] == "F")
                {
                    cout << "FOUND FACE" << '\n';
                    foundF = true;
                }
                else if (tokens[0] == "GE")
                {
                    cout << "FOUND GE" << '\n';
                    foundGE = true;
                }
                else if (tokens[0] == "E")
                {
                    cout << "FOUND EDGE" << '\n';

                }
                else if (tokens[0]== "V" && foundF == true)
                {

                    
                   
                    
                    //VertexConnectivityList.push_back(data);//from_string<double>(dd, tokens[1], std::dec);
                    //VertexConnectivityList[faceCounter].value2 = &dd;//from_string<double>(dd, tokens[2], std::dec);
                    //VertexConnectivityList[faceCounter].value3 = &dd;//from_string<double>(dd, tokens[3], std::dec);

                    
                    
                    
                    cout << "FOUND VERTEX when foundf=true" << '\n';
                    foundF = false;
                    faceCounter++;
                    
                }
                else if (tokens[0] == "N")
                {
                    cout << "FOUND NORMAL" << '\n';
                    
                }
                else if (tokens[0] == "V" && foundF == false)
                {
                    cout << "FOUND VERTEX when foundf=false" << '\n';
                    //foundF = true;

                    
                    if(vertexCounter<100)
                    {
                        vert[vertexCounter].x = 0.0;
                        vert[vertexCounter].y = 0.0;
                        vert[vertexCounter].z = 0.0;
                    }
                    
                    vertexCounter++;
                    
                }
               // else
               //     cout << tokens[0] << '\n';
                //cout << vertexCounter << '\n';
               // cout << faceCounter << '\n';




                
            }
            myfile.close();
            
            VertexLocation = vert;
        }
            
        else cout << "Unable to open file";
        
        
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
    
    
    
}