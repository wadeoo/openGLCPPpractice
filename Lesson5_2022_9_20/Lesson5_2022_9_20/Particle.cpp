//======================================================================
/**
*  @file      Particle.cpp
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ���Ӷ����� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-18	
*  �޸����ڣ� 2006-12-19
*	
*/																			
//======================================================================
#include "Particle.h"

/** ���캯�� */
CParticle::CParticle():m_iNum(0),m_pList(NULL)
{	
}

/** �������� */
CParticle::~CParticle()
{
	if(m_pList != NULL)
	{
		delete []m_pList;
		m_pList = NULL;
	}
	
}

/** ���ӵĳ�ʼ�� */
bool CParticle::Init(int _num)
{
	m_iNum = _num;
	m_pList = new Particle[m_iNum];
	if(m_pList == NULL)
		return false;
	return true;
}

/** ���ӵ���Ⱦ */
void CParticle::Render()
{
}

/** ���ӵĸ��� */
void CParticle::Update()
{
}
