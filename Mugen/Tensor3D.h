//
//  Tensor3D.h
//  Mugen
//
//  Created by Diego Andrade on 5/12/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__Tensor3D__
#define __Mugen__Tensor3D__

#include <stdio.h>
#include <iomanip>
#include <limits>
#include <iostream>
#include <math.h>
#include "Vector3D.h"

#include "Common.h"

using namespace std;

class Tensor3D
{
    
    
protected:
    //double value[6];
    
public:
    inline Tensor3D();
   // inline Tensor3D(double m0, double m1, double m2,double m3, double m4, double m5);
    inline Tensor3D(double a0, double b0, double c0);
   // inline Tensor3D(const Tensor3D &a);
    inline void Set(const double &m0, const double &m1, const double &m2, const double &m3, const double &m4, const double &m5);
    
    
    inline Tensor3D &set(double a0, double b0,double c0);
    
  //  inline Tensor3D &set(const Tensor3D &t);
    
    inline Tensor3D &operator=(const Tensor3D &t);
    
    inline int operator==(const Tensor3D &t) const;
    inline int operator!=(const Tensor3D &t) const;
    
    inline Tensor3D &operator+=(const Tensor3D &t);
    inline Tensor3D &operator-=(const Tensor3D &t);
    inline Tensor3D &operator*=(const Tensor3D &t);
    inline Tensor3D &operator/=(const Tensor3D &t);
    
    struct{
            double m0, m1, m2,m3,m4,m5;
        };
        
    double L[3][3];
    double R[3][3];
    
    void printTensor ();
    
    
    
};

inline Tensor3D::Tensor3D() {
    m0 = m1 = m2 = m3 = m4 = m5 = 0.0;
    L[0][0]=L[0][1]=L[0][2]=L[1][0]=L[1][1]=L[1][2]=L[2][0]=L[2][1]=L[2][2]=0.0;
    R[0][0]=R[0][1]=R[0][2]=R[1][0]=R[1][1]=R[1][2]=R[2][0]=R[2][1]=R[2][2]=0.0;
}

inline double length(double a, double b, double c)
{
    return sqrt(a*a+b*b+c*c);
    
}




//-------------------------------------------------------------------

/*inline Tensor3D operator-(const Tensor3D &t) {
    return Tensor3D(-t.m0,-t.m1,-t.m2,-t.m3,-t.m4,-t.m5);
}


inline Tensor3D &Tensor3D::operator=(const Tensor3D &t) {
    return set(t);
}*/


//-------------------------------------------------------------------

inline int Tensor3D::operator==(const Tensor3D &t) const {
    return ((m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0));
}

inline int Tensor3D::operator!=(const Tensor3D &t) const {
    return ((m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0) && (m0 == t.m0)); //((a != v.a) || (b != v.b) || (c != v.c));
}

//-------------------------------------------------------------------

inline Tensor3D &Tensor3D::operator+=(const Tensor3D &t) {
    m0 += t.m0;
   // b += v.b;
   // c += v.c;
    return (*this);
}
/*
inline Tensor3D &Tensor3D::operator-=(const Vector3D &t) {
    a -= v.a;
    b -= v.b;
    c -= v.c;
    return (*this);
}

inline Tensor3D &Tensor3D::operator*=(const Vector3D &t) {
    a *= v.a;
    b *= v.b;
    c *= v.c;
    return (*this);
}
 */

//-------------------------------------------------------------------

/*inline Vector3D operator+(const Vector3D &v,const Vector3D &u) {
    return Vector3D(v.a + u.a, v.b + u.b, v.c + u.c);
}

inline Vector3D operator-(const Vector3D &v,const Vector3D &u) {
    return Vector3D(v.a - u.a, v.b - u.b, v.c - u.c);
}

inline Vector3D operator+(const Vector3D &v,double b){
    return Vector3D(v.a + b, v.b + b, v.c + b);
}

inline Vector3D operator-(const Vector3D &v,double b){
    return Vector3D(v.a - b, v.b - b, v.c - b);
}

inline Vector3D operator*(const Vector3D &v,double b){
    return Vector3D(v.a * b, v.b * b, v.c * b);
}

inline Vector3D operator/(const Vector3D &v,double b){
    return Vector3D(v.a / b, v.b / b, v.c / b);
}

inline Vector3D operator+(double a,const Vector3D &u){
    return Vector3D(a + u.a, a + u.b, a + u.c);
}

inline Vector3D operator-(double a,const Vector3D &u){
    return Vector3D(a - u.a, a - u.b, a - u.c);
}

inline Vector3D operator*(double a,const Vector3D &u){
    return Vector3D(a * u.a, a * u.b, a * u.c);
}
*/



#endif /* defined(__Mugen__Tensor3D__) */
