//################################################
// <Camera.h>
//
//------------------------------------------------
// 2012/11/21 ~
//						SekiyamaRumi
//################################################
#ifndef _____CAMERA_H_____
#define _____CAMERA_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//�C���N���[�h
#include <windows.h>
#include "Matrix.h"		//����
#include "Input.h"	//���͏���
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define VIEW_POS_GAME	(VECTOR3(0.0f, 8.0f, 15.0f))
#define VIEW_CENT_GAME	(VECTOR3(0.0f, 0.0f, 0.0f))
#define VIEW_UP_GAME	(VECTOR3(0.0f, 1.0f, 0.0f))

#define VIEW_POS_ZEYE_GAME (VECTOR3(0.0f, 4.0f, 15.0f))

#define VIEW_POS_OP		(VECTOR3(0.0f, 2.0f, 18.0f))
#define VIEW_CENT_OP	(VECTOR3(0.0f, 0.0f, 0.0f))
#define VIEW_UP_OP		(VECTOR3(0.0f, 1.0f, 0.0f))

//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class CAMERA
{
public:
	//�B��̃A�N�Z�X�o�H
	static CAMERA *Instance()
	{
		static CAMERA inst;
		return &inst;
	}
private:
	CAMERA();
	INPUT_MNG *pInput;

public:
	~CAMERA();
	MATRIX		m_CameraMat;			//�J�����}�g���b�N�X
	float		m_Speed;
	
	MATRIX		m_ViewMat;				//�r���[�s��ۑ�
	VECTOR3 ViewPos;
	VECTOR3 ViewCent;
	VECTOR3 ViewUp;
	float   m_Zoom;

	VECTOR3 vecx;						//X����
	VECTOR3 vecz;						//Z����
	VECTOR3 vecy;						//Y����

	VECTOR3 Cpos;
	float rotZ;
	float rotR;

	void Update(VECTOR3 pvec, VECTOR3 evec);	//�J�����̍X�V
	void SetGameCamera();				//�J�����̐ݒ�
	void SetOpCamera();					//�J�����ݒ�I�[�v�j���O
	void ResetOp();						//���Z�b�gOP
	void ResetGame();					//���Z�b�gGAME
	void GetVecCamera();				//�J�����x�N�g���擾
	void GetMatrixInv(MATRIX *mat);		//�J�����}�g���b�N�X�̋t�s��

	bool Operatable;		//����\��
	void CAMERA::SetOperatable(bool flg);
private:
	void Move(VECTOR3 pvec);
	void MoveZ(VECTOR3 pvec, VECTOR3 evec);
	void GetCameraInfo();				//�J�������擾
};

//################################################
// End of File
//################################################
#endif _____CAMERA_H_____
