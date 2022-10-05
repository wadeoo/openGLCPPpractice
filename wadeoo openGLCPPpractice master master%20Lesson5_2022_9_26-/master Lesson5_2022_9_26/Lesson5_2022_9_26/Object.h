//========================================================
/**
*  @file      Object.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ����ʵ����Ļ���
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __CGW_OBJECT_H__
#define __CGW_OBJECT_H__

#include "mathlib.h"
#include "terrain.h"

/**\brief
 * ������Ϸʵ����Ļ���
 */
class Object
{
public:
	Object(void);
	~Object(void);

	float	r1,r2;		//!< ��Χ�еİ뾶,�ֱ���x,y�ϵķ���

	void Render();

	void SetPos(vector3d v)		{m_sPos=v;m_sPos.y = CTerrain::GetTerrainPointer()->getAveHeight(m_sPos.x ,m_sPos.z);}

	vector3d GetPos(void)		{return m_sPos;}

	void SetHeightAt(float _h)	{m_sPos.y=_h;}


private:
	virtual void OnRender(){}


protected:
	vector3d   m_sPos;

};

#endif