//========================================================
/**
*  @file      Water.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ˮ����Ⱦ
*  ����ƽ̨�� Windows98/2000/NT/XP
*
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26
*  �޸����ڣ� 2007-07-26
*
*/
//========================================================

#ifndef _WATER_H_
#define _WATER_H_

#include "texture.h"


/**\brief
* ˮ����Ⱦ��
*/
class CWater
{
public:
	CWater();
	~CWater();

	/**\brief
	* ��ʼ��,��Ҫ�����������
	*/
	BOOL Init();


	/**\brief
	*  ˮ����Ⱦ
	*/
	void Render();



private:
	//! ����
	CTexture texture;

	//! �����ƶ�����С��λ
	float delta;

};

#endif
