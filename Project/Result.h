//################################################
// <Result.h>
//
//------------------------------------------------
//2013/01/31 
//						SekiyamaRumi
//################################################
#ifndef ______RESULT_H______
#define ______RESULT_H______

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"	//インクルード
#include "Common.h"		//共通
#include "Polygon.h"	//ポリゴン描画
#include "Fade.h"		//フェード描画
#include "Score.h"		//スコアヘッダ
#include "MeshMng.h"	//メッシュマネージャ
#include "Camera.h"		//カメラ
#include "Score.h"		//スコア
#include "DeadNum.h"	//死亡数
#include "Player.h"
#include "Time.h"		//時間
#include "Input.h"

//================================================
//定数定義
//================================================
enum {
	RESULT_BG,			//背景
	RESULT_BG_FRAME1,	//デコレーション
	RESULT_BG_FRAME2,	//デコレーション
	RESULT_BG_STENCIL,	//ステンシル
	RESULT_ITEM_NAME1,	//出力データ項目 タイム
	RESULT_ITEM_NAME2,	//出力データ項目 死亡回数
	RESULT_ITEM_NAME3,	//出力データ項目 スコア
	RESULT_VAL,			//評価
	RESULT_MATERIAL_NUM	//素材数
};
#define RESULT_DECO_NUM		(5)		//デコレーション
//================================================
//プロトタイプ宣言
//================================================
class RESULT_MNG
{
public:
	static RESULT_MNG *Instance()
	{
		static RESULT_MNG Inst;
		return &Inst;
	}

private:
	RESULT_MNG(){}
	CAMERA *m_pCmr;
	SCORE  *m_pScr;	
	DEAD_NUM *m_pDeadNum;
	PLAYER *m_pPlayer;
	TIME_MNG *m_pTime;
	INPUT_MNG	*m_Input;
	
	POLYGON3D   m_stencil;					//ステンシル
	POLYGON3D   m_pol[RESULT_MATERIAL_NUM];	//ポリゴン
	BILLBOARD2D	m_bil[RESULT_MATERIAL_NUM];	//ビルボード2D用構造体
	GLuint		m_TexID;					//テクスチャID
	GLuint		m_TexIDD;					//テクスチャID　デコ
	GLuint		m_TexIDS;					//テクスチャID　スコア
	GLuint		m_TexIDV;					//テクスチャID　評価
	GLuint		m_TexIDT;					//テクスチャID　タイム
	int			m_nState;					//状態
	int			m_nCnt;						//フレームカウンタ
	int			m_nTime;					//時間受け取り
	int			m_nEvaluation;				//評価受け取
	int			m_nScr;						//スコア受け取
	bool		m_bScrFlg;					//スコア描画フラグ
	bool		m_bTimFlg;					//タイム描画フラグ
	bool        m_bDeadFlg;					//死亡数描画フラグ
	FADE		m_fade;						//フェード
	MESH		m_MeshDeco;					//背景で使用するモデル
	
	//カウンタとフラグ
	int			Cnt;
	bool		flg;

	int			m_Val;						//評価
	//デコレーション
	VECTOR3 m_Ditlpos[RESULT_DECO_NUM];		//デコ位置
	float   m_DAng[RESULT_DECO_NUM];		//デコ回転 傾き
	float   m_DAngM[RESULT_DECO_NUM];		//デコ回転 自身の回転
	float   m_DScl[RESULT_DECO_NUM];		//デコ拡大

	//ステンシル
	VECTOR3 m_vSSlide;						//スライド

	void Load(void);			//読み込み
	void DrawModel(void);		//モデル描画
	void DrawStencil(void);		//ステンシル描画
	bool ItemMoveAppear(void);	//出力項目名出現
	bool ItemMoveClose(void);	//出力項目名しまう
public:
	virtual ~RESULT_MNG(){}
	void Init(void);	//初期化
	void Reset(void);	//リセット
	void Release(void);	//解放
	bool Update(void);	//更新
	void Draw(void);	//描画
	void Draw2D(void);	//描画2D 
};


//################################################
// End of File
//################################################
#endif ______RESULT_H______
