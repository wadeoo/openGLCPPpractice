#include "Light.h"

static float lightPositionMoon[] = {0,500,500,0};
static float diffuseLightMoon[] = { 1, 1, 1, 1 };
static float specularLightMoon[] = { 1, 1, 1, 1 };
static float ambientLightMoon[] = { 1, 1, 1, 0.1 };
//static float moonlightDirection[] = { 0, -1, -1 };

/** 定义三个光源（红色 绿色和蓝色）的位置 */
static float lightPositionR[] = { 200, 230, 600, 1.0f };
static float lightPositionG[] = { 150.f, 230, 600, 1.0f };
static float lightPositionB[] = { 100.f, 230, 600, 1.0f };

/** 定义三个光源的漫射光 */
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

/** 定义三个光源的镜面光 */
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };




Light::Light()
{
	/// 初始化用户自定义的程序变量
	m_bRedX = 0.0f;
	m_bGreenX = 0.0f;
	m_bBlueX = 0.0f;
	m_bRedY = 0.0f;
	m_bGreenY = 0.0f;
	m_bBlueY = 0.0f;
}


Light::~Light()
{
}

void Light::Init(){
	glEnable(GL_LIGHTING);

	//设置月光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightMoon);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightMoon);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionMoon);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightMoon);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, moonlightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.f);

	/** 设置1号红色光源 */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	/** 设置2号绿色光源 */
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	/** 设置3号蓝色光源 */
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);



	glEnable(GL_LIGHT0);
}

void Light::Update(){
	/** 用户自定义的更新过程 */

	/**　更新红色光源 */
	if (g_Keys.IsPressed(0x31) == false)       /**< 当数字'1'键没有被按下时 */
	{
		glEnable(GL_LIGHT1);                  /**< 启用1号红色光源 */
		//m_bRedX += 0.01;  /**< 更新旋转角度 */
		//m_bRedY += 0.01;
	}
	else
	{
		glDisable(GL_LIGHT1);                 /**< 当被按下时，禁用该光源 */
	}

	/**　更新绿色光源 */
	if (g_Keys.IsPressed(0x32) == false)        /**< 当数字'2'键没有被按下时 */
	{
		glEnable(GL_LIGHT2);                   /**< 启用2号绿色光源 */
		//m_bGreenX += 0.01; /**< 更新旋转角度 */
		//m_bGreenY += 0.01;
	}
	else
		glDisable(GL_LIGHT2);                 /**< 当被按下时，禁用该光源 */

	/**　更新蓝色光源 */
	if (g_Keys.IsPressed(0x33) == false)       /**< 当数字'3'键没有被按下时 */
	{
		glEnable(GL_LIGHT3);                  /**< 启用3号蓝色光源 */
		//m_bBlueX += 0.01; /**< 更新旋转角度 */
		//m_bBlueY += 0.01;
	}
	else
		glDisable(GL_LIGHT3);               /**< 当被按下时，禁用该光源 */
}


void Light::Draw(){


	/** 红色光源 */
	glPushMatrix();
	/** 旋转红色光源球 */
	glRotatef(m_bRedX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bRedY, 0.0f, 1.0f, 0.0f);

	/** 设置红色光源位置 */
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	/**< 在光源位置处绘制一个球代表光源 */
	glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
	glColor3f(1.0f, 0.0f, 0.0f);	/**< 红色 */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< 关闭光照 */
	auxSolidSphere(1);
	glEnable(GL_LIGHTING);  /**< 启用光照 */
	glPopAttrib();
	glPopMatrix();

	/** 绿色光源 */
	glPushMatrix();
	/** 旋转绿色光源球 */
	glRotatef(m_bGreenX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bGreenY, 0.0f, 1.0f, 0.0f);

	/** 设置绿色光源位置 */
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	/**< 在光源位置处绘制一个球代表光源 */
	glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
	glColor3f(0.0f, 1.0f, 0.0f);	/**< 绿色 */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< 关闭光照 */
	auxSolidSphere(0.1);
	glEnable(GL_LIGHTING);  /**< 启用光照 */
	glPopAttrib();
	glPopMatrix();

	/** 蓝色光源 */
	glPushMatrix();

	/** 旋转蓝色光源球 */
	glRotatef(m_bBlueX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bBlueY, 0.0f, 1.0f, 0.0f);

	/** 设置蓝色光源位置 */
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	/**< 在光源位置处绘制一个球代表光源 */
	glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
	glColor3f(0.0f, 0.0f, 1.0f);	/**< 蓝色 */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< 关闭光照 */
	auxSolidSphere(0.1);
	glEnable(GL_LIGHTING);  /**< 启用光照 */
	glPopAttrib();
	glPopMatrix();


}