//################################################
// <Time.h>
//
//------------------------------------------------
// 2013/01/31 ~
//						SekiyamaRumi
//################################################
#ifndef _____TIME_H_____
#define _____TIME_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include <time.h>
#include "NumView.h"
//================================================
//�萔��`
//================================================

//================================================
//�N���X�錾
//================================================
class TIME_MNG :public NUM_VIEW
{
public:
	static TIME_MNG* Instance()
	{
		static TIME_MNG Inst;
		return &Inst;
	}
	~TIME_MNG();
private:
	TIME_MNG();
	GLuint  m_TexID;
	DWORD   m_NowTime;		//���ݎ���
	DWORD   m_StartTime;	//�J�n����
	DWORD   m_ElapsedTime;	//�o�ߎ���

	DWORD   m_mm;			//�~���b
	DWORD   m_m;			//�b
	DWORD   m_s;			//��
public:
	void Load (void);
	void Release(void);
	void Reset(void);	//���Z�b�g
	void Start(void);	//�X�^�[�g
	void Update(void);	//�X�V
	void SetPos(float X, float Y, float W, float H);		//�����w��
	void Draw (GLuint texId);	//�`��
	void Draw ();	//�`��
};

//################################################
// End of File
//################################################
#endif _____TIME_H_____
