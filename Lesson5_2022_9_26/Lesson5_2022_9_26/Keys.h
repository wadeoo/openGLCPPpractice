#pragma once
//定义键盘类
#include "stdafx.h"
class Keys
{
public:

	/** 构造函数 */
	Keys() { Clear(); }

	/** 清空所有的按键信息 */
	void Clear() { ZeroMemory(&m_KeyDown, sizeof(m_KeyDown)); }

	/** 判断某个键是否按下 */
	bool IsPressed(unsigned int key)	{ return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false; }

	/** 设置某个键被按下 */
	void SetPressed(unsigned int key)	{ if (key < MAX_KEYS) m_KeyDown[key] = true; }

	/** 设置某个键被释放 */
	void SetReleased(unsigned int key)	{ if (key < MAX_KEYS) m_KeyDown[key] = false; }

private:
	static const unsigned int MAX_KEYS = 256;
	bool m_KeyDown[MAX_KEYS];									/**< 保存256个按键的状态 */
};