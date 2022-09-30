#include "Light.h"

static float lightPositionMoon[] = {0,500,500,0};
static float diffuseLightMoon[] = { 1, 1, 1, 1 };
static float specularLightMoon[] = { 1, 1, 1, 1 };
static float ambientLightMoon[] = { 1, 1, 1, 0.1 };
//static float moonlightDirection[] = { 0, -1, -1 };

/** ����������Դ����ɫ ��ɫ����ɫ����λ�� */
static float lightPositionR[] = { 200, 230, 600, 1.0f };
static float lightPositionG[] = { 150.f, 230, 600, 1.0f };
static float lightPositionB[] = { 100.f, 230, 600, 1.0f };

/** ����������Դ������� */
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

/** ����������Դ�ľ���� */
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };




Light::Light()
{
	/// ��ʼ���û��Զ���ĳ������
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

	//�����¹�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightMoon);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightMoon);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionMoon);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightMoon);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, moonlightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.f);

	/** ����1�ź�ɫ��Դ */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	/** ����2����ɫ��Դ */
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	/** ����3����ɫ��Դ */
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);



	glEnable(GL_LIGHT0);
}

void Light::Update(){
	/** �û��Զ���ĸ��¹��� */

	/**�����º�ɫ��Դ */
	if (g_Keys.IsPressed(0x31) == false)       /**< ������'1'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT1);                  /**< ����1�ź�ɫ��Դ */
		//m_bRedX += 0.01;  /**< ������ת�Ƕ� */
		//m_bRedY += 0.01;
	}
	else
	{
		glDisable(GL_LIGHT1);                 /**< ��������ʱ�����øù�Դ */
	}

	/**��������ɫ��Դ */
	if (g_Keys.IsPressed(0x32) == false)        /**< ������'2'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT2);                   /**< ����2����ɫ��Դ */
		//m_bGreenX += 0.01; /**< ������ת�Ƕ� */
		//m_bGreenY += 0.01;
	}
	else
		glDisable(GL_LIGHT2);                 /**< ��������ʱ�����øù�Դ */

	/**��������ɫ��Դ */
	if (g_Keys.IsPressed(0x33) == false)       /**< ������'3'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT3);                  /**< ����3����ɫ��Դ */
		//m_bBlueX += 0.01; /**< ������ת�Ƕ� */
		//m_bBlueY += 0.01;
	}
	else
		glDisable(GL_LIGHT3);               /**< ��������ʱ�����øù�Դ */
}


void Light::Draw(){


	/** ��ɫ��Դ */
	glPushMatrix();
	/** ��ת��ɫ��Դ�� */
	glRotatef(m_bRedX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bRedY, 0.0f, 1.0f, 0.0f);

	/** ���ú�ɫ��Դλ�� */
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	/**< �ڹ�Դλ�ô�����һ��������Դ */
	glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
	glColor3f(1.0f, 0.0f, 0.0f);	/**< ��ɫ */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< �رչ��� */
	auxSolidSphere(1);
	glEnable(GL_LIGHTING);  /**< ���ù��� */
	glPopAttrib();
	glPopMatrix();

	/** ��ɫ��Դ */
	glPushMatrix();
	/** ��ת��ɫ��Դ�� */
	glRotatef(m_bGreenX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bGreenY, 0.0f, 1.0f, 0.0f);

	/** ������ɫ��Դλ�� */
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);

	/**< �ڹ�Դλ�ô�����һ��������Դ */
	glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
	glColor3f(0.0f, 1.0f, 0.0f);	/**< ��ɫ */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< �رչ��� */
	auxSolidSphere(0.1);
	glEnable(GL_LIGHTING);  /**< ���ù��� */
	glPopAttrib();
	glPopMatrix();

	/** ��ɫ��Դ */
	glPushMatrix();

	/** ��ת��ɫ��Դ�� */
	glRotatef(m_bBlueX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_bBlueY, 0.0f, 1.0f, 0.0f);

	/** ������ɫ��Դλ�� */
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	/**< �ڹ�Դλ�ô�����һ��������Դ */
	glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
	glColor3f(0.0f, 0.0f, 1.0f);	/**< ��ɫ */

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);	/**< �رչ��� */
	auxSolidSphere(0.1);
	glEnable(GL_LIGHTING);  /**< ���ù��� */
	glPopAttrib();
	glPopMatrix();


}