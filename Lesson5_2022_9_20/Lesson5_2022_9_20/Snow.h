//======================================================================
/**
*  @file      Snow.h
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ѩ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-18	
*  �޸����ڣ� 2006-12-19
*	
*/																			
//======================================================================

#ifndef  __SNOW_H__
#define  __SNOW_H__


#include "CBMPLoader.h"
#include "Particle.h"


/** ѩ����Ⱦ�� */
class CSnow : public CParticle
{

public:
	CSnow()  {};
	~CSnow() {};
	
	bool		Init(int num );  /** ��ʼ������ */
	void		Render();        /**< ��Ⱦ���� */
	void		Update();        /**< ���¹��� */

private:
	CBMPLoader  m_texture;       /**< ���ӵ����� */


}; 

#endif //__SNOW_H__
