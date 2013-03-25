//################################################
// <Object.h>
//
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
//################################################
#ifndef _____OBJECT_H_____
#define _____OBJECT_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Matrix.h"
#include "MeshMng.h"
#include "ShaderMng.h"	//�V�F�[�_�}�l�[�W��
//================================================
//�萔��`
//================================================

//================================================
//�\���̒�`
//================================================

//================================================
//�N���X��`
//================================================
class OBJECT{
public:
	MATRIX		m_Matrix;		//�ϊ��}�g���b�N�X (����)
	MATRIX		m_MatrixRot;	//�ϊ��}�g���b�N�X�i��]�j
	VECTOR3		m_Pos;			//�ʒu
	VECTOR3     m_PosPrev;		//�ʒu���W�O
	VECTOR3		m_vec;			//�L�����̌���
	VECTOR3		m_vecPrev;		//�L�����̌����O
	VECTOR3     m_vecS;			//�ړ����x
	VECTOR3     m_Scale;		//�g��
	float		m_Rad;			//��]�p
	int			m_State;		//���
	int			m_Life;			//�̗�
	bool		m_Live;			//����
	float       m_Speed;		//���x
	int			m_Type;			//�^�C�v
	float		m_ScaleRate;	//�g�嗦
	float		m_Width;		//���f����
	int			m_Attack;		//�U����
	int			m_Timer;		//�^�C�}�[
	VECTOR3     m_crossPrev;	//�����x�N�g���ۑ��p
	SHADOWVOLUME m_Shadow;		//�e
	SHADER_MNG  *p_ShadeMng;	//�V�F�[�_�}�l�[�W��
	
	bool	m_Effect;			//�G�t�F�N�g�\��

	MESH		*m_Mesh;		//���b�V���f�[�^
	GLuint		m_TexID;		//�e�N�X�`��ID

	OBJECT();
	virtual ~OBJECT();

	void Move(VECTOR3 vec);		//�ړ�����
	void LifeCount(int damage);	//�_���[�W�v�Z
	bool JudgLife(void);		//���S����
};

//################################################
// End of File
//################################################
#endif _____OBJECT_H_____
