//################################################
// <Smoke.h>
//
//------------------------------------------------
// 2013/01/06 ~
//						SekiyamaRumi
//################################################
#ifndef _____SMOKE_H_____
#define _____SMOKE_H_____

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
#define SMOKE_NUM	(1000)
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class SMOKE:public EFFECT
{
public:
	static SMOKE* Instance(void)
	{
		static SMOKE inst;
		return &inst;
	};
	~SMOKE();
private:
	SMOKE();
	
	GLuint	m_TexID;	//�e�N�X�`��ID
	MESH	m_Mesh;

//	void UpdateSmoke(void);		//���̍X�V

public:
	BILLBOARD m_Smoke[SMOKE_NUM];

	void Init(void);	//������
	void Load(void);	//�ǂݍ���
	void Reset(void);	//���Z�b�g
	void UpDate(void);	//�X�V
	void SetSmoke(VECTOR3 vec);	//���̃Z�b�g
	void Draw(void);	//�`��
	
};

//################################################
// End of File
//################################################
#endif _____SMOKE_H_____