//################################################
// <EnemyNormal.h>
//�@�v���C���[���T�ɂ���Ƃ��A�����̌����Ă������
// ����A�O���ɂ���Ƃ��A�v���C���[�̕����֓ˌ����Ă����B
//�A�v���C���[���������������A�����_���ȕ����֐i��ł���
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMY_NORMAL_H_____
#define _____ENEMY_NORMAL_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Enemy.h"
#include "ShaderMng.h"	//�V�F�[�_
#include "Matrix.h"		//���w
#include "EffectMng.h"
#include "Sound.h"

//================================================
//�萔��`
//================================================
//�G�̍U�����
enum ENEMY_ATK_STATE
{
	ROT,	//��]
	BACK,	//��뉺����
	JUMP	//��т�����
};
//================================================
//�N���X��`
//================================================
class ENEMY_NORMAL:public ENEMY
{
public:
	ENEMY_NORMAL();
	virtual ~ENEMY_NORMAL();

	void Init(void);		//������
	void Reset(void);		//���Z�b�g
	void SetData(void);		//�f�[�^�̏����l���Z�b�g
	void Load(void);		//�ǂݍ���
	void Release(void);		//���
	void Create(void);		//�쐬
	void Deleate(void);		//�폜
	void Draw(void);		//�`��
	bool Update(VECTOR3 pos, float w, int a);		//�X�V
	void SetLive(bool);
	VECTOR3 m_vecFree;
private:
	SHADER_MNG *m_pShader;
	EFFECT_MNG *m_pEffectMng;
	SOUND	   *m_pSE;
	float m_RotAtc;				//�U������]
	bool MotionAttack(void);	//�U�����[�V����
	bool MotionDamage(void);	//�_���[�W���[�V����

	MESH	m_MeshDmg1;
	MESH	m_MeshNormal;
	MESH	m_Inside;
	MESH	m_MeshBomb;		//�����p���b�V��
	GLuint	m_TexInside;
	
	VECTOR3 Addpos;
	int nCntAtk;
	int nCntDmg;
};

//################################################
// End of File
//################################################
#endif _____ENEMY_NORMAL_H_____

