//========================================================
/**
*  @file      structdef.cpp
*
*  项目描述： 构造游戏引擎
*  文件描述:  常用结构定义  
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     WWBOSS
*  电子邮件:  wwboss123@gmail.com
*  创建日期： 2007-07-26	
*  修改日期： 2007-07-26
*
*/     
//========================================================


#include "stdafx.h"
#include "structdef.h"



/** 下面是SWindowInfo结构的实现  */

//! SWindowInfo结构的静态变量初始化
SWindowInfo*	SWindowInfo::m_pInfo=NULL;
BOOL			SWindowInfo::m_bFullScreen=FALSE;
int				SWindowInfo::m_iWidth=640;
int				SWindowInfo::m_iHeight=480;
int				SWindowInfo::m_iBits=32;
HINSTANCE		SWindowInfo::m_hInstance=NULL;
HWND			SWindowInfo::m_hWnd=NULL;
char*			SWindowInfo::m_strWinName=NULL;



