//
//  matrix3x3.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/6/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include "matrix3x3.h"



matrix3x3::matrix3x3()
{
    /*for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            M[i][j]=0.0;
        }
    }*/
    
}

double matrix3x3::GetDeterminant(double &det)
{
    det=v(1,1)*(v(2,2)*v(3,3)-v(2,3)*v(3,2))
    -v(1,2)*(v(2,1)*v(3,3)-v(2,3)*v(3,1))
    +v(1,3)*(v(2,1)*v(3,2)-v(2,2)*v(3,1));
    
    return det;
    
}

inline const double & matrix3x3::v(int row, int column) const
{
    int nColumnvar = 3;
    int nRowvar = 3;
    
    if(1<=row && row<=nRowvar && 1<=column && column<=nColumnvar)
    {
        return dat[(row-1)*nColumnvar+(column-1)];
    }
    else
    {
        cout << " matrix3x3::v()\n" << endl;
        cout << " Index out of range.  (Note : Row/Column begins with 1\n" << endl;
        return dat[0];
    }
    
}

void matrix3x3::Set(int row,int column,const double &a)
{
    int nColumnvar = 3;
    int nRowvar = 3;
    
    if(1<=row && row<=nRowvar && 1<=column && column<=nColumnvar)
    {
        dat[(row-1)*nColumnvar+(column-1)]=a;
        cout << " isOK\n" << endl;
    }
    else
    {
        cout << " matrix3x3::Set()\n" << endl;
        cout << " There is an Error\n" << endl;
    }
}

void matrix3x3::SetMtx(int row,int column,const double &a)
{
    M[row][column] = a;
}


// Jacobi Method
//    Reference
//    Terrence J. Akai, Applied Numerical Methods for Engineers, John Wiley & Sons, Inc, 1993
//    pp. 282-285

//
// Diagonal Elements of YsMatrixTemplate &value will contain eigen values
// Columns of YsMatrixTemplate &vector will contain eigen vectors of a corresponding eigen value of the same column.

inline void matrix3x3::JacobiFindAngle(double &cs, double &sn, const double &app, const double &aqq, const double &apq) const
{
    double alpha,delta;
    
    delta=app-aqq;
    alpha=sqrt(delta*delta+4*apq*apq);
    cs=sqrt((alpha+delta)/(2*alpha));
    sn=apq/(cs*alpha);
    cout << " isOK JacobiFindAngle\n" << endl;
}


inline void matrix3x3::JacobiRotate(matrix3x3 &a,matrix3x3 &x, int p,int q,const double &cs,const double &sn) const
{
    int k,n;
    double t1,t2;
    n=a.nr();
    for(k=1; k<=n; k++)
    {
        t1=a.v(p,k);
        a.Set(p,k, cs*t1+sn*a.v(q,k));
        a.Set(q,k,-sn*t1+cs*a.v(q,k));
    }
    for(k=1; k<=n; k++)
    {
        t1=a.v(k,p);
        t2=x.v(k,p);
        
        a.Set(k,p, cs*t1+sn*a.v(k,q));
        a.Set(k,q,-sn*t1+cs*a.v(k,q));
        x.Set(k,p, cs*t2+sn*x.v(k,q));
        x.Set(k,q,-sn*t2+cs*x.v(k,q));
    }
    
    cout << " isOK JacobiRotate\n" << endl;
    
    
}

void matrix3x3::FindEigenValueEigenVectorByJacobiMethod (matrix3x3 &value,matrix3x3 &vector,const double toleranceD)
{
    int p,q,n;
    p=q=n=0;
    bool done;
    double cs,sn;
    
    if(nr()==nc())
    {
        n=nr();
        
        value=(*this);
        vector.LoadIdentity();
        
        done=false;
        while(done!=true)
        {
            done=true;
            for(p=1; p<=n-1; p++)
            {
                for(q=p+1; q<=n; q++)
                {
                    
                    cout << "hola" << endl;
                    /*if(Abs(value.v(p,q))>tolerance) //abs????
                    {
                        done=false;
                        JacobiFindAngle(cs,sn,value.v(p,p),value.v(q,q),value.v(p,q));
                        JacobiRotate(value,vector,p,q,cs,sn);
                    }*/
                }
            }
        }
        cout << " isOK FindEigenValueEigenVectorByJacobiMethod\n" << endl;
    }
    else
    {
        cout << "FindEigenValueEigenVectorByJacobiMethod()\n" << endl;
        cout << "FindEigenValueEigenVectorByJacobiMethod()\n"<< endl;
    }
    
    
}

void matrix3x3::LoadIdentity(void)
{
    int i,j;
    for(i=1; i<=nRow; i++)
    {
        for(j=1; j<=nColumn; j++)
        {
            if(i==j)
            {
                Set(i,j,1.0);
            }
            else
            {
                Set(i,j,0.0);
            }
        }
    }
}

inline void matrix3x3::Rotate(matrix3x3 &A, matrix3x3 &R, int p, int q)
{
    int n = 3; // nr();
    double d = (A.M[p][p]-A.M[q][q])/(2.0*A.M[p][q]);  // d = cot 2θ
    double t = sign(d)/(fabs(d)+sqrt(d*d+1));       // t = tan θ
    double c = 1.0/sqrt(t*t + 1);                   // c = cos θ
    double s = t * c;                               // s = sin θ
    
    A.M[p][p] += t*A.M[p][q];
    A.M[q][q] -= t*A.M[p][q];
    A.M[p][q] = A.M[q][p] = 0.0;
    
    for(int k=0; k < n ; ++k)
    {
        if( k != p && k != q)
        {
            double Akp = c*A.M[k][p] + s*A.M[k][q];
            double Akq = -s*A.M[k][p] + c*A.M[k][q];
            A.M[k][p] = A.M[p][k] = Akp;
            A.M[k][q] = A.M[q][k] = Akq;
        }
    }
    for(int k=0; k < n ; ++k)
    {
        double Rkp = c*R.M[k][p] + s*R.M[k][q];
        double Rkq = -s*R.M[k][p] + c*R.M[k][q];
        R.M[k][p] = Rkp;
        R.M[k][q] = Rkq;
    }

}

inline void matrix3x3::Rotate(double A[3][3] , double R[3][3] , int p, int q)
{
    int n = 3; // nr();
    double d = (A[p][p]-A[q][q])/(2.0*A[p][q]);     // d = cot 2θ
    double t = sign(d)/(fabs(d)+sqrt(d*d+1));       // t = tan θ
    double c = 1.0/sqrt(t*t + 1);                   // c = cos θ
    double s = t * c;                               // s = sin θ
    
    A[p][p] += t*A[p][q];
    A[q][q] -= t*A[p][q];
    A[p][q] = A[q][p] = 0.0;
    
    for(int k=0; k < n ; ++k)
    {
        if( k != p && k != q)                       // transform A
        {
            double Akp =  c*A[k][p] + s*A[k][q];
            double Akq = -s*A[k][p] + c*A[k][q];
            A[k][p] = A[p][k] = Akp;
            A[k][q] = A[q][k] = Akq;
        }
    }
    for(int k=0; k < n ; ++k)                       // store rotation
    {
        double Rkp =  c*R[k][p] + s*R[k][q];
        double Rkq = -s*R[k][p] + c*R[k][q];
        R[k][p] = Rkp;
        R[k][q] = Rkq;
    }
    
}

double matrix3x3::sign(double val) {
    return (double(0) < val) - (val < double(0));
}

inline double matrix3x3::maxOffDiag(double A[3][3], int &p, int &q)
{
    int n = 3;
    double max = 0.0;
    
    for ( int i =0; i <n-1; ++i)
    {
        for ( int j = i+1; j < n ; ++j)
        {
            double Aij = fabs(A[i][j]);
            if(Aij > max)
            {
                max = Aij;
                p=i;
                q=j;
            }
        }
        
    }
    return max;
}

inline double matrix3x3::maxOffDiag(matrix3x3 &A, int &p, int &q)
{
    int n = 3;
    double max = 0.0;
    
    for ( int i =0; i <n-1; ++i)
    {
        for ( int j = i+1; j < n ; ++j)
        {
            double Aij = fabs(A.M[i][j]);
            if(Aij > max)
            {
                max = Aij;
                p=i;
                q=j;
            }
        }
        
        
    }
    return max;
}

STATE matrix3x3::jacrot(matrix3x3 &A, matrix3x3 &R)
//  final A is diagonal matric of eigenvalues
//  final R has eigenvectors in rows
{
    STATE S = ITERATING;
    int n = 3;
    for (int i=0; i< n ; ++i) R.M[i][i] = 1.0 ;//unit matrix
    int iter = 0;
    
    while ( S == ITERATING)
    {
        int p,q;
        double max = maxOffDiag(A,p,q);
        if(max > tolerance)
        {
            Rotate(A,R,p,q);
            ++iter;
            if (++iter == maxiter) S = WONTSTOP;
        } else
        {
            S = SUCESS;
            R.Transpose() ; //eigen vectors in rows
        }
    }
    cout << "iter " << iter << endl;
    printMtrx();
    
    return S;
    
    
}

STATE matrix3x3::jacrot(double A[3][3] , double R[3][3])
//  final A is diagonal matric of eigenvalues
//  final R has eigenvectors in rows
{
    STATE S = ITERATING;
    int n = 3;
    for (int i=0; i< n ; ++i) R[i][i] = 1.0 ;//unit matrix
    int iter = 0;
    
    while ( S == ITERATING)
    {
        int p,q;
        double max = maxOffDiag(A,p,q);
        if(max > tolerance)
        {
            Rotate(A,R,p,q);
            ++iter;
            if (++iter == maxiter) S = WONTSTOP;
        } else
        {
            S = SUCESS;
            Transpose(R) ; //eigen vectors in rows
        }
    }
    cout << "iter " << iter << endl;
    printMtrx(A);
    printMtrx(R);

    
    return S;
    
    
}

void matrix3x3::Transpose(double R[3][3])
{
    
    double dat[3][3];
    
    for (int i=0;i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            dat[i][j] = R[j][i];
        }
        
    }
    
    for (int i=0;i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            R[i][j] = dat[i][j];
        }
        
    }
    
}

void matrix3x3::Transpose()
{
    
    double dat[3][3];
    
    for (int i=0;i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            dat[i][j] = M[j][i];
        }
        
    }
    
    for (int i=0;i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            M[i][j] = dat[i][j];
        }
        
    }
    
}


void matrix3x3::printMtrx()
{
    for(int i = 0 ; i< 3; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            cout << "M[" << i << "][" << j << "]:\t" << M[i][j] << "\t" ;
        }
        cout << endl;
    }
    
}

void matrix3x3::printMtrx(double Mx[3][3])
{
    for(int i = 0 ; i< 3; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            cout << "M[" << i << "][" << j << "]:\t" << Mx[i][j] << "\t" ;
        }
        cout << endl;
    }
    
}
