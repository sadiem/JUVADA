//################################################
// <EnemyMng.h>
//
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMYMNG_H_____
#define _____ENEMYMNG_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Object.h"
#include "Enemy.h"				//�G�̊�{�N���X
#include "EnemyCommon.h"		//�G�l�~�[���ʃw�b�_
#include "Player.h"				//�v���C���[
#include "Smoke.h"				//��
#include "EffectMng.h"
#include "Score.h"
#include "Sound.h"

//================================================
//���C�u������`
//================================================

class PLAYER;
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
//�N���X��`
//================================================
class ENEMYMNG
{
public:
	static ENEMYMNG *Instance()
	{
		static ENEMYMNG Inst;
		return &Inst;
	};

private:
	ENEMYMNG();
	PLAYER *m_pPlayer;		//�v���C���[�|�C���^
	EFFECT_MNG	*m_pEffectMng;
public:
	~ENEMYMNG();
	ENEMY  *m_pEnemy[ENEMY_NOMAL_NUM];		//�U�R�L������
	ENEMY  *m_pEnemyBoss;	//�{�X
	SCORE  *m_pScore;
	SOUND  *m_pSE;
	int    m_nGameEnd;						//�Q�[���G���h�t���O

	int m_DeadCnt;						//�|������
	int m_BossCnt;						//�|�����{�X�̐�

	void Init(PLAYER *pPlayer);			//������
	void Reset(void);		//���Z�b�g
	void Load(void);		//�ǂݍ���
	void Release(void);		//���
	void Create(void);		//�쐬
	void Deleate(void);		//�폜
	void Draw(void);		//�`��
	void Update(void);		//�X�V
};

//################################################
// End of File
//################################################
#endif _____ENEMYMNG_H_____

