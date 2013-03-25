//################################################
// <LightPillar.h>
//
//------------------------------------------------
// 2012/01/10 ~
//						Akihito Tanaka
//################################################
#ifndef _____L_PILLAR_H_____
#define _____L_PILLAR_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define PILLAR_NUM	(2)
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class L_PILLAR:public IMPACT
{
public:
	static L_PILLAR* Instance(void)
	{
		static L_PILLAR inst;
		return &inst;
	};
	~L_PILLAR();
private:
	L_PILLAR();
	
	//GLuint	m_TexID;	//�e�N�X�`��ID
	//MESH	m_Impact[IMPACT_NUM];
	//bool	m_Live;
	//VECTOR3 m_Pos;		//�\���ʒu
	//float	m_Alpha[IMPACT_NUM];	//�A���t�@�l
	//float	m_Scale[IMPACT_NUM];	//�X�P�[��
	//float	m_ScaleRate;
	//int		m_Time[IMPACT_NUM];
	//bool	m_dsp[IMPACT_NUM];		//�\���t���O

public:
	//void Init(void);	//������
	void Load(void);	//�ǂݍ���
	void Reset(void);	//���Z�b�g
	void UpDate(void);	//�X�V
	void Set(VECTOR3 vec);	//�����ʒu�̃Z�b�g
	void Draw(void);	//�`��
	
};

//################################################
// End of File
//################################################
#endif _____L_PILLAR_H_____