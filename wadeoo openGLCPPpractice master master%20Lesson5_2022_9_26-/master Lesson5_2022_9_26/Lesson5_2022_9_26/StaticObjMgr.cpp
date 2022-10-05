//========================================================
/**
*  @file      StaticObjMgr.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��̬ʵ����������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#include "stdafx.h"
#include "StaticObjMgr.h"
#include "IniFile.h"


CStaticObjMgr* CStaticObjMgr::m_pStaticObjMgr=NULL;

CStaticObjMgr::CStaticObjMgr()
{
	m_pStaticObjMgr=this;
}

CStaticObjMgr::~CStaticObjMgr()
{
	_DELETE_ARRAY(m_pObjArray);
}


/**\brief
 * ��ʼ��
 */
BOOL CStaticObjMgr::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);
	m_nObjNum=Ini.ReadInt(index,"ObjNum");
	m_pObjArray=new StaticObj[m_nObjNum];

	//��ʼ��ģ��
	char* strFile;
	char* strIndex;
	for(unsigned int i=0; i<m_nObjNum; ++i)
	{
		strFile = Ini.ReadText(index, i);
		strIndex = Ini.ReadData(index,i);
		m_pObjArray[i].LoadIni(strFile, strIndex);
		_FREE(strFile);
		_FREE(strIndex);
	}

	return TRUE;
}

