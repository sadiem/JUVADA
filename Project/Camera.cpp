//################################################
// <Camera.cpp>
//
//------------------------------------------------
// 2012/11/21 ~						SekiyamaRumi
// 2013/1/15	入力処理部分修正	akihtio tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Camera.h"
#include "Graphic.h"
//================================================
//定数定義
//================================================
#define MAX_ROT (60.0f / 360.0f * 3.141592f)
#define ZOOM_MIN	(0.0f)
#define ZOOM_MAX	(20.0f)

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
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
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CAMERA::~CAMERA()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット　OP
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
	m_CameraMat.m[0][0] = ViewPos.x;	//視点位置	X
	m_CameraMat.m[0][1] = ViewPos.y;	//視点位置	Y
	m_CameraMat.m[0][2] = ViewPos.z;	//視点位置	Z
	m_CameraMat.m[0][3] = 0.0f;	//視点位置	W

	m_CameraMat.m[1][0] = ViewCent.x;	//注視点位置	X
	m_CameraMat.m[1][1] = ViewCent.y;	//注視点位置	Y
	m_CameraMat.m[1][2] = ViewCent.z;	//注視点位置	Z
	m_CameraMat.m[1][3] = 0.0f;	//注視点位置	W

	m_CameraMat.m[2][0] = ViewUp.x;	//UPベクトル位置	X
	m_CameraMat.m[2][1] = ViewUp.y;	//UPベクトル位置	Y
	m_CameraMat.m[2][2] = ViewUp.z;	//UPベクトル位置	Z
	m_CameraMat.m[2][3] = 0.0f;	//UPベクトル位置	W

	m_CameraMat.m[3][0] = 0.0f;	//
	m_CameraMat.m[3][1] = 0.0f;	//
	m_CameraMat.m[3][2] = 0.0f;	//
	m_CameraMat.m[3][3] = 1.0f;	//	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット　GAME
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
	m_CameraMat.m[0][0] = ViewPos.x;	//視点位置	X
	m_CameraMat.m[0][1] = ViewPos.y;	//視点位置	Y
	m_CameraMat.m[0][2] = ViewPos.z;	//視点位置	Z
	m_CameraMat.m[0][3] = 0.0f;	//視点位置	W

	m_CameraMat.m[1][0] = ViewCent.x;	//注視点位置	X
	m_CameraMat.m[1][1] = ViewCent.y;	//注視点位置	Y
	m_CameraMat.m[1][2] = ViewCent.z;	//注視点位置	Z
	m_CameraMat.m[1][3] = 0.0f;	//注視点位置	W

	m_CameraMat.m[2][0] = ViewUp.x;	//UPベクトル位置	X
	m_CameraMat.m[2][1] = ViewUp.y;	//UPベクトル位置	Y
	m_CameraMat.m[2][2] = ViewUp.z;	//UPベクトル位置	Z
	m_CameraMat.m[2][3] = 0.0f;	//UPベクトル位置	W

	m_CameraMat.m[3][0] = 0.0f;	//
	m_CameraMat.m[3][1] = 0.0f;	//
	m_CameraMat.m[3][2] = 0.0f;	//
	m_CameraMat.m[3][3] = 1.0f;	//	
	Operatable = true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラの更新
//--in--------------------------------------------
//注視点座標
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

	//移動処理
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

	//ズーム
	if(pInput->GetBtnState(BTN_R2))	//上	Z
	{
		m_Zoom += 0.5f;

		if(m_Zoom > ZOOM_MAX)
			m_Zoom = ZOOM_MAX;
	}
	if(pInput->GetBtnState(BTN_L2))	//下	X
	{
		m_Zoom -= 0.5f;
		if(m_Zoom < ZOOM_MIN)
			m_Zoom = ZOOM_MIN;
	}

	Move(pvec);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラ移動
//--in--------------------------------------------
//　移動するベクトル
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::Move(VECTOR3 pvec)
{
	MATRIX mat, matTransC, matRotR, matRotZ, matTransP;
	MatrixIdentity(&mat);
	VECTOR3 vec = VIEW_POS_GAME;

	//視点から注視点までのベクトル
	MatrixTranslation(&matTransP, vec.x, vec.y, vec.z);				//移動
	MatrixRotationAxis(&matRotZ, vecx, rotZ);						//Y軸回転
	MatrixRotationAxis(&matRotR, VECTOR3(0.0f, 1.0f, 0.0f), rotR);	//X軸回転
	MatrixTranslation(&matTransC, pvec.x, pvec.y, pvec.z);			//移動
	
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
//Z注目カメラ移動
//--in--------------------------------------------
//　視点位置、注視点
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


	//視点から注視点までのベクトル
	MatrixTranslation(&matTransP, vec.x, vec.y, vec.z);					//移動
	//MatrixRotationAxis(&matRotZ, vecx, rotZ);							//X軸回転
	//MatrixRotationAxis(&matRotR, VECTOR3(0.0f, 1.0f, 0.0f), rot);	//Y軸回転
	MatrixTranslation(&matTransC, pvec.x, pvec.y, pvec.z);				//移動

	
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
//カメラの設定 (GAME)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::SetGameCamera()
{
	gluLookAt(ViewPos.x,   ViewPos.y,  ViewPos.z,		//視点座標						//視点位置(Z)
			  ViewCent.x,  ViewCent.y, ViewCent.z,		//注視点位置
			  ViewUp.x,	   ViewUp.y,   ViewUp.z);		//アップベクトル
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&m_CameraMat);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラの設定 (OP)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::SetOpCamera()
{
	gluLookAt(ViewPos.x,   ViewPos.y,  ViewPos.z,		//視点座標						//視点位置(Z)
			  ViewCent.x,  ViewCent.y, ViewCent.z,		//注視点位置
			  ViewUp.x,	   ViewUp.y,   ViewUp.z);		//アップベクトル
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&m_CameraMat);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラのベクトル成分抽出(プレイヤー用)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::GetVecCamera()
{
	VECTOR3 temp;
	//----------------------------------------
	// キャラ移動で使うカメラのベクトルを取得
	//----------------------------------------
	float *pmat;
	pmat = GetViewMat();

	//X軸成分
	vecx.x = *(pmat + 0);
	vecx.y = 0.0f;
	vecx.z = *(pmat + 8);

	//Z軸成分
	vecz.x = *(pmat + 2);
	vecz.y = 0.0f;
	vecz.z = *(pmat + 10);
	
	//Y軸成分
	vecy.x = *(pmat + 1);
	vecy.y = *(pmat + 5);
	vecy.z = *(pmat + 9);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラのベクトル成分抽出(カメラ用)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CAMERA::GetCameraInfo()
{
	VECTOR3 temp;
	//----------------------------------------
	// キャラ移動で使うカメラのベクトルを取得
	//----------------------------------------
	float *pmat;
	pmat = GetViewMat();

	//X軸成分
	vecx.x = *(pmat + 0);
	vecx.y = *(pmat + 4);
	vecx.z = *(pmat + 8);

	//Z軸成分
	vecz.x = *(pmat + 2);
	vecz.y = *(pmat + 6);
	vecz.z = *(pmat + 10);
	
	//Y軸成分
	vecy.x = *(pmat + 1);
	vecy.y = *(pmat + 5);
	vecy.z = *(pmat + 9);

	//座標
	Cpos.x = *(pmat + 12);
	Cpos.y = *(pmat + 13);
	Cpos.z = *(pmat + 14);

	//ビュー行列の生成
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
