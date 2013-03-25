//################################################
// <LineParticle.h>
//
//------------------------------------------------
// 2012/01/18 ~
//						Akihito Tanaka
//################################################
#ifndef _____LINE_PARTICLE_H_____
#define _____LINE_PARTICLE_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
#include "Object.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define LINE_NUM	(100)
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class LINE_PARTICLE
{
public:
	LINE_PARTICLE();
	~LINE_PARTICLE();
private:	
	GLuint	m_TexID;	//�e�N�X�`��ID
	MESH	*m_Line[LINE_NUM];
	VECTOR3 m_Pos;		//�\���ʒu
	float	m_Alpha[LINE_NUM];	//�A���t�@�l
	float	m_Scale[LINE_NUM];	//�X�P�[��
	float	m_ScaleRate;
	int		m_Time[LINE_NUM];
	float	m_TexOffset[LINE_NUM];		//�e�N�X�`���A�j���[�V�����p�I�t�Z�b�g
	bool	m_dsp[LINE_NUM];		//�\���t���O
	float	m_RadY[LINE_NUM];		//�\���p�x(Y����])
	float	m_RadX[LINE_NUM];		//�\���p�x(X����])

public:

	void Init(void);	//������
	void Load(MESH *mesh);	//�ǂݍ���
	void Reset(void);	//���Z�b�g
	void UpDate(void);	//�X�V
	void Set(OBJECT *obj);	//�����ʒu�̃Z�b�g
	void Gen(void);		//�p�[�e�B�N���̐���
	void Draw(void);	//�`��
	bool	m_Live;
	OBJECT	*m_Obj;		//�I�u�W�F�N�g�|�C���^
	
};

//################################################
// End of File
//################################################
#endif _____LINE_PARTICLE_H_____
