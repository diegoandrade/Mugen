//
//  Vector3D.cpp
//  Mugen
//
//  Created by Diego Andrade on 4/2/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Vector3D.h"

/*! Returns X component */
inline double Vector3D::x() const // 2001/04/17 : Don't make it const double &
{
    return value[0];
}
/*! Returns Y component */
inline double Vector3D::y(void) const  // 2001/04/17 : Don't make it const double &
{
    return value[1];
}
/*! Returns Z component */
inline double Vector3D::z(void) const  // 2001/04/17 : Don't make it const double &
{
    return value[2];
}

/*! Rotates the vector in XY plane (X goes to the right, Y goes up)
 counter clockwise. */
inline void Vector3D::RotateXY(const double &ang)
{
    double c,s,xx,yy;
    c=cos(ang);
    s=sin(ang);
    xx=x()*c-y()*s;
    yy=x()*s+y()*c;
 //   SetX(xx);
  //  SetY(yy);
}
/*! Rotates the vector in XY plane (X goes to the right, Y goes up)
 clockwise. */
inline void Vector3D::RotateYX(const double &ang)
{
    RotateXY(-ang);
}
/*! Rotates the vector in XZ plane (X goes to the right, Z goes up)
 counter clockwise. */
inline void Vector3D::RotateXZ(const double &ang)
{
    double c,s,xx,zz;
    c=cos(ang);
    s=sin(ang);

    xx=x()*c-z()*s;
    zz=x()*s+z()*c;
    SetX(xx);
    SetZ(zz);
}
/*! Rotates the vector in XZ plane (X goes to the right, Z goes up)
 clockwise. */
inline void Vector3D::RotateZX(const double &ang)
{
    RotateXZ(-ang);
}
/*! Rotates the vector in YZ plane (Y goes to the right, Z goes up)
 counter clockwise. */
inline void Vector3D::RotateYZ(const double &ang)
{
    double c,s,yy,zz;
    c=cos(ang);
    s=sin(ang);
    yy=y()*c-z()*s;
    zz=y()*s+z()*c;
    SetY(yy);
    SetZ(zz);
}
/*! Rotates the vector in YZ plane (Z goes to the right, Y goes up)
 counter clockwise. */
inline void Vector3D::RotateZY(const double &ang)
{
    RotateYZ(-ang);
}

/*! Sets X component */
inline void Vector3D::SetX(const double &x)
{
    value[0]=x;
}
/*! Sets Y component */
inline void Vector3D::SetY(const double &y)
{
    value[1]=y;
}
/*! Sets Z component */
inline void Vector3D::SetZ(const double &z)
{
    value[2]=z;
}

void Vector3D::Set(const char x[],const char y[],const char z[])
{
    value[0]=atof(x);
    value[1]=atof(y);
    value[2]=atof(z);
}

