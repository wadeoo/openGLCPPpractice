//======================================================================
/**
*  @file      Input.cpp
*
*  ��Ŀ������ DirectInput����ϵͳ
*   
*  �ļ�����:  ����ϵͳ��CInputSystem
*             ����,��CKeyboard��CMouse��CJoystick�ֱ�����������̡����
*             ����Ϸ�ֱ���CInputSystem�������豸�Ĺ����ࡣ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-24	
*  �޸����ڣ� 2007-07-24
*/																			
//======================================================================

#include "Input.h"


//************** ������CKeyboard��ʵ�� **************************/
/** ���캯�� */
CKeyboard::CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd)
{
	/** �����豸���� */
	if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
	{
		MessageBox(NULL,"���������豸����ʧ�ܣ�","����",MB_OK);
	}

    /** �������ݸ�ʽ */
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(NULL,"���ü������ݸ�ʽʧ�ܣ�","����",MB_OK);
	}

    /** ����Э����� */ 
	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(NULL,"���ü���Э�����ʧ�ܣ�","����",MB_OK);
	}

	/** �������� */ 
	if (FAILED(m_pDIDev->Acquire()))
	{
		MessageBox(NULL,"��������豸ʧ�ܣ�","����",MB_OK);
	}

	/** ������������ */
	Clear();
}

/** �������� */
CKeyboard::~CKeyboard()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}

/** ���¼������� */
bool CKeyboard::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
  {
		if (FAILED(m_pDIDev->Acquire()))
			return false;

		if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys),(LPVOID)m_keys)))
			return false;
	}

	return TRUE;
}

//************** �����CMouse��ʵ�� **************************/
/** ���캯�� */
CMouse::CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive)
{




	/** �õ���ǰ���ڵĴ�С */
	RECT r;
	GetClientRect(hwnd , &r);
	m_iWidth = r.right - r.left;
	m_iHeight = r.bottom - r.top;

	m_iMousePos.x = m_iWidth/2;
	m_iMousePos.y = m_iHeight/2;

	/** �����豸���� */
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
	{
		MessageBox(NULL,"��������豸����ʧ�ܣ�","����",MB_OK);
	}

	/** �������ݸ�ʽ */
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(NULL,"����������ݸ�ʽʧ�ܣ�","����",MB_OK);
	}

	DWORD flags;

	if (isExclusive)
		flags = DISCL_FOREGROUND|DISCL_EXCLUSIVE|DISCL_NOWINKEY;
	else
		flags = DISCL_FOREGROUND|DISCL_NONEXCLUSIVE;

	/** ����Э����� */
	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, flags)))
	{
		MessageBox(NULL,"�������Э�����ʧ�ܣ�","����",MB_OK);
	}
    
	/** ����������� */
	DIPROPDWORD  dipROPWORD;
	dipROPWORD.diph.dwSize = sizeof(DIPROPDWORD);
	dipROPWORD.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipROPWORD.diph.dwObj = 0;
	dipROPWORD.diph.dwHow = DIPH_DEVICE;
	dipROPWORD.dwData = DINPUT_BUFFERSIZE;
	
	if(FAILED(m_pDIDev->SetProperty(DIPROP_BUFFERSIZE,&dipROPWORD.diph)))
	{
		MessageBox(NULL,"��������豸����ʧ�ܣ�","����",MB_OK);
	}
	
	/** �����豸 */
	if (FAILED(m_pDIDev->Acquire()))
	{
		MessageBox(NULL,"��������豸ʧ�ܣ�","����",MB_OK);
	}

}

/** �ж��������Ƿ��� */
bool CMouse::IsLButtonPressed()
{
	for(int i=0;i<DINPUT_BUFFERSIZE; i++)
	{
		if((m_diData[i].dwOfs == DIMOFS_BUTTON0) && 
		   (m_diData[i].dwData & 0x80))
		   return true;
	}
	return false;
}

/** �ж�����Ҽ��Ƿ��� */
bool CMouse::IsRButtonPressed()
{
	for(int i=0;i<DINPUT_BUFFERSIZE; i++)
	{
		if((m_diData[i].dwOfs == DIMOFS_BUTTON1) && 
		   (m_diData[i].dwData & 0x80))
		   return true;
	}
	return false;
}


/** �ж�����м��Ƿ��� */
bool CMouse::IsMButtonPressed()
{
	for(int i=0;i<DINPUT_BUFFERSIZE; i++)
	{
		if((m_diData[i].dwOfs == DIMOFS_BUTTON2) && 
		   (m_diData[i].dwData & 0x80))
		   return true;
	}
	return false;
}

/** �������� */
CMouse::~CMouse()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}


/** ���������� */
bool CMouse::Update()
{
	HRESULT  hr;
	DWORD  dwReadNum = 1;
	int i;

	/** ������껺���� */
	ZeroMemory(m_diData,sizeof(DIDEVICEOBJECTDATA) * DINPUT_BUFFERSIZE);

	/**ѭ����ȡ������� */
	for(i=0; i<DINPUT_BUFFERSIZE;i++)
	{
		hr = m_pDIDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
							&m_diData[i],&dwReadNum,0);
		if(hr == DIERR_INPUTLOST)
		{
			m_pDIDev->Acquire();
			hr = m_pDIDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
							&m_diData[i],&dwReadNum,0);
			if(FAILED(hr))
			{
				MessageBox(NULL,"ȡ����껺��������ʧ��!","����",MB_OK);
				return false;
			}
		}

		/** �������λ�� */
		if(m_diData[i].dwOfs == DIMOFS_X)
			m_iMousePos.x += m_diData[i].dwData;

		if(m_diData[i].dwOfs == DIMOFS_Y)
			m_iMousePos.y += m_diData[i].dwData;
		
		/** ��������ڴ��ڷ�Χ */
		if(m_iMousePos.x < 0)
			m_iMousePos.x = 0;
		if(m_iMousePos.x> m_iWidth)
			m_iMousePos.x = m_iWidth;
		if(m_iMousePos.y < 0)
			m_iMousePos.y = 0;
		if(m_iMousePos.y > m_iHeight)
			m_iMousePos.y = m_iHeight;
        		
	}
	return true;
}


//************** ��Ϸ�ֱ�CJoystick��ʵ�� *******************************/

CJoystick::CJoystick(LPDIRECTINPUT8 pDI,HWND hwnd,HINSTANCE appInstance)
:m_iMin(-100),m_iMax(100),m_iDeadZone(20)
{
	HRESULT hr;
	m_pDI = pDI;

	/** ö���Ѱ�װ��������Ϸ�� */
	/**hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL,(LPDIENUMDEVICESCALLBACKA)EnumJSCallback,&m_pDIDev,DIEDFL_ATTACHEDONLY);
	if(FAILED(hr))
	{
		MessageBox(NULL,"ö����Ϸ��ʧ��!","����",MB_OK);
		exit(-1);
	}*/
	if(m_pDIDev == NULL)
	{
		MessageBox(NULL,"û�а�װ��Ϸ��!","����",MB_OK);
		exit(-1);
	}

	/** ������Ϸ�˵����ݸ�ʽ */
	hr = m_pDIDev->SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hr))
		MessageBox(NULL,"������Ϸ�����ݸ�ʽʧ�ܣ�","����",MB_OK);

	/** ������Ϸ�˵�Э���㼶 */
	hr = m_pDIDev->SetCooperativeLevel(hwnd,DISCL_BACKGROUND|DISCL_NONEXCLUSIVE);
	if(FAILED(hr))
		MessageBox(NULL,"������Ϸ��Э���㼶ʧ�ܣ�","����",MB_OK);

	/** ������Ϸ�˵��᷶Χ */
	DIPROPRANGE  dipROPRANGE;
	dipROPRANGE.diph.dwSize = sizeof(DIPROPRANGE);
	dipROPRANGE.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipROPRANGE.diph.dwObj = 0;
	dipROPRANGE.diph.dwHow = DIPH_DEVICE;
	dipROPRANGE.lMin = m_iMin;
	dipROPRANGE.lMax = m_iMax;

	hr = m_pDIDev->SetProperty(DIPROP_RANGE,&dipROPRANGE.diph);
	if(FAILED(hr))
		MessageBox(NULL,"������Ϸ���᷶Χʧ�ܣ�","����",MB_OK);

	/** ������Ϸ�˵�������Χ */
	DIPROPDWORD  dipROPDWORD;
	dipROPDWORD.diph.dwSize = sizeof(DIPROPDWORD);
	dipROPDWORD.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipROPDWORD.diph.dwObj = 0;
	dipROPDWORD.diph.dwHow = DIPH_DEVICE;
	dipROPDWORD.dwData = 100 * m_iDeadZone;

	hr = m_pDIDev->SetProperty(DIPROP_DEADZONE,&dipROPDWORD.diph);
	if(FAILED(hr))
		MessageBox(NULL,"������Ϸ��������Χʧ�ܣ�","����",MB_OK);

	/** ��ʼ�������� */
	ZeroMemory(&m_diJoyState2,sizeof(DIJOYSTATE2));
    

}

/** �ص����� */
bool CALLBACK CJoystick::EnumJSCallback(LPCDIDEVICEINSTANCE  pDIDeviceInstance, LPVOID pvRef)
{
	HRESULT hr;
	LPDIRECTINPUTDEVICE8* ppDID = (LPDIRECTINPUTDEVICE8* )pvRef;
	hr = m_pDI->CreateDevice(pDIDeviceInstance->guidInstance,ppDID,NULL);
	if(FAILED(hr))
		return DIENUM_CONTINUE;
	else
		return DIENUM_STOP;
}

/** ���£���ȡ���� */
bool CJoystick::Update()
{
	/** ��ȡ��Ϸ�˵ķ���Ȩ */
	HRESULT hr;
	hr = m_pDIDev->Acquire();
	if(FAILED(hr))
	{
		MessageBox(NULL,"�����Ϸ�˷���Ȩʧ�ܣ�","����",MB_OK);
		return false;
	}

	/** �����Ϸ�� */
	hr = m_pDIDev->Poll();
	if(FAILED(hr))
	{
		MessageBox(NULL,"�����Ϸ��ʧ�ܣ�","����",MB_OK);
		return false;
	}

	/** ��ȡ��Ϸ�˵����� */
	hr = m_pDIDev->GetDeviceState(sizeof(DIJOYSTATE2),&m_diJoyState2);
	
	/** �豸��ʧ */
	if(hr == DIERR_INPUTLOST)
	{
		m_pDIDev->Acquire();  /**< ���»���豸ʹ��Ȩ */
		m_pDIDev->GetDeviceState(sizeof(DIJOYSTATE2),&m_diJoyState2);
		if(FAILED(hr))
		{
			MessageBox(NULL,"��ȡ��Ϸ������ʧ�ܣ�","����",MB_OK);
			return false;
		}

	}
	return true;

}

CJoystick::~CJoystick()
{
	if (m_pDI)
		m_pDI->Release();


	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}


//************** ����ϵͳ��CInputSystem��ʵ�� **************************/

CInputSystem* CInputSystem::m_pInput = NULL;
HWND CInputSystem::m_hWnd = NULL;

/** ��ʼ���豸 */
bool CInputSystem::Init(HWND hwnd,HINSTANCE appInstance,
						bool isExclusive,DWORD flags)
{
	m_pKeyboard = NULL; 
	m_pMouse = NULL;
	m_pJoystick = NULL;

	m_hWnd = hwnd;

	/** ����DirectInput�ӿڶ��� */
	if (FAILED(DirectInput8Create(appInstance,
								DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								(void **)&m_pDI,NULL)))
	{
		MessageBox(NULL,"����DirectInput�ӿڶ���ʧ��!","����",MB_OK);
		return false;
	}
    
	/** �������� */
	if (flags & IS_USEKEYBOARD)
	{
		m_pKeyboard = new CKeyboard(m_pDI, hwnd);
	}

	/** ������� */
	if (flags & IS_USEMOUSE)
	{
		m_pMouse = new CMouse(m_pDI, hwnd, true);
	}
	
	/** ������Ϸ�� */
	if (flags & IS_USEJOYSTICK)
	{
		m_pJoystick = new CJoystick(m_pDI,hwnd,appInstance);
	}

	return true;

}

/** ���������豸�Ĳ��� */
void CInputSystem::Update()
{
	/** ���̸��� */
	if (m_pKeyboard)	
		m_pKeyboard->Update();
	
	/** ������ */
	if (m_pMouse)		
		m_pMouse->Update();
	
	/** ��Ϸ�˸��� */
	if (m_pJoystick)		
		m_pJoystick->Update();

}

/** �ͷ������豸��Դ */
bool CInputSystem::ShutDown()
{
	UnacquireAll();

    if (m_pKeyboard)
	{  
		delete m_pKeyboard;
		m_pKeyboard  = NULL;
	}

    if (m_pMouse)
	{
	   delete m_pMouse;
	   m_pMouse = NULL;
	}

	if (m_pJoystick)
	{
	   delete m_pJoystick;
	   m_pJoystick = NULL;
	}
    
	/** �ͷŽӿڶ��� */
	if (FAILED(m_pDI->Release()))
		return false;

     return true;
}

/** ��ù���3D���� */
Vector3  CInputSystem::GetMousePosition()
{
	float depth[2];
	Point2 p;

	/** �õ����ĵ�ǰ2Dλ�� */
	p = m_pMouse->GetMousePos();

	GLdouble x,y,z;

	/** �õ����ص����ֵ */
	glReadPixels(p.x,p.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,depth);
	
	/** �õ�ģ�;����ͶӰ���� */
	GLdouble model[16],project[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,model);
	glGetDoublev(GL_PROJECTION_MATRIX,project);

	/** ����õ���������� */
	GLint viewport[4]={0,0,m_pMouse->m_iWidth,m_pMouse->m_iHeight};
	gluUnProject(p.x,p.y,depth[0],model,project,viewport,&x,&y,&z);

	return Vector3((float)x,(float)y,(float)z);
}


