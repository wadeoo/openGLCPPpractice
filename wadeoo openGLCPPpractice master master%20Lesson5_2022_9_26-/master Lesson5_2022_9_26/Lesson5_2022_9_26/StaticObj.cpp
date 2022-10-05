//========================================================
/**
*  @file      StaticObj.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ�еľ�̬ʵ��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#include "stdafx.h"
#include "staticobj.h"
#include "inifile.h"
#include "terrain.h"

StaticObj::StaticObj(void):m_fDir(0.f),
						m_bSelected(FALSE)
{
}

StaticObj::~StaticObj(void)
{
}


BOOL StaticObj::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);
	m_sPos.x=(float)Ini.ReadInt(index,"x");
	m_sPos.z=(float)Ini.ReadInt(index,"y");
	m_sPos.y=CTerrain::GetTerrainPointer()->getAveHeight(m_sPos.x,m_sPos.z);
	m_fDir=(float)Ini.ReadInt(index,"direction");
	vector3d t_v;
	t_v.x=PERSENT(Ini.ReadInt(index,"scale_x"));
	t_v.y=PERSENT(Ini.ReadInt(index,"scale_y"));
	t_v.z=PERSENT(Ini.ReadInt(index,"scale_z"));
	r1=PERSENT(Ini.ReadInt(index,"r1"));
	r2=PERSENT(Ini.ReadInt(index,"r2"));
	ms3d.Load(Ini.ReadText(index,"ModelFile"),t_v);
	ms3d.LoadTexFromIni(filename,index);


	return TRUE;
}


void StaticObj::OnRender()
{
	glPushMatrix();
	glTranslatef(m_sPos.x ,m_sPos.y , m_sPos.z);
	glRotatef(m_fDir , 0.0f , 1.0f , 0.0f);
	if(m_bSelected)
	{
		glColor3f(1.f,0.f,0.f);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-r1,2,-r2);
			glVertex3f(-r1,2, r2);
			glVertex3f( r1,2, r2);
			glVertex3f( r1,2,-r2);
		glEnd();
	}
	ms3d.Render();
	glPopMatrix();
}