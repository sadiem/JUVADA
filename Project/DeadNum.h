//################################################
// <DeadNum.cpp>
// �Q�[����ʒ��A��ɃX�R�A�̏o��(2D)
//------------------------------------------------
// 2013/01/30 ~
//						SekiyamaRumi
//################################################
#ifndef _____DEAD_NUM_H_____
#define _____DEAD_NUM_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include <windows.h>		//Windows �v���O�����ɂ͂����t����
#include <tchar.h>			//�ėp�e�L�X�g �}�b�s���O

#include "NumView.h"		//���l�o�̓w�b�_

//================================================
//�萔��`
//================================================

//================================================
//�N���X�錾
//================================================
class DEAD_NUM: public NUM_VIEW
{
private:
	DEAD_NUM(){}
	GLuint m_TexID;

public:
	static DEAD_NUM *Instance()
	{
		static DEAD_NUM Inst;
		return &Inst;
	}
	virtual ~DEAD_NUM(){}
	
	void SetTexID(GLuint TexID);				//�e�N�X�`��ID�Z�b�g
	void SetNum(int nDeadNum);					//���l�Z�b�g
	void SetVer(int X, int Y, int W, int H);	//�e�N�X�`�����
	void Draw(void);							//�`��
};

//################################################
// End of File
//################################################
#endif _____DEAD_NUM_H_____
