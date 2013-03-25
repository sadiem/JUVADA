//################################################
// <Sound.cpp>
//
//------------------------------------------------
//2013/02/05		Akihito Tanaka
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Sound.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================

//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//���C���֐�
//------------------------------------------------
//�������y�у��C�����[�v
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SOUND::LoadSE()
{
	for(int i = 0; i < MAX_SE; i++)
	{
		SE[i].Open(wavSE[i],false);
	}
}
void SOUND::LoadBG()
{
	for(int i = 0; i < MAX_BG; i++)
	{
		BGM[i].Open(wavBGM[i],true);
	}
}
void WaveFile::Open( const char *filename, bool loopFlg)
{

	alutInit(NULL,0);
	buffer = alutCreateBufferFromFile(filename);
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	if(loopFlg)
		alSourcei(source, AL_LOOPING, AL_TRUE);		//���[�v����
	else
		alSourcei(source, AL_LOOPING, AL_FALSE);	//���[�v���Ȃ�
}
void WaveFile::Play()
{
	alSourcePlay(source);
}
void WaveFile::Stop()
{
	// �\�[�X�̒�~
	alSourceStop(source);
	 
	// �Đ��ʒu��擪�ɂ��܂�
	alSourceRewind(source);
}
void WaveFile::FadeOut(float vol)
{
	if(vol < 0.0f)
		vol = 0.0f;

	if(vol > 1.0f)
		vol = 1.0f;

	alSourcef(source, AL_GAIN, vol);
}
void WaveFile::del()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}
//void OggFile::Open(const char * filename)
//{
//	device = alcOpenDevice(NULL);
//	context = alcCreateContext(device, NULL);
//	alcMakeContextCurrent(context);
//	alGenSources(1, &source);
//	FILE *fp;
//	fopen_s(&fp, filename, "rb");
//	int current = 0;
//	ov_open(fp, &vf, NULL, 0);
//}
//void OggFile::Play()
//{
//
//}
void SOUND::PlaySE(int type)
{
	SE[type].Play();
}
void SOUND::StopSE(int type)
{
	SE[type].Stop();
}
void SOUND::PlayBG(int type)
{
	BGM[type].Play();
}
void SOUND::StopBG(int type)
{
	BGM[type].Stop();
}
void SOUND::Reset()
{

	for(int i = 0; i < MAX_SE; i++)
	{
		StopSE(i);
	}
	for(int i = 0; i < MAX_BG; i++)
	{
		StopBG(i);
	}
}
void SOUND::FadeOut(int type, float vol)
{
	SE[type].FadeOut(vol);
}
void SOUND::del(void)
{

	for(int i = 0; i < MAX_SE; i++)
	{
		SE[i].del();
	}
	for(int i = 0; i < MAX_BG; i++)
	{
		BGM[i].del();
	}
}
//################################################
// End of File
//################################################
