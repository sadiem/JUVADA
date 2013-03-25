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
//インクルードヘッダ
//================================================
#include "Include.h"	//インクルード
#include <windows.h>
#include "Matrix.h"		//共通
#include "Input.h"	//入力処理
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define VIEW_POS_GAME	(VECTOR3(0.0f, 8.0f, 15.0f))
#define VIEW_CENT_GAME	(VECTOR3(0.0f, 0.0f, 0.0f))
#define VIEW_UP_GAME	(VECTOR3(0.0f, 1.0f, 0.0f))

#define VIEW_POS_ZEYE_GAME (VECTOR3(0.0f, 4.0f, 15.0f))

#define VIEW_POS_OP		(VECTOR3(0.0f, 2.0f, 18.0f))
#define VIEW_CENT_OP	(VECTOR3(0.0f, 0.0f, 0.0f))
#define VIEW_UP_OP		(VECTOR3(0.0f, 1.0f, 0.0f))

//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//================================================
class CAMERA
{
public:
	//唯一のアクセス経路
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
	MATRIX		m_CameraMat;			//カメラマトリックス
	float		m_Speed;
	
	MATRIX		m_ViewMat;				//ビュー行列保存
	VECTOR3 ViewPos;
	VECTOR3 ViewCent;
	VECTOR3 ViewUp;
	float   m_Zoom;

	VECTOR3 vecx;						//X方向
	VECTOR3 vecz;						//Z方向
	VECTOR3 vecy;						//Y方向

	VECTOR3 Cpos;
	float rotZ;
	float rotR;

	void Update(VECTOR3 pvec, VECTOR3 evec);	//カメラの更新
	void SetGameCamera();				//カメラの設定
	void SetOpCamera();					//カメラ設定オープニング
	void ResetOp();						//リセットOP
	void ResetGame();					//リセットGAME
	void GetVecCamera();				//カメラベクトル取得
	void GetMatrixInv(MATRIX *mat);		//カメラマトリックスの逆行列

	bool Operatable;		//操作可能か
	void CAMERA::SetOperatable(bool flg);
private:
	void Move(VECTOR3 pvec);
	void MoveZ(VECTOR3 pvec, VECTOR3 evec);
	void GetCameraInfo();				//カメラ情報取得
};

//################################################
// End of File
//################################################
#endif _____CAMERA_H_____
