/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include "Camera.h"
#include "Keys.h"
#include "3DSLoader.h"
#include "MD2Loader.h"
#include "Font.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "Input.h"

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

GLfloat	rtri;				// Angle For The Triangle ( NEW )
GLfloat	rquad;				// Angle For The Quad ( NEW )

void UpdateCamera();

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

Camera f_Camera;
Keys f_Keys;
GLFont f_Font;
CSkyBox f_SkyBox;
CTerrain f_Terrain;

float f_Fps=0;
bool f_sp=false;
bool f_RenderMode=true;
bool f_mp = false;

CInputSystem*  f_pInput; 
CInputSystem*  f_pInputForMouse; 




C3DSLoader f_3DS;
CMD2Loader f_MD2;

//direct keyboard drawfunc
void DirectKeyboardDraw(){
	/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);

	/** 检测键盘输入数据 */
	char string[50] = { "您没有按下任何键" };

	/** 检测A键按下？ */
	if (f_pInput->GetKeyboard()->KeyDown(DIK_A))
		sprintf(string, "您按下了 %s 键", "A");

	/** 检测F1键按下？ */
	if (f_pInput->GetKeyboard()->KeyDown(DIK_F1))
		sprintf(string, "您按下了 %s 键", "F1");

	/** 检测Ctrl和A键同时按下？*/
	if (f_pInput->GetKeyboard()->KeyDown(DIK_A) &&
		f_pInput->GetKeyboard()->KeyDown(DIK_LCONTROL))
		sprintf(string, "您按下了 %s 键", "CTRL + A");

	/** 输出提示信息 */
	glColor3f(1.0f, 0.0f, 1.0f);
	f_Font.PrintText(string, -2.0, 0.0);

	glFlush();
}


void DirectMouseDraw(){
	/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);

	/** 检测鼠标输入数据 */
	char string[50];
	static bool flag = false;
	static bool lButtonDown = false;
	static bool rButtonDown = false;

	/** 设置变量 */
	if (f_pInputForMouse->GetMouse()->IsLButtonPressed())
		lButtonDown = true;
	if (f_pInputForMouse->GetMouse()->IsRButtonPressed())
		rButtonDown = true;

	if (lButtonDown && f_pInputForMouse->GetMouse()->IsLButtonPressed() == false)
	{
		lButtonDown = false;
		flag = false;
	}

	if (rButtonDown && f_pInputForMouse->GetMouse()->IsRButtonPressed() == false)
	{
		rButtonDown = false;
		flag = false;
	}

	/** 左键按下时 */
	if (lButtonDown && !flag)
	{
		flag = true;
		sprintf(string, "鼠标左键被按下，位置为：%d,%d",
			f_pInputForMouse->GetMouse()->GetMousePos().x,
			f_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string, "提示", MB_OK);

	}

	/** 右键按下时 */
	if (rButtonDown && !flag)
	{
		flag = true;
		sprintf(string, "鼠标右健被按下，位置为：%d,%d",
			f_pInputForMouse->GetMouse()->GetMousePos().x,
			f_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string, "提示", MB_OK);

	}

	glFlush();
}




/** 计算帧速 */
void CaculateFrameRate()
{
	static float framesPerSecond = 0.0f;	     /**< 保存显示帧数 */
	static float lastTime = 0.0f;	     /**< 记录上次时间 */
	float currentTime = GetTickCount() * 0.001f; /**< 获得当前时间 */

	framesPerSecond++;                           /**< 显示帧数递增1 */
	/** 如果时间差大于1.0秒 */
	if (currentTime - lastTime > 1.0f)
	{

		lastTime = currentTime;                   /**< 保存当前时间 */
		f_Fps = framesPerSecond;                  /**< 当前帧数传给m_Fps */
		framesPerSecond = 0;                      /**< 将帧数置零 */
	}
}



/** 输出文字信息 */
void  mainPrintText()
{
	char string[128];                               /**< 用于保存输出字符串 */
	glPushAttrib(GL_CURRENT_BIT);                   /**< 保存现有颜色属性信息 */
	glColor3f(0.0f, 1.0f, 1.0f);                      /**< 设置文字颜色 */
	sprintf(string, "当前位置:X=%3.1f  Y=%3.1f Speed =%3.1f ",
		f_Camera.getPosition().x, f_Camera.getPosition().z, f_Camera.getSpeed()); /**< 字符串赋值 */
	f_Font.PrintText(string, -5.0f, 3.5f);

	/** 输出帧速 */
	CaculateFrameRate();                               /**< 计算帧速 */
	sprintf(string, "FPS:%d", (int)f_Fps);               /**< 字符串赋值 */
	f_Font.PrintText(string, -5.0f, 3.0f);              /**< 输出字符串 */


	/** 输出帧名称 */
	sprintf(string, "当前动作:%s(按'M'键切换下一个动作)", f_MD2.GetModel().pAnimations[f_MD2.GetModel().currentAnim].strName);
	f_Font.PrintText(string, -5.0f, 2.5f);
	glPopAttrib();

}



void UpdateCamera()
{
	f_Camera.setViewByMouse();

	/** 键盘按键响应 */
	if (f_Keys.IsPressed(VK_SHIFT))                      /**< 按下SHIFT键时加速 */
	{
		f_Camera.setSpeed(2.0f);
	}
	if (!f_Keys.IsPressed(VK_SHIFT))
	{
		f_Camera.setSpeed(1.0f);
	}
	if (f_Keys.IsPressed(VK_UP) || f_Keys.IsPressed('W'))   /**< 向上方向键或'W'键按下 */
		f_Camera.moveCamera(f_Camera.getSpeed());          /**< 移动摄像机 */

	if (f_Keys.IsPressed(VK_DOWN) || f_Keys.IsPressed('S')) /**< 向下方向键或'S'键按下 */
		f_Camera.moveCamera(-f_Camera.getSpeed());         /**< 移动摄像机 */

	if (f_Keys.IsPressed(VK_LEFT) || f_Keys.IsPressed('A')) /**< 向左方向键或'A'键按下 */
		f_Camera.yawCamera(-f_Camera.getSpeed());          /**< 移动摄像机 */

	if (f_Keys.IsPressed(VK_RIGHT) || f_Keys.IsPressed('D')) /**< 向右方向键或'D'键按下 */
		f_Camera.yawCamera(f_Camera.getSpeed());            /**< 移动摄像机 */

	/** 空格键切换绘制模式 */
	if (f_Keys.IsPressed(VK_SPACE) && !f_sp)
	{
		f_sp = true;
		f_RenderMode = !f_RenderMode;
		if (f_RenderMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


	if (!f_Keys.IsPressed(VK_SPACE))
		f_sp = false;




	/** 'M'键播放下一个动作 */
	if (f_Keys.IsPressed('M') && !f_mp)
	{
		f_mp= true;

		/** 设置当前动作为下一个动作 */
		f_MD2.GetModel().currentAnim = (f_MD2.GetModel().currentAnim + 1) % (f_MD2.GetModel().numOfAnimations);

		/** 设置当前帧为下一个动作的开始帧 */
		f_MD2.GetModel().currentFrame = (f_MD2.GetModel()).pAnimations[f_MD2.GetModel().currentAnim].startFrame;
	}
	if (!f_Keys.IsPressed('M'))
	{
		f_mp= false;
	}

}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/** 创建输入系统 */
	f_pInput = new CInputSystem();

	/** 输入系统初始化 */
	f_pInput->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD);


	/** 创建输入系统鼠标 */
	f_pInputForMouse = new CInputSystem();

	/** 输入系统初始化 */
	f_pInputForMouse->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true,IS_USEMOUSE);


	/*初始化字体*/
	if (!f_Font.InitFont())
		MessageBox(NULL, "初始化字体失败!", "错误", MB_OK);

	if (!f_Terrain.init())
		MessageBox(NULL, "初始化地形失败", "错误", MB_OK);

	if (!f_SkyBox.init())
		MessageBox(NULL, "初始化字体失败!", " 错误", MB_OK);



	/** 初始化3DS文件 */
	f_3DS.Init("data/model.3ds");
	f_MD2.Init("hobgoblin.MD2", "hobgoblin.bmp");

	f_Camera.setCamera(0.0f, 1.5f, 6.0f, 0.0f, 0.0f, -1.f, 0.0f, 1.0f, 0.0f);
//	f_Camera.setCamera(381, 35, 674, 374.5, 35, 669, 0, 1, 0);



	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{


	/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	DirectKeyboardDraw();

	DirectMouseDraw();







	/** 放置摄像机 */
	f_Camera.setLook();

	//地形
	f_Terrain.render();

	//天空
	f_SkyBox.render();

	//3ds
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);
	f_3DS.Draw();                            /**< 显示3DS模型 */
	glPopMatrix();

	//glLoadIdentity();
	///** 放置摄像机 */
	//f_Camera.setLook();

	//md2
	glPushAttrib(GL_CURRENT_BIT); /**< 保存现有颜色属实性 */
	glPushMatrix();
	glTranslatef(-5, 1, 0);
	//glTranslatef(300,600,18);

	//glScalef(.05f,.05f,.05f);
	glScalef(0.5f,0.5f,0.5f);

	f_MD2.AnimateMD2Model();
	glPopMatrix();
	glPopAttrib();   /**< 恢复前一属性 */

	mainPrintText();


	glFlush();

	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{

	/** 用户自定义的卸载过程 */
	if (f_pInput)
	{
		delete f_pInput;
		f_pInput = NULL;
	}


	if (f_pInputForMouse)
	{
		delete f_pInputForMouse;
		f_pInputForMouse = NULL;
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}


}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< 得到屏幕宽度的一半 */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< 得到屏幕高度的一半 */

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		middleX-(WindowRect.right - WindowRect.left)/2, middleY-(WindowRect.bottom - WindowRect.top)/2,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
		// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
		// A NonZero Value Indicates The Window Is Minimized.
		if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
			active = TRUE;						// Program Is Active
		else
			active = FALSE;						// Program Is No Longer Active

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		f_Keys.SetPressed(wParam);

		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		f_Keys.SetReleased(wParam);

		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Solid Object Tutorial",640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done = TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's Solid Object Tutorial", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
			UpdateCamera();
			f_pInput->Update();
			f_pInputForMouse->Update();
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
