#ifndef YSGEOMETRY_IS_INCLUDED
#define YSGEOMETRY_IS_INCLUDED
/* { */

#include <math.h>

#define YSMATHFAST  // This line disables Memory Leak Tracking

////////////////////////////////////////////////////////////


// Declaration /////////////////////////////////////////////
class YsVec2
{
public:
	inline YsVec2()
	{
	}
	inline YsVec2(const double &x,const double &y)
	{
		value[0]=x;
		value[1]=y;
	}

	// Added 2001/04/30 >>
	YsVec2(const char *x,const char *y);
	// Added 2001/04/30 <<

	// Added 2001/04/26 >>
	inline const double &operator[](int idx) const
	{
		return value[idx];
	}
	inline double &operator[](int idx)
	{
		return value[idx];
	}
	operator const double *() const
	{
		return GetValue();
	}
	const char *Txt(const char *fmt="%10.6lf %10.6lf") const;
	// Added 2001/04/26 <<

	// Added 2001/05/04 >>
	inline void AddX(const double &x)
	{
		value[0]+=x;
	}
	inline void AddY(const double &y)
	{
		value[1]+=y;
	}
	inline void SubX(const double &x)
	{
		value[0]-=x;
	}
	inline void SubY(const double &y)
	{
		value[1]-=y;
	}
	inline void MulX(const double &x)
	{
		value[0]*=x;
	}
	inline void MulY(const double &y)
	{
		value[1]*=y;
	}
	inline void DivX(const double &x)
	{
		value[0]/=x;
	}
	inline void DivY(const double &y)
	{
		value[1]/=y;
	}
	// Added 2001/05/04 <<


	inline double x(void) const  // 2001/04/17 : Don't make it const double &
	{
		return value[0];
	}
	inline double y(void) const  // 2001/04/17 : Don't make it const double &
	{
		return value[1];
	}
	inline const double *GetValue(void) const
	{
		return value;
	}
	inline void Get(double &x,double &y) const
	{
		x=value[0];
		y=value[1];
	}
	inline double GetSquareLength(void) const
	{
		return value[0]*value[0]+value[1]*value[1];
	}
	inline double GetLength(void) const
	{
		return (double)sqrt(GetSquareLength());
	}

/*	inline double L0Norm(void) const
	{
		return YsGreater(fabs(value[0]),fabs(value[1]));
	}
*/
	inline int GetLongestAxis(void) const
	{
		if(fabs(value[0])>fabs(value[1]))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	inline double GetLongestDimension(void) const
	{
		if(fabs(value[0])>fabs(value[1]))
		{
			return fabs(value[0]);
		}
		else
		{
			return fabs(value[1]);
		}
	}

	YSBOOL IsNormalized(void) const;
	YSRESULT Normalize(void);
	/*inline YSBOOL IsZeroVector(void) const
	{
		if(GetSquareLength()<YsToleranceSqr)
		{
			return YSTRUE;
		}
		else
		{
			return YSFALSE;
		}
	}*/
    
	inline void Set(const double &x,const double &y)
	{
		value[0]=x;
		value[1]=y;
	}
	inline void SetX(const double &x)
	{
		value[0]=x;
	}
	inline void SetY(const double &y)
	{
		value[1]=y;
	}
	inline void Set(const double v[2])
	{
		value[0]=v[0];
		value[1]=v[1];
	}
	inline void GetXY(const double *vec3)
	{
		value[0]=vec3[0];
		value[1]=vec3[1];
	}
	inline void GetXZ(const double *vec3)
	{
		value[0]=vec3[0];
		value[1]=vec3[2];
	}
	inline void Rotate(const double &ang)
	{
		double c,s,xx,yy;
		c=cos(ang);
		s=sin(ang);
		xx=x()*c-y()*s;
		yy=x()*s+y()*c;
		Set(xx,yy);
	}


	inline const YsVec2 &operator+=(const YsVec2 &a)
	{
		value[0]+=a.value[0];
		value[1]+=a.value[1];
		return *this;
	}
	inline const YsVec2 &operator-=(const YsVec2 &a)
	{
		value[0]-=a.value[0];
		value[1]-=a.value[1];
		return *this;
	}
	inline const YsVec2 &operator/=(double a)
	{
		value[0]/=a;
		value[1]/=a;
		return *this;
	}
	inline const YsVec2 &operator*=(double a)
	{
		value[0]*=a;
		value[1]*=a;
		return *this;
	}

protected:
	double value[2];
};

inline const YsVec2 operator-(const YsVec2 &a)
{
	return YsVec2(-a.x(),-a.y());
}

inline const YsVec2 operator-(const YsVec2 &a,const YsVec2 &b)
{
	return YsVec2(a.x()-b.x(),a.y()-b.y());
}

inline const YsVec2 operator+(const YsVec2 &a,const YsVec2 &b)
{
	return YsVec2(a.x()+b.x(),a.y()+b.y());
}

inline const YsVec2 operator/(const YsVec2 &a,const double &b)
{
	return YsVec2(a.x()/b,a.y()/b);
}

inline const YsVec2 operator*(const YsVec2 &a,const double &b)
{
	return YsVec2(a.x()*b,a.y()*b);
}

inline const YsVec2 operator*(const double &b,const YsVec2 &a)
{
	return YsVec2(a.x()*b,a.y()*b);
}

inline double operator*(const YsVec2 &a,const YsVec2 &b)
{
	return a.x()*b.x()+a.y()*b.y();
}

inline double operator^(const YsVec2 &a,const YsVec2 &b)
{
	// x1 y1
	// x2 y2
	double z;
	z=a.x()*b.y()-a.y()*b.x();
	return z;
}

inline int operator==(const YsVec2 &a,const YsVec2 &b)
{
	// Fixed 2000/11/10
	// return ((a-b).GetSquareLength()<YsTolerance);

	// Modified again 2000/11/10
	// if(YsEqual(a.x(),b.x())==YSTRUE &&
	//    YsEqual(a.y(),b.y())==YSTRUE)
	// {
	// 	return 1;
	// }
	// else
	// {
	// 	return 0;
	// }

    return 1;//((a-b).GetSquareLength()<YsSqr(YsTolerance));  // Modified 2000/11/10
}

inline int operator!=(const YsVec2 &a,const YsVec2 &b)
{
	// Fixed 2000/11/10
	// return ((a-b).GetSquareLength()>=YsTolerance);

	// Modified again 2000/11/10
	// if(YsEqual(a.x(),b.x())!=YSTRUE ||
	//    YsEqual(a.y(),b.y())!=YSTRUE)
	// {
	// 	return 1;
	// }
	// else
	// {
	// 	return 0;
	// }

    return 1; //((a-b).GetSquareLength()>=YsSqr(YsTolerance));  // Modified 2000/11/10
}


inline const YsVec2 &YsLonger(const YsVec2 &v1,const YsVec2 &v2)
{
	return (v1.GetSquareLength()>=v2.GetSquareLength() ? v1 : v2);
}


////////////////////////////////////////////////////////////

// Declaration /////////////////////////////////////////////
class YsVec3
{
public:
	inline YsVec3()
	{
	}
	inline YsVec3(const double &x,const double &y,const double &z)
	{
		value[0]=x;
		value[1]=y;
		value[2]=z;
	}
	YsVec3(const char *x,const char *y,const char *z);

	// Added 2001/04/26 >>
	inline const double &operator[](int idx) const
	{
		return value[idx];
	}
	inline double &operator[](int idx)
	{
		return value[idx];
	}
	operator const double *() const
	{
		return GetValue();
	}
	const char *Txt(const char *fmt="%10.6lf %10.6lf %10.6lf") const;
	// Added 2001/04/26 <<

	// Added 2001/05/04 >>
	inline void AddX(const double &x)
	{
		value[0]+=x;
	}
	inline void AddY(const double &y)
	{
		value[1]+=y;
	}
	inline void AddZ(const double &z)
	{
		value[2]+=z;
	}
	inline void SubX(const double &x)
	{
		value[0]-=x;
	}
	inline void SubY(const double &y)
	{
		value[1]-=y;
	}
	inline void SubZ(const double &z)
	{
		value[2]-=z;
	}
	inline void MulX(const double &x)
	{
		value[0]*=x;
	}
	inline void MulY(const double &y)
	{
		value[1]*=y;
	}
	inline void MulZ(const double &z)
	{
		value[2]*=z;
	}
	inline void DivX(const double &x)
	{
		value[0]/=x;
	}
	inline void DivY(const double &y)
	{
		value[1]/=y;
	}
	inline void DivZ(const double &z)
	{
		value[2]/=z;
	}
	// Added 2001/05/04 <<

	inline double x(void) const   // 2001/04/17 : Don't make it const double &
	{
		return value[0];
	}
	inline double y(void) const  // 2001/04/17 : Don't make it const double &
	{
		return value[1];
	}
	inline double z(void) const  // 2001/04/17 : Don't make it const double &
	{
		return value[2];
	}
	inline const double *GetValue(void) const
	{
		return value;
	}
	inline void Set(const double &x,const double &y,const double &z)
	{
		value[0]=x;
		value[1]=y;
		value[2]=z;
	}
	inline void SetX(const double &x)
	{
		value[0]=x;
	}
	inline void SetY(const double &y)
	{
		value[1]=y;
	}
	inline void SetZ(const double &z)
	{
		value[2]=z;
	}
	inline void SetXY(const YsVec2 &vec2)
	{
		value[0]=vec2[0];
		value[1]=vec2[1];
		value[2]=0.0;
	}
	inline void SetXZ(const YsVec2 &vec2)
	{
		value[0]=vec2[0];
		value[1]=0.0;
		value[2]=vec2[1];
	}
	inline void Set(const double v[3])
	{
		value[0]=v[0];
		value[1]=v[1];
		value[2]=v[2];
	}
	inline void Get(double &x,double &y,double &z) const
	{
		x=value[0];
		y=value[1];
		z=value[2];
	}
	inline double GetSquareLength(void) const
	{
		return value[0]*value[0]+value[1]*value[1]+value[2]*value[2];
	}
	inline double GetLength(void) const
	{
		return (double)sqrt(GetSquareLength());
	}

	YSBOOL IsNormalized(void) const;
	YSRESULT Normalize(void);

	

	inline int GetLongestAxis(void) const
	{
		if(fabs(value[0])>fabs(value[1]) && fabs(value[0])>fabs(value[2]))
		{
			return 0;
		}
		else if(fabs(value[1])>fabs(value[2]))
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	inline double GetLongestDimension(void) const
	{
		if(fabs(value[0])>fabs(value[1]) && fabs(value[0])>fabs(value[2]))
		{
			return fabs(value[0]);
		}
		else if(fabs(value[1])>fabs(value[2]))
		{
			return fabs(value[1]);
		}
		else
		{
			return fabs(value[2]);
		}
	}

	YsVec3 GetArbitraryPerpendicularVector(void) const;

	inline void RotateXY(const double &ang)
	{
		double c,s,xx,yy;
		c=cos(ang);
		s=sin(ang);
		xx=x()*c-y()*s;
		yy=x()*s+y()*c;
		SetX(xx);
		SetY(yy);
	}
	inline void RotateYX(const double &ang)
	{
		RotateXY(-ang);
	}
	inline void RotateXZ(const double &ang)
	{
		double c,s,xx,zz;
		c=cos(ang);
		s=sin(ang);
		xx=x()*c-z()*s;
		zz=x()*s+z()*c;
		SetX(xx);
		SetZ(zz);
	}
	inline void RotateZX(const double &ang)
	{
		RotateXZ(-ang);
	}
	inline void RotateYZ(const double &ang)
	{
		double c,s,yy,zz;
		c=cos(ang);
		s=sin(ang);
		yy=y()*c-z()*s;
		zz=y()*s+z()*c;
		SetY(yy);
		SetZ(zz);
	}
	inline void RotateZY(const double &ang)
	{
		RotateYZ(-ang);
	}

	inline const YsVec3 &operator+=(const YsVec3 &a)
	{
		value[0]+=a.value[0];
		value[1]+=a.value[1];
		value[2]+=a.value[2];
		return *this;
	}
	inline const YsVec3 &operator-=(const YsVec3 &a)
	{
		value[0]-=a.value[0];
		value[1]-=a.value[1];
		value[2]-=a.value[2];
		return *this;
	}
	inline const YsVec3 &operator/=(double a)
	{
		value[0]/=a;
		value[1]/=a;
		value[2]/=a;
		return *this;
	}
	inline const YsVec3 &operator*=(double a)
	{
		value[0]*=a;
		value[1]*=a;
		value[2]*=a;
		return *this;
	}

protected:
	double value[3];
};

inline const YsVec3 operator-(const YsVec3 &a)
{
	return YsVec3(-a.x(),-a.y(),-a.z());
}

inline const YsVec3 operator-(const YsVec3 &a,const YsVec3 &b)
{
	return YsVec3(a.x()-b.x(),a.y()-b.y(),a.z()-b.z());
}

inline const YsVec3 operator+(const YsVec3 &a,const YsVec3 &b)
{
	return YsVec3(a.x()+b.x(),a.y()+b.y(),a.z()+b.z());
}

inline const YsVec3 operator/(const YsVec3 &a,const double &b)
{
	return YsVec3(a.x()/b,a.y()/b,a.z()/b);
}

inline const YsVec3 operator*(const YsVec3 &a,const double &b)
{
	return YsVec3(a.x()*b,a.y()*b,a.z()*b);
}

inline const YsVec3 operator*(const double &b,const YsVec3 &a)
{
	return YsVec3(a.x()*b,a.y()*b,a.z()*b);
}

inline double operator*(const YsVec3 &a,const YsVec3 &b)
{
	return a.x()*b.x()+a.y()*b.y()+a.z()*b.z();
}

inline const YsVec3 operator^(const YsVec3 &a,const YsVec3 &b)
{
	// y1 z1 x1 y1
	// y2 z2 x2 y2
	double x,y,z;

	x=a.y()*b.z()-a.z()*b.y();
	y=a.z()*b.x()-a.x()*b.z();
	z=a.x()*b.y()-a.y()*b.x();
	return YsVec3(x,y,z);
}

inline int operator==(const YsVec3 &a,const YsVec3 &b)
{
	// Fixed 2000/11/10
	// return ((a-b).GetSquareLength()<YsTolerance);

	// Modified again 2000/11/10
	//if(YsEqual(a.x(),b.x())==YSTRUE &&
	//   YsEqual(a.y(),b.y())==YSTRUE &&
	//   YsEqual(a.z(),b.z())==YSTRUE)
	//{
	//	return 1;
	//}
	//else
	//{
	//	return 0;
	//}

    return 1;//((a-b).GetSquareLength()<YsSqr(YsTolerance));  // Modified 2000/11/10
}

inline int operator!=(const YsVec3 &a,const YsVec3 &b)
{
	// Fixed 2000/11/10
	// return ((a-b).GetSquareLength()>=YsTolerance);

	// Modified again 2000/11/10
	//if(YsEqual(a.x(),b.x())!=YSTRUE ||
	//   YsEqual(a.y(),b.y())!=YSTRUE ||
	//   YsEqual(a.z(),b.z())!=YSTRUE)
	//{
	//	return 1;
	//}
	//else
	//{
	//	return 0;
	//}

    return 1;//((a-b).GetSquareLength()>=YsSqr(YsTolerance));  // Modified 2000/11/10
}


inline const YsVec3 &YsLonger(const YsVec3 &v1,const YsVec3 &v2)
{
	return (v1.GetSquareLength()>=v2.GetSquareLength() ? v1 : v2);
}



////////////////////////////////////////////////////////////

/* } */
#endif
