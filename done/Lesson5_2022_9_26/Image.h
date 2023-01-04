//========================================================
/**
*  @file      Image.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �����ļ�������
*  ����ƽ̨�� Windows98/2000/NT/XP
*
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26
*  �޸����ڣ� 2007-07-26
*
*/
//========================================================

#ifndef _IMAGE_H_
#define _IMAGE_H_

/** ������ɫ������ */
typedef DWORD DWCOLOR;
#pragma pack(1)


/**\brief
* tga�ļ����ļ�ͷ�ṹ
*/
typedef struct _tgaHeader
{
	//! ͨ��Ϊ0�������Ϊ0������header���������bLength���ֽ�
	BYTE bLength;
	//! 0��ʾ�е�ɫ�壬1��ʾû��
	BYTE bPalType;
	//! ��ʾͼ������
	//! 0 ��ʾδ����ͼ������
	//! 1 ��ʾû��ѹ���ĵ�ɫ��ͼ��
	//! 2 ��ʾû��ѹ����ȫ��ͼ��
	//! 3 ��ʾû��ѹ���ĻҶ�ͼ��
	//! 9 ��ʾRLEѹ���ĵ�ɫ��ͼ��
	//! 10 ��ʾRLEѹ����ȫ��ͼ��
	//! 11 ��ʾRLEѹ���ĻҶ�ͼ��
	BYTE bImageType;
	//! ��ɫ�����ʼ����
	WORD wPalFirstMax;
	//! ��ɫ�����ݳ���
	WORD wPalLength;
	//! ��ɫ��ÿһλ��ɫ��ռ��λ��
	BYTE wPalBits;
	//! ͼ���������Ļ���½ǵ�X����
	WORD wLeft;
	//! ͼ���������Ļ���½ǵ�Y����
	WORD wBottom;
	//! ͼ��Ŀ��
	WORD wWidth;
	//! ͼ��ĸ߶�
	WORD wDepth;
	//! ÿ�����������λ��
	BYTE bBits;

	struct descriptor
	{
		BYTE AlphaBits : 4;
		//! 1��ʾͼ�����������෴�洢
		BYTE HorMirror : 1;
		//! 1��ʾͼ���������µߵ��洢
		BYTE VerMirror : 1;
		BYTE Reserved : 2;
	}Descriptor;

}tgaHeader;

#pragma pack()


/**\brief
* �����ļ�������
*/
class CImage
{
public:
	CImage(void);
	~CImage(void);


	/**\brief
	* ����tga�ļ�
	*/
	void LoadTga(char *filename);


	/**\brief
	* ����bmp�ļ�
	*/
	void LoadBitmap(char*filename);


	/**\brief
	* �����alphaֵ��tga�ļ�
	*/
	void LoadTgaWithAlpha(char*filename, DWCOLOR keycolor);


	/**\brief
	* �����alphaֵ��bmp�ļ�
	*/
	void LoadBitmapWithAlpha(char*filename, DWCOLOR keycolor);


	/**\brief
	* ȡ����������ָ��
	*/
	unsigned char* GetImageData(void){ return m_pImageData; }


	/**\brief
	* ȡ��ͼ��ĸ߶�
	*/
	int GetHeight(void){ return m_iHeight; }


	/**\brief
	* ȡ��ͼ��Ŀ��
	*/
	int GetWidth(void){ return m_iWidth; }



private:
	//! ͼ��Ŀ�
	int m_iWidth;

	//! ͼ��ĸ�
	int m_iHeight;

	//! ��ɫ
	int m_iColor;

	//! ������ָ��
	unsigned char *m_pImageData;


	unsigned char* LoadUncompessedTga(char*filename);

	unsigned char* LoadCompessedTga(char *filename);
};

#endif