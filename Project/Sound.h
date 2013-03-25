//################################################
// <Sound.h>
//------------------------------------------------
//2013/02/05		Akihito Tanaka
//################################################

#ifndef _____SOUND_H_____
#define _____SOUND_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================

//#pragma comment ( lib, "libogg_static.lib" )
//#pragma comment ( lib, "libvorbis_static.lib" )
//#pragma comment ( lib, "libvorbisfile_static.lib" )
#pragma comment ( lib, "OpenAL32.lib" )
//#include "vorbis/vorbisfile.h"
#include <windows.h>

//#include <al.h>
//#include <alc.h>
#include <stdio.h>
#include <AL/alut.h>
#include <vector>
#include <iostream>
#include <fstream>

#define NUM_BUFFERS 32
#define BUFFER_SIZE 4096
//================================================
//���C�u������`
//================================================

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")
//================================================
//�萔��`
//================================================
enum SE{
	BUTTON_ON,		//�Q�[���X�^�[�g		
	YES,		//����
	//NO,			//�߂�
	SE_BOMB,		//����
	DRILL,
	PARTS_MOVE,
	BG_TITLE,		//�^�C�g���W���O��	
	WARNING,
	SE_ATTACK,
	MAX_SE
};
enum BGM{
	//BG_TITLE,		//�Q�[���X�^�[�g		
	BG_SELECT,		//����
	BG_GAME_NORMAL,			//�߂�
	BG_GAME_BOSS,			//�߂�
	BG_RESULT,		//����
	MAX_BG,
};

//�T�E���h�t�@�C��
const char wavSE[MAX_SE][256] = {	{"SOUND\\start.wav"},
									{"SOUND\\kati.wav"},
									{"SOUND\\Bomb.wav"},
									{"SOUND\\Drill.wav"},
									{"SOUND\\PartsMove.wav"},
									{"SOUND\\OP_jingle.wav"},
									{"SOUND\\warning.wav"},
									{"SOUND\\attack.wav"},};	
const char wavBGM[MAX_BG][256] = {	//{"SOUND\\OP_jingle.wav"},
									{"SOUND\\Select.wav"},
									{"SOUND\\GameNormal.wav"},
									{"SOUND\\GameBoss.wav"},
									{"SOUND\\Result.wav"},};		
//================================================
//�N���X��`
//================================================
//using namespace std;

class WaveFile{
private:
	ALuint buffer;
	ALuint source;
public:
	WaveFile(){};
	~WaveFile(){};
	void Open( const char *filename, bool loopFlg);
	void Play();
	void Stop();
	void FadeOut(float vol);
	void del();
};

//class OggFile{
//private:
//	ALCdevice *device;
//    ALCcontext *context;
//    ALuint source, buffer;
//    ALint state, num;
//	OggVorbis_File vf;
//
//	void Open(const char *filename);
//public:
//	void Play();
//
//};

class SOUND{
private:
	SOUND(){};
	WaveFile SE[MAX_SE];
	WaveFile BGM[MAX_BG];
public:
	static SOUND* Instance()
	{
		static SOUND Inst;
		return &Inst;
	};
	void PlaySE(int type);
	void StopSE(int type);
	void PlayBG(int type);
	void StopBG(int type);
	void LoadSE();
	void LoadBG();
	void Reset();
	void FadeOut(int type, float vol);
	void del();
	~SOUND(){};
};

//================================================
//�v���g�^�C�v�錾
//================================================


#endif _____SOUND_H_____
//################################################
// End of File
//################################################
