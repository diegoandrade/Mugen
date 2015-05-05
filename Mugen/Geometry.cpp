//
//  Geometry.cpp
//  Mugen
//
//  Created by Diego Andrade on 4/30/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include "Geometry.h"
#include "ysgeometry.h"

////////////////////////////////////////////////////////////
// Implementation //////////////////////////////////////////
YsAtt3::YsAtt3(const double &h,const double &p,const double &b)
{
    Set(h,p,b);
}

void YsAtt3::Set(const double &h,const double &p,const double &b)
{
    hdg=h;
    pch=p;
    bnk=b;
}

void YsAtt3::SetH(const double &h)
{
    hdg=h;
}

void YsAtt3::SetP(const double &p)
{
    pch=p;
}

void YsAtt3::SetB(const double &b)
{
    bnk=b;
}

void YsAtt3::AddH(const double &h)
{
    hdg+=h;
}

void YsAtt3::AddP(const double &p)
{
    pch+=p;
}

void YsAtt3::AddB(const double &b)
{
    bnk+=b;
}

YsVec3 YsAtt3::GetForwardVector(void) const
{
    YsVec3 vec;
    vec.Set(0.0,0.0,-1.0);
    Mul(vec,vec);
    return vec;
}

YsVec3 YsAtt3::GetUpVector(void) const
{
    YsVec3 vec;
    vec.Set(0.0,1.0,0.0);
    Mul(vec,vec);
    return vec;
}

YSRESULT YsAtt3::SetTwoVector(const YsVec3 &fwd,const YsVec3 &up)
{
    SetForwardVector(fwd);
    SetUpVector(up);
    return YSOK;
}

YSRESULT YsAtt3::SetForwardVector(YsVec3 ev)
{
    
    if(ev.y()>1.0)   // 2002/02/05
    {
        ev.SetY(1.0);
    }
    else if(ev.y()<-1.0)
    {
        ev.SetY(-1.0);
    }
    
    hdg=atan2(-ev.x(),-ev.z());
    pch=asin(ev.y());
    bnk=0.0;
    
    return YSOK;
}

YSRESULT YsAtt3::SetUpVector(YsVec3 uv)
{
    if(uv.IsNormalized()!=YSTRUE)
    {
        uv.Normalize();
    }
    
    SetB(0.0);
    
    MulInverse(uv,uv);
    
    double dBnk=0.0;
            dBnk=atan2(-uv.x(),uv.y());
    SetB(dBnk);
    
    return YSOK;
}

void YsAtt3::NoseUp(const double &d)
{
    YsVec3 fwd,up;
    fwd.Set(0.0,sin(d),-cos(d));
    up.Set (0.0,cos(d), sin(d));
    Mul(fwd,fwd);
    Mul(up,up);
 //   SetTwoVector(fwd,up);
}

void YsAtt3::YawLeft(const double &d)
{
    YsVec3 fwd,up;
    fwd.Set(-sin(d),0.0,-cos(d));
    up.Set (0.0,1.0,0.0);
    Mul(fwd,fwd);
    Mul(up,up);
  //  SetTwoVector(fwd,up);
}
