#pragma once

class Lesson5_2022_9_26
{
public:
	Lesson5_2022_9_26();
	~Lesson5_2022_9_26();
};


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
#include "stdafx.h"
#include "CBMPLoader.h"
#include "Font.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "3DSLoader.h"
#include "MD2Loader.h"
#include "Keys.h"
#include "Input.h"


HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

C3DSLoader g_3DS;
CMD2Loader g_MD2;
CTerrain g_Terrain;
CSkyBox g_SkyBox;
GLFont g_Font;
Camera g_Camera;
Keys   g_Keys;
CInputSystem* g_pInputForKeyboard;
CInputSystem* g_pInputForMouse;

float g_Fps;
bool  g_RenderMode;//绘制模式
bool g_Sp;//空格键是否释放
bool g_Mp;//'M'键是否释放
float lift; //摄像机升降



LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc


//输入系统初始化
void InputSystemInit(){
	/** 创建输入系统 */
	g_pInputForKeyboard = new CInputSystem();

	/** 输入系统初始化 */
	g_pInputForKeyboard->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD);

	/** 创建输入系统 */
	g_pInputForMouse = new CInputSystem();

	/** 输入系统初始化 */
	g_pInputForMouse->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD | IS_USEMOUSE);
}





//输入系统卸载
void InputSystemUninit(){

	if (g_pInputForKeyboard)
	{
		delete g_pInputForKeyboard;
		g_pInputForKeyboard = NULL;
	}

	if (g_pInputForMouse)
	{
		delete g_pInputForMouse;
		g_pInputForMouse = NULL;
	}
}

//输入系统draw func  在printText()中使用
void InputSystemDraw(){

	//for keyboard 
	/** 检测键盘输入数据 */
	char string1[50] = { "您没有按下任何键" };

	/** 检测A键按下？ */
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_A))
		sprintf(string1, "您按下了 %s 键", "A");

	/** 检测F1键按下？ */
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_F1))
		sprintf(string1, "您按下了 %s 键", "F1");

	/** 检测Ctrl和A键同时按下？*/
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_A) &&
		g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_LCONTROL))
		sprintf(string1, "您按下了 %s 键", "CTRL + A");

	/** 输出提示信息 */
	glColor3f(1.0f, 0.0f, 1.0f);
	g_Font.PrintText(string1, -5.0, 2.5);


	//fot mouse
	/** 检测鼠标输入数据 */
	char string2[50];
	static bool flag = false;
	static bool lButtonDown = false;
	static bool rButtonDown = false;

	/** 设置变量 */
	if (g_pInputForMouse->GetMouse()->IsLButtonPressed())
		lButtonDown = true;
	if (g_pInputForMouse->GetMouse()->IsRButtonPressed())
		rButtonDown = true;

	if (lButtonDown && g_pInputForMouse->GetMouse()->IsLButtonPressed() == false)
	{
		lButtonDown = false;
		flag = false;
	}

	if (rButtonDown && g_pInputForMouse->GetMouse()->IsRButtonPressed() == false)
	{
		rButtonDown = false;
		flag = false;
	}

	/** 左键按下时 */
	if (lButtonDown && !flag)
	{
		flag = true;
		sprintf(string2, "鼠标左键被按下，位置为：%d,%d",
			g_pInputForMouse->GetMouse()->GetMousePos().x,
			g_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string2, "提示", MB_OK);

	}

	/** 右键按下时 */
	if (rButtonDown && !flag)
	{
		flag = true;
		sprintf(string2, "鼠标右健被按下，位置为：%d,%d",
			g_pInputForMouse->GetMouse()->GetMousePos().x,
			g_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string2, "提示", MB_OK);

	}

}


/** 更新摄像机 */
void UpdateCamera()
{
	g_Camera.setViewByMouse();

	/** 键盘按键响应 */
	if (g_Keys.IsPressed(VK_SHIFT))                        /**< 按下SHIFT键时加速 */
	{
		g_Camera.setSpeed(10.f);
	}
	if (!g_Keys.IsPressed(VK_SHIFT))
	{
		g_Camera.setSpeed(6.f);
	}
	if (g_Keys.IsPressed(VK_UP) || g_Keys.IsPressed('W'))   /**< 向上方向键或'W'键按下 */
		g_Camera.moveCamera(g_Camera.getSpeed());          /**< 移动摄像机 */

	if (g_Keys.IsPressed(VK_DOWN) || g_Keys.IsPressed('S')) /**< 向下方向键或'S'键按下 */
		g_Camera.moveCamera(-g_Camera.getSpeed());         /**< 移动摄像机 */

	if (g_Keys.IsPressed(VK_LEFT) || g_Keys.IsPressed('A')) /**< 向左方向键或'A'键按下 */
		g_Camera.yawCamera(-g_Camera.getSpeed());          /**< 移动摄像机 */

	if (g_Keys.IsPressed(VK_RIGHT) || g_Keys.IsPressed('D')) /**< 向右方向键或'D'键按下 */
		g_Camera.yawCamera(g_Camera.getSpeed());            /**< 移动摄像机 */

	//控制摄像机升降
	if (g_Keys.IsPressed('Q'))
		lift++;
	if (g_Keys.IsPressed('E'))
		lift--;

	/** 根据地形高度更新摄像机 */
	Vector3 vPos = g_Camera.getPosition();                  /**< 得到当前摄像机位置 */
	Vector3 vNewPos = vPos;


	/** 设置摄像机高度为 地形高度 + 10 + lift*/
	vNewPos.y = (float)g_Terrain.getAveHeight(vPos.x, vPos.z) + 10+lift;

	/** 得到高度差值 */
	float temp = vNewPos.y - vPos.y;

	/** 更新摄像机方向 */
	Vector3 vView = g_Camera.getView();
	vView.y += temp;

	/** 设置摄像机 */
	g_Camera.setCamera(vNewPos.x, vNewPos.y, vNewPos.z,
		vView.x, vView.y, vView.z,
		0, 1, 0);

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
		g_Fps = framesPerSecond;                  /**< 当前帧数传给m_Fps */
		framesPerSecond = 0;                      /**< 将帧数置零 */
	}

}


/** 输出文字信息 */
void  PrintText()
{
	char string[128];                               /**< 用于保存输出字符串 */
	glPushAttrib(GL_CURRENT_BIT);                   /**< 保存现有颜色属性信息 */
	glColor3f(0.0f, 1.0f, 1.0f);                      /**< 设置文字颜色 */
	sprintf(string, "当前位置:X=%3.1f  Y=%3.1f Speed =%3.1f ",
		g_Camera.getPosition().x, g_Camera.getPosition().z, g_Camera.getSpeed()); /**< 字符串赋值 */
	g_Font.PrintText(string, -5.0f, 3.5f);

	/** 输出帧速 */
	CaculateFrameRate();                               /**< 计算帧速 */
	sprintf(string, "FPS:%d", (int)g_Fps);               /**< 字符串赋值 */
	g_Font.PrintText(string, -5.0f, 3.0f);              /**< 输出字符串 */

	//输入系统有关字体显示
	InputSystemDraw();

	/** 输出帧名称 */
	sprintf(string, "当前动作:%s(按'M'键切换下一个动作)", g_MD2.GetModel().pAnimations[g_MD2.GetModel().currentAnim].strName);
	g_Font.PrintText(string, -5.0f, 2.0f);

	glPopAttrib();

}


/** 显示3DS模型 */
void Show3DS(float x, float z, float scale)
{
	glPushMatrix();
	float y = g_Terrain.getAveHeight(x, z);  /**< 获得此处地形高度 */
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	g_3DS.Draw();                            /**< 显示3DS模型 */
	glPopMatrix();

}

//MD2模型显示加动画
void Md2Animate(float x, float z, float h, float scale){

	glPushAttrib(GL_CURRENT_BIT); /**< 保存现有颜色属实性 */
	float y = g_Terrain.getAveHeight(x, z) + h;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	g_MD2.AnimateMD2Model();
	glPopMatrix();
	glPopAttrib();   /**< 恢复前一属性 */
}

/** 程序更新函数 */
void Update()
{

	/** 用户自定义的更新过程 */

	/** 输入系统更新 */
	g_pInputForKeyboard->Update();
	g_pInputForMouse->Update();

	/** 更新摄像机 */
	UpdateCamera();

	/** 空格键切换绘制模式 */
	if (g_Keys.IsPressed(VK_SPACE) && !g_Sp)
	{
		g_Sp = true;
		g_RenderMode = !g_RenderMode;
		if (g_RenderMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (!g_Keys.IsPressed(VK_SPACE))
		g_Sp = false;

	/** 'M'键播放下一个动作 */
	if (g_Keys.IsPressed('M') && !g_Mp)
	{
		g_Mp= true;

		/** 设置当前动作为下一个动作 */
		g_MD2.GetModel().currentAnim = (g_MD2.GetModel().currentAnim + 1) % (g_MD2.GetModel().numOfAnimations);

		/** 设置当前帧为下一个动作的开始帧 */
		g_MD2.GetModel().currentFrame = (g_MD2.GetModel()).pAnimations[g_MD2.GetModel().currentAnim].startFrame;
	}
	if (!g_Keys.IsPressed('M'))
	{
		g_Mp= false;
	}
}



























































