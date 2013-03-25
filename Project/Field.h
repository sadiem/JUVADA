//################################################
// <Field.h>
// �w�i����
//------------------------------------------------
// 2012/11/26 ~					SekiyamaRumi
// 2013/1/29	��̕`��𕪗��@Akihito Tanaka
//################################################
#ifndef _____FIELD_H_____
#define _____FIELD_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Common.h"
#include "Mesh.h"
#include "Matrix.h"
#include "ShaderMng.h"

//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define SKY_POS (VECTOR3(0.0f, 0.0f, 0.0f))
#define FENCE_NUM	(20)	//�t�F���X��
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class FIELD
{
public:
	static FIELD* Instance()
	{
		static FIELD Inst;
		return &Inst;
	};

private:
	FIELD();
	VECTOR3 m_skypos;		//�X�J�C�h�[�����W
	SHADER_MNG *m_Shade;	//�V�F�[�_�}�l�[�W��
	GLuint  m_TexIDField;	//�e�N�X�`���ԍ�
	GLuint  m_TexIDFieldB;	//�e�N�X�`���ԍ�
	GLuint  m_TexIDFieldBack;	//�e�N�X�`���ԍ�
	GLuint  m_TexIDSky;		//�e�N�X�`���ԍ�
	GLuint  m_TexIDSaku;	//�e�N�X�`���ԍ�
	MESH    m_Mesh;			//���b�V���f�[�^
	MESH    m_MeshfieldBack;	//���b�V���f�[�^
	MESH    m_Meshsky;		//���b�V���f�[�^
	MESH	m_MeshSaku;		//���b�V���f�[�^
	GLuint  m_nShdID;		//�V�F�[�_ID

public:

	~FIELD();
	VECTOR3 m_FencePos[FENCE_NUM];	//��̈ʒu
	float   m_FenceRot[FENCE_NUM];	//��̉�]

	void Init();			//������
	void Load();			//�ǂݍ���
	void Release();			//���
	void Update();			//�X�V
	void Draw();			//�`��
	void DrawFence();		//��̕`��

};
//################################################
// End of File
//################################################
#endif _____FIELD_H_____

