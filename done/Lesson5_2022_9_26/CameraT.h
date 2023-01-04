#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "mathlib.h"
#include "stdafx.h"
#include "Input.h"
#include "structdef.h"

#define SYS_KEYBOARD (CInputSystem::GetSysInput()->GetKeyboard())
#define SYS_MOUSE	(CInputSystem::GetSysInput()->GetMouse())


//第三人称摄像机类
class CameraT
{
public:
	CameraT();
	~CameraT();



	/**\brief
	* 获得旋转角度
	*/
	float GetDir(void){ return direction; }

	/**\brief
	* 获得倾角
	*/
	float GetPitch(void){ return pitch; }


	/**\brief
	* 获得摄像机到英雄的矩离
	*/
	float GetViewDistance(void){ return dist_to_role; }


	/**\brief
	* 获得摄像机的位置
	*/
	void GetCameraPos(vector3d *pVector){ *pVector = position; }


	/**\brief
	* 获得摄像机到英雄的矩离
	*/
	float GetDestToRole(){ return dist_to_role; }


	/**\brief
	* 设置变幻矩阵
	*/
	void FrameMove(void);


	/**\brief
	* 更新摄像的参数，把它放到主循环中
	*/
	void Update(void);


	/**\brief
	* 获得当前摄像机的指针
	*/
	static CameraT* GetCameraPointer(void){ return m_pCamera; }



private:
	//! 正在用的摄像机的指针
	static CameraT *m_pCamera;

	//! 到英雄的矩离
	float dist_to_role;

	//! 摄像机的位置
	vector3d position;

	//! 英雄的位置
	vector3d role_pos;

	//! 旋转角度
	float direction;

	//! 倾斜
	float pitch;

};

#endif