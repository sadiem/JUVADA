//################################################
// <Rock.h>
//
//------------------------------------------------
// 2013/01/22
//						Akihito Tanaka
//################################################
#ifndef _____ROCK_H_____
#define _____ROCK_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
#include "Object.h"
#include "ShaderMng.h"	//�V�F�[�_�}�l�[�W��
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define ROCK_NUM	(20)

enum ROCK_TYPE{
	LINE,
	CIRCLE,
	MAX_TYPE,
};
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class ROCK:public EFFECT
{
public:
	static ROCK* Instance(void)
	{
		static ROCK inst;
		return &inst;
	};
	~ROCK();
private:
	ROCK();
	void Gen(int type);
	
	int		m_Type;			//��̃^�C�v
	GLuint	m_TexID;		//�e�N�X�`��ID
	GLuint	m_TexBumpID;	//�o���v�e�N�X�`��ID
	MESH	m_Mesh;
	OBJECT *m_Obj;
	int		m_interval;
	bool	m_Set;		//�V���ɃZ�b�g���邩
	bool	m_LR;		//���E���]�t���O
	float	m_Rad[ROCK_NUM];
	float	m_AngX[ROCK_NUM];	//X����]�i�|��j
	float	m_MaxScale[ROCK_NUM];
	SHADER_MNG *m_pShaderMng;

public:
	BILLBOARD m_Rock[ROCK_NUM];

	void Init(void);	//������
	void Load(void);	//�ǂݍ���
	void Reset(void);	//���Z�b�g
	void UpDate(void);	//�X�V
	void Set(OBJECT *obj, int type);	//��̃Z�b�g
	void Remove(void);	//��̃Z�b�g
	void Draw(void);	//�`��
	
};

//################################################
// End of File
//################################################
#endif _____ROCK_H_____
