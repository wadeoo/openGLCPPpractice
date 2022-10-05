//========================================================
/**
*  @file      Info.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ����ʵ�����Ϣ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _INFO_H_
#define _INFO_H_

#include "mathlib.h"
#include "terrain.h"
#include <vector>

using namespace std;

#define TREE      0
#define HOUSE     1
#define MONSTER   2
#define ROLE      3
#define EARTH     4


///////////////////
/**\brief
 * ��̬ʵ���״̬
 */
enum OBJ_STATE
{
	STAND =0,
	PAIN,
	WALK,
	RUN,
	ATTACK,
	DEATH
};


/////////////////////////////
//! MD2ģ�Ͷ�����֡�����б�
#define STAND_START		1
#define STAND_END		10
#define WALK_START		136
#define WALK_END		142 
#define RUN_START		41
#define RUN_END			46
#define ATTACK_START	47
#define ATTACK_END		54
#define PAIN1_START		55
#define PAIN1_END		58
#define PAIN2_START		59 
#define PAIN2_END		63 
#define PAIN3_START		64 
#define PAIN3_END		68 
#define JUMP_START		69
#define JUMP_END		74
#define DEATH1_START	179
#define DEATH1_END		184
#define DEATH2_START	185
#define DEATH2_END		190
#define DEATH3_START	191
#define DEATH3_END		198



//////////////////////////////
/**\brief
 * ��̬ʵ�����Ϣ�ṹ
 */
struct SActiveObjPro
{

	SColor m_sColor;					//!< ��ɫ

	OBJ_STATE object_state,old_state;	//!< ��ǰ״̬����״̬

	int curr_frame,next_frame;			//!< ��ǰ֡����һ֡

	float		t,t_add;				//!< ��ֵ

	float		speed;					//!< �ٶ�

	vector3d	vPosition;				//!< 3dλ��

	float		r1,r2;					//!< ��Χ�еİ뾶,�ֱ���x,y�ϵķ���

	BOOL		m_bSelected;			//!< �Ƿ�ѡ��

	float		yrot;					//!< ��ת�Ƕ�

	vector2d	orient;					//!< ����

	vector2d start_pos,end_pos,curr_pos;//!< 2dλ��,��ʼ����������ǰλ��

	int life,curr_life;					//!< ����������ǰ����

	BOOL bArrive;						//!< �ж��Ƿ񵽴�

	BOOL shadow;						//!< �Ƿ����Ӱ

	float dist_min,dist_max;			//!< ��������

	SActiveObjPro();
	~SActiveObjPro(){}

	void ChangeCurrFrame();

	void SetObjectState(OBJ_STATE state)
	{
		if(object_state != state)
		{
			old_state = object_state;
			object_state = state;
			ChangeCurrFrame();
		}
	}


	void ReduceLife(int delta)
	{
		curr_life -= delta;
		if(curr_life < 0)curr_life = 0;
		if(object_state != DEATH)
			SetObjectState(PAIN);
	}


	void GetObjectPos(vector3d *pVector){*pVector=vPosition;}

	void SetObjectPos(vector3d &v){vPosition = v;}

	float GetLife()
	{
		float t = curr_life/(float)life;
		if(t > 1.0f)t = 1.0f;
		if(t < 0.0f)t = 0.0f;
		return t;
	}

	void Update();
};



////////////////////////////
/**\brief
 * ��̬ʵ�����Ϣ����
 */
class CInfo  
{
public:
	CInfo(){}
	~CInfo(){}


	/**\brief
	 * ��һ���������Ϣ�����б�
	 */
	void PushMonster(SActiveObjPro *pProperty){m_pMonsterProperty.push_back(pProperty);}


	/**\brief
	 * ���Ӣ�۵���Ϣ
	 */
	void PushRole(SActiveObjPro * pProperty){m_pRoleProperty = pProperty;}


	/**\brief
	 * ���ĳһ�����ָ��
	 */
	SActiveObjPro* GetMonsterPointer(int id){return m_pMonsterProperty[id];}


	/**\brief
	 * ���Ӣ�۵�ָ��
	 */
	SActiveObjPro* GetRolePointer(){return m_pRoleProperty;}


	/**\brief
	 * ��ù���ĸ���
	 */
	unsigned int GetMonstersNum(void){return m_pMonsterProperty.size();}

private:
	//! �������Ϣ�б�
	vector<SActiveObjPro*> m_pMonsterProperty;

	//! Ӣ�۵���Ϣ
	SActiveObjPro *m_pRoleProperty;
};



#endif