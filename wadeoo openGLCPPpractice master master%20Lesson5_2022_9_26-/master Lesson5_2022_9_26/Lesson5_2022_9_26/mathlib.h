//========================================================
/**
*  @file      mathlib.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��ѧ�����õ���Ľṹ  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/     
//========================================================


#ifndef _MATH_LIB_H__
#define _MATH_LIB_H__

#include <math.h>
#include <assert.h>

#ifndef EPSILON
#define EPSILON 0.0001f
#endif

#ifndef PI
#define PI 3.1415926f
#endif



//////////////////////////////////////////////////////
/**\brief
 * vector2d 2Dʸ��
 */
struct vector2d
{
	//----------------------------------
	union
	{
		struct{float x , y;};
		float vector2[2];
	};
	//----------------------------------

	vector2d(){}
	~vector2d(){}

	vector2d(float _x ,float _y):x(_x),y(_y){}
	vector2d(float *f):x(f[0]),y(f[1])		{}
	vector2d(const vector2d& vector):x(vector.x),y(vector.y){}

	float mag()		{return (float)sqrt(x*x+y*y);}
	float mag_sqr()	{return x*x + y*y;}

	/**\brief
	 * ����֮��ľ���
	 */
	float dist(vector2d& vector);
	float dot(vector2d& vector);

	/**\brief
	 * �õ���ά�����Ĵ�ֱ����
	 */
	void change(){float m;m = x;x = -y;y = m;}

	/**\brief
	 * �㵽ֱ�ߵľ���
	 */
	float dist(vector2d&p1 , vector2d&p2);

	/**\brief
	 * �жϵ㵽ֱ�ߵ�ͶӰ�Ƿ����߶���
	 */
	BOOL bPtInLine(vector2d p1 , vector2d p2);

	float dist_sqr(vector2d& vector);

	void set(float _x , float _y){x=_x;y=_y;}

	void normalize(){float d=mag();x/=d;y/=d;}

	void operator  =(vector2d vector) {x = vector.x;y = vector.y;}
	void operator +=(vector2d& vector){x+= vector.x;y+= vector.y;}
	void operator -=(vector2d& vector){x-= vector.x;y-= vector.y;}

	vector2d operator +(vector2d& vector);
	vector2d operator -(vector2d& vector);

	vector2d operator *(float s);
	vector2d operator /(float& s);


	/**\brief
	 * �õ������Ļ���
	 */
	float getradian()
	{
		if(fabs(x)<=EPSILON&&y>0)return 90.0f;
		if(fabs(x)<=EPSILON&&y<0)return 270.0f;
		if(fabs(y)<=EPSILON&&x>0)return 0.0f;
		if(fabs(y)<=EPSILON&&x<0)return 180.0f;

		float rel = asinf(fabsf(y));
		rel = rel*180.0f / PI;
		if(x>0&&y>0)return rel;
		if(x<0&&y>0)return 180.0f - rel;
		if(x<0&&y<0)return 180.0f + rel;
		if(x>0&&y<0)return 360.0f - rel;

		return 0;
	}


	/**\brief
	 * ��ת����
	 */
	void rotate(float s);
};



///////////////////////////////////////////////////////////
/**\brief
 * 3Dʸ���ṹ
 */
struct vector3d
{
	//-------------------------------------
	union
	{
		struct{float x,y,z;};
		float v[3];
	};
	//-------------------------------------

	vector3d()	{}
	~vector3d()	{}

	vector3d(float _x,float _y,float _z):x(_x),y(_y),z(_z)	{}
	vector3d(float f[]):x(f[0]),y(f[1]),z(f[2])				{}

	void set(float _x,float _y,float _z){x=_x;y=_y;z=_z;}

	float mag(){return sqrtf(x*x + y*y + z*z);}
	float mag_sqr(){return x*x + y*y + z*z;}

	float dist(vector3d& vector);
	float dist_sqr(vector3d& vector);

	vector3d cross(const vector3d& p);


	/**\brief
	 * ʸ���Ĺ��
	 */
	void normalize();

	void operator  =(const vector3d& p);
	void operator +=(const vector3d& p);
	void operator -=(const vector3d& p);
	void operator *=(const float& s);
	void operator /=(const float& s);

	vector3d operator+(const vector3d& _v);
	vector3d operator-(const vector3d& _v);
	vector3d operator*(const float& s);
	
	static float dot(const vector3d& p1,const vector3d& p2);
};



///////////////////////////////////////////////////////
/**\brief
 * 2D�ռ��е���
 */
struct line2d
{
	vector2d p1;
	vector2d p2;

	BOOL IsIntersect(line2d& line);

	vector2d GetIntersectPoint(line2d& line);
};



//////////////////////////////////////////////////////
/**\brief
 * Բ�ṹ
 */
struct SCircle
{
	//----------------------------------
	//! Բ��λ��
	vector2d	pos;
	//! �뾶
	float		radius;
	//----------------------------------

	SCircle()	{}
	~SCircle()	{}

	/**\brief
	 * �ж��߶κ�Բ�Ƿ��ཻ
	 */
	BOOL isIntersect(vector2d& p1 , vector2d& p2);
	void Set(vector2d &v , float& r);

	/**\brief
	 * �õ�Բ�����p1���е�
	 */
	vector2d getpoint(vector2d& p1 , vector2d& p2);

	/**\brief
	 * Բ�ĸ�ֵ����
	 */
	void operator =(SCircle c);
};




////////////////////////////////////////////////////////
/**\brief
 * �нṹ
 */
class CBox  
{
public:
	CBox(){}
	~CBox(){}

public:
	vector3d min;
	vector3d max;

	float xsize()		{return max.x - min.x;}
	float ysize()		{return max.y - min.y;}
	float zsize()		{return max.z - min.z;}

	vector3d size()		{return max - min;}
	vector3d center()	{return (min+max)*0.5f;}


	/**\brief
	 * ����Ϊv�ĵ��Ƿ��ڴ���������
	 */
	inline BOOL PtInBox(vector3d& v){
		return (v.x >= min.x) && (v.x <= max.x) &&
			(v.y >= min.y) && (v.y <= max.y) &&
			(v.z >= min.z) && (v.z <= max.z);
	};

	vector3d closestPointTo(vector3d& v);

	BOOL IntersectSphere(vector3d& vcenter , float radius);

	float IntersectRay(vector3d& start , vector3d&end);

	vector3d corner(int i);

};




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<������inline������ʵ��>>>>>>>>>>>>>>>>>>>>



////////////////////////////////////////////////////////////
//-----------------------vector2d---------------------------
/**\brief
 * �㵽ֱ�ߵľ���
 */
inline float vector2d::dist(vector2d&p1 , vector2d&p2)
{
	vector2d p(p2.x - p1.x , p2.y - p1.y);
	p.normalize();
	p.change();
	return p.dot(vector2d(x-p1.x,y-p1.y));
}

/**\brief
 * ��ת����
 */
inline void vector2d::rotate(float s)
{
	x = x*(float)cos(s) - y*(float)sin(s);
	y = x*(float)sin(s) + y*(float)cos(s);
}

inline float vector2d::dist_sqr(vector2d& vector)
{
	return (x-vector.x)*(x-vector.x)+(y-vector.y)*(y-vector.y);
}

/**\brief
 * ����֮��ľ���
 */
inline float vector2d::dist(vector2d& vector)
{
	return (float)sqrt(  (x-vector.x)*(x-vector.x)
						+(y-vector.y)*(y-vector.y)
						);
}

inline float vector2d::dot(vector2d& vector)
{
	return x*vector.x + y*vector.y;
}

inline vector2d vector2d::operator +(vector2d& vector)
{
	return vector2d(x+vector.x ,y + vector.y);
}

inline vector2d vector2d::operator -(vector2d& vector)
{
	return vector2d(x-vector.x , y-vector.y);
}

inline vector2d vector2d::operator *(float s)
{
	return vector2d(x*s,y*s);
}

inline vector2d vector2d::operator /(float& s)
{
	return vector2d(x/s,y/s);
}



///////////////////////////////////////////////////////////
//-----------------------vector3d--------------------------

inline float vector3d::dist(vector3d& vector)
{
	return (float)sqrt(	 (x-vector.x)*(x-vector.x)
						+(y-vector.y)*(y-vector.y)
						+(z-vector.z)*(z-vector.z)
						);
}


inline float vector3d::dist_sqr(vector3d& vector)
{
	return ( (x-vector.x)*(x-vector.x)
			+(y-vector.y)*(y-vector.y)
			+(z-vector.z)*(z-vector.z)
			);
}


inline vector3d vector3d::cross(const vector3d& p)
{
	return(vector3d(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x));
}


/**\brief
 * ʸ���Ĺ��
 */
inline void vector3d::normalize()
{
	float invmag =1.0f/mag();
	x *= invmag;
	y *= invmag;
	z *= invmag;
}

inline void vector3d::operator  =(const vector3d& p)
{
	x = p.x;y = p.y;z = p.z;
}

inline void vector3d::operator +=(const vector3d& p)
{
	x += p.x;y += p.y;z += p.z;
}

inline void vector3d::operator -=(const vector3d& p)
{
	x -= p.x;y -= p.y;z -= p.z;
}

inline void vector3d::operator *=(const float& s)
{
	x *= s;y *= s;z *= s;
}

inline void vector3d::operator /=(const float& s)
{
	x /= s;y /= s;z /= s;
}	

inline vector3d vector3d::operator+(const vector3d& _v)
{
	return vector3d(x+_v.x,y+_v.y,z+_v.z);
}

inline vector3d vector3d::operator-(const vector3d& _v)
{
	return vector3d(x-_v.x,y-_v.y,z-_v.z);
}

inline vector3d vector3d::operator*(const float& s)
{
	return vector3d(x*s,y*s,z*s);
}

inline float vector3d::dot(const vector3d& p1 , const vector3d& p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}




//////////////////////////////////////////////////////////
//-----------------------SCircle--------------------------
/**\brief
 * Բ�ĸ�ֵ����
 */
inline void SCircle::operator =(SCircle c)
{
	pos = c.pos;
	radius = c.radius;
}



//////////////////////////////////////////////////////////
//------------------------CBox----------------------------

//inline BOOL CBox::PtInBox(vector3d&v)
//{
//	return (v.x >= min.x)&&(v.x <= max.x)&&
//		   (v.y >= min.y)&&(v.y <= max.y)&&
//		   (v.z >= min.z)&&(v.z <= max.z);
//}



#endif