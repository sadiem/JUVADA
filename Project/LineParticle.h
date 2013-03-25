//################################################
// <LineParticle.h>
//
//------------------------------------------------
// 2012/01/18 ~
//						Akihito Tanaka
//################################################
#ifndef _____LINE_PARTICLE_H_____
#define _____LINE_PARTICLE_H_____

//================================================
//インクルードヘッダ
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
#include "Object.h"
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define LINE_NUM	(100)
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
class LINE_PARTICLE
{
public:
	LINE_PARTICLE();
	~LINE_PARTICLE();
private:	
	GLuint	m_TexID;	//テクスチャID
	MESH	*m_Line[LINE_NUM];
	VECTOR3 m_Pos;		//表示位置
	float	m_Alpha[LINE_NUM];	//アルファ値
	float	m_Scale[LINE_NUM];	//スケール
	float	m_ScaleRate;
	int		m_Time[LINE_NUM];
	float	m_TexOffset[LINE_NUM];		//テクスチャアニメーション用オフセット
	bool	m_dsp[LINE_NUM];		//表示フラグ
	float	m_RadY[LINE_NUM];		//表示角度(Y軸回転)
	float	m_RadX[LINE_NUM];		//表示角度(X軸回転)

public:

	void Init(void);	//初期化
	void Load(MESH *mesh);	//読み込み
	void Reset(void);	//リセット
	void UpDate(void);	//更新
	void Set(OBJECT *obj);	//発生位置のセット
	void Gen(void);		//パーティクルの生成
	void Draw(void);	//描画
	bool	m_Live;
	OBJECT	*m_Obj;		//オブジェクトポインタ
	
};

//################################################
// End of File
//################################################
#endif _____LINE_PARTICLE_H_____
