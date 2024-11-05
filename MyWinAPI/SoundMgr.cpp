#include "pch.h"
#include "SoundMgr.h"

#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
#include "fmod_errors.h"
using namespace FMOD;

#include "PathMgr.h"

#include <codecvt>


SoundMgr::SoundMgr()
	:m_system(nullptr), m_SFXchannel(nullptr), m_BGMchannel(nullptr)
	, m_soundPath(new char[512]), m_adjustedPath(new char[512])
	, m_bgms{}, m_sfxs{}
	, m_VolumeZero(false)
	, m_isBlueNight(false), m_isBlueUpSide(true)
{
	// FMOD 시스템 객체 초기화
	FMOD_System_Create(&m_system, FMOD_VERSION);
	FMOD_System_Init(m_system, (UINT)SOUND_SFX::END + 1, FMOD_INIT_NORMAL, nullptr);


	//경로 설정
	wstring path = PathMgr::GetInstance()->getContentPath();
	path += L"sound\\";
	WideCharToMultiByte(CP_UTF8, 0, path.c_str(), -1, m_soundPath, 512, nullptr, nullptr);
}

SoundMgr::~SoundMgr()
{
	///시스템 객체 해제
	FMOD_System_Close(m_system);
	FMOD_System_Release(m_system);

	delete(m_soundPath);
	delete(m_adjustedPath);
}

char* SoundMgr::adjustPath(const char* _filepath)
{
	m_adjustedPath[0] = '\0';
	strcat_s(m_adjustedPath, 512, m_soundPath);
	strcat_s(m_adjustedPath, 512, _filepath);

	return m_adjustedPath;
}


void SoundMgr::initialize()
{
	//사운드 장착-> 배경음
	FMOD_System_CreateSound(m_system, adjustPath("BGM\\B00.wav"),
		FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &m_bgms[0]);

	FMOD_System_CreateSound(m_system, adjustPath("BGM\\B01.wav"),
		FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &m_bgms[1]);

	FMOD_System_CreateSound(m_system, adjustPath("BGM\\B02.wav"),
		FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &m_bgms[2]);

	FMOD_System_CreateSound(m_system, adjustPath("BGM\\B03.wav"),
		FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &m_bgms[3]);

	FMOD_System_CreateSound(m_system, adjustPath("BGM\\B04.wav"),
		FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &m_bgms[4]);



 	//효과음
	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E00.wav"),
	 	FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[0]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E01.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[1]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E02_1.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[2]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E02_2.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[3]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E02_3.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[4]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E02_4.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[5]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E03_1.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[6]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E03_2.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[7]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E03_3.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[8]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E04.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[9]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E05.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[10]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E06.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[11]);

	FMOD_System_CreateSound(m_system, adjustPath("SFX\\E07.wav"),
		FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &m_sfxs[12]);
}

void SoundMgr::update()
{
	FMOD_System_Update(m_system);
}



void SoundMgr::playBGM(UINT _bgm)
{
	if (m_VolumeZero) return;
	FMOD_System_PlaySound(m_system, m_bgms[_bgm], NULL, 0, &m_BGMchannel);
}

void SoundMgr::playSFX(UINT _sfx)
{
	if (m_VolumeZero) return;
	FMOD_System_PlaySound(m_system, m_sfxs[_sfx], NULL, 0, &m_SFXchannel);
}



void SoundMgr::adjustBGMVolume(float _volume)
{
	FMOD_Channel_SetVolume(m_BGMchannel, _volume);
}

void SoundMgr::adjustSFXVolume(float _volume)
{
	FMOD_Channel_SetVolume(m_SFXchannel, _volume);

	if (_volume < 0.5) m_VolumeZero = true;
	else m_VolumeZero = false;
}

void SoundMgr::playBlueBGM()
{
	if (m_VolumeZero) return;
	FMOD_Channel_SetVolume(m_BGMchannel, 1.f);
	if (!m_isBlueNight)
	{
		if (m_isBlueUpSide) FMOD_System_PlaySound(m_system, m_bgms[(UINT)SOUND_BGM::DAY_SKY], NULL, 0, &m_BGMchannel);
		else				FMOD_System_PlaySound(m_system, m_bgms[(UINT)SOUND_BGM::DAY_OCEAN], NULL, 0, &m_BGMchannel);
	}
	else
	{
		if (m_isBlueUpSide) FMOD_System_PlaySound(m_system, m_bgms[(UINT)SOUND_BGM::NIGHT_SKY], NULL, 0, &m_BGMchannel);
		else				FMOD_System_PlaySound(m_system, m_bgms[(UINT)SOUND_BGM::NIGHT_OCEAN], NULL, 0, &m_BGMchannel);
	}
}


void SoundMgr::stopBGM()
{
	FMOD_Channel_Stop(m_BGMchannel);
}