//################################################
// <Score.cpp>
//
//------------------------------------------------
// 2012/11/09 ~
//2013/01/31  �C��
//						SekiyamaRumi
//################################################
#ifndef _____SCORE_H_____
#define _____SCORE_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include <windows.h>		//Windows �v���O�����ɂ͂����t����
#include <tchar.h>			//�ėp�e�L�X�g �}�b�s���O

#include "NumView.h"		//���l�o�̓w�b�_

//================================================
//�萔��`
//================================================
//�X�R�A�����N�\
#define SCORE_SSS	(100)
#define SCORE_SS	(90)
#define SCORE_S		(80)
#define SCORE_A		(50)
#define SCORE_B		(40)
#define SCORE_C		(30)
#define SCORE_D		(0)

enum{
	RANK_D,
	RANK_C,
	RANK_B,
	RANK_A,
	RANK_S,
	RANK_SS,
	RANK_SSS
};
//================================================
//�N���X�錾
//================================================
//class SCORE;
class SCORE: public NUM_VIEW
{
private:
	SCORE();						//�R���X�g���N�^
	int m_nScore;			//�X�R�A

public:
	static SCORE *Instance()
	{
		static SCORE Inst;
		return &Inst;
	}

	virtual ~SCORE();		//�f�X�g���N�^
	GLuint m_TexID;			//�e�N�X�`��ID
	
	void Init();			//������
	void Load();			//�f�[�^�̃��[�h
	void Update(int Enemy, int Boss);	//�X�V
	void Draw(void);		//�`��
	void Reset(void);		//���Z�b�g

	void SetTexID(GLuint TexID);				//�e�N�X�`��ID�Z�b�g
	void SetNum(void);							//���l�Z�b�g
	void SetVer(int X, int Y, int W, int H);	//�e�N�X�`�����
	int ColEvolution(void);						//�]������p
	int GetScore(void){return m_nScore;}
private:
	void Calc(void);					//�X�R�A�̌v�Z
	void addEnemyDeathScore(int num);	//�X�R�A���Z:�G�|������
	int EnemyDeath;
	int BossDeath;
	int nCount;
	int nCombo;
	int nMaxCombo;
};

//################################################
// End of File
//################################################
#endif _____SCORE_H_____
