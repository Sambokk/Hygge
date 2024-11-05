#pragma once

#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
#include "fmod_errors.h"
using namespace FMOD;

enum class SOUND_BGM
{
	TITLE = 0,
	DAY_SKY,
	DAY_OCEAN,
	NIGHT_SKY,
	NIGHT_OCEAN,

	END
};

enum class SOUND_SFX
{
	CAMERA_CHANGE = 0,
	OBJ_PICK,

	OBJ_CLICK_1,
	OBJ_CLICK_2,
	OBJ_CLICK_3,
	OBJ_CLICK_4,

	OBJ_CHANGE_1,
	OBJ_CHANGE_2,
	OBJ_CHANGE_3,

	OBJ_COMBINE,
	OBJ_INTERACT,
	STAGE_CLEAR,

	OBJ_TAP,
	
	END
};


class SoundMgr
{
	SINGLE(SoundMgr);

/// FMOD 맴버 변수
private:
	char* m_soundPath;                    //패스매니저에서 가져온 파일 경로를 저장하는 문자열
	char* m_adjustedPath;                 //각 파일의 경로를 fmod에 전달하기 위한 임시 문자열 

	bool m_VolumeZero;

	FMOD_SYSTEM* m_system;
	FMOD_CHANNEL* m_SFXchannel;
	FMOD_CHANNEL* m_BGMchannel;
	FMOD_SOUND* m_bgms[(UINT)SOUND_BGM::END];
	FMOD_SOUND* m_sfxs[(UINT)SOUND_SFX::END];


/// blueScene용 맴버 변수
private:
	bool m_isBlueNight;
	bool m_isBlueUpSide;


///Game Progress 
public:
	void initialize();
	void update();
	//////////////////////////////


/// FMOD 맴버 함수
public:
	void playBGM(UINT _bgm);
	void stopBGM();
	void adjustBGMVolume(float _volume);

	void playSFX(UINT _sfx);
	void adjustSFXVolume(float _volume);
	void setVolumeZero(bool _isZero) { m_VolumeZero = _isZero; }

/// 블루씬을 위한 함수
public:
	void playBlueBGM();

	void setBlueNight(bool _isNight) { m_isBlueNight = _isNight; }
	void setBlueUpSide(bool _isUpSide) { m_isBlueUpSide = _isUpSide; }

private:
	char* adjustPath(const char* _filepath);
};


