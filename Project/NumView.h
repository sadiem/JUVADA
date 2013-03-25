//################################################
//<NumView.h>
// ���l�`��
//------------------------------------------------
//2012/06/11 ~
//2013/01/31  �C��
//						SekiyamaRumi
//################################################
#ifndef _____NUM_VIEW_H______
#define _____NUM_VIEW_H______
//================================================
//�C���N���[�h
//================================================
#include <windows.h>		//Windows �v���O�����ɂ͂����t����
#include <tchar.h>			//�ėp�e�L�X�g �}�b�s���O

#include "Include.h"		//�C���N���[�h
#include "Number.h"			//�����w�b�_

//================================================
//�萔��`
//================================================

#define DIGIT	(5)
#define DIGIT_TIME	(8)

//================================================
//�N���X��`
//================================================
class NUM_VIEW
{
private:
	NUMBER		m_Num[DIGIT];	//�X�R�A�\���p
	NUMBER		m_NumT[DIGIT_TIME];	//�X�R�A�\���p


public:
	NUM_VIEW();				//�R���X�g���N�^
	virtual ~NUM_VIEW();			//�f�X�g���N�^

protected:
	float		m_x;		//�����ʒu_x
	float		m_y;		//�����ʒu_y
	float		m_num_w;	//���l�e�N�X�`���̉���
	float		m_num_h;	//���l�e�N�X�`���̏c��

	void Load(char *pszFName);		//���[�h
	void Draw(GLuint TexID);		//�`��
	void DrawTime(GLuint TexID);	//�`��@�^�C��
	void Updata(int nNum1);			//�X�V
	void SetTex(int nNum);			//�e�N�X�`���Z�b�g
	void SetTex(DWORD s, DWORD m, DWORD mm);	//���ԗp
};

#endif _____NUM_VIEW_H______
