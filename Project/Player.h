//################################################
// <Player.cpp>
// �v���C���[����
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
// 2013/1/22			���}�b�v�ǉ�	Akihito Tanaka
//################################################
#ifndef _____PLAYER_H______
#define _____PLAYER_H______

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Object.h"		//�I�u�W�F�N�g�w�b�_
#include "Input.h"		//�W���C�p�b�h�w�b�_
#include "Shadow.h"		//�e
#include "CubeMap.h"	//���}�b�v
#include "EnemyMng.h"	//�G�}�l�[�W��
#include "Camera.h"		//�J����

class CUBEMAP;
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define TEX_NUM (2)		//�e�N�X�`����

//================================================
//�\���̒�`
//================================================
enum PLAYER_STATE{
	P_WAIT   = -1,		//�҂�
	P_NORMAL = 0,		//�ʏ�
	P_UP,				//�����オ��
	P_DOWN,				//����������
	P_ENEMY_IN_COLLECT,	//�G�ߊl���
	P_ENEMY_COLLECT,	//�ʏ�T�C�Y�֖߂��@�G���͈͓��ɂ���Ƃ�
	P_NORMAL_COLLECT,	//�ʏ�T�C�Y�֖߂�	�G���͈͊O�ł���Ƃ�
	P_ATC_SCALE,		//�g�k�A�N�V����
	P_ATC_TRANSFORM,	//�ό`�A�N�V����
	P_ATC_DEAD,			//���S�A�N�V����
	P_NORMAL_FLAT,		
	P_DAMEGE_ACT,		//�_���[�W�A�N�V����
};
//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//--�A�N�V�����P�@(�L�����̎����オ�蓮��)
//--�A�N�V�����Q�@(�L�����̉����蓮��)
//================================================
class PLAYER:public OBJECT
{
public:
	static PLAYER* Instance()
	{
		static PLAYER Inst;
		return &Inst;
	};
private:
	PLAYER();
	ENEMYMNG	*m_EnemyMng;		//�G�}�l�[�W��
	CAMERA		*m_pCamera;
	MATRIX      m_RotTrans;			//�ړ����̃L�����̉�]
	MATRIX      m_ActMove;			//�A�N�V�����ړ��}�g���b�N�X
	MATRIX      m_Act1;				//�A�N�V�����P�̃}�g���b�N�X
	VECTOR3		m_Accel;			//�����x

	bool		m_bDamage;			//�̗̓R�s�[
	bool		m_bAtkFlg;			//�U�������̃t���O

	//�e�N�X�`��
	GLuint		m_TexRed;			//��
	GLuint		m_TexNormal;		//�ʏ�
	GLuint		m_CubeTexID;
	int			m_TexFrashDirect;	//�F�̕ς�����
	int			m_nTexFrashCnt;		//�t���[���J�E���^

	int			m_WaitTime;			//�ҋ@�J�E���g
	//�g�k�A�N�V�����p
	int			m_ScaleWaitTime;	//�J�����ςȂ��ł��鎞��

	//���[�t�B���O�p
	MESH		m_MeshA;			
	MESH		m_MeshB;
	MESH		m_MeshC;
	int			m_nCntFrame;	//�t���[���J�E���g
	int			m_nDirect;		//�A�j���[�V��������
	bool		m_nStartTrans;	//���[�t�B���O�J�n�t���O
	//���݃A�N�V�����p
	int			m_nDct_Sink;
	bool		m_bSflg;
	float		m_fSink;			//���ޗ�

	//�������Ȃ�A�N�V����
	int			m_nDct_Flat;
	bool		m_bFflg;

	SOUND		*m_pSE;
	
	//���S�A�N�V����
	int			m_nDeadActFrame;
	int			m_nFrameCnt;
	int			m_nFrashTimeCnt;
	int			m_nColDIrect;			//�F�̕ω��̕���
	float		m_x;
	COLOR		m_col;				//���̐F��ۑ�
	CUBEMAP		*m_pCube;			//�L���[�u�}�b�v			
public:
	VECTOR3     m_RotAxis;			//��]��
	int			m_ScaleFlg;			//�g�k�t���O
	int			m_InEnemyFlg;		//�G���͈͓��ɂ��邩�ǂ����̃t���O
	INPUT_MNG		*m_pInput;
	int			m_DeadNum;			//���S��
	//�v���C���[���g���C�t���O
	bool		m_bRetry;

public:
	virtual ~PLAYER();
	
	void Init(void);			//������
	void Reset(void);			//���Z�b�g
	void Load(void);			//�ǂݍ���
	void Release(void);			//���
	void Update(VECTOR3 vecx, VECTOR3 vecy);	//�X�V
	void Draw(void);			//�`��
	void Act(int nState);		//�A�N�V����

	//�ǉ�
	void DrawCubeMap();
	void DrawCube();

private:
	bool ScaleActCollect(void);	//�g�k���̃T�C�Y��
	bool ScaleAttack(void);		//�g�k�U��
	void ScaleAct(void);		//�g�k
	void RotateAct(int flg);	//�ւ̎����オ��
	bool TransformAct(void);	//�ό`
	bool CheckVec(VECTOR3 *vec);	//�ړ��������`�F�b�N
	void CheckField(VECTOR3 *vec);	//�t�B�[���h���ɂ��邩�ǂ���
	void DeadAct(void);			//���S�A�N�V����
	void TexFrash(void);		//�e�N�X�`���̐؂�ւ��Ńt���b�V���\��
};

//################################################
// End of File
//################################################
#endif _____PLAYER_H______

