//################################################
// <Camera.cpp>
//
//------------------------------------------------
// 2012/11/21 ~						SekiyamaRumi
// 2013/1/15	���͏��������C��	akihtio tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Camera.h"
#include "Graphic.h"
//================================================
//�萔��`
//================================================
#define MAX_ROT (60.0f / 360.0f * 3.141592f)
#define ZOOM_MIN	(0.0f)
#define ZOOM_MAX	(20.0f)

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CAMERA::CAMERA()
{
	vecx = VECTOR3(1.0f, 0.0f, 0.0f);
	vecz = VECTOR3(0.0f, 0.0f, -1.0f);
	pInput = INPUT_MNG::getInstance();
	Operatable = true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CAMERA::~CAMERA()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g�@OP
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::ResetOp()
{
	ViewPos = VIEW_POS_OP;
	ViewCent = VIEW_CENT_OP;
	ViewUp = VIEW_UP_OP;
	m_CameraMat.m[0][0] = ViewPos.x;	//���_�ʒu	X
	m_CameraMat.m[0][1] = ViewPos.y;	//���_�ʒu	Y
	m_CameraMat.m[0][2] = ViewPos.z;	//���_�ʒu	Z
	m_CameraMat.m[0][3] = 0.0f;	//���_�ʒu	W

	m_CameraMat.m[1][0] = ViewCent.x;	//�����_�ʒu	X
	m_CameraMat.m[1][1] = ViewCent.y;	//�����_�ʒu	Y
	m_CameraMat.m[1][2] = ViewCent.z;	//�����_�ʒu	Z
	m_CameraMat.m[1][3] = 0.0f;	//�����_�ʒu	W

	m_CameraMat.m[2][0] = ViewUp.x;	//UP�x�N�g���ʒu	X
	m_CameraMat.m[2][1] = ViewUp.y;	//UP�x�N�g���ʒu	Y
	m_CameraMat.m[2][2] = ViewUp.z;	//UP�x�N�g���ʒu	Z
	m_CameraMat.m[2][3] = 0.0f;	//UP�x�N�g���ʒu	W

	m_CameraMat.m[3][0] = 0.0f;	//
	m_CameraMat.m[3][1] = 0.0f;	//
	m_CameraMat.m[3][2] = 0.0f;	//
	m_CameraMat.m[3][3] = 1.0f;	//	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g�@GAME
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::ResetGame()
{
	ViewPos = VIEW_POS_GAME;
	ViewCent = VIEW_CENT_GAME;
	ViewUp = VIEW_UP_GAME;
	m_CameraMat.m[0][0] = ViewPos.x;	//���_�ʒu	X
	m_CameraMat.m[0][1] = ViewPos.y;	//���_�ʒu	Y
	m_CameraMat.m[0][2] = ViewPos.z;	//���_�ʒu	Z
	m_CameraMat.m[0][3] = 0.0f;	//���_�ʒu	W

	m_CameraMat.m[1][0] = ViewCent.x;	//�����_�ʒu	X
	m_CameraMat.m[1][1] = ViewCent.y;	//�����_�ʒu	Y
	m_CameraMat.m[1][2] = ViewCent.z;	//�����_�ʒu	Z
	m_CameraMat.m[1][3] = 0.0f;	//�����_�ʒu	W

	m_CameraMat.m[2][0] = ViewUp.x;	//UP�x�N�g���ʒu	X
	m_CameraMat.m[2][1] = ViewUp.y;	//UP�x�N�g���ʒu	Y
	m_CameraMat.m[2][2] = ViewUp.z;	//UP�x�N�g���ʒu	Z
	m_CameraMat.m[2][3] = 0.0f;	//UP�x�N�g���ʒu	W

	m_CameraMat.m[3][0] = 0.0f;	//
	m_CameraMat.m[3][1] = 0.0f;	//
	m_CameraMat.m[3][2] = 0.0f;	//
	m_CameraMat.m[3][3] = 1.0f;	//	
	Operatable = true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����̍X�V
//--in--------------------------------------------
//�����_���W
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::Update(VECTOR3 pvec, VECTOR3 evec)
{
	VECTOR3 vec;

	if(!Operatable)
	{
		MoveZ(pvec, evec);
		return;
	}

	//�ړ�����
	if(pInput->GetBtnState(BTN_CAM_DOWN))
	{
		rotZ -= 0.03f;
		if(rotZ < -MAX_ROT / 2.0f)
			rotZ = -MAX_ROT / 2.0f;
	}
	if(pInput->GetBtnState(BTN_CAM_UP))
	{
		rotZ += 0.03f;
		if(rotZ > MAX_ROT)
			rotZ = MAX_ROT;
	}
	if(pInput->GetBtnState(BTN_CAM_RIGHT))
	{
		rotR += 0.03f;
		//Move(pvec);
	}
	if(pInput->GetBtnState(BTN_CAM_LEFT))
	{
		rotR -= 0.03f;
	}

	//�Y�[��
	if(pInput->GetBtnState(BTN_R2))	//��	Z
	{
		m_Zoom += 0.5f;

		if(m_Zoom > ZOOM_MAX)
			m_Zoom = ZOOM_MAX;
	}
	if(pInput->GetBtnState(BTN_L2))	//��	X
	{
		m_Zoom -= 0.5f;
		if(m_Zoom < ZOOM_MIN)
			m_Zoom = ZOOM_MIN;
	}

	Move(pvec);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����ړ�
//--in--------------------------------------------
//�@�ړ�����x�N�g��
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::Move(VECTOR3 pvec)
{
	MATRIX mat, matTransC, matRotR, matRotZ, matTransP;
	MatrixIdentity(&mat);
	VECTOR3 vec = VIEW_POS_GAME;

	//���_���璍���_�܂ł̃x�N�g��
	MatrixTranslation(&matTransP, vec.x, vec.y, vec.z);				//�ړ�
	MatrixRotationAxis(&matRotZ, vecx, rotZ);						//Y����]
	MatrixRotationAxis(&matRotR, VECTOR3(0.0f, 1.0f, 0.0f), rotR);	//X����]
	MatrixTranslation(&matTransC, pvec.x, pvec.y, pvec.z);			//�ړ�
	
	MatrixMultiply(&mat, mat, matTransC);
	MatrixMultiply(&mat, mat, matRotZ);
	MatrixMultiply(&mat, mat, matRotR);
	MatrixMultiply(&mat, mat, matTransP);

	ViewPos.x = mat._41;
	ViewPos.y = mat._42;
	ViewPos.z = mat._43;

	ViewCent.x = pvec.x;
	ViewCent.y = pvec.y;
	ViewCent.z = pvec.z;

	VECTOR3 v;
	v = ViewPos - ViewCent;
	Vec3Normalize(&v, v);
	ViewPos += v * m_Zoom;
}//++++++++++++++++++++++++++++++++++++++++++++++++
//Z���ڃJ�����ړ�
//--in--------------------------------------------
//�@���_�ʒu�A�����_
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::MoveZ(VECTOR3 pvec, VECTOR3 evec)
{
	MATRIX mat, matTransC, matRotR, matRotZ, matTransP;
	MatrixIdentity(&mat);
	VECTOR3 vec = VIEW_POS_ZEYE_GAME;

	VECTOR3 vWork = evec - pvec;
	//float rot = VectoVec( VECTOR3(0.0f, 0.0f, 1.0f), v);

	vWork.y = 0.0f;
	Vec3Normalize(&vWork, vWork);


	//���_���璍���_�܂ł̃x�N�g��
	MatrixTranslation(&matTransP, vec.x, vec.y, vec.z);					//�ړ�
	//MatrixRotationAxis(&matRotZ, vecx, rotZ);							//X����]
	//MatrixRotationAxis(&matRotR, VECTOR3(0.0f, 1.0f, 0.0f), rot);	//Y����]
	MatrixTranslation(&matTransC, pvec.x, pvec.y, pvec.z);				//�ړ�

	
	MatrixMultiply(&mat, mat, matTransC);
	//MatrixMultiply(&mat, mat, matRotZ);
	//MatrixMultiply(&mat, mat, matRotR);
	MatrixMultiply(&mat, mat, matTransP);

	ViewPos.x = pvec.x - vWork.x * 15.0f;
	ViewPos.y = pvec.y + 3.0f;
	ViewPos.z = pvec.z - vWork.z * 15.0f;

	ViewCent.x = evec.x;
	ViewCent.y = evec.y;
	ViewCent.z = evec.z;

	//VECTOR3 v;
	//v = ViewPos - ViewCent;
	//Vec3Normalize(&v, v);
	//ViewPos += v * m_Zoom;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����̐ݒ� (GAME)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::SetGameCamera()
{
	gluLookAt(ViewPos.x,   ViewPos.y,  ViewPos.z,		//���_���W						//���_�ʒu(Z)
			  ViewCent.x,  ViewCent.y, ViewCent.z,		//�����_�ʒu
			  ViewUp.x,	   ViewUp.y,   ViewUp.z);		//�A�b�v�x�N�g��
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&m_CameraMat);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����̐ݒ� (OP)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::SetOpCamera()
{
	gluLookAt(ViewPos.x,   ViewPos.y,  ViewPos.z,		//���_���W						//���_�ʒu(Z)
			  ViewCent.x,  ViewCent.y, ViewCent.z,		//�����_�ʒu
			  ViewUp.x,	   ViewUp.y,   ViewUp.z);		//�A�b�v�x�N�g��
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&m_CameraMat);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����̃x�N�g���������o(�v���C���[�p)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::GetVecCamera()
{
	VECTOR3 temp;
	//----------------------------------------
	// �L�����ړ��Ŏg���J�����̃x�N�g�����擾
	//----------------------------------------
	float *pmat;
	pmat = GetViewMat();

	//X������
	vecx.x = *(pmat + 0);
	vecx.y = 0.0f;
	vecx.z = *(pmat + 8);

	//Z������
	vecz.x = *(pmat + 2);
	vecz.y = 0.0f;
	vecz.z = *(pmat + 10);
	
	//Y������
	vecy.x = *(pmat + 1);
	vecy.y = *(pmat + 5);
	vecy.z = *(pmat + 9);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�����̃x�N�g���������o(�J�����p)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::GetCameraInfo()
{
	VECTOR3 temp;
	//----------------------------------------
	// �L�����ړ��Ŏg���J�����̃x�N�g�����擾
	//----------------------------------------
	float *pmat;
	pmat = GetViewMat();

	//X������
	vecx.x = *(pmat + 0);
	vecx.y = *(pmat + 4);
	vecx.z = *(pmat + 8);

	//Z������
	vecz.x = *(pmat + 2);
	vecz.y = *(pmat + 6);
	vecz.z = *(pmat + 10);
	
	//Y������
	vecy.x = *(pmat + 1);
	vecy.y = *(pmat + 5);
	vecy.z = *(pmat + 9);

	//���W
	Cpos.x = *(pmat + 12);
	Cpos.y = *(pmat + 13);
	Cpos.z = *(pmat + 14);

	//�r���[�s��̐���
	m_ViewMat.m[0][1] = *(pmat + 0);
	m_ViewMat.m[0][2] = *(pmat + 1);
	m_ViewMat.m[0][3] = *(pmat + 2);
	m_ViewMat.m[0][4] = *(pmat + 3);

	m_ViewMat.m[1][1] = *(pmat + 4);
	m_ViewMat.m[1][2] = *(pmat + 5);
	m_ViewMat.m[1][3] = *(pmat + 6);
	m_ViewMat.m[1][4] = *(pmat + 7);

	m_ViewMat.m[2][1] = *(pmat + 8);
	m_ViewMat.m[2][2] = *(pmat + 9);
	m_ViewMat.m[2][3] = *(pmat + 10);
	m_ViewMat.m[2][4] = *(pmat + 11);

	m_ViewMat.m[3][1] = *(pmat + 12);
	m_ViewMat.m[3][2] = *(pmat + 13);
	m_ViewMat.m[3][3] = *(pmat + 14);
	m_ViewMat.m[3][4] = *(pmat + 15);
}

void CAMERA::GetMatrixInv(MATRIX *mat)
{
	MatrixInv(mat, m_CameraMat);
}
void CAMERA::SetOperatable(bool flg)
{
	Operatable = flg;
}
//################################################
// End of File
//################################################
