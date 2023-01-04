//======================================================================
/**
*  @file      Particle.h
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

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "stdafx.h"
#include "Vector.h"



/** ���ӽṹ */
struct Particle
{
	Vector3   position;		       /**< ���ӵ�λ�� */
	
	Vector3   velocity;            /**< ���ӵ��ٶ� */
	
	Vector3   acceleration;        /**< ���ӵļ��ٶ� */
	
	float     lifetime;            /**< ��������ֵ */
	
	float     dec;		           /**< ������ʧ���ٶ� */
	
	float     size;		           /**< ���ӳߴ� */
	
	float     color[3];            /**< ���ӵ���ɫ */
	
};


/** ������ */
class CParticle
{

public:

	CParticle();                  /**< ���캯�� */

	virtual ~CParticle();         /**< �������� */
	
	/** ���ӵĳ�ʼ�� */
	virtual bool Init(int _num);

	/** ���ӵ���Ⱦ */
	virtual void Render() = 0;

	/** ���ӵĸ��� */
	virtual void Update() = 0;

protected:

	int           m_iNum;	              /**< ��������Ŀ */
	Particle*     m_pList;				  /**< ����ָ�� */

};

#endif