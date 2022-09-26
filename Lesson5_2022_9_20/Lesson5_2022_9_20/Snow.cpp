//======================================================================
/**
*  @file      Snow.cpp
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ѩ���� 
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
#include "Snow.h"

/** ѩ���ĳ�ʼ�� */
bool CSnow::Init(int num)
{
	/** ��ʼ��������ĿΪnum�� */
	if(CParticle::Init(num))
	{
		for(int i=0; i<m_iNum; i++)
		{
			/** ��ʼ��λ�� */
			float x,y,z,vx,vy,vz;

			x = 0.1f * (rand() % 50) - 2.5f;
			
			y = 2 + 0.1f * (rand() % 2);
		
			if((int)x % 2 == 0)
				z = rand()%6;
		    else 
				z = -rand()%3;
			m_pList[i].position = Vector3(x,y,z);

			/** ��ʼ���ٶ� */
			vx = 0.00001 * (rand()%100);
			vy = 0.0000002 * (rand()%28000);
			vz = 0.0;
			m_pList[i].velocity = Vector3(vx,vy,vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = Vector3(0.0,0.000005f,0.0);

			/** ��ʼ����������ʱ�� */
			m_pList[i].lifetime = 100;
			
			/** ��ʼ�����ӵĳߴ� */
			m_pList[i].size = 0.01f;

			/** ��ʼ�����ӵ���ʧ�ٶ� */
			m_pList[i].dec = 0.005 * (rand()%50);

			/** ��ʼ�����ӵ���ɫ */
			m_pList[i].color[0] = 255;
			m_pList[i].color[1] = 255;
			m_pList[i].color[2] = 255;

		}
		
		/** ������������ */
		if(!m_texture.LoadBitmap("Data/flare.bmp"))
		{
			MessageBox(NULL,"������������ʧ��!","����",MB_OK);
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

/** ѩ������Ⱦ */
void CSnow::Render()
{

	/** ���û�����ӻ�ð�͸��Ч�� */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);				     /**< ���û�� */

	/** ������ */
	glBindTexture(GL_TEXTURE_2D,m_texture.ID);
	
	/** ��ʼ��Ⱦѩ�� */
	for(int i=0; i<m_iNum; ++i)
	{
		float x = m_pList[i].position.x;
		float y = m_pList[i].position.y;
		float z = m_pList[i].position.z;
		float size = m_pList[i].size;

		/** �����������ʧ���������������� */
		if (y <= -1 || m_pList[i].lifetime <= 0)
			break;
		
		glColor3fv(m_pList[i].color);
		glNormal3f(0.0f,0.0f,1.0f);     /**< ���巨�߷��� */
		
		/** �������� */
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
			glTexCoord2f(1.0f,0.0f);glVertex3f(x-size,y+size,z);
			glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
			glTexCoord2f(0.0f,1.0f);glVertex3f(x+size,y-size,z);
		glEnd();
				
	}
	
	/** ������������ */
	Update();
	glDisable(GL_BLEND);
}

/** ѩ���ĸ��� */
void CSnow::Update()
{
	for(int i = 0; i<m_iNum; ++i)
	{
		/** ����λ�� */
		m_pList[i].position.x += m_pList[i].velocity.x * 5;
		m_pList[i].position.y -= m_pList[i].velocity.y;
		if(m_pList[i].position.x > 3.0)
			m_pList[i].position.x = -2.0;

		/** �����ٶ� */
		m_pList[i].velocity.y += m_pList[i].acceleration.y;

		/** ��������ʱ�� */
		m_pList[i].lifetime -= m_pList[i].dec;

		/** ���������ʧ���������� */
		if (m_pList[i].position.y <= -1 || m_pList[i].lifetime <= 0)
		{
			/** ��ʼ��λ�� */
			float x,y,z,vx,vy,vz;
			x = 0.1f * (rand()%50) - 2.5f;
			y = 2 + 0.1f * (rand()%2);
			
			if((int)x%2 == 0)
				z = rand()%6;
		    else 
				z = -rand()%3;
			m_pList[i].position = Vector3(x,y,z);

			/** ��ʼ���ٶ� */
			vx = (float)(0.00001 * (rand()%100));
			vy = (float)(0.0000002 * (rand()%28000));
			vz = 0.0;
			m_pList[i].velocity = Vector3(vx,vy,vz);

			/** ��ʼ�����ٶ� */
			m_pList[i].acceleration = Vector3(0.0,0.000005f,0.0);

			/** ��ʼ������ʱ�� */
			m_pList[i].lifetime = 100;

			/** ��ʼ����ʧ�ٶ� */
			m_pList[i].dec = 0.005*(rand()%50);
		}

	}
	
}

