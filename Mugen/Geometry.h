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
#include "ysgeometry.h"



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
    
    double hdg,pch,bnk;
    
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
    inline void Set(const double &h,const double &p,const double &b);
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
    YsVec3 GetForwardVector(void) const;
    /*! Returns a upward vector */
    YsVec3 GetUpVector(void) const;
    /*! Calculates Euler angle based on the forward vector and upward vector. */
    YSRESULT SetTwoVector(const YsVec3 &fwd,const YsVec3 &up);
    /*! Calculates heading and pitch angles based on the forward vector.  Bank angle will be set to zero. */
    YSRESULT SetForwardVector(YsVec3 vec);
    /*! Calculates bank angle based on the given upward vector.  Heading and pitch angles will not change. */
    YSRESULT SetUpVector(YsVec3 up);
    
    inline void Mul(YsVec3 &to,const YsVec3 &from) const
    {
        to=from;
        to.RotateXY(bnk);
        to.RotateYZ(pch);  // RotateZY(-pch);
        to.RotateXZ(-hdg);
    }
    
    inline void MulInverse(YsVec3 &to,const YsVec3 &from) const
    {
        to=from;
        to.RotateXZ(hdg);
        to.RotateYZ(-pch);  // RotateZY(pch);
        to.RotateXY(-bnk);
    }

    void NoseUp(const double &d);
    void YawLeft(const double &d);
    
};


#endif /* defined(__Mugen__Geometry__) */