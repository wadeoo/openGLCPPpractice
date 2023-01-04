#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "mathlib.h"
#include "stdafx.h"
#include "Input.h"
#include "structdef.h"

#define SYS_KEYBOARD (CInputSystem::GetSysInput()->GetKeyboard())
#define SYS_MOUSE	(CInputSystem::GetSysInput()->GetMouse())


//�����˳��������
class CameraT
{
public:
	CameraT();
	~CameraT();



	/**\brief
	* �����ת�Ƕ�
	*/
	float GetDir(void){ return direction; }

	/**\brief
	* ������
	*/
	float GetPitch(void){ return pitch; }


	/**\brief
	* ����������Ӣ�۵ľ���
	*/
	float GetViewDistance(void){ return dist_to_role; }


	/**\brief
	* ����������λ��
	*/
	void GetCameraPos(vector3d *pVector){ *pVector = position; }


	/**\brief
	* ����������Ӣ�۵ľ���
	*/
	float GetDestToRole(){ return dist_to_role; }


	/**\brief
	* ���ñ�þ���
	*/
	void FrameMove(void);


	/**\brief
	* ��������Ĳ����������ŵ���ѭ����
	*/
	void Update(void);


	/**\brief
	* ��õ�ǰ�������ָ��
	*/
	static CameraT* GetCameraPointer(void){ return m_pCamera; }



private:
	//! �����õ��������ָ��
	static CameraT *m_pCamera;

	//! ��Ӣ�۵ľ���
	float dist_to_role;

	//! �������λ��
	vector3d position;

	//! Ӣ�۵�λ��
	vector3d role_pos;

	//! ��ת�Ƕ�
	float direction;

	//! ��б
	float pitch;

};

#endif