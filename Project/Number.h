//################################################
//<Number.cpp>
// �����ꕶ�����o�͂���
//------------------------------------------------
//�}�C���X�C�[�p�쐬
//2012/06/11 ~
//						SekiyamaRumi
//################################################
#ifndef _____NUMBER_H______
#define _____NUMBER_H______

//================================================
//�C���N���[�h
//================================================
#include <windows.h>		//Windows �v���O�����ɂ͂����t����
#include <tchar.h>			//�ėp�e�L�X�g �}�b�s���O

#include "Include.h"		//�C���N���[�h

//================================================
//�\���̒�`
//================================================
struct FVERTEX_SCORE{
	GLfloat	tu, tv;			//�e�N�X�`�����W
	GLfloat x, y, z;		//���_���W
};

//================================================
//�N���X��`
//================================================
class NUMBER
{
private:
	FVERTEX_SCORE		m_Ver[4];	//���_���
	GLfloat				m_fPosX;	//�ʒu	X
	GLfloat				m_fPosY;	//�ʒu	Y
	int					m_Number;	//�o�͂��鐔��

public:
	NUMBER();						//�R���X�g���N�^
	virtual ~NUMBER();						//�f�X�g���N�^

	void Disp(GLuint fID);			//�`��
	void SetNum(int num);			//�\�����鐔��
	void SetPos(float x, float y,int nD, float m_num_w, float m_num_h);		//���W���Z�b�g����
	
};

#endif _____NUMBER_H______
