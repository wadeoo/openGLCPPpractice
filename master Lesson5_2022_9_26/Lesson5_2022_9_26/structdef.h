//========================================================
/**
*  @file      structdef.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ���ýṹ����  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/     
//========================================================


#ifndef __STRUCT_DEF_H__
#define __STRUCT_DEF_H__


/** ���ú� */
#define _ERROR(info)	MessageBox(NULL,info,"error",MB_OK)
#define _DELETE(X)		try{ if((X)!=NULL){delete (X); (X) = NULL; } } catch(...) { _ERROR("error delete!"); }

/**\brief
 * ������Ϣ�ṹ
 */
struct SWindowInfo
{
	//! �Ƿ�ȫ����ʾ
	static BOOL			m_bFullScreen;

	//! ���ڿ�
	static int			m_iWidth;

	//! ���ڸ�
	static int			m_iHeight;
	
	//! ��ɫλ��
	static int			m_iBits;

	//! ������������
	static HINSTANCE	m_hInstance;

	//! ���ھ��
	static HWND			m_hWnd;

	//! ������
	static char*		m_strWinName;

	SWindowInfo()		{ m_pInfo = this; }
	~SWindowInfo()		{ _DELETE(m_strWinName);}

	/**\brief
	 * ��õ�ǰ������Ϣ��ָ��
	 */
	static SWindowInfo* GetSysWinInfo(){return m_pInfo;}



private:
	//! ������Ϣָ��
	static SWindowInfo* m_pInfo;
};



/**\brief
 * 2D�ռ��еĵ�
 */
struct SPoint2
{
	union
	{
		struct{int x,y;};
		int point2[2];
	};

	SPoint2()									:x(0),y(0){}
	SPoint2(int _x,int _y)						:x(_x),y(_y){}
	const SPoint2 &operator=(const SPoint2 &p)	{x=p.x;y=p.y;return *this;}
};


/**\brief
 * 3D�ռ��еĵ�
 */
struct SPoint3
{
	union
	{
		struct {float x,y,z;};
		float point3[3];
	};

	SPoint3()									:x(0.0f),y(0.0f),z(0.0f){}
	SPoint3(float _x,float _y,float _z)			:x(_x),y(_y),z(_z){}
	const SPoint3 &operator=(const SPoint3 &p)	{x=p.x;y=p.y;z=p.z;return *this;}
};



/**\brief
 * ��ɫ�ṹ
 */
struct SColor
{
	union
	{
		struct {float r,g,b,a;};
		float color4[4];
	};

	SColor()									:r(0.0f),g(0.0f),b(0.0f),a(0.0f){}
	SColor(float _r,float _g,float _b,float _a)	:r(_r),g(_g),b(_b),a(_a){}
	const SColor &operator=(const SColor &c)	{r=c.r;g=c.g;b=c.b;a=c.a;return *this;}
	const SColor operator!(){SColor c;c.r=1.f-r;c.g=1.f-g;c.b=1.f-b;return c;}
};



/**\brief
 * ���νṹ
 */
struct SRect
{
	union
	{
		struct {int x,y,width,height;};
		int rect[4];
	};

	SRect():x(0),y(0),width(100),height(100){}
	SRect(int _x,int _y,int _w,int _h)		:x(_x),y(_y),width(_w),height(_h){};
	const SRect &operator=(const SRect &r)	{x=r.x;y=r.y;width=r.width;height=r.height;return *this;}
	BOOL PointIn(SPoint2 p){if(p.x>=x&&p.y>=y&&p.x<=x+width&&p.y<=y+height)return TRUE;else return FALSE;}
};



#endif