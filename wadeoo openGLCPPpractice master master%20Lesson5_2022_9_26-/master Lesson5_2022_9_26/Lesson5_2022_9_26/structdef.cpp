//========================================================
/**
*  @file      structdef.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ���ýṹ����  
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
#include "structdef.h"



/** ������SWindowInfo�ṹ��ʵ��  */

//! SWindowInfo�ṹ�ľ�̬������ʼ��
SWindowInfo*	SWindowInfo::m_pInfo=NULL;
BOOL			SWindowInfo::m_bFullScreen=FALSE;
int				SWindowInfo::m_iWidth=640;
int				SWindowInfo::m_iHeight=480;
int				SWindowInfo::m_iBits=32;
HINSTANCE		SWindowInfo::m_hInstance=NULL;
HWND			SWindowInfo::m_hWnd=NULL;
char*			SWindowInfo::m_strWinName=NULL;



