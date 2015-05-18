#ifndef INC_Vector3D_H
#define INC_Vector3D_H

#include <math.h>

class Vector3D{
    
    
protected:
    double value[3];
    //double value2[2];
    
public:
    inline Vector3D();
    inline Vector3D(double d);
    inline Vector3D(double a0, double b0, double c0);
    inline Vector3D(const Vector3D &a);
    inline Vector3D(const double *a);
    inline void Set(const double &x,const double &y,const double &z);
    
    inline Vector3D &set(double a0, double b0,double c0);
    
    inline Vector3D &set(const Vector3D &v);
    inline Vector3D &set(const double d);
    inline Vector3D &set(const double *v);
    
    inline Vector3D &operator=(const Vector3D &v);
    inline Vector3D &operator=(const double d);
    inline Vector3D &operator=(const double *a);
    
    inline int operator==(const Vector3D &v) const;
    inline int operator!=(const Vector3D &v) const;
    inline int operator==(double d) const;
    inline int operator!=(double d) const;
    
    inline Vector3D &operator+=(double d);
    inline Vector3D &operator-=(double d);
    inline Vector3D &operator*=(double d);
    inline Vector3D &operator/=(double d);
    
    inline Vector3D &operator+=(const Vector3D &v);
    inline Vector3D &operator-=(const Vector3D &v);
    inline Vector3D &operator*=(const Vector3D &v);
    inline Vector3D &operator/=(const Vector3D &v);
    inline double length(const Vector3D &v);
    inline void normalize(Vector3D &a);
    
    inline Vector3D setMinTo1();
    
    inline double dot(const Vector3D &v, const Vector3D &b);
    inline Vector3D cross(const Vector3D &v);
    
    inline double x(void) const;
    inline double y(void) const;
    inline double z(void) const;
    
    inline void RotateXY(const double &ang);
    inline void RotateYX(const double &ang);
    
    inline void RotateXZ(const double &ang);
    inline void RotateZX(const double &ang);
    
    inline void RotateYZ(const double &ang);
    inline void RotateZY(const double &ang);

    inline void SetX(const double &x);
    inline void SetY(const double &y);
    inline void SetZ(const double &z);
    
    inline void Set(const char x[],const char y[],const char z[]);
    
    union{
        struct{
            double a, b, c;
        };
        struct{
            double x1, y1, z1;
        };
       
        //double elements[3];
    };
    



    
};



inline Vector3D operator-(const Vector3D &v);

inline Vector3D operator+(const Vector3D &v, const Vector3D &u);
inline Vector3D operator-(const Vector3D &v, const Vector3D &u);

inline Vector3D operator+(const Vector3D &v, double b);
inline Vector3D operator-(const Vector3D &v, double b);
inline Vector3D operator*(const Vector3D &v, double b);
inline Vector3D operator/(const Vector3D &v, double b);

inline Vector3D operator+(double a, const Vector3D &u);
inline Vector3D operator-(double a, const Vector3D &u);
inline Vector3D operator*(double a, const Vector3D &u);

inline double length(const Vector3D &v);
inline void normalize(Vector3D &v);

inline double dot(const Vector3D &v,const Vector3D &u);
inline Vector3D cross(const Vector3D &v, const Vector3D &u);

inline Vector3D rotate(double angle, Vector3D axis, Vector3D v);

inline Vector3D::Vector3D() {
    a = b = c = 0.0;
}

inline Vector3D::Vector3D(double d) {
    a = b = c = d;
}

inline Vector3D::Vector3D(double a0,double b0, double c0) {
    a = a0;
    b = b0;
    c = c0;
}

inline Vector3D::Vector3D(const Vector3D &v) {
    a = v.a;
    b = v.b;
    c = v.c;
}

inline Vector3D::Vector3D(const double *v) {
    a = v[0];
    b = v[1];
    b = v[2];
}

inline void Vector3D::Set(const double &x,const double &y,const double &z)
{
    value[0]=x;
    value[1]=y;
    value[2]=z;
}




//-------------------------------------------------------------------


inline Vector3D &Vector3D::set(double a0, double b0, double c0) {
    a = a0;
    b = b0;
    c = c0;
    return (*this);
}

inline Vector3D &Vector3D::set(double d) {
    a = b = c = d;
    return (*this);
}

inline Vector3D &Vector3D::set(const Vector3D &v) {
    a = v.a;
    b = v.b;
    c = v.c;
    return (*this);
}

inline Vector3D &Vector3D::set(const double *v) {
    a = v[0];
    b = v[1];
    c = v[2];
    return (*this);
}

inline Vector3D operator-(const Vector3D &v) {
    return Vector3D(-v.a, -v.b, -v.c);
}


inline Vector3D &Vector3D::operator=(const Vector3D &v) {
    return set(v);
}

inline Vector3D &Vector3D::operator=(const double *v) {
    return set(v);
}

inline Vector3D &Vector3D::operator=(const double d) {
    return set(d);
}

inline Vector3D Vector3D::setMinTo1(){
    Vector3D tmp(*this);
    
    double min = a;
    int i = 0;
    if(b < min){
        min = b;
        i = 1;
    }
    if(c < min){
        min = c;
        i = 2;
    }
    
    if(i == 0)
        tmp.a = 1.0;
    else if(i == 1)
        tmp.b = 1.0;
    else if(i == 2)
        tmp.c = 1.0;
    
    return tmp;
}

//-------------------------------------------------------------------

inline int Vector3D::operator==(const Vector3D &v) const {
    return ((a == v.a) && (b == v.b) && (c == v.c));
}

inline int Vector3D::operator!=(const Vector3D &v) const {
    return ((a != v.a) || (b != v.b) || (c != v.c));
}

inline int Vector3D::operator==(double d) const {
    return ((a == d) && (b == d) && (c == d));
}

inline int Vector3D::operator!=(double d) const {
    return ((a != d) || (b != d) || (c != d));
}

//-------------------------------------------------------------------

inline Vector3D &Vector3D::operator+=(double d) {
    a += d;
    b += d;
    c += d;
    return (*this);
}

inline Vector3D &Vector3D::operator-=(double d) {
    a -= d;
    b -= d;
    c -= d;
    return (*this);
}

inline Vector3D &Vector3D::operator*=(double d) {
    a *= d;
    b *= d;
    c *= d;
    return (*this);
}

inline Vector3D &Vector3D::operator+=(const Vector3D &v) {
    a += v.a;
    b += v.b;
    c += v.c;
    return (*this);
}

inline Vector3D &Vector3D::operator-=(const Vector3D &v) {
    a -= v.a;
    b -= v.b;
    c -= v.c;
    return (*this);
}

inline Vector3D &Vector3D::operator*=(const Vector3D &v) {
    a *= v.a;
    b *= v.b;
    c *= v.c;
    return (*this);
}

//-------------------------------------------------------------------

inline Vector3D operator+(const Vector3D &v,const Vector3D &u) {
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

inline double length(const Vector3D &v) {
    return sqrt(v.a * v.a + v.b * v.b + v.c * v.c);
}

inline void normalize(Vector3D &v) {
    double m = length(v);
    if (m != 0.0) v *= (1/m);
}

inline double dot(const Vector3D &v,const Vector3D &u) {
    return (v.a * u.a + v.b * u.b + v.c * u.c);
}

inline Vector3D cross(const Vector3D &v, const Vector3D &u) {
    //return Vector3D(v.b * u.c - v.c * u.b, 
    //			 v.c * u.a - v.a * u.c,
    //			 v.a * u.b - v.b * u.a);
    
    Vector3D result(v.b * u.c - v.c * u.b, 
                   v.c * u.a - v.a * u.c,
                   v.a * u.b - v.b * u.a);
    return result;
}

inline Vector3D rotate(double angle, Vector3D axis, Vector3D v){
    return Vector3D(0.0);
}



#endif