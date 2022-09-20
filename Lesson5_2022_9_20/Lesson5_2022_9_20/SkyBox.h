//========================================================
/**
*  @file      SkyBox.h
*
*  ��Ŀ������ MD2�ļ�����
*  �ļ�����:  ��պ���  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-05-17	
*  
*
*/     
//========================================================
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "stdafx.h"
#include "CBMPLoader.h"
#include "Vector.h"
#include "Camera.h"

#define GL_CLAMP_TO_EDGE	0x812F

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool init();
	
	/** ��Ⱦ */
	void render();

private:
	
	CBMPLoader  m_texture[5];   /**< ��պ�����   */
	Vector3     m_CameraPos;    /**< ��ǰ�����λ�� */
	float       length;         /**< ���� */
	float       width;          /**< ���� */
	float       height;         /**< �߶� */
	float       yRot;           /**< ��Y����ת */
		
};


#endif ///__SKYBOX_H__