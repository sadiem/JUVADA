//################################################
// <LightPillar.h>
//
//------------------------------------------------
// 2012/01/10 ~
//						Akihito Tanaka
//################################################
#ifndef _____L_PILLAR_H_____
#define _____L_PILLAR_H_____

//================================================
//インクルードヘッダ
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define PILLAR_NUM	(2)
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
class L_PILLAR:public IMPACT
{
public:
	static L_PILLAR* Instance(void)
	{
		static L_PILLAR inst;
		return &inst;
	};
	~L_PILLAR();
private:
	L_PILLAR();
	
	//GLuint	m_TexID;	//テクスチャID
	//MESH	m_Impact[IMPACT_NUM];
	//bool	m_Live;
	//VECTOR3 m_Pos;		//表示位置
	//float	m_Alpha[IMPACT_NUM];	//アルファ値
	//float	m_Scale[IMPACT_NUM];	//スケール
	//float	m_ScaleRate;
	//int		m_Time[IMPACT_NUM];
	//bool	m_dsp[IMPACT_NUM];		//表示フラグ

public:
	//void Init(void);	//初期化
	void Load(void);	//読み込み
	void Reset(void);	//リセット
	void UpDate(void);	//更新
	void Set(VECTOR3 vec);	//発生位置のセット
	void Draw(void);	//描画
	
};

//################################################
// End of File
//################################################
#endif _____L_PILLAR_H_____
