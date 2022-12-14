//======================================================================
/**
*  @file      Input.h
*
*  项目描述： DirectInput键盘演示
*   
*  文件描述:  输入系统类CInputSystem
*             其中,类CKeyboard、CMouse、CJoystick分别用来处理键盘、鼠标
*			  和游戏手柄，CInputSystem是输入设备的管理类。
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     WWBOSS
*  电子邮件:  wwboss123@gmail.com
*  创建日期： 2007-07-24	
*  修改日期： 2007-07-24
*/																			
//======================================================================

#ifndef __INPUT_H__
#define __INPUT_H__

#include "stdafx.h"
#include "Vector.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2
#define IS_USEJOYSTICK  4

/** 鼠标缓冲区大小 */
#define DINPUT_BUFFERSIZE  16

/** 键盘类 */
class CKeyboard
{
public:
	/** 构造函数和析构函数 */
	CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
	~CKeyboard();

	/** 判断某个键是否被按下 */
	bool KeyDown(char key);
	
	/** 判断某个键是否被释放 */
	bool KeyUp(char key);
	
	/** 对键盘数据清零 */
	void Clear();

	/** 更新键盘数据 */
	bool Update();	

	/** 取键盘数据 */
	bool Acquire();

	/** 停止取数据 */
	bool Unacquire();

private:
	/** 键盘设备 */
	LPDIRECTINPUTDEVICE8  m_pDIDev;

	/** 键盘数据区 */
	char    m_keys[256];
};



/** 鼠标类 */
class CMouse
{
public:
	/** 构造函数和析构函数 */
	CMouse(LPDIRECTINPUT8 pDI,HWND hwnd,bool isExclusive);
	~CMouse();

	/** 鼠标左键是否按下 */
	bool	IsLButtonPressed();

	/** 鼠标右键是否按下 */
	bool	IsRButtonPressed();

	/** 鼠标中键是否按下 */
	bool	IsMButtonPressed();

			
	/** 获得光标位置 */
	Point2	GetMousePos();

	/** 更新鼠标参数 */
	bool	Update();

	/** 取鼠标数据 */
	bool	Acquire();
		
	/** 停止取数据 */
	bool	Unacquire();

	/** 窗口宽 */
	int		m_iWidth;

	/** 窗口高 */
	int		m_iHeight;


private:
	/** 鼠标设备 */
	LPDIRECTINPUTDEVICE8	m_pDIDev;

	/** 缓冲区数据数组 */
	DIDEVICEOBJECTDATA      m_diData[DINPUT_BUFFERSIZE];
	
	/** 光标位置 */
	Point2					m_iMousePos;
};

/**  游戏手柄 */
class CJoystick
{
public:
	CJoystick(LPDIRECTINPUT8 pDI,HWND hwnd, HINSTANCE appInstance);
	~CJoystick();

	/** 更新手柄参数 */
	bool Update();

	/** 取手柄数据 */
	bool Acquire();

	/** 判断手柄按键 */
	bool  IsButtonPressed(int iButton);

	/** 设置游戏杆范围 */
	void  SetMin(int min);
	void  SetMax(int max);

	/** 设置游戏杆死区范围 */
	void  SetDeadZone(int deadzone);

	/** 停止取手柄数据 */
	bool Unacquire();

private:

	/** 枚举设备回调函数 */
	bool CALLBACK EnumJSCallback(LPCDIDEVICEINSTANCE  pDIDeviceInstance, LPVOID pvRef);


private:
	LPDIRECTINPUT8        m_pDI;
	
	/** 手柄设备 */
	LPDIRECTINPUTDEVICE8  m_pDIDev;

	/** 手柄状态数据 */
	DIJOYSTATE2           m_diJoyState2;

	/** 游戏杆轴范围 */
	int    m_iMin;
	int    m_iMax;

	/** 游戏杆死区范围 */
	int    m_iDeadZone;
};



/** 输入系统类 */
class CInputSystem
{
public:
	/** 构造函数和析构函数 */
	CInputSystem()  {  m_pInput = this;	}

	~CInputSystem() {  ShutDown();     }  

	/** 初始化输入设备 */
	bool Init(HWND hwnd,HINSTANCE appInstance,
		      bool isExclusive,DWORD flags=0);

	/** 释放输入设备资源 */
	bool ShutDown();

	/** 取输入设备的数据 */
	void  AcquireAll();

	/** 停止取输入设备的数据 */
	void  UnacquireAll();

	/** 更新输入设备的参数 */
	void	Update();

	/** 获得光标的3D坐标 */
	Vector3  GetMousePosition();	

	/** 获得键盘 */
	CKeyboard*  GetKeyboard(){  return  m_pKeyboard; }

	/** 获得鼠标 */
	CMouse*       GetMouse() {  return  m_pMouse; }

	/** 获得游戏杆 */
	CJoystick*   GetJoystick() {  return  m_pJoystick; }
	
	/** 得到当前的窗口句柄 */
	static HWND GetSysHWnd() {  return  m_hWnd; }
	
	/** 得到当前的输入设备 */
	static CInputSystem* GetSysInput(){  return  m_pInput; }

private:
	/** 输入系统 */
	static CInputSystem*  m_pInput;

	/** 窗口句柄 */
	static HWND  m_hWnd;

	/** 键盘 */
	CKeyboard*    m_pKeyboard;

	/** 鼠标 */
	CMouse*       m_pMouse;

	/** 游戏杆 */
	CJoystick*    m_pJoystick;

	/** 输入设备 */
	LPDIRECTINPUT8 m_pDI;

};

//////////////////////////////////////////////////////////////////////////
/**  CKeybord类inline操作和实现 */ 

/** key键是否按下 */
inline bool CKeyboard::KeyDown(char key)
{
	return (m_keys[key] & 0x80) ? true : false;
}

/** key键是否按下 */
inline bool CKeyboard::KeyUp(char key)
{
	return (m_keys[key] & 0x80) ? false : true;
}

/** 对键盘数据清零 */
inline void CKeyboard::Clear()
{
	ZeroMemory(m_keys,256*sizeof(char));
}

/** 取键盘数据 */
inline bool CKeyboard::Acquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Acquire()));
}

/** 停止取数据 */
inline bool CKeyboard::Unacquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Unacquire()));
}

//////////////////////////////////////////////////////////////////
/**  CMoust类inline操作和实现 */ 

/** 获得光标位置 */
inline Point2 CMouse::GetMousePos()
{
	return m_iMousePos;
}

/** 取鼠标数据 */
inline bool CMouse::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

/** 停止取数据 */
inline bool CMouse::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}

//////////////////////////////////////////////////////////////////
/**  CJoystick类inline操作和实现 */ 

/** 取手柄数据 */
inline bool CJoystick::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

/** 停止取数据 */
inline bool CJoystick::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}

/** 判断手柄按键 */
inline bool CJoystick::IsButtonPressed(int iButton)
{
	if(m_diJoyState2.rgbButtons[iButton] & 0x80)
		return true;
	else
		return false;
}

/** 设置函数 */
inline void CJoystick::SetMin(int min)
{
	m_iMin = min;
}

inline void CJoystick::SetMax(int max)
{
	m_iMax = max;
}

inline void CJoystick::SetDeadZone(int deadzone)
{
	m_iDeadZone = deadzone;
}

/////////////////////////////////////////////////////////////
/** CInputSystem类的inline操作 */

/** 取输入设备的数据 */
inline void CInputSystem::AcquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Acquire();
	if (m_pMouse)		m_pMouse->Acquire();
	if(m_pJoystick)     m_pJoystick->Acquire();
	
}

/** 停止取数据 */
inline void CInputSystem::UnacquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Unacquire();
	if (m_pMouse)		m_pMouse->Unacquire();
	if(m_pJoystick)     m_pJoystick->Unacquire();
	
}


#endif //__INPUT_H__
