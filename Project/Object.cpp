//################################################
// <Object.cpp>
//
//------------------------------------------------
// 2012/12/02 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Object.h"
#include "math.h"
//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================

//================================================
//クラス定義
//================================================
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
OBJECT::OBJECT()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
OBJECT::~OBJECT()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//ダメージ計算
//--in--------------------------------------------
// なし
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void OBJECT::LifeCount(int damage)
{
	m_Life -= damage;
	//ライフがなくなったら０に戻しておく
	if(m_Life < 0)
		m_Life = 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//死亡判定
//--in--------------------------------------------
// なし
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OBJECT::JudgLife(void)
{
	if(m_Life <= 0)	//体力がなくなったとき
	{
		m_Live = false;	//死亡判定フラグを立てる
		return true;
	}return false;
}		

//++++++++++++++++++++++++++++++++++++++++++++++++
//移動処理
//--in--------------------------------------------
//方向ベクトル
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void OBJECT::Move(VECTOR3 vec)
{
	MATRIX mat;
	VECTOR3 vecT;
	VECTOR3 vecV;	//姿勢ベクトル
	VECTOR3 vectmp;
	float fRot = 0.0f;

	m_Pos += vec;

	//姿勢ベクトル取得
	vecT.x = m_MatrixRot._31;
	vecT.y = m_MatrixRot._32;
	vecT.z = m_MatrixRot._33;

	if(VecLength(vec) != 0)
		Vec3Normalize(&vec, vec);
	//進行方向と姿勢ベクトルのハーフベクトル(キャラの次の向き)を求める
	vecV = vecT + vec;
	if(VecLength(vecV) == 0.0f)
	{
		vec.x = 0.01f;
		vecV = vecT + vec;
	}

	//正規化
	Vec3Normalize(&vecV, vecV);
	Vec3Normalize(&vecT, vecT);

	//角度を出す
	fRot = VectoVec(vecT, vecV);
	m_Rad += fRot;

	//回転マトリックスの更新
	MatrixRotationY(&m_MatrixRot, m_Rad);
}



//################################################
// End of File
//################################################