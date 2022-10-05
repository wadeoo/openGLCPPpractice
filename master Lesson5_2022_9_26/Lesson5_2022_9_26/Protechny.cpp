//======================================================================
/**
*  @file      Protechny.cpp
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ��Ȫ��
*  ����ƽ̨�� Windows98/2000/NT/XP
*
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-18
*  �޸����ڣ� 2006-12-19
*
*/
//======================================================================

#include "stdafx.h"
#include "Protechny.h"

/** ��Ȫ���ӵĳ�ʼ�� */
bool CProtechny::Init(int num)
{
	/** ��ʼ��������ĿΪnum�� */
	if (CParticle::Init(num))
	{
		for (int i = 0; i<m_iNum; i++)
		{
			/** ��ʼ��λ�� */
			float x, y, z, vx, vy, vz;

			x = 0.005f * (rand() % 9);
			y = 0.005f * (rand() % 9) - 1;
			z = 0.005f * (rand() % 6);
			m_pList[i].position = Vector3(x, y, z);

			/** ��ʼ���ٶ� */
			vx = 0.0000007f * (rand() % 9000 - rand() % 9000);
			vy = 0.0000042f * (rand() % 9000);
			vz = 0.0000001f * (rand() % 9000);
			m_pList[i].velocity = Vector3(vx, vy, vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = Vector3(0.0, -0.00025f, 0.0);

			/** ��ʼ����������ʱ�� */
			m_pList[i].lifetime = 100;

			/** ��ʼ�����ӵĳߴ� */
			m_pList[i].size = 0.01f;

			/** ��ʼ�����ӵ���ʧ�ٶ� */
			m_pList[i].dec = 0.05 * (rand() % 50);

			/** ��ʼ�����ӵ���ɫ */
			m_pList[i].color[0] =1;
			m_pList[i].color[1] =1;
			m_pList[i].color[2] =1;

		}

		/** ������������ */
		if (!m_texture.LoadBitmap("Data/flare.bmp"))
		{
			MessageBox(NULL, "������������ʧ��!", "����", MB_OK);
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

/** ��Ȫ���ӵ���Ⱦ */
void CProtechny::Render()
{
	/** ������ */
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);

	/** ��ʼ��Ⱦ��Ȫ */
	for (int i = 0; i<m_iNum; ++i)
	{
		float x = m_pList[i].position.x;
		float y = m_pList[i].position.y;
		float z = m_pList[i].position.z;
		float size = m_pList[i].size;

		glColor3fv(m_pList[i].color);
		glNormal3f(0.0f, 0.0f, 1.0f);     /**< ���巨�߷��� */

		/** �������� */
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);
		glEnd();

	}

	/** ������������ */
	Update();
}

/** ��Ȫ���ӵĸ��� */
void CProtechny::Update()
{
	for (int i = 0; i<m_iNum; ++i)
	{
		/** ����λ�� */
		m_pList[i].position.x += m_pList[i].velocity.x;
		m_pList[i].position.y += m_pList[i].velocity.y;
		m_pList[i].position.z += m_pList[i].velocity.z;

		/** �����ٶ� */
		m_pList[i].velocity.y += m_pList[i].acceleration.y;

		/** ��������ʱ�� */
		m_pList[i].lifetime -= m_pList[i].dec;

		/** ���������ʧ���������� */
		if (m_pList[i].position.y <= -1 || m_pList[i].lifetime <= 0)
		{
			/** ��ʼ��λ�� */
			float x, y, z, vx, vy, vz;
			x = 0.005f * (rand() % 9);
			y = 0.005f * (rand() % 9) - 1;
			z = 0.000001f * (rand() % 9000);
			m_pList[i].position = Vector3(x, y, z);

			/** ��ʼ���ٶ� */
			vx = 0.0000007f * (rand() % 9000 - rand() % 9000);
			vy = 0.0000042f * (rand() % 9000);
			vz = 0.0000001f * (rand() % 90000);
			m_pList[i].velocity = Vector3(vx, vy, vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = Vector3(0.0, -0.00025f, 0.0);

			/** ��ʼ������ʱ�� */
			m_pList[i].lifetime = 100;

			/** ��ʼ����ʧ�ٶ� */
			m_pList[i].dec = 0.05*(rand() % 50);
		}



		if (m_pList[i].color[0] > 1 || m_pList[i].color[1] > 1 || m_pList[3].color[2] > 1)
		{
			m_pList[i].color[0] = 1;
			m_pList[i].color[1] = 0;
			m_pList[i].color[2] = 0;
		}


		if (m_pList[i].color[0] == 1 && m_pList[i].color[1] != 1){
		}
		else if (m_pList[i].color[1] == 1 && m_pList[i].color[2] != 1){
		}
		else{

		}
		m_pList[i].color[0] += 0.0000001*(std::rand());



	}

}

