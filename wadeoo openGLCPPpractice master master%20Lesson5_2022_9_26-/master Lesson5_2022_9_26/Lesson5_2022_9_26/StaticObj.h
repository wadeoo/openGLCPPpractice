//========================================================
/**
*  @file      StaticObj.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ�еľ�̬ʵ��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __STATIC_OBJ_H__
#define __STATIC_OBJ_H__

#include "object.h"
#include "MS3DFile.h"
#include "terrain.h"
#include "general.h"

class StaticObj : public Object
{
public:
	StaticObj(void);
	~StaticObj(void);

	void SetDir(float _dir)		{m_fDir=_dir;}
	float GetDir()				{return m_fDir;}

	BOOL LoadIni(char* filename,char* index);

	virtual void OnRender();

	void SetSelecte(BOOL b)		{m_bSelected=b;}

private:
	CMS3DFile ms3d;			//!< MS3D�ļ�����

	float		m_fDir;		//!< ����

	BOOL		m_bSelected;//!< �Ƿ�ѡ��
};


#endif