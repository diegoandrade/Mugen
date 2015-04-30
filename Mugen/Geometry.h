//
//  Geometry.h
//  Mugen
//
//  Created by Diego Andrade on 4/30/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#ifndef __Mugen__Geometry__
#define __Mugen__Geometry__

#include <stdio.h>
#include "Vector3D.h"
#include "ysdef.h"



////////////////////////////////////////////////////////////
/*! An Euler-angle class.  It represents a rotation by three angles, heading, pitch, and bank.
 Heading angle defines a rotation in XZ plane.  Pitch angle defines a elevation angle from XZ plane,
 or the rotation about the object's own X axis, and ranges from -PI/2 to +PI/2.  Bank angle
 defines a rotation about the object's own Z axis.
 
 The orientation of the heading rotation depends on the global variable YsCoordSysModel.
 When the coordinate system model is a right-hand coordinate system (such as OpenGL's coordinate
 system) the heading rotation is a clockwise rotation in XZ plane (X goes to the right and Z
 goes up).  Or, if the coordinate system model is a left-hand coordinate sytem (such as Direct3D's
 coordinate system) the heading rotation is a counter-clockwise rotation in XZ plane.
 
 Since positive-Z direction flips between typical left-hand and right-hand coordinate systems,
 from the viewer, the heading rotation appears to be the same regardless of the coordinante system
 model.
 
 Bank angle is often also called as roll angle.  However, in aviation terminology, roll is
 often used as a rotational velocity and bank is an angle from the horizon.  Therefore, here
 I use bank angle instead of roll angle.
 
 \sa operator*(const YsAtt3 &att,const YsVec3 &vec)
 \sa operator*(const YsMatrix3x3 &mat,const YsAtt3 &att)
 \sa operator*(const YsAtt3 &att,const YsMatrix3x3 &mat)
 \sa operator*(const YsMatrix4x4 &mat,const YsAtt3 &att)
 \sa operator*(const YsAtt3 &att,const YsMatrix4x4 &mat)
 \sa operator==(const YsAtt3 &a,const YsAtt3 &b)
 \sa operator!=(const YsAtt3 &a,const YsAtt3 &b)
 \sa YsCoordSysModel
 */
class YsAtt3
{
public:
    /*! Default constructor.  Does nothing. */
    inline YsAtt3(){}
    /*! A constructor that takes heading, pitch, and bank angles.
	    \param h [In] Heading angle in radian
	    \param p [In] Pitch angle in radian
	    \param b [In] Bank angle in radian */
    YsAtt3(const double &h,const double &p,const double &b);
    
    /*! Returns heading angle */
    inline double h(void) const
    {
        return hdg;
    }
    /*! Returns pitch angle */
    inline double p(void) const
    {
        return pch;
    }
    /*! Returns bank angle */
    inline double b(void) const
    {
        return bnk;
    }
    /*! Sets all three angles */
    void Set(const double &h,const double &p,const double &b);
    /*! Sets heading angle */
    void SetH(const double &h);
    /*! Sets pitch angle */
    void SetP(const double &p);
    /*! Sets bank angle */
    void SetB(const double &b);
    /*! Sets heading angle */
    void AddH(const double &h);
    /*! Sets pitch angle */
    void AddP(const double &p);
    /*! Sets bank angle */
    void AddB(const double &b);
    /*! Returns a forward vector */
    Vector3D GetForwardVector(void) const;
    /*! Returns a upward vector */
    Vector3D GetUpVector(void) const;
    /*! Calculates Euler angle based on the forward vector and upward vector. */
    YSRESULT SetTwoVector(const Vector3D &fwd,const Vector3D &up);
    /*! Calculates heading and pitch angles based on the forward vector.  Bank angle will be set to zero. */
    YSRESULT SetForwardVector(Vector3D vec);
    /*! Calculates bank angle based on the given upward vector.  Heading and pitch angles will not change. */
    YSRESULT SetUpVector(Vector3D up);
    

    
    /*! Rotates a vector.
	    \param to [Out] Output vector
	    \param from [In] Input vector
	    */
    inline void Mul(Vector3D &to,const Vector3D &from) const
    {
        to=from;
        
        to.RotateXY(bnk);
        to.RotateYZ(pch);  // RotateZY(-pch);
        to.RotateXZ(-hdg);
    }
    
    /*! Inversely rotates a vector.
	    \param to [Out] Output vector
	    \param from [In] Input vector
	    */
    inline void MulInverse(Vector3D &to,const Vector3D &from) const
    {
        to=from;
        to.RotateXZ(hdg);
        to.RotateYZ(-pch);  // RotateZY(pch);
        to.RotateXY(-bnk);
    }
    
    /*! Rotates about the object's own X axis */
    void NoseUp(const double &d);
    /*! Rotates about the object's own Y axis counter clockwise */
    void YawLeft(const double &d);
    
    /*! Converts the Euler angle to a 4x4 matrix */
    inline const YsMatrix4x4 &GetMatrix4x4(YsMatrix4x4 &mat) const
    {
        mat.Initialize();
        switch(YsCoordSysModel)
        {
            case YSBLUEIMPULSE:
                mat.RotateXZ(hdg);
                mat.RotateZY(pch);
                mat.RotateXY(bnk);
                break;
            case YSOPENGL:
                mat.RotateXZ(-hdg);
                mat.RotateZY(-pch);
                mat.RotateXY(bnk);
                break;
        }
        return mat;
    }
    
    /*! Converts the Euler angle to a 3x3 matrix */
    inline const YsMatrix3x3 &GetMatrix3x3(YsMatrix3x3 &mat) const
    {
        mat.Initialize();
        switch(YsCoordSysModel)
        {
            case YSBLUEIMPULSE:
                mat.RotateXZ(hdg);
                mat.RotateZY(pch);
                mat.RotateXY(bnk);
                break;
            case YSOPENGL:
                mat.RotateXZ(-hdg);
                mat.RotateZY(-pch);
                mat.RotateXY(bnk);
                break;
        }
        return mat;
    }
    
    /// \cond
protected:
    double hdg,pch,bnk;
    /// \endcond
};

/*! Rotates a vector by the rotation defined by the Euler angle. */
inline Vector3D operator*(const YsAtt3 &att,const Vector3D &vec)
{
    Vector3D r;
    att.Mul(r,vec);
    return r;
}

/*! Multiplies a 3x3 matrix and the rotation defined by the Euler angle and returns a 3x3 matrix. */
inline YsMatrix3x3 operator*(const YsMatrix3x3 &mat,const YsAtt3 &att)
{
    YsMatrix3x3 r(YSFALSE);
    r=mat;
    r.Rotate(att);
    return r;
}

/*! Multiplies the rotation defined by the Euler angle and a 3x3 matrix and returns a 3x3 matrix. */
inline YsMatrix3x3 operator*(const YsAtt3 &att,const YsMatrix3x3 &mat)
{
    YsMatrix3x3 r(YSFALSE);
    att.GetMatrix3x3(r);
    r=r*mat;
    return r;
}

/*! Multiplies a 4x4 matrix and the rotation defined by the Euler angle and returns a 3x3 matrix. */
inline YsMatrix4x4 operator*(const YsMatrix4x4 &mat,const YsAtt3 &att)
{
    YsMatrix4x4 r(YSFALSE);
    r=mat;
    r.Rotate(att);
    return r;
}

/*! Multiplies the rotation defined by the Euler angle and a 4x4 matrix and returns a 3x3 matrix. */
inline YsMatrix4x4 operator*(const YsAtt3 &att,const YsMatrix4x4 &mat)
{
    YsMatrix4x4 r(YSFALSE);
    att.GetMatrix4x4(r);
    r=r*mat;
    return r;
}

/*! Compares two Euler angles. */
inline int operator==(const YsAtt3 &a,const YsAtt3 &b)
{
    return (YsEqual(a.h(),b.h())==YSTRUE && YsEqual(a.p(),b.p())==YSTRUE && YsEqual(a.b(),b.b())==YSTRUE);
}

/*! Compares two Euler angles. */
inline int operator!=(const YsAtt3 &a,const YsAtt3 &b)
{
    return (YsEqual(a.h(),b.h())!=YSTRUE || YsEqual(a.p(),b.p())!=YSTRUE || YsEqual(a.b(),b.b())!=YSTRUE);
}

inline void YsMatrix4x4::Multiply(const class YsVec3 &pos,const class YsAtt3 &att)
{
    Translate(pos);
    RotateXZ(att.h());
    RotateZY(att.p());
    RotateXY(att.b());
}

#endif /* defined(__Mugen__Geometry__) */