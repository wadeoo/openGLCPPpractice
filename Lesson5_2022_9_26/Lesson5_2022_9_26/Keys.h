#pragma once
//���������
#include "stdafx.h"
class Keys
{
public:

	/** ���캯�� */
	Keys() { Clear(); }

	/** ������еİ�����Ϣ */
	void Clear() { ZeroMemory(&m_KeyDown, sizeof(m_KeyDown)); }

	/** �ж�ĳ�����Ƿ��� */
	bool IsPressed(unsigned int key)	{ return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false; }

	/** ����ĳ���������� */
	void SetPressed(unsigned int key)	{ if (key < MAX_KEYS) m_KeyDown[key] = true; }

	/** ����ĳ�������ͷ� */
	void SetReleased(unsigned int key)	{ if (key < MAX_KEYS) m_KeyDown[key] = false; }

private:
	static const unsigned int MAX_KEYS = 256;
	bool m_KeyDown[MAX_KEYS];									/**< ����256��������״̬ */
};