#pragma once

#include <io.h>
#include <fcntl.h>

#define SYS_KEYBOARD (CInputSystem::GetSysInput()->GetKeyboard())
#define SYS_MOUSE	(CInputSystem::GetSysInput()->GetMouse())
int SYS_WIDTH = 640;
int SYS_HEIGHT = 480;

/** 将INI文件中的int型数转化为float型 */
#define PERSENT(iNum) ((float)(iNum)*0.01f)

/** 常用宏 */
#define _ERROR(info)	MessageBox(NULL,info,"error",MB_OK)
#define _DELETE(X)		try{ if((X)!=NULL){delete (X); (X) = NULL; } } catch(...) { _ERROR("error delete!"); }
#define _FREE(X)		try{ if((X)!=NULL){free(X);(X)=NULL; } } catch(...) { _ERROR("error free()!"); }
#define _DELETE_ARRAY(X)try{ if((X)!=NULL){delete[] (X); (X) = NULL; } } catch(...) { _ERROR("error delete[]!"); }



/**\brief
* 获取文件长度
*/
static int GetFileLength(char *name)
{
	int fh, nbytes;

	fh = _open(name, _O_RDONLY);//只读模式
	if (fh == -1){ return -1; }
	nbytes = _filelength(fh);
	_close(fh);

	return nbytes;
}


/**\brief
* 显示调试信息
*/
static void ShowMessage(char *msg, ...)
{
	va_list va;
	char str[256];

	va_start(va, msg);
	vsprintf(str, msg, va);
	va_end(va);

	MessageBox(NULL, str, "Message", MB_OK);
}


class general
{
public:
	general();
	~general();
};

