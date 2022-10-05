//========================================================
/**
*  @file      Role.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ�е�Ӣ��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef _GAME_ROLE_H_
#define _GAME_ROLE_H_

#include "mathlib.h"
#include "ActiveObj.h"
#include "input.h"
#include "fireball.h"
#include "sound.h"
#include "general.h"

extern CInfo ObjectInfo;


/**\brief
 * ��Ϸ�е�Ӣ��
 */
class CRole:public CActiveObj
{
public:
	CRole(void);
	~CRole(void){_DELETE(property)}

	void SetSpeed(float s);

	BOOL GetMonsterInfo(char *pInfo,float& t);

	void SetShadow(BOOL b){property->shadow=b;}
	void SetSelecte(BOOL b)		{property->m_bSelected=b;}
	void SetPickState(int state,int id){pick_state=state;objectid=id;}

	virtual void Render_Pick(void);

	virtual void EndRender(void);

	virtual void OnRender(void){CActiveObj::OnRender();fireball.Render();}

	BOOL Init(void);

	static CRole* GetRolePointer(){return m_pRole;}
	
	BOOL LoadIni(char* _filename,char* _index);

	float energy;//����
	float stamina;//����


private:
	MD2_ANIMATION *m_pAnimations;
	CFireball fireball;
	int pick_state;
	BOOL bPick;

	int objectid,pickid;

	static CRole* m_pRole;
	SActiveObjPro* m_pMonster;

	BOOL bRightMouseDown;

	CSound sound;
	CSound run;
	BOOL IsRun;
};


#endif