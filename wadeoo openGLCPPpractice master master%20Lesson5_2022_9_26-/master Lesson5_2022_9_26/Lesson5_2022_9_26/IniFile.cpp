//========================================================
/**
*  @file      IniFile.cpp
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




#include "stdafx.h"
#include "IniFile.h"


CIniFile::CIniFile()
{
	DataLen=0;
	Data=NULL;
	IndexNum=0;
	IndexList=NULL;
}


CIniFile::CIniFile(char* filename)
{
	DataLen=0;
	Data=NULL;
	IndexNum=0;
	IndexList=NULL;
	Open(filename);
}


CIniFile::~CIniFile()
{
	if( DataLen!=0 && Data != NULL )		_DELETE( Data );
	if( IndexNum!=0 && IndexList!=NULL )	_DELETE( IndexList );
}


//-----------------------------------------
//public
//�����ļ�
BOOL CIniFile::Open(char *filename)
{
	strcpy(FileName, filename);

	_DELETE( Data );

	DataLen=GetFileLength(filename);		//��ȡ�ļ�����
	if( DataLen > 0 )						//�ļ�����
	{
		Data=new char[DataLen];

		FILE *fp;
		fp=fopen(filename, "rb");
		fread(Data, DataLen, 1, fp);		//������
		fclose(fp);

		InitIndex();						//��ʼ������
	}
	else
	{
		DataLen=1;
		Data=new char[DataLen];
		memset(Data, 0, 1);
		InitIndex();
	}

	return FALSE;
}


//-----------------------------------------
//public
//д���ļ�
BOOL CIniFile::Save(char *filename)
{
	if( filename==NULL )
		filename=FileName;

	FILE *fp;
	fp=fopen(filename, "wb");
	if( fp==NULL )
	{
		_ERROR("Can't save file");
		return FALSE;
	}

	fwrite(Data, DataLen, 1, fp);
	fclose(fp);

	return TRUE;
}


//-----------------------------------------
//public
//��������е�����λ��
void CIniFile::InitIndex()
{
	IndexNum=0;

	for(int i=0; i<DataLen; ++i)
	{
		//�ҵ�,Ҫ��[��ͷ�����Ҷ����֮��Ҫ�ûس��ֿ�
		if( Data[i]=='[' && (i==0||(i>0&&Data[i-1]=='\n')  ) )
		{
			++IndexNum;
		}
	}

	//�����ڴ�
	_DELETE( IndexList );
	if( IndexNum>0 )
		IndexList=new int[IndexNum];

	int n=0;
	//��ʼ��
	for(int i=0; i<DataLen; ++i)
	{
		if( Data[i]=='[' && ((i>0&&Data[i-1]=='\n' )|| i==0) )
		{
			IndexList[n]=i+1;		//���浽�������λ���� [ ����һ���ַ���λ��
			++n;
		}
	}
}


//-----------------------------------------
//public
//����ָ������λ��
int CIniFile::FindIndex(char *string)
{
	for(int i=0; i<IndexNum; ++i)
	{
		char *str=ReadText( IndexList[i] );		//���������������Ե�����
		if( strcmp(string, str) == 0 )			//�Ƚϣ������ͬ�ͷ��ر����λ��
		{
			_FREE( str );
			return IndexList[i];				//�������ڵ�λ�ã��� [ ���ַ�����һ��λ��
		}
		_FREE( str );
	}
	return -1;
}


//����ָ�����ݵ����ݵ�λ��
int CIniFile::FindData(int index, char *string)
{
	int p=index;						//ָ��

	while(1)
	{									//��������(����)���ڵ���
		p=GotoNextLine(p);				//��һ�е�λ��
		char *name=ReadDataName(p);		//��һ�����֣�ע��p�ǰ���ַ�ķ�ʽ���ε�
		if( strcmp(string, name)==0 )	//��ͬ�ͷ���λ�ã��������ݿ�ʼ��λ��
		{
			_FREE( name );
			return p;
		}

		_FREE( name );
		if( p>=DataLen ) return -1;		//û���ҵ�
	}
	return -1;
}


//����
int CIniFile::GotoNextLine(int p)
{
	for(int i=p; i<DataLen; ++i)
	{
		if( Data[i]=='\n' )				//�س�����
			return i+1;

	}
	return DataLen;
}


//��ָ��λ�ö�һ��������
char *CIniFile::ReadDataName(int &p)		//���ò�������ͨ��p���أ�����ֵ��
{											//���ݵ����ݵ�λ��
	char chr;
	char *Ret;
	int m=0;

	Ret=(char *)malloc(256);
	memset(Ret, 0, 256);

	for(int i=p; i<DataLen; ++i)
	{
		chr=Data[i];

		//����
		if( chr == '\r' )
		{
			p=i+1;
			return Ret;
		}
		
		//����
		if( chr == '=' || chr == ';' )
		{
			p=i+1;						//ָ�����ݵ����ݣ������˷ָ���
			return Ret;
		}
		
		Ret[m]=chr;
		++m;
	}
	return Ret;
}


//��ָ��λ�ö�һ�ַ���
char *CIniFile::ReadText(int p)
{
	char chr;
	char *Ret;
	int n=p, m=0;

	int EndLine=GotoNextLine(p);		//��һ�е�λ�ã�ֻ��һ�е�����
	Ret=(char *)malloc(EndLine-p+1);	//�����ڴ�
	memset(Ret, 0, EndLine-p+1);		//��0

	for(int i=0; i<DataLen-p; ++i)
	{
		chr=Data[n];

										//����	�÷ֺţ��س���TAB������]����
		if( chr == ';' || chr == '\r' || chr == '\t' || chr == ']' )
		{
			return Ret;
		}
		
		Ret[m]=chr;		//���뵽������
		++m;
		++n;
	}
	return Ret;
}


//����ͨ��ʽ��һ�ַ�������
char *CIniFile::ReadText(char *index, char *name)
{
	int n=FindIndex(index);				//ͨ�����������ҵ�λ��
	if( n == -1 )
	{
		ShowMessage("Can't find [%s] in file '%s'!", index, FileName);
		return "";
	}

	int m=FindData(n, name);			//ͨ��������λ�ú����������ҵ��������ݵ�λ��
	if( m==-1 )
	{
		ShowMessage("Can't find [%s]-'%s' in file '%s'!", index, name, FileName);
		return "";
	}

	return ReadText(m);					//����������
}


//��ָ�����ж�һ�ַ��������������������ڶ���һ�����ݣ�
//���ҿ��Բ����ľ�������֣�������ѭ���ķ�ʽ��
char *CIniFile::ReadText(char *index, int lines)
{
	int n=FindIndex(index);			//ͨ�����������ҵ�λ��
	if( n == -1 )
	{
		ShowMessage("Can't find [%s] in file '%s'!", index, FileName);
		return "";
	}

	n=GotoNextLine(n);				//����ָ������
	for(int i=0; i<lines; ++i)
	{
		if( n<DataLen )
			n=GotoNextLine(n);
	}

	//������
	while( n<=DataLen )
	{
		if( Data[n] == '=' )		//�ҵ��ָ��� =
		{
			++n;					//�ƶ���=����һ���ַ�
			return ReadText(n);		//��������
		}
		if( Data[n] == '\r' )
		{
			return "";				//û���ҵ�
		}
		++n;
	}

	return "";
}


//����ͨ��ʽ��һ��������
int CIniFile::ReadInt(char *index, char *name)
{
	int n=FindIndex(index);
	if( n == -1 )
	{
		ShowMessage("Can't find [%s] in file <%s>",index, FileName);
		return ERROR_DATA;
	}

	int m=FindData(n, name);		//���������ע��
	if( m==-1 )
	{
		ShowMessage("Can't find [%s] '%s' in file <%s>",index, name, FileName);
		return ERROR_DATA;
	}

	char *str=ReadText(m);
	int ret=atoi(str);				//ת��������
	_FREE(str);
	return ret;
}


//��ָ�����ж�һ������ͬ����Ϊ�˳����Ķ�ȡ�����ҿ��Բ����ľ��������
int CIniFile::ReadInt(char *index, int lines)
{
	int n=FindIndex(index);
	if( n == -1 )
	{
		ShowMessage("Can't find [%s] in file <%s>",index, FileName);
		return ERROR_DATA;
	}

	//����ָ������
	n=GotoNextLine(n);
	for(int i=0; i<lines; ++i)
	{
		if( n<DataLen )
			n=GotoNextLine(n);
	}

	//������
	while( n<DataLen )
	{
		if( Data[n] == '=' )
		{
			++n;
			char *str=ReadText(n);
			int ret=atoi(str);
			_FREE(str);
			return ret;
		}
		if( Data[n] == '\r' )
		{
			return ERROR_DATA;
		}
		++n;
	}

	return ERROR_DATA;
}


//��ָ�����ж�һ��������
char *CIniFile::ReadData(char *index, int lines)
{
	int n=FindIndex(index);	
	if( n == -1 )
	{
		ShowMessage("Can't find [%s] in file <%s>",index, FileName);
		return NULL;
	}

									//����ָ������
	n=GotoNextLine(n);
	for(int i=0; i<lines; ++i)
	{
		if( n<DataLen )
			n=GotoNextLine(n);
	}

	return ReadDataName(n);			//�������ַ���
}


//����ͨ��ʽдһ�ַ������ݡ����������֣�����
BOOL CIniFile::WriteText(char *index, char *name, char *string)
{
	int n=FindIndex(index);
	if( n == -1 )					//�½�����
	{
		AddIndex(index);			//����һ��һ������
		n=FindIndex(index);			//�ҵ���λ��
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return TRUE;
	}

	//��������
	int m=FindData(n, name);
	if( m==-1 )						//�½�����
	{
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return TRUE;
	}

									//��������
	ModityData(n, name, string);	//�޸�һ������

	return TRUE;
}


//����ͨ��ʽдһ����
BOOL CIniFile::WriteInt(char *index, char *name, int num)
{
	char string[32];
	sprintf(string, "%d", num);

	int n=FindIndex(index);
	if( n == -1 )					//�½�����
	{
		AddIndex(index);			//�������ע��
		n=FindIndex(index);
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return TRUE;
	}

									//��������
	int m=FindData(n, name);
	if( m==-1 )						//�½�����
	{
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return TRUE;
	}

									//��������
	ModityData(n, name, string);	//�޸�һ������

	return TRUE;
}


//����һ������
BOOL CIniFile::AddIndex(char *index)
{
	char str[256];
	memset(str, 0, 256);
	int n=FindIndex(index);						//���ҿ���û��һ����

	if( n == -1 )								//�½�����
	{
		sprintf(str,"\r\n[%s]\r\n",index);		//ע���ʽ������Ҫ�ֿ�
		Data=(char *)realloc(Data, DataLen+strlen(str));	//���·����ڴ�
		sprintf(&Data[DataLen], "%s", str);		//���ں���
		DataLen+=strlen(str);					//���³���

		InitIndex();							//���½���������
		return TRUE;
	}
	
	return FALSE;								//�Ѿ�����
}


//�ڵ�ǰλ�ü���һ������
BOOL CIniFile::AddData(int p, char *name, char *string)
{
	char *str;
	int len=strlen(string);
	str=new char[len+256];						//�����ռ�
	memset(str, 0, len+256);
	sprintf(str,"%s=%s\r\n",name,string);		//����tiamo=1�ĸ�ʽ
	len=strlen(str);							//�����㳤��

	p=GotoNextLine(p);	//����
	Data=(char *)realloc(Data, DataLen+len);	//���·����ڴ�

	char *temp=new char[DataLen-p];				//��������ݷŵ�temp����
	memcpy(temp, &Data[p], DataLen-p);
	memcpy(&Data[p+len], temp, DataLen-p);		//�Ѻ���İᵽĩβ
	memcpy(&Data[p], str, len);					//�����¼ӵ�����
	DataLen+=len;								//�������ݳ���

	_DELETE( temp );
	_DELETE( str );
	return TRUE;
}


//�ڵ�ǰλ���޸�һ�����ݵ�ֵ
BOOL CIniFile::ModityData(int p, char *name, char *string)
{
	int n=FindData(p, name);					//�ҵ����ݡ�ע�⣺���ص�n�����ݵ�λ��

	char *t=ReadText(n);						//�������ݵ�����
	p=n+strlen(t);								//�ƶ������ݵ�ĩβ����һ��λ��
	_FREE(t);

	int newlen=strlen(string);					//�µ����ݳ���
	int oldlen=p-n;								//t�ĳ��ȣ�Ҳ����ԭ�������ݳ���

	Data=(char *)realloc(Data, DataLen+newlen-oldlen);	//���·����ڴ�

	char *temp=new char[DataLen-p];						//��ͬ�ķ���
	memcpy(temp, &Data[p], DataLen-p);
	memcpy(&Data[n+newlen], temp, DataLen-p);			//�Ѻ���İᵽĩβ
	memcpy(&Data[n], string, newlen);
	DataLen+=newlen-oldlen;								//�������ݳ���

	_DELETE( temp );
	return TRUE;
}


//����ļ�������
int CIniFile::GetLines(int cur)
{
	int n=1;
	for(int i=0; i<cur; ++i)
	{
		if( Data[i]=='\n' )					//�ҵ�\n�������µ�һ��
			++n;
	}
	return n;
}


//�������������������Ǳ���(����)����ι��ж����У�һ��������ѭ��������
int CIniFile::GetContinueDataNum(char *index)
{
	int num=0;
	int n=FindIndex(index);
	n=GotoNextLine(n);					//��������(����)
	while(1)
	{									//Ҫ��һ�еĿ�ͷ����������ַ��Ļ����ͽ���
		if( Data[n] == '\r' || Data[n] == -3 || Data[n] == EOF 
			|| Data[n] == ' ' || Data[n] == '/' || Data[n] == '\t' || Data[n] == '\n' )
		{
			return num;
		}
		else
		{
			++num;
			n=GotoNextLine(n);			//����һ�еĿ�ͷ
			if( n >= DataLen )
				return num;				//�ļ�����
		}
	}
}
