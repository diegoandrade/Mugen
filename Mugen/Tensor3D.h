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

class Tensor3D
{
    
    
protected:
    double value[6];
    
public:
    inline Tensor3D();
    inline Tensor3D(double m0, double m1, double m2,double m3, double m4, double m5);
    inline Tensor3D(double a0, double b0, double c0);
    inline Tensor3D(const Tensor3D &a);
    inline void Set(const double &m0, const double &m1, const double &m2, const double &m3, const double &m4, const double &m5);
    
    
    inline Tensor3D &set(double a0, double b0,double c0);
    
    inline Tensor3D &set(const Tensor3D &t);
    
    inline Tensor3D &operator=(const Tensor3D &t);
    
    inline int operator==(const Tensor3D &t) const;
    inline int operator!=(const Tensor3D &t) const;
    
    inline Tensor3D &operator+=(const Tensor3D &t);
    inline Tensor3D &operator-=(const Tensor3D &t);
    inline Tensor3D &operator*=(const Tensor3D &t);
    inline Tensor3D &operator/=(const Tensor3D &t);
    
    union{
        struct{
            double m0, m1, m2,m3,m4,m5;
        };
        
        double A[3][3];
        double R[3][3];
    
    };
    
};

inline Tensor3D::Tensor3D() {
    m0 = m1 = m2 = m3 = m4 = m5 = 0.0;
}

//-------------------------------------------------------------------

inline Tensor3D operator-(const Tensor3D &t) {
    return Tensor3D(-t.m0,-t.m1,-t.m2,-t.m3,-t.m4,-t.m5);
}


inline Tensor3D &Tensor3D::operator=(const Tensor3D &t) {
    return set(t);
}


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
