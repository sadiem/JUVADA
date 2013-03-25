//################################################
// <Select.h>
// セレクトメニューを作成
//------------------------------------------------
// 2013/01/18 ~
//						SekiyamaRumi
//################################################
#ifndef _____SELECT_H_____
#define _____SELECT_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Include.h"	//インクルードヘッダ
#include "MeshMng.h"	//メッシュマネージャ
#include "Common.h"		//共通
#include "ShaderMng.h"		//シェーダマネージャ
#include "Camera.h"			//カメラマネージャ
#include "Input.h"
#include "Sound.h"
//================================================
//定数定義
//================================================
#define SLECT_BUTTOM_NUM	(4)		//ボタン数
#define SLECT_DECO_NUM		(5)		//デコレーション
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//================================================
class SELECT
{
public:
	SELECT();
	~SELECT();

	void Init(void);		//初期化
	void Reset(void);		//リセット
	void Release(void);		//リリース
	bool Update(void);		//更新
	void Draw(void);		//描画
	int GetSelect(void);//キーセレクト
private:
	POLYGON3D	m_PFade;	//フェード用ポリゴン
	POLYGON3D	m_PBg;		//BG用ポリゴン
	POLYGON3D	m_PButtom[SLECT_BUTTOM_NUM];	//ボタン用ポリゴン
	POLYGON3D	m_PStencil;	//ステンシル用ポリゴン
	POLYGON3D	m_PEndselect;		//終了選択画面
	POLYGON3D	m_PButtumEnd[2];	//終了画面ボタン

	VECTOR2D	m_CopyTexButtom[SLECT_BUTTOM_NUM][4];	//ボタンテクスチャ座標のコピー

	CAMERA		*m_pCmr;		//カメラマネージャ
	SHADER_MNG  *m_pShadeMng;	//シェーダマネージャ
	INPUT_MNG	*m_pInput;
	SOUND		*m_pSE;

	int			m_nState;	//状態遷移
	int			m_nInState;	//状態遷移(第二) 
	int			m_nCnt;		//フレームカウンタ
	int			m_nSelect;	//場面選択
	int			m_nKeyEnd;	//終了画面内キー


	bool bflg;
	bool bflgKey1;
	bool bflgKey2;
	int nCnt;

	bool		m_bButtunChange[4];	//ボタン画像変換フラグ

	MESH m_MeshT;			//メッシュタイトル
	MESH m_MeshDeco;		//デコレーション

	GLuint  m_TexID;		//テクスチャID	ポリ
	GLuint  m_TexIDM;		//テクスチャID	モデル
	GLuint  m_TexIDD;		//テクスチャID	モデル デコレーション
	GLuint  m_TexIDT;		//テクスチャID	タイトル
	GLuint	m_TexIDF;		//テクスチャID	フェード
	GLuint	m_TexIDE;		//テクスチャID	エンドセレクト
	
	VECTOR3 m_Titlpos;		//タイトル位置
	float   m_TAngZ;		//タイトル回転
	float   m_TAngY;		//タイトル回転
	float   m_TScl;			//タイトル拡大
	float   m_EScl;			//終了選択画面拡大率
	
	//デコレーション
	VECTOR3 m_Ditlpos[SLECT_DECO_NUM];		//タイトル位置
	float   m_DAng[SLECT_DECO_NUM];			//タイトル回転 傾き
	float   m_DAngM[SLECT_DECO_NUM];		//タイトル回転 自身の回転
	float   m_DScl[SLECT_DECO_NUM];			//タイトル拡大
	
	//ステンシル
	VECTOR3 m_vSSlide;							//スライド

	VECTOR3	m_vBtmpos[SLECT_BUTTOM_NUM];		//ボタン位置
	VECTOR3 m_vBtmposCopy[SLECT_BUTTOM_NUM];	//コピー

	bool FadeIn(POLYGON3D *pol);				//フェードin
	bool FadeOut(POLYGON3D *pol);				//フェードout
	void DrawModel();							//モデル描画
	void DrawTitle();							//モデル描画→タイトル
	void DrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, float scl, int m_TexID, bool flg);	//ポリゴン描画
	void SetPoli(void);							//頂点セット
	void DrawStencil(void);						//ステンシル描画
	bool TexMoveAppear(void);					//ボタンテクスチャの移動
	bool TexMovePutaway(void);					//ボタンをしまう	
	void TexChange(int nID, int flg);			//選択中ボタンのテクスチャ変更
	void TexMovePutawayEnd(int nMove);				//終了選択ボタンのテクスチャ切り替え
};
//################################################
// End of File
//################################################
#endif _____SELECT_H_____
