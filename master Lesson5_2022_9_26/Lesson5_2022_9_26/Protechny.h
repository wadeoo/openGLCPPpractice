//======================================================================
/**
*  @file      Protechny.h
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ��Ȫ�� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-18	
*  �޸����ڣ� 2006-12-19
*	
*/																			
//======================================================================

#ifndef  __PROTECHNY_H__
#define  __PROTECHNY_H__


#include "CBMPLoader.h"
#include "Particle.h"


/** ��Ȫ�� */
class CProtechny : public CParticle
{

public:
	CProtechny()  {};
	~CProtechny() {};
	
	bool		Init(int num );  /**< ��ʼ������ */
	void		Render();        /**< ��Ⱦ���� */
	void		Update();        /**< ���¹��� */

private:
	CBMPLoader  m_texture;       /**< ���ӵ����� */

}; 

#endif //__PROTECHNY_H__
