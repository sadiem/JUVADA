//################################################
// <Object.h>
//
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
//################################################
#ifndef _____OBJECT_H_____
#define _____OBJECT_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Matrix.h"
#include "MeshMng.h"
#include "ShaderMng.h"	//シェーダマネージャ
//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================

//================================================
//クラス定義
//================================================
class OBJECT{
public:
	MATRIX		m_Matrix;		//変換マトリックス (合成)
	MATRIX		m_MatrixRot;	//変換マトリックス（回転）
	VECTOR3		m_Pos;			//位置
	VECTOR3     m_PosPrev;		//位置座標前
	VECTOR3		m_vec;			//キャラの向き
	VECTOR3		m_vecPrev;		//キャラの向き前
	VECTOR3     m_vecS;			//移動速度
	VECTOR3     m_Scale;		//拡大
	float		m_Rad;			//回転角
	int			m_State;		//状態
	int			m_Life;			//体力
	bool		m_Live;			//生存
	float       m_Speed;		//速度
	int			m_Type;			//タイプ
	float		m_ScaleRate;	//拡大率
	float		m_Width;		//モデル幅
	int			m_Attack;		//攻撃力
	int			m_Timer;		//タイマー
	VECTOR3     m_crossPrev;	//視線ベクトル保存用
	SHADOWVOLUME m_Shadow;		//影
	SHADER_MNG  *p_ShadeMng;	//シェーダマネージャ
	
	bool	m_Effect;			//エフェクト表示

	MESH		*m_Mesh;		//メッシュデータ
	GLuint		m_TexID;		//テクスチャID

	OBJECT();
	virtual ~OBJECT();

	void Move(VECTOR3 vec);		//移動処理
	void LifeCount(int damage);	//ダメージ計算
	bool JudgLife(void);		//死亡判定
};

//################################################
// End of File
//################################################
#endif _____OBJECT_H_____
