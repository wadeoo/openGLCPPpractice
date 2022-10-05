//======================================================================
/**
*  @file      Sound.cpp
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

#include "sound.h"

CSoundManager* CSoundManager::m_pSoundManager = NULL;

CSound::CSound()
{
}

CSound::~CSound()
{
	if(m_pDirectSoundBuf)
		m_pDirectSoundBuf->Release();

}

/** ����wav�ļ� */
bool CSound::LoadWaveFile(const char* fileName)
{
	/** ��wav�ļ� */
	FILE*  fp;
	if((fp = fopen(fileName,"rb")) == NULL)
	{
		MessageBox(NULL,"��wav�ļ�ʧ��!","����",MB_OK);
		return false;
	}

	/** �����ļ��������������� */
	if(!GetSecondaryBuffer(fp))
	{
		MessageBox(NULL,"������������ʧ��!","����",MB_OK);
		fclose(fp);
		return false;
	}

	/** ���������ļ����� */
	if(!LoadData(fp))
	{
		MessageBox(NULL,"������������ʧ��!","����",MB_OK);
		fclose(fp);
		return false;
	}

	/** �ر��ļ� */
	fclose(fp);
	return true;
    
}

/** �������������� */
bool CSound::GetSecondaryBuffer(FILE* fp)
{
	/** ��ȡwav�ļ���ͷ����Ϣ */
	WaveFileHeader* pHeader = new WaveFileHeader();
	fseek(fp,0,SEEK_SET);
	fread(pHeader,1,sizeof(WaveFileHeader),fp);

	/** ����Ƿ�Ϊwav�ļ� */
	if(memcmp(pHeader->RiffID,"RIFF",4)    ||
		memcmp(pHeader->WaveID,"WAVE",4)   ||
		memcmp(pHeader->FormatID,"fmt ",4) ||
		memcmp(pHeader->DataID,"data",4))
	{
		MessageBox(NULL,"���ļ�����wav��ʽ���ļ�","����",MB_OK);
		return false;
	}
	
	/** ������ʽ�ṹ�� */
	WAVEFORMATEX   waveFormat;
	ZeroMemory(&waveFormat,sizeof(WAVEFORMATEX));

	/** ����������ʽ */
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = pHeader->Channels;          /**< ������ */
	waveFormat.nSamplesPerSec = pHeader->SampleRate;   /**< ����Ƶ�� */
	waveFormat.wBitsPerSample = pHeader->BitsPerSample;/**< λ�� */
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) 
							* waveFormat.nChannels;     
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * 
								waveFormat.nBlockAlign;

	/** ��仺���������ṹ�� */
	DSBUFFERDESC  bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS
						| DSBCAPS_STATIC;
	bufferDesc.dwBufferBytes = pHeader->DataSize;
	bufferDesc.lpwfxFormat = &waveFormat;

	/** ���DirectSoundBuffer�ӿڶ��� */
	IDirectSoundBuffer*  pDirectSoundBuf = NULL;
	if(FAILED(CSoundManager::GetSoundManager()->GetDirectSound()->
				CreateSoundBuffer(&bufferDesc,&pDirectSoundBuf,NULL)))
	
		return false;
	
	/** �ٴλ�ȡDirectSoundBuffer�ӿڶ��� */
	if(FAILED(pDirectSoundBuf->QueryInterface(IID_IDirectSoundBuffer8,
		                       (void** )&m_pDirectSoundBuf)))
	{
        MessageBox(NULL,"����DirectSoundBuffer�ӿڶ���ʧ��!","����",MB_OK);
		m_pDirectSoundBuf->Release();
		return false;
	}

	/** ɾ��ָ�룬���ɹ����� */
	delete pHeader;
	return true;

}

/** ������������ */
bool  CSound::LoadData(FILE* fp)
{
	/** ���wav�ļ��Ĵ�С */
	WaveFileHeader* pHeader = new WaveFileHeader();
	fseek(fp,0,SEEK_SET);
	fread(pHeader,1,sizeof(WaveFileHeader),fp);

	/** ���������� */
	BYTE*  pSoundPtr1;
	BYTE*  pSoundPtr2;
	DWORD  dwSoundSize1,dwSoundSize2;

	if(FAILED(m_pDirectSoundBuf->Lock(0,pHeader->DataSize,
		               (void** )&pSoundPtr1,&dwSoundSize1, 
					   (void** )&pSoundPtr2,&dwSoundSize2,0)))
	{
		MessageBox(NULL,"����������ʧ��!","����",MB_OK);
	    return false;
	}

	/**�����ݵ������� */
	fread(pSoundPtr1,1,dwSoundSize1,fp);
	if(pSoundPtr2 != NULL)
		fread(pSoundPtr2,1,dwSoundSize2,fp);

	/** ���� */
	m_pDirectSoundBuf->Unlock(pSoundPtr1,dwSoundSize1,
		                      pSoundPtr2,dwSoundSize2);
	
	/** ɾ��ָ�룬���ɹ����� */
	delete pHeader;
	return true;

}

/** ���� */
bool CSound::Play(bool bLoop)
{
	if(m_pDirectSoundBuf == NULL)
		return false;

	m_pDirectSoundBuf->SetCurrentPosition(0);

	if(FAILED(m_pDirectSoundBuf->Play(0,0,bLoop?true:false)))
		return false;
	return true;
}

/** ֹͣ */
bool CSound::Stop()
{
	if(FAILED(m_pDirectSoundBuf->Stop()))
		return false;
	return true;
}




/////////////////////////
CSoundManager::CSoundManager()
{
	m_pDirectSound = NULL;
	m_pSoundManager = this;
}

CSoundManager::~CSoundManager()
{
	if(m_pDirectSound)
		m_pDirectSound->Release();

}

/** ��ʼ�� */
bool CSoundManager::Init(HWND hwnd,DWORD dwCoopLevel)
{
	/** ����DirectSound���� */
	if(FAILED(DirectSoundCreate8(NULL,&m_pDirectSound,NULL)))
		return false;

	/** ����Э������ */
	if(FAILED(m_pDirectSound->SetCooperativeLevel(hwnd,dwCoopLevel)))
		return false;
	return true;

}

/** ������������ */
bool CSoundManager::SetPrimaryBuffer(WORD channels,DWORD SamplePerSec,WORD BitsPerSample)
{
	if(m_pDirectSound == NULL)
		return false;

	/** ������������������ṹ�� */
	DSBUFFERDESC  bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	bufferDesc.dwBufferBytes = 0;   /**< ����������������Ϊ0 */
	bufferDesc.lpwfxFormat = NULL;  /**< ����������������ΪNULL */

	/** ȡ���������� */
	IDirectSoundBuffer*  pDirectSoundBuf = NULL;
	if(FAILED(m_pDirectSound->CreateSoundBuffer(&bufferDesc,&pDirectSoundBuf,NULL)))
		return false;

	/** �������������Զ����ʽ */
	WAVEFORMATEX   waveFormat;
	ZeroMemory(&waveFormat,sizeof(WAVEFORMATEX));

	/** ����������ʽ */
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = channels;          
	waveFormat.nSamplesPerSec = SamplePerSec;   
	waveFormat.wBitsPerSample = BitsPerSample;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) *
							 waveFormat.nChannels;     
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * 
								waveFormat.nBlockAlign;

	if(FAILED(pDirectSoundBuf->SetFormat(&waveFormat)))
		return false;

	/** �ͷ����������ӿڶ��� */
	pDirectSoundBuf->Release();
	return true;

}
