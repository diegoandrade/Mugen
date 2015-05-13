//
//  matrix3x3.h
//  Mugen
//
//  Created by Diego Andrade on 5/6/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__matrix3x3__
#define __Mugen__matrix3x3__

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Vector3D.h"

using namespace std;

#define EPS 10e-08
#define tolerance 10e-10
#define maxiter 100000

#ifndef STATE_IS_DEFINED
#define YSBOOL_IS_DEFINED
/*! Enum for boolearn. */
typedef enum
{
    SUCESS,     /*!< False */
    WONTSTOP,      /*!< True */
    ITERATING  /*!< Unable to tell true or false. */
} STATE;
#endif

class matrix3x3
{
protected:
    double nRow,nColumn;
    
    double dat[9];
    


public:
    double M[3][3];

    inline int nr(void) const
    {
        return nRow;
    }
    inline int nc(void) const
    {
        return nColumn;
    }
    inline const double Abs(const double &a)
    {
        return (a>=0 ? a : -a);
    }
    
    matrix3x3();
    inline matrix3x3(double n, double m) {
        nRow=n;
        nColumn=m;
    }
    
    inline matrix3x3(double sq) {
        nRow=sq;
        nColumn=sq;
    }
    
    
//    {
//        evec[0] = from.evec[0];
//        evec[1] = from.evec[1];
//        evec[2] = from.evec[2];
//    }
    
    inline const double & v(int row,int column) const;
    void Set(int row,int column,const double &a);
    
    void SetMtx(int row,int column,const double &a);
    
    
    void LoadIdentity(void);
    
    
    //! set identity metric
//    inline void Initialize()
//    {
//        evec[0].Set(1.,0.,0.);
//        evec[1].Set(0.,1.,0.);
//        evec[2].Set(0.,0.,1.);
//        
//    }
    

    double GetDeterminant (double &det);
  //  inline double InitializeMatrix( double &v);
  //  inline double
    
    inline void JacobiFindAngle (double &cs,double &sn,const double &app,const double &aqq,const double &apq) const;
    inline void JacobiRotate(matrix3x3 &a,matrix3x3 &x, int p,int q,const double &cs,const double &sn) const;
    
    void FindEigenValueEigenVectorByJacobiMethod (matrix3x3 &value,matrix3x3 &vector,const double toleranceD);
    
    inline void Rotate (matrix3x3 &A,matrix3x3 &R, int p, int q );
    inline void Rotate (double A[3][3],double R[3][3], int p, int q );
    
    double sign(double val);
    inline double maxOffDiag (matrix3x3 &A, int &p, int &q);
    inline double maxOffDiag (double A[3][3], int &p, int &q);
    
    STATE jacrot (matrix3x3 &A,matrix3x3 &R);
    STATE jacrot (double A[3][3],double R[3][3]);
    void Transpose ();
    void Transpose (double R[3][3]);
    
    void printMtrx ();
    void printMtrx (double Mx[3][3]);


    
private:
    //Vector3D evec[3];


    
    
};





#endif /* defined(__Mugen__matrix3x3__) */
