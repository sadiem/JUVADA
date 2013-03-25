//################################################
// <PostEffectMng.h>
//
//------------------------------------------------
// 2013/1/30
//						Akihito Tanaka
//################################################
#ifndef _____POST_EFFECT_MNG_H_____
#define _____POST_EFFECT_MNG_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "FBO.h"


//================================================
//�萔��`
//================================================
//================================================
//�N���X��`
//================================================

class POST_EFFECT_MNG{
	
public:
	static POST_EFFECT_MNG* Instance()
	{
		static POST_EFFECT_MNG Inst;
		return &Inst;
	};
private:
	POST_EFFECT_MNG();

	//��ʂ̕`��Ώ�
	FBO RenderBuffer;
public:
	void Init();
	void StartRenderMain();			//�t���[���o�b�t�@�ɏ����o���J�n
	void EndRenderMain();			//�t���[���o�b�t�@�ɏ����o���I��
	void Draw();					//��ʂɏ����o��

};
#endif _____POST_EFFECT_MNG_H_____