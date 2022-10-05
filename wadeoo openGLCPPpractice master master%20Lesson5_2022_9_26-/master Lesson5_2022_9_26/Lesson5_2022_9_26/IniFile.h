//========================================================
/**
*  @file      IniFile.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  INI�ļ���д��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================
#ifndef _INI_FILE_H_
#define _INI_FILE_H_

//! �������
#define ERROR_DATA -99999999

#include "stdafx.h"
#include "general.h"


/**\brief
 * INI�ļ���д��
 */
class CIniFile
{
public:
	CIniFile();
	~CIniFile();

	/**\brief
	 * ��ʼ���������ļ�
	 */
	CIniFile(char *);


	/**\brief
	 * �����ļ�����
	 */
	char*	GetData() {return Data;}
	
	
	/**\brief
	 * �����ļ�������
	 */
	int		GetLines(int);

	
	/**\brief
	 * �������ļ�
	 */
	BOOL	Open(char *);
	
	
	/**\brief
	 * ���������ļ�
	 */
	BOOL	Save(char *filename=NULL);


	/**\brief
	 * ��һ������
	 */
	int		ReadInt(char *, char *);

	
	/**\brief
	 * ��һ���ַ���
	 */
	char*	ReadText(char *, char *);
	
	
	/**\brief
	 * ��ָ�����ж�һ����
	 */
	int		ReadInt(char *, int );
	
	
	/**\brief
	 * ��ָ�����ж�һ�ַ������Ⱥź���ģ�
	 */
	char*	ReadText(char *, int);
	
	
	/**\brief
	 * ��ָ���ж�һ�ַ����ƣ��Ⱥ�ǰ��ģ�
	 */
	char*	ReadData(char *, int);

	
	/**\brief
	 * дһ������
	 */
	BOOL	WriteInt(char *, char *, int);
	
	
	/**\brief
	 * дһ���ַ���
	 */
	BOOL	WriteText(char *, char *, char *);

	
	/**\brief
	 * ������������������INDEX����һ�����У�
	 */
	int		GetContinueDataNum(char *);


private:
	//! �ļ���
	char	FileName[MAX_PATH];
	
	//! �ļ�����
	int		DataLen;
	
	//! �ļ�����
	char*	Data;

	//! ������Ŀ��[]����Ŀ��
	int		IndexNum;
	
	//! ������λ���б�
	int*	IndexList;

	//! ��ǰָ��
	int		Point;
	
	//! ��ǰ����
	int		Line, Word;


	/**\brief
	 * ��ʼ������
	 */
	void	InitIndex();
	
	
	/**\brief
	 * ���ر���λ��
	 */
	int		FindIndex(char *);
	
	
	/**\brief
	 * ��������λ��
	 */
	int		FindData(int, char *);
	
	
	/**\brief
	 *  ����
	 */
	int		GotoNextLine(int);
	
	
	/**\brief
	 * ��ָ��λ�ö�һ��������
	 */
	char*	ReadDataName(int &);
	
	
	/**\brief
	 * ��ָ��λ�ö��ַ���
	 */
	char*	ReadText(int);

	
	/**\brief
	 * ����һ������
	 */
	BOOL	AddIndex(char *);
	
	
	/**\brief
	 * �ڵ�ǰλ�ü���һ������
	 */
	BOOL	AddData(int, char *, char *);
	
	
	/**\brief
	 * �ڵ�ǰλ���޸�һ�����ݵ�ֵ
	 */
	BOOL	ModityData(int, char *, char *);

};

#endif