//======================================================================
/**
*  @file      Sound.h
*
*  ��Ŀ������ DirectSound������ʾ
*   
*  �ļ�����:  DirectSound��Ƶϵͳ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-24	
*  �޸����ڣ� 2007-07-24
*/																			
//======================================================================

#ifndef __SOUND_H__
#define __SOUND_H__

#include "stdafx.h"

/** ����WAV�ļ�ͷ�ṹ */
typedef struct sWaveHeader
{
	char  RiffID[4];          // 'RIFF'�� 
	long  WaveformChunkSize;  // RIFF��Ĵ�С��4���ֽ� 
	char  WaveID[4];          // .wav�ļ�Ϊ��WAVE��
	char  FormatID[4];        // 'fmt'�� ������һ���ո� 
	long  FormatChunkSize;    //fmt��Ĵ�С��16���ֽ�
	short Channels;           //������
	long  SampleRate;         //����Ƶ��
	long  BytesPerSec;        //ÿ������ֽ���
	short BlockAlign;         //����������С
	short BitsPerSample;      //bitλ��
	char  DataID[4];          //data��
	long  DataSize;           //data��Ĵ�С��ʵ���������ݴ�С
}WaveFileHeader;


/** DirectSound��Ч�� */
class CSound
{
public:
	CSound();
	~CSound();
	
	/** ����.wav�ļ� */
	bool LoadWaveFile(const char* fileName);
	
	/** �������������� */
	bool GetSecondaryBuffer(FILE* fp);

	/** ������������ */
	bool LoadData(FILE* fp);

	/** ���� */
	bool  Play(bool bLoop);

	/** ֹͣ */
	bool  Stop();


private:
    /** DirectSoundBuffer�ӿڶ��� */
	IDirectSoundBuffer8*   m_pDirectSoundBuf;
};


/** ��Ƶϵͳ������ */
class CSoundManager
{
public:
	CSoundManager();
	~CSoundManager();

	/** ��ʼ�� */
	bool Init(HWND  hwnd,DWORD dwCoopLevel = DSSCL_NORMAL);

	/** ������������ */
	bool SetPrimaryBuffer(WORD channels = 1,DWORD dwSamplesPerSec = 22050,
		                  WORD wBitsPerSample = 16);

	/** ��õ�ǰCSoundManager�� */
	static CSoundManager*  GetSoundManager(){ return  m_pSoundManager; }

	/** ���DirectSound8���� */
	IDirectSound8*  GetDirectSound()        { return  m_pDirectSound; }


private:
	/** ��ǰȫ����Ƶϵͳ�� */
	static CSoundManager*  m_pSoundManager;

	/** DirectSound8�ӿڶ��� */
	IDirectSound8*         m_pDirectSound;

};


#endif //__SOUND_H__