//========================================================
/**
*  @file      Object.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ����ʵ����Ļ���
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#include "stdafx.h"
#include "object.h"
#include "role.h"

Object::Object(void):m_sPos(vector3d(0.f,0.f,0.f)),r1(24.f),r2(20.f)
{
}


Object::~Object(void)
{
}


void Object::Render()
{
	vector3d v=CRole::GetRolePointer()->GetPos();
	if((fabsf(m_sPos.x-v.x)<450)&&(fabsf(m_sPos.z-v.z)<450) )
	{
		OnRender();
	}
}