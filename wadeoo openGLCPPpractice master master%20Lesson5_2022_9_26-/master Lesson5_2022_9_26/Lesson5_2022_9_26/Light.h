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
	float m_bRedX;                                      /**< 红色球的旋转角度 */
	float m_bRedY;
	float m_bGreenX;                                    /**< 绿色球的旋转角度 */
	float m_bGreenY;
	float m_bBlueX;                                     /**< 蓝色球的旋转角度 */
	float m_bBlueY;
};

