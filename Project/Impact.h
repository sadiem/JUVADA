//################################################
// <Impact.h>
//
//------------------------------------------------
// 2012/01/10 ~
//						Akihito Tanaka
//################################################
#ifndef _____IMPACT_H_____
#define _____IMPACT_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
#include "Random.h"	//����
#include "Matrix.h"	//���w
#include "TexMng.h"	//�e�N�X�`���}�l�[�W��
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define IMPACT_NUM	(5)
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class IMPACT:public EFFECT
{
public:
	static IMPACT* Instance(void)
	{
		static IMPACT inst;
		return &inst;
	};
	~IMPACT();
protected:
	IMPACT();
	
	GLuint	m_TexID;	//�e�N�X�`��ID
	MESH	m_Impact[IMPACT_NUM];
	bool	m_Live;
	VECTOR3 m_Pos;		//�\���ʒu
	float	m_Alpha[IMPACT_NUM];	//�A���t�@�l
	float	m_Scale[IMPACT_NUM];	//�X�P�[��
	float	m_ScaleRate;
	int		m_Time[IMPACT_NUM];
	bool	m_dsp[IMPACT_NUM];		//�\���t���O

public:

	void Init(void);	//������
	void Load(void);	//�ǂݍ���
	void Reset(void);	//���Z�b�g
	void UpDate(void);	//�X�V
	void Set(VECTOR3 vec);	//�����ʒu�̃Z�b�g
	void Draw(void);	//�`��
	
};

//################################################
// End of File
//################################################
#endif _____IMPACT_H_____
