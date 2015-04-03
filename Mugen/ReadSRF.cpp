//
//  ReadSRF.cpp
//  Yui
//
//  Created by Diego Andrade on 3/26/15.
//  Copyright (c) 2015 Carnegie Mellon University. All rights reserved.
//

//#define DEBUG(x) do { std::cerr << x; } while (0)

#undef DEBUG 
//#define DEBUG

#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG

#include "ReadSRF.h"

ReadSRF::ReadSRF()
{

    numberOfVerticesInFile=0;
    numberOfFacesInFile=0;
    
    boundary = (int *)malloc(1000*sizeof(int));
    interior = (int *)malloc(100*sizeof(int));
    boundaryCounter = 0;
    boundarySize = 0;
    interiorCounter = 0;
    boundaryPicesCounter =0; //part in the boundary use to draw the perimeter
    tokenSize = 0;
    
    numberOfVerticesConnectedTo=0;
    
}

ReadSRF::~ReadSRF()
{
   VertexLocation = (VerticesOutput *)malloc(1000*sizeof(VerticesOutput)); //another way of initializing that is dynamic
}

void ReadSRF::init()
{

}

int * ReadSRF::getVerticesConnectedTo(int idl, VerticesOutput* vert)
{
    int* temp = (int *)malloc(numberOfFacesInFile*sizeof(int));
    int j = 0;
    
    for(int i=0; i<numberOfFacesInFile  ; i++)
    {
         //cout << "i: " <<i << "\t";
        if(idl == vert[i].id1)
        {
            temp[j]= vert[i].id2;
            temp[j+1]= vert[i].id3;
            D(
              cout << "idl: " <<idl << "\t";
              cout << "connection 1: " << temp[j] << "\t";
              cout << "connection 2: " << temp[j+1] << "\n" ;
              )

            j=j+2;
        }
        else if(idl == vert[i].id2)
        {
            temp[j]= vert[i].id1;
            temp[j+1]= vert[i].id3;

             D(
               cout << "idl: " <<idl << "\t";
               cout << "connection 1: " << temp[j] << "\t";
               cout << "connection 2: " << temp[j+1] << "\n" ;
               )

            j=j+2;
        }
        else if (idl == vert[i].id3)
        {
            
            temp[j]= vert[i].id1;
            temp[j+1]= vert[i].id2;

            D(
              cout << "idl: " <<idl << "\t";
              cout << "connection 1: " << temp[j] << "\t";
              cout << "connection 2: " << temp[j+1] << "\n" ;
              )

            j=j+2;
        }
       

        
    }
    numberOfVerticesConnectedTo = j;
    return temp;
}

int* ReadSRF::getVerticesConnectedInOrder (int* vert)
{
    int* tmp = (int *)malloc(numberOfVerticesConnectedTo*sizeof(int));
    std::set<int> s;
    for(int i=0; i< numberOfVerticesConnectedTo; i++)
    {
        D(cout << "values: " << vert[i] << "\n";)
        s.insert(vert[i]);
    }
    
    for (auto i : s){
        D(cout << " - values: " << i << "\n";)
        //of << i << '\n';
        tmp[i]=i;
    }
    
    return tmp;
}

void ReadSRF::ReadSRFFile(const char* file)
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
            bool foundGF = false;
            bool foundF = false;
            
            
            while ( getline (myfile,line) && foundGF ==false)
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
                else if (tokens[0] == "GE" )
                {
                    D( cout << "FOUND GE" << '\n'; )
                    for(int i=2;i<tokens.size();i++){
                         D(cout << "numer of tokens:" << tokens[i] <<'\n';)
                        tempValue = tokens[i];
                        boundary[boundarySize] = stoi(tempValue, &sz);
                        tokenSize = (int)tokens.size(); //used to create the perimeter
                        boundarySize++;
                        
                        
                        
                    }
                                    
                    boundaryPicesCounter++;
                    foundGE = true;
                }
                else if (tokens[0] == "GF" )
                {
                    D(cout << "FOUND GF" << '\n';)
                    foundGF = true;
                }
                else if (tokens[0] == "E")
                {
                    D(cout << "FOUND EDGE" << '\n';)

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
                    D(cout << "FOUND NORMAL" << '\n';)
                    
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
        
        
        VertexLocation = vert; //
        
        numberOfVerticesInFile = vertexCounter;
        numberOfFacesInFile = faceCounter;
        
        cout << "numberOfVerticesInFile: " << numberOfVerticesInFile << '\n';
        cout << "numberOfFacesInFile: " << numberOfFacesInFile << '\n';
        cout << "Boundary members: " << boundarySize << '\n';
        
        cout << "----------------------------------" <<  '\n';
        
        D(
        for(int i =0; i< boundarySize ; i++)
        {
            cout << i <<  "  Boundary members:  " << boundary[i] << '\n';
            
        }
        )
        for(int i=0; i<numberOfVerticesInFile; i++)
        {
            for(int j=0; j<boundarySize; j++)
            {
               
                if(boundary[j]==i)
                {
                    
                   D( cout << "Boundary contained in [ "<< j << "]: "<< boundary[j] << "\n";)
                    boundaryCounter++;
                    break;
                }
           
                
            }
            if(i>= boundaryCounter)
            {
                interior[i-boundaryCounter] = i;
                D(cout << "Interior points in [ "<<  i << "]: "<< interior[i-boundaryCounter]<< "\n";)
                
                interiorCounter++;
            }
            
            
        }
        
        
        D(cout << "----------------------------------" <<  '\n';)
        cout << "Interior Counter " << interiorCounter<< '\n';
        cout << "Boundary Counter " << boundaryCounter << '\n';
        
       
 
        
    }
    
    catch (...)
    {
        cout << "Exception ocurred";
        
    }
    
    
    
}