//################################################
// <EnemyBossHpBar.cpp>
//
//------------------------------------------------
// 2013/02/06 ~
//						SekiyamaRumi
//################################################
#ifndef _____BOSS_HP_BAR_H_____
#define _____BOSS_HP_BAR_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//�C���N���[�h�w�b�_
#include "Common.h"		//���ʃw�b�_
#include "EnemyMng.h"	//
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define B_BAR_W	(600)
#define B_BAR_H	(120)
#define POS_B_BAR_X (120)	//�����ʒu
#define POS_B_BAR_Y (480)

//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class BOSS_HP_BAR
{
public:
	static BOSS_HP_BAR* Instance()
	{
		static BOSS_HP_BAR Inst;
		return &Inst;
	}
	~BOSS_HP_BAR();
private:
	BOSS_HP_BAR();
	ENEMYMNG	*m_pEnemyMng;
	//----------------------------
	// 0�c�t���[��
	// 1�c�o�[
	// 2�c�J�o�[
	//----------------------------
	FVERTEX  m_Poly[3][4];		//�|��
	GLuint   m_TexID;		//�e�N�X�`���h�c
	
public:
	float  nM;
	void Init(void);
	void Reset(void);	//���Z�b�g
	void Load (void);	//�ǂݍ���
	void Update(int nHP, int nMaxHP);
	void Draw(void);
};
//################################################
// End of File
//################################################
#endif _____BOSS_HP_BAR_H_____