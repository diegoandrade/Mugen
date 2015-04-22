//
//  VectorRepresentationOGL.cpp
//  Mugen
//
//  Created by Diego Andrade on 4/2/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#undef DEBUG
//#define DEBUG

#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG


#include "VectorRepresentationOGL.h"

VectorRepresentationOGL::VectorRepresentationOGL()
{
    
    
}

VectorRepresentationOGL::~VectorRepresentationOGL()
{
    
}

void VectorRepresentationOGL::getPoints(const char* file)
{
   
    objRSRF->ReadSRFFile(file);
    vertexLocation = (VerticesOutput *)malloc(objRSRF->numberOfVerticesInFile *sizeof(VerticesOutput)); //using previously open files, make sure this do not explode
    
    for(int i=0; i< objRSRF->numberOfVerticesInFile; i++)
    {
        vertexLocation[i] = objRSRF->VertexLocation[i];
    }
    
}

void VectorRepresentationOGL::getVectors(const char* fileName)
{
    
    getPoints(fileName);
    objNRoSyVer =(VerticesOutput *)malloc(objRSRF->numberOfVerticesInFile*sizeof(VerticesOutput)); //AQUI majke sure the size is correct
    
    int numVerts, N;
    FILE *inFile;
    float Ka, Kb, Kc;
    
    inFile = fopen(fileName, "r");
    if(inFile == NULL)
        return;
        
    fscanf(inFile, "%d %d\n", &numVerts, &N);
    if(numVerts != objRSRF->numberOfVerticesInFile){
        //writeLine("Error: file mismatch.");
        cout << "Error: file mismatch." << endl;
        cout << "Number of Vertices: " << numVerts << endl;
        cout << "Number of Vertices InFIle: " << objRSRF->numberOfVerticesInFile <<endl;
        return;
    }

    
    for(int i = 0; i < numVerts; i++){
        //Vertex *vert = verts[i];
        
        fscanf(inFile, "%f %f %f\n",
               &Ka,
               &Kb,
               &Kc);
        
        Vector3D K3D(Ka, Kb, Kc);
        objNRoSyVer[i].x = Ka;
        objNRoSyVer[i].y = Kb;
        objNRoSyVer[i].z = Kc;
        
        D( cout << i+1 << " Ka: " << Ka << "\tKb: " << Kb << "\tKc: " << Kc << endl);
        

    }
    
    fclose(inFile);
    
    
}
