//################################################
// <Opening.h>
// オープニング管理マネージャ
//------------------------------------------------
// 2013/01/14 ~
//						SekiyamaRumi
//################################################

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "Common.h"			//共通ヘッダ
#include "Input.h"			//キーヘッダ
#include "MeshMng.h"		//メッシュマネージャ
#include "ShaderMng.h"		//シェーダマネージャ
#include "Sound.h"

//================================================
//クラス定義
//================================================
class OP
{
public:
	OP();
	~OP();

	void Init(void);		//初期化
	void Reset(void);		//リセット
	bool Update(void);		//更新
	void Draw(void);		//描画

private:
	SHADER_MNG *m_pShadeMng;	//シェーダマネージャ
	INPUT_MNG  *m_pInput;			//キーポインタ
	SOUND	   *m_pSE;
	MESH m_MeshR;			//メッシュリング
	MESH m_MeshT;			//メッシュタイトル
	MESH m_MeshD;			//メッシュデコレーション

	bool m_bFlgPushStart;	//スタートボタン待ち
	int m_nState;			//状態
	int m_nInState;			//状態(switch文中)
	int m_nRingState;		//リング状態
	int m_nCnt;				//カウンタ

	POLYGON3D m_PFade;		//フェード用ポリゴン
	POLYGON3D m_PLogo;		//ロゴ用ポリゴン
	POLYGON3D m_PBg;		//BG用ポリゴン
	POLYGON3D m_PPushEnter;	//PUSHENTER用ポリゴン

	bool	m_RbDraw;		//描画フラグ
	VECTOR3 m_Ringpos;		//リング位置
	float	m_RAng;			//リング回転
	float   m_RScl;			//リング拡大率
	float   m_RJump;		//ジャンプ
	VECTOR3 m_Titlpos;		//タイトル位置
	float   m_TAng;			//タイトル回転
	float   m_TScl;			//タイトル拡大
	float   m_DAng;			//デコレーションの回転

	GLuint  m_TexID;		//テクスチャID	ポリ
	GLuint  m_TexIDM;		//テクスチャID	モデル
	GLuint  m_TexIDT;		//テクスチャID　タイトル
	GLuint  m_TexIDB;		//テクスチャID　BG

	bool FadeIn(POLYGON3D *pol);				//フェードin
	bool FadeOut(POLYGON3D *pol);				//フェードout
	void DrawModel();	//モデル描画
	void DrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID, bool flg);	//ポリゴン描画
	void SetPoli(void);		//頂点セット
};

//################################################
// End of File
//################################################
