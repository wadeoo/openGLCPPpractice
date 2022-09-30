#pragma once
#include "stdafx.h"
#include "Keys.h"

extern Keys g_Keys;

class Light
{
public:
	Light();
	~Light();
	void  Init();
	void Update();
	void Draw();
private:
	float m_bRedX;                                      /**< ��ɫ�����ת�Ƕ� */
	float m_bRedY;
	float m_bGreenX;                                    /**< ��ɫ�����ת�Ƕ� */
	float m_bGreenY;
	float m_bBlueX;                                     /**< ��ɫ�����ת�Ƕ� */
	float m_bBlueY;
};

