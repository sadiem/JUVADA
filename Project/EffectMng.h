//################################################
// <EffectMng.h>
//
//------------------------------------------------
// 2013/1/7
//						Akihito Tanaka
//################################################
#ifndef _____EFFECT_MNG_H_____
#define _____EFFECT_MNG_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "Smoke.h"			//�V�F�[�_
#include "Impact.h"
#include "Emitter.h"
#include "Matrix.h"
#include "Object.h"
#include "TexMng.h"
#include "LineParticle.h"
#include "MeshMng.h"
#include "Rock.h"

//================================================
//�萔��`
//================================================
enum EFFECT_TYPE
{
	E_SMOKE_L,		//��(��)
	E_SMOKE_S,		//��(��)
	E_IMPACT,			//�Ռ��g
	E_PARTICLE_SPIN,	//�X�s���p�[�e�B�N��
	E_PARTICLE_SPLASH,	//���˃p�[�e�B�N��
	E_PARTICLE_BOMB,	//���˃p�[�e�B�N��
	E_PARTICLE_LINE,	//���C���p�[�e�B�N��
	E_ROCK_LINE,		//��̋O��
	E_ROCK_CIRCLE,		//�~�`�Ɋ��z�u
};

#define MAX_EMITTER	(30)	//�p�[�e�B�N�������ʒu�ő吔
#define MAX_LINE	(20)	//���C���p�[�e�B�N�������ʒu�ő吔
//================================================
//�N���X��`
//================================================
class EFFECT_MNG
{
public:
	static EFFECT_MNG* Instance()
	{
		static EFFECT_MNG Inst;
		return &Inst;
	};
private:
	EFFECT_MNG();
	SMOKE *pSmoke;
	IMPACT	*pImpact;
	ROCK	*pRock;
	EMITTER	m_Emitter[MAX_EMITTER];
	LINE_PARTICLE pLine[MAX_LINE];
	GLuint	m_TexSpin;
	GLuint	m_TexBomb;
	MESH	m_MeshLine;


public:
	~EFFECT_MNG();

	void Load(void);	//�G�t�F�N�g�ǂݍ���
	void Set(int type, OBJECT *obj); //�`��ʒu�w��
	void Remove(int type);
	void UpDate();	//�A�b�v�f�[�g
	void Draw(void);	//�`��
};

//################################################
// End of File
//################################################
#endif _____EFFECT_MNG_H_____
