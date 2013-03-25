//################################################
// <Enemy.h>
// �G�l�~�[�̊�{�N���X
//------------------------------------------------
// 2012/12/06 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMY_H_____
#define _____ENEMY_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Object.h"
#include "Mesh.h"
#include "Common.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
enum ENEMY_STATE{
	DEAD = -1,	//�������ĂȂ�
	MOVE,		//�ړ�
	ATTACK,		//�U������
	DAMAGE,		//�U�����󂯂�
	SPLIT,		//����
	ACT1,		//�A�N�V����1
	ACT2,		//�A�N�V����2
	ACT3,		//�A�N�V����3

	STATE_NUM	//��Ԑ�
};
//�G�̎��
enum ENEMY_TYPE{
	NORMAL,			//�m�[�}���ȓG
	BOSS,			//�{�X

	TYPE_NUM       //
};

//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class ENEMY:public OBJECT
{
protected:
	MESH	m_MeshB;				//���b�V���f�[�^
	int     m_DeadNum;				//���S��
	int     m_AtkState;				//�U�����

	bool    m_AtkMotion;			//�U�����[�V�����t���O
	bool    m_DmgMotion;			//�_���[�W���[�V�����t���O
	VECTOR3 m_vecFree;				//�v���C���[���߂��ɂ��Ȃ��Ƃ��̐i�ވړ��x�N�g��
public:
	ENEMY();
	virtual ~ENEMY();
	bool    m_ColPlayer;			//�v���C���[�Ƃ̏Փ˃t���O
	bool    m_ColRingIn;			//�v���C���[�̃����O���Ɋ܂܂�Ă��邩�̃t���O
	bool    m_AtkHitPlayer;			//�v���C���[�ւ̍U�������t���O
	bool	m_JumpFlg;				//�W�����v�t���O

	int     m_AppearBoss;			//�{�X��p�o����
	virtual void Init(void)		= 0;		//������
	virtual void Reset(void)	= 0;		//���Z�b�g
	virtual void SetData(void)	= 0;		//�f�[�^�̏����l���Z�b�g
	virtual void Load(void)		= 0;		//�ǂݍ���
	virtual void Release(void)	= 0;		//���
	virtual void Create(void)	= 0;		//�쐬
	virtual void Deleate(void)	= 0;		//�폜
	virtual void Draw(void)		= 0;		//�`��
	virtual void SetLive(bool)		= 0;	//�����t���O�Z�b�^
	virtual bool Update(VECTOR3 pos, float w, int a)	= 0;		//�X�V
	
};

//################################################
// End of File
//################################################
#endif _____ENEMY_H_____

