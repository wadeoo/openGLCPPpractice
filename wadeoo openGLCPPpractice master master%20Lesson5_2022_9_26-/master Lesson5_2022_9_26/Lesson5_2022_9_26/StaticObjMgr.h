//========================================================
/**
*  @file      StaticObjMgr.h
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

#ifndef _STATIC_OBJ_MGR_H_
#define _STATIC_OBJ_MGR_H_

#include "StaticObj.h"
#include "terrain.h"
#include <vector>
using namespace std;


/**\brief
 * ��̬ʵ����������
 */
class CStaticObjMgr
{
public:
	CStaticObjMgr();
	~CStaticObjMgr();


	/**\brief
	 * ��ö���ĸ���
	 */
	unsigned int GetObjNum(){return m_nObjNum;}
	

	/**\brief
	 * ��ѡ�������õ���Ⱦ
	 */
	void Render_Pick(int id);
	
	
	/**\brief
	 * ��Ⱦ���о�̬����ʵ��
	 */
	void Render();
	

	/**\brief
	 * ��ʼ��
	 */
	BOOL LoadIni(char* filename,char* index);


	static CStaticObjMgr* GetSysStaticObjMgr(void){return m_pStaticObjMgr;}


	StaticObj* GetStaticObj(unsigned int n){if(n>=m_nObjNum)return NULL;return m_pObjArray+n;}
private:
	//! MS3D�ļ�����
	CMS3DFile ms3d;

	//!
	unsigned int m_nObjNum;

	//! 
	StaticObj* m_pObjArray;

	static CStaticObjMgr* m_pStaticObjMgr;
};





////////////////////////////////////////////////////////
//--------------------inline����ʵ��--------------------
/**\brief
 * ��ѡ�������õ���Ⱦ
 */
inline void CStaticObjMgr::Render_Pick(int id)
{
	(m_pObjArray+id)->Render();
}



/**\brief
 * ��Ⱦ���о�̬����ʵ��
 */
inline void CStaticObjMgr::Render()
{
	for(unsigned int i=0;i<m_nObjNum;++i)
	{
		(m_pObjArray+i)->Render();
	}
}

#endif