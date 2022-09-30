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
#include "Sound.h"
#include "Snow.h"
#include "Protechny.h"
#include "Light.h"


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
CSoundManager* g_pSoundManager;                     /**< 音频系统管理类 */
CSound*        g_pSound1;                           /**< 声音1 */
CSound*        g_pSound2;                           /**< 声音2 */
CSnow			g_Snow; //雪花实例
CProtechny g_Protechny;
Light g_light;

float g_Fps;
bool  g_RenderMode;//绘制模式
bool g_Sp;//空格键是否释放
bool g_Mp;//'M'键是否释放
float lift; //摄像机升降
bool fog_switch;//控制雾效的开关
bool sound_switch;//
bool isSoundPlaying;//
bool snow_switch;//

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc




//protechny 初始化函数
void ProtechnyInit(){


	glPushAttrib(GL_ALL_ATTRIB_BITS);


	glEnable(GL_TEXTURE_2D);             /**< 开启纹理映射 */

	/** 设置混合因子获得半透明效果 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);				     /**< 启用混和 */

	
	if (!g_Protechny.Init(5000))
	{
		MessageBox(NULL, "protechny系统初始化失败!", "错误", MB_OK);
		exit(-1);
	}


	glPopAttrib();
}





//snow初始化函数
void  SnowInit(){

	glPushAttrib(GL_ALL_ATTRIB_BITS);


	glEnable(GL_TEXTURE_2D);             /**< 开启纹理映射 */

	/** 设置混合因子获得半透明效果 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);				     /**< 启用混和 */

	if (!g_Snow.Init(50000))
	{
		MessageBox(NULL, "雪花系统初始化失败!", "错误", MB_OK);
		exit(-1);
	}



	glPopAttrib();

}



//snow draw 函数
void SnowDraw(){



	Vector3 cameraPos = g_Camera.getPosition();

	


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glTranslatef(400, 220, 400);
	glScalef(200, 200, 200);



	//渲染雪花
	g_Snow.Render();


	glTranslated(0, 0, 1);
	glRotatef(90, 0, 1, 0);


	//旋转后二次渲染雪花
	g_Snow.Render();

	glPopMatrix();
	glPopAttrib();

}



//protechny draw 函数
void ProtechnyDraw(){

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glTranslatef(200, 240, 600);

	glScalef(30,30,30);

	//渲染喷泉
	g_Protechny.Render();

	glRotatef(90, 0, 1, 0);

	//旋转后二次渲染喷泉
	g_Protechny.Render();


	glPopMatrix();
	glPopAttrib();
}



//音频系统和声音对象初始化函数
void SoundRelatedInit(){

	g_pSoundManager = new CSoundManager();
	g_pSound1 = new CSound();
	g_pSound2 = new CSound();


	/** 音频系统初始化 */
	g_pSoundManager->Init(hWnd);

	/** 设置主缓冲区格式 */
	g_pSoundManager->SetPrimaryBuffer();

}


//控制声音播放
void  soundPlay(){
	/** 载入声音并播放 */

	g_pSound2->LoadWaveFile("explosion.wav");
	g_pSound2->Play(true);

	g_pSound1->LoadWaveFile("airplane.wav");
	g_pSound1->Play(true);

}


//音频系统和声音对象卸载函数
void SoundRelatedUninit(){

	if (g_pSound1)
		delete g_pSound1;
	if (g_pSound2)
		delete g_pSound2;

	if (g_pSoundManager)
		delete g_pSoundManager;

}






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


	///** 按下‘P’键停止飞机声音播放 */
	//if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_P))
	//{
	//	g_pSound1->Stop();
	//	
	//}

	///** 按下‘X’键停止爆炸声音播放 */
	//if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_X))
	//{
	//	g_pSound2->Stop();
	//}




	/** 输出提示信息 */
	glColor3f(1.0f, 0.0f, 1.0f);
	g_Font.PrintText(string1, -5.0, 2.f);


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
		g_Camera.setSpeed(5.f);
	}
	if (!g_Keys.IsPressed(VK_SHIFT))
	{
		g_Camera.setSpeed(1.f);
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

	//控制sound_switch
	if (g_Keys.IsPressed('P'))
		sound_switch = !sound_switch;


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
	sprintf(string, "当前位置:X=%3.1f Y=%3.1f Z=%3.1f Speed =%3.1f ",
		g_Camera.getPosition().x,g_Camera.getPosition().y, g_Camera.getPosition().z, g_Camera.getSpeed()); /**< 字符串赋值 */
	g_Font.PrintText(string, -5.0f, 3.5f);

	sprintf(string, "当前观察点:X=%3.1f Y=%3.1f Z=%3.1f  ",
		g_Camera.getView().x, g_Camera.getView().y, g_Camera.getView().z); /**< 字符串赋值 */
	g_Font.PrintText(string, -5.0f, 3.f);


	/** 输出帧速 */
	CaculateFrameRate();                               /**< 计算帧速 */
	sprintf(string, "FPS:%d", (int)g_Fps);               /**< 字符串赋值 */
	g_Font.PrintText(string, -5.0f, 2.5f);              /**< 输出字符串 */

	//输入系统有关字体显示
	InputSystemDraw();

	/** 输出帧名称 */
	sprintf(string, "当前动作:%s(按'M'键切换下一个动作)", g_MD2.GetModel().pAnimations[g_MD2.GetModel().currentAnim].strName);
	g_Font.PrintText(string, -5.0f, 1.5f);

	/** 输出声音控制提示信息 */
	g_Font.PrintText("按下‘P’键开关声音", -5.f, 1.f);
	g_Font.PrintText("按下‘X’键开关雪", -5.f, .5f);

	//网格模式开关提示
	g_Font.PrintText("按下空格键开关网格绘制模式", -5.f, 0.f);


	//雾效开关提示
	g_Font.PrintText("按下'F'键开关雾效", -5.f, -.5f);


	glPopAttrib();

}


/** 显示3DS模型 */
void Show3DS(float x, float z, float scale)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	float y = g_Terrain.getAveHeight(x, z);  /**< 获得此处地形高度 */
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	g_3DS.Draw();                            /**< 显示3DS模型 */
	glPopMatrix();
	glPopAttrib();
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

	//灯光更新
	g_light.Update();

	/** 输入系统更新 */
	g_pInputForKeyboard->Update();
	g_pInputForMouse->Update();

	/** 更新摄像机 */
	UpdateCamera();

	/** 根据开关决定是否初始化雾效 */
	if (fog_switch)
	{
		CTerrain::initFog();
	}
	else
	{
		CTerrain::uninitFog();
	}

	//根据开关状态和声音播放状态决定行为
	if (sound_switch && !isSoundPlaying)
	{
		soundPlay();
		isSoundPlaying = true;
	}
	else if (!sound_switch && isSoundPlaying)
	{
		g_pSound1->Stop();
		g_pSound2->Stop();
		isSoundPlaying = false;
	}


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


	//按f开关雾效
	if (g_Keys.IsPressed('F'))
	{
		fog_switch = !fog_switch;
	}

	//按x开关雪景
	if (g_Keys.IsPressed('X'))
	{
		snow_switch = !snow_switch;
	}

	
}



//主卸载函数
void Uninit(){

	InputSystemUninit();
	SoundRelatedUninit();
}























































