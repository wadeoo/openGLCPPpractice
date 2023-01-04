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
CSoundManager* g_pSoundManager;                     /**< ��Ƶϵͳ������ */
CSound*        g_pSound1;                           /**< ����1 */
CSound*        g_pSound2;                           /**< ����2 */
CSnow			g_Snow; //ѩ��ʵ��
CProtechny g_Protechny;
Light g_light;

float g_Fps;
bool  g_RenderMode;//����ģʽ
bool g_Sp;//�ո���Ƿ��ͷ�
bool g_Mp;//'M'���Ƿ��ͷ�
float lift; //���������
bool fog_switch;//������Ч�Ŀ���
bool sound_switch;//
bool isSoundPlaying;//
bool snow_switch;//

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc




//protechny ��ʼ������
void ProtechnyInit(){


	glPushAttrib(GL_ALL_ATTRIB_BITS);


	glEnable(GL_TEXTURE_2D);             /**< ��������ӳ�� */

	/** ���û�����ӻ�ð�͸��Ч�� */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);				     /**< ���û�� */

	
	if (!g_Protechny.Init(5000))
	{
		MessageBox(NULL, "protechnyϵͳ��ʼ��ʧ��!", "����", MB_OK);
		exit(-1);
	}


	glPopAttrib();
}





//snow��ʼ������
void  SnowInit(){

	glPushAttrib(GL_ALL_ATTRIB_BITS);


	glEnable(GL_TEXTURE_2D);             /**< ��������ӳ�� */

	/** ���û�����ӻ�ð�͸��Ч�� */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);				     /**< ���û�� */

	if (!g_Snow.Init(50000))
	{
		MessageBox(NULL, "ѩ��ϵͳ��ʼ��ʧ��!", "����", MB_OK);
		exit(-1);
	}



	glPopAttrib();

}



//snow draw ����
void SnowDraw(){



	Vector3 cameraPos = g_Camera.getPosition();

	


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glTranslatef(400, 220, 400);
	glScalef(200, 200, 200);



	//��Ⱦѩ��
	g_Snow.Render();


	glTranslated(0, 0, 1);
	glRotatef(90, 0, 1, 0);


	//��ת�������Ⱦѩ��
	g_Snow.Render();

	glPopMatrix();
	glPopAttrib();

}



//protechny draw ����
void ProtechnyDraw(){

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glTranslatef(200, 240, 600);

	glScalef(30,30,30);

	//��Ⱦ��Ȫ
	g_Protechny.Render();

	glRotatef(90, 0, 1, 0);

	//��ת�������Ⱦ��Ȫ
	g_Protechny.Render();


	glPopMatrix();
	glPopAttrib();
}



//��Ƶϵͳ�����������ʼ������
void SoundRelatedInit(){

	g_pSoundManager = new CSoundManager();
	g_pSound1 = new CSound();
	g_pSound2 = new CSound();


	/** ��Ƶϵͳ��ʼ�� */
	g_pSoundManager->Init(hWnd);

	/** ��������������ʽ */
	g_pSoundManager->SetPrimaryBuffer();

}


//������������
void  soundPlay(){
	/** �������������� */

	g_pSound2->LoadWaveFile("explosion.wav");
	g_pSound2->Play(true);

	g_pSound1->LoadWaveFile("airplane.wav");
	g_pSound1->Play(true);

}


//��Ƶϵͳ����������ж�غ���
void SoundRelatedUninit(){

	if (g_pSound1)
		delete g_pSound1;
	if (g_pSound2)
		delete g_pSound2;

	if (g_pSoundManager)
		delete g_pSoundManager;

}






//����ϵͳ��ʼ��
void InputSystemInit(){
	/** ��������ϵͳ */
	g_pInputForKeyboard = new CInputSystem();

	/** ����ϵͳ��ʼ�� */
	g_pInputForKeyboard->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD);

	/** ��������ϵͳ */
	g_pInputForMouse = new CInputSystem();

	/** ����ϵͳ��ʼ�� */
	g_pInputForMouse->Init(hWnd, (HINSTANCE)GetModuleHandle(NULL),
		true, IS_USEKEYBOARD | IS_USEMOUSE);
}





//����ϵͳж��
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

//����ϵͳdraw func  ��printText()��ʹ��
void InputSystemDraw(){

	//for keyboard 
	/** �������������� */
	char string1[50] = { "��û�а����κμ�" };

	/** ���A�����£� */
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_A))
		sprintf(string1, "�������� %s ��", "A");

	/** ���F1�����£� */
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_F1))
		sprintf(string1, "�������� %s ��", "F1");

	/** ���Ctrl��A��ͬʱ���£�*/
	if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_A) &&
		g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_LCONTROL))
		sprintf(string1, "�������� %s ��", "CTRL + A");


	///** ���¡�P����ֹͣ�ɻ��������� */
	//if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_P))
	//{
	//	g_pSound1->Stop();
	//	
	//}

	///** ���¡�X����ֹͣ��ը�������� */
	//if (g_pInputForKeyboard->GetKeyboard()->KeyDown(DIK_X))
	//{
	//	g_pSound2->Stop();
	//}




	/** �����ʾ��Ϣ */
	glColor3f(1.0f, 0.0f, 1.0f);
	g_Font.PrintText(string1, -5.0, 2.f);


	//fot mouse
	/** �������������� */
	char string2[50];
	static bool flag = false;
	static bool lButtonDown = false;
	static bool rButtonDown = false;

	/** ���ñ��� */
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

	/** �������ʱ */
	if (lButtonDown && !flag)
	{
		flag = true;
		sprintf(string2, "�����������£�λ��Ϊ��%d,%d",
			g_pInputForMouse->GetMouse()->GetMousePos().x,
			g_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string2, "��ʾ", MB_OK);

	}

	/** �Ҽ�����ʱ */
	if (rButtonDown && !flag)
	{
		flag = true;
		sprintf(string2, "����ҽ������£�λ��Ϊ��%d,%d",
			g_pInputForMouse->GetMouse()->GetMousePos().x,
			g_pInputForMouse->GetMouse()->GetMousePos().y);
		MessageBox(NULL, string2, "��ʾ", MB_OK);

	}

}


/** ��������� */
void UpdateCamera()
{
	g_Camera.setViewByMouse();

	/** ���̰�����Ӧ */
	if (g_Keys.IsPressed(VK_SHIFT))                        /**< ����SHIFT��ʱ���� */
	{
		g_Camera.setSpeed(5.f);
	}
	if (!g_Keys.IsPressed(VK_SHIFT))
	{
		g_Camera.setSpeed(1.f);
	}
	if (g_Keys.IsPressed(VK_UP) || g_Keys.IsPressed('W'))   /**< ���Ϸ������'W'������ */
		g_Camera.moveCamera(g_Camera.getSpeed());          /**< �ƶ������ */

	if (g_Keys.IsPressed(VK_DOWN) || g_Keys.IsPressed('S')) /**< ���·������'S'������ */
		g_Camera.moveCamera(-g_Camera.getSpeed());         /**< �ƶ������ */

	if (g_Keys.IsPressed(VK_LEFT) || g_Keys.IsPressed('A')) /**< ���������'A'������ */
		g_Camera.yawCamera(-g_Camera.getSpeed());          /**< �ƶ������ */

	if (g_Keys.IsPressed(VK_RIGHT) || g_Keys.IsPressed('D')) /**< ���ҷ������'D'������ */
		g_Camera.yawCamera(g_Camera.getSpeed());            /**< �ƶ������ */

	//�������������
	if (g_Keys.IsPressed('Q'))
		lift++;
	if (g_Keys.IsPressed('E'))
		lift--;

	//����sound_switch
	if (g_Keys.IsPressed('P'))
		sound_switch = !sound_switch;


	/** ���ݵ��θ߶ȸ�������� */
	Vector3 vPos = g_Camera.getPosition();                  /**< �õ���ǰ�����λ�� */
	Vector3 vNewPos = vPos;


	/** ����������߶�Ϊ ���θ߶� + 10 + lift*/
	vNewPos.y = (float)g_Terrain.getAveHeight(vPos.x, vPos.z) + 10+lift;

	/** �õ��߶Ȳ�ֵ */
	float temp = vNewPos.y - vPos.y;

	/** ������������� */
	Vector3 vView = g_Camera.getView();
	vView.y += temp;

	/** ��������� */
	g_Camera.setCamera(vNewPos.x, vNewPos.y, vNewPos.z,
		vView.x, vView.y, vView.z,
		0, 1, 0);

}


/** ����֡�� */
void CaculateFrameRate()
{
	static float framesPerSecond = 0.0f;	     /**< ������ʾ֡�� */
	static float lastTime = 0.0f;	     /**< ��¼�ϴ�ʱ�� */
	float currentTime = GetTickCount() * 0.001f; /**< ��õ�ǰʱ�� */

	framesPerSecond++;                           /**< ��ʾ֡������1 */
	/** ���ʱ������1.0�� */
	if (currentTime - lastTime > 1.0f)
	{

		lastTime = currentTime;                   /**< ���浱ǰʱ�� */
		g_Fps = framesPerSecond;                  /**< ��ǰ֡������m_Fps */
		framesPerSecond = 0;                      /**< ��֡������ */
	}

}


/** ���������Ϣ */
void  PrintText()
{
	char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f, 1.0f, 1.0f);                      /**< ����������ɫ */
	sprintf(string, "��ǰλ��:X=%3.1f Y=%3.1f Z=%3.1f Speed =%3.1f ",
		g_Camera.getPosition().x,g_Camera.getPosition().y, g_Camera.getPosition().z, g_Camera.getSpeed()); /**< �ַ�����ֵ */
	g_Font.PrintText(string, -5.0f, 3.5f);

	sprintf(string, "��ǰ�۲��:X=%3.1f Y=%3.1f Z=%3.1f  ",
		g_Camera.getView().x, g_Camera.getView().y, g_Camera.getView().z); /**< �ַ�����ֵ */
	g_Font.PrintText(string, -5.0f, 3.f);


	/** ���֡�� */
	CaculateFrameRate();                               /**< ����֡�� */
	sprintf(string, "FPS:%d", (int)g_Fps);               /**< �ַ�����ֵ */
	g_Font.PrintText(string, -5.0f, 2.5f);              /**< ����ַ��� */

	//����ϵͳ�й�������ʾ
	InputSystemDraw();

	/** ���֡���� */
	sprintf(string, "��ǰ����:%s(��'M'���л���һ������)", g_MD2.GetModel().pAnimations[g_MD2.GetModel().currentAnim].strName);
	g_Font.PrintText(string, -5.0f, 1.5f);

	/** �������������ʾ��Ϣ */
	g_Font.PrintText("���¡�P������������", -5.f, 1.f);
	g_Font.PrintText("���¡�X��������ѩ", -5.f, .5f);

	//����ģʽ������ʾ
	g_Font.PrintText("���¿ո�������������ģʽ", -5.f, 0.f);


	//��Ч������ʾ
	g_Font.PrintText("����'F'��������Ч", -5.f, -.5f);


	glPopAttrib();

}


/** ��ʾ3DSģ�� */
void Show3DS(float x, float z, float scale)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	float y = g_Terrain.getAveHeight(x, z);  /**< ��ô˴����θ߶� */
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	g_3DS.Draw();                            /**< ��ʾ3DSģ�� */
	glPopMatrix();
	glPopAttrib();
}

//MD2ģ����ʾ�Ӷ���
void Md2Animate(float x, float z, float h, float scale){

	glPushAttrib(GL_CURRENT_BIT); /**< ����������ɫ��ʵ�� */
	float y = g_Terrain.getAveHeight(x, z) + h;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	g_MD2.AnimateMD2Model();
	glPopMatrix();
	glPopAttrib();   /**< �ָ�ǰһ���� */
}

/** ������º��� */
void Update()
{

	/** �û��Զ���ĸ��¹��� */

	//�ƹ����
	g_light.Update();

	/** ����ϵͳ���� */
	g_pInputForKeyboard->Update();
	g_pInputForMouse->Update();

	/** ��������� */
	UpdateCamera();

	/** ���ݿ��ؾ����Ƿ��ʼ����Ч */
	if (fog_switch)
	{
		CTerrain::initFog();
	}
	else
	{
		CTerrain::uninitFog();
	}

	//���ݿ���״̬����������״̬������Ϊ
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


	/** �ո���л�����ģʽ */
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

	/** 'M'��������һ������ */
	if (g_Keys.IsPressed('M') && !g_Mp)
	{
		g_Mp= true;

		/** ���õ�ǰ����Ϊ��һ������ */
		g_MD2.GetModel().currentAnim = (g_MD2.GetModel().currentAnim + 1) % (g_MD2.GetModel().numOfAnimations);

		/** ���õ�ǰ֡Ϊ��һ�������Ŀ�ʼ֡ */
		g_MD2.GetModel().currentFrame = (g_MD2.GetModel()).pAnimations[g_MD2.GetModel().currentAnim].startFrame;
	}
	if (!g_Keys.IsPressed('M'))
	{
		g_Mp= false;
	}


	//��f������Ч
	if (g_Keys.IsPressed('F'))
	{
		fog_switch = !fog_switch;
	}

	//��x����ѩ��
	if (g_Keys.IsPressed('X'))
	{
		snow_switch = !snow_switch;
	}

	
}



//��ж�غ���
void Uninit(){

	InputSystemUninit();
	SoundRelatedUninit();
}






















































