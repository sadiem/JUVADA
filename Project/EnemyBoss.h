//################################################
// <EnemyBossl.h>
//------------------------------------------------
// 2013/1/7
//					akihito tanaka
//################################################
#ifndef _____ENEMY_BOSS_H_____
#define _____ENEMY_BOSS_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Enemy.h"
#include "EffectMng.h"
#include "ShaderMng.h"
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
#include "Sound.h"
#include "Camera.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
enum BOSS_STATE{
	BOSS_START,			//�{�X�o���J�n
	FALL,				//����
	APPEAR,				//�o��
	WAIT,				//�ҋ@
	PRE_JUMP_ATTACK,	//�W�����v�U������
	JUMP_ATTACK,		//�W�����v�U��
	PRE_SPIN_ATTACK,	//�X�s���U������
	SPIN_ATTACK,		//�X�s���U��
	PRE_BEAM_ATTACK,	//�r�[���U������
	BEAM_ATTACK,		//�r�[���U��
	DAMAGE_HIT,			//�_���[�W���[�V����
	DEAD_BOSS,			//���S
	BOSS_STATE_NUM,		//��Ԑ�

};

#define BOSS_PARTS	(8)			//�{�X�̃p�[�c��
#define APPEAR_WAIT	(250)		//������̐Î~����
#define TRANSCOUNT	(30)		//�ό`����

//================================================
//�N���X��`
//================================================
class ENEMY_BOSS:public ENEMY
{
public:
	ENEMY_BOSS();
	virtual ~ENEMY_BOSS();

	void Init(void);					//������
	void Reset(void);					//���Z�b�g
	void Load(void);					//�ǂݍ���
	void Release(void);					//���
	void Create(void);					//�쐬
	void Deleate(void);					//�폜
	void SetData(void);					//�f�[�^�̏����l���Z�b�g
	bool Update(VECTOR3 pos, float w, int a);		//�X�V
	void Draw(void);					//�`��
	void SetLive(bool);					//�����t���O�Z�b�g

private:
	MESH m_MeshArmor[BOSS_PARTS];		//�O���b�V��
	MESH m_MeshEye;						//�������b�V��
	GLuint	m_TexID;					//�O�e�N�X�`��ID
	GLuint	m_TexBumpID;				//�o���v�e�N�X�`��ID
	GLuint	m_TexEyeID;					//�ڋʂ̃e�N�X�`��ID

	EFFECT_MNG	*m_EffectMng;			//�G�t�F�N�g�}�l�[�W��
	SHADER_MNG	*m_ShaderMng;			//�V�F�[�_�}�l�[�W��
	SOUND		*m_pSE;					//�T�E���h�}�l�[�W��
	CAMERA		*m_pCamera;				//�J����

	VECTOR3	m_PartsOffset[BOSS_PARTS];	//�p�[�c�I�t�Z�b�g
	VECTOR3	m_PartsMove[BOSS_PARTS];	//�p�[�c�ړ��X�s�[�h
	int		m_Count;					//�ėp�J�E���^
	float   m_SpinRad;					//�X�s����]�p
	float   m_SpinAdd;					//�X�s����]�p���Z�l
	VECTOR3 m_vAttack;					//�U������
	VECTOR3 m_AtkMove;					//�U���ړ�����
	float	m_EyeScale;					//�ڋʂ̑傫��
	
	void EyeMove(VECTOR3 pos);			//�ڋʂ̈ړ�
	bool MotionDamage(void);			//�_���[�W���[�V����

	bool	m_First;					//�v���X���̏���t���O
};

//################################################
// End of File
//################################################
#endif _____ENEMY_BOSS_H_____

