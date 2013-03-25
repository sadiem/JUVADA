//################################################
// <Player.cpp>
// プレイヤー動作
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
// 2013/1/22			環境マップ追加	Akihito Tanaka
//################################################
#ifndef _____PLAYER_H______
#define _____PLAYER_H______

//================================================
//インクルードヘッダ
//================================================
#include "Object.h"		//オブジェクトヘッダ
#include "Input.h"		//ジョイパッドヘッダ
#include "Shadow.h"		//影
#include "CubeMap.h"	//環境マップ
#include "EnemyMng.h"	//敵マネージャ
#include "Camera.h"		//カメラ

class CUBEMAP;
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define TEX_NUM (2)		//テクスチャ数

//================================================
//構造体定義
//================================================
enum PLAYER_STATE{
	P_WAIT   = -1,		//待ち
	P_NORMAL = 0,		//通常
	P_UP,				//持ち上がり
	P_DOWN,				//持ち下がり
	P_ENEMY_IN_COLLECT,	//敵捕獲状態
	P_ENEMY_COLLECT,	//通常サイズへ戻す　敵が範囲内にいるとき
	P_NORMAL_COLLECT,	//通常サイズへ戻す	敵が範囲外であるとき
	P_ATC_SCALE,		//拡縮アクション
	P_ATC_TRANSFORM,	//変形アクション
	P_ATC_DEAD,			//死亡アクション
	P_NORMAL_FLAT,		
	P_DAMEGE_ACT,		//ダメージアクション
};
//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//--アクション１　(キャラの持ち上がり動作)
//--アクション２　(キャラの下がり動作)
//================================================
class PLAYER:public OBJECT
{
public:
	static PLAYER* Instance()
	{
		static PLAYER Inst;
		return &Inst;
	};
private:
	PLAYER();
	ENEMYMNG	*m_EnemyMng;		//敵マネージャ
	CAMERA		*m_pCamera;
	MATRIX      m_RotTrans;			//移動時のキャラの回転
	MATRIX      m_ActMove;			//アクション移動マトリックス
	MATRIX      m_Act1;				//アクション１のマトリックス
	VECTOR3		m_Accel;			//加速度

	bool		m_bDamage;			//体力コピー
	bool		m_bAtkFlg;			//攻撃中かのフラグ

	//テクスチャ
	GLuint		m_TexRed;			//赤
	GLuint		m_TexNormal;		//通常
	GLuint		m_CubeTexID;
	int			m_TexFrashDirect;	//色の変わる方向
	int			m_nTexFrashCnt;		//フレームカウンタ

	int			m_WaitTime;			//待機カウント
	//拡縮アクション用
	int			m_ScaleWaitTime;	//開きっぱなしである時間

	//モーフィング用
	MESH		m_MeshA;			
	MESH		m_MeshB;
	MESH		m_MeshC;
	int			m_nCntFrame;	//フレームカウント
	int			m_nDirect;		//アニメーション方向
	bool		m_nStartTrans;	//モーフィング開始フラグ
	//沈みアクション用
	int			m_nDct_Sink;
	bool		m_bSflg;
	float		m_fSink;			//沈む量

	//平たくなるアクション
	int			m_nDct_Flat;
	bool		m_bFflg;

	SOUND		*m_pSE;
	
	//死亡アクション
	int			m_nDeadActFrame;
	int			m_nFrameCnt;
	int			m_nFrashTimeCnt;
	int			m_nColDIrect;			//色の変化の方向
	float		m_x;
	COLOR		m_col;				//元の色を保存
	CUBEMAP		*m_pCube;			//キューブマップ			
public:
	VECTOR3     m_RotAxis;			//回転軸
	int			m_ScaleFlg;			//拡縮フラグ
	int			m_InEnemyFlg;		//敵が範囲内にいるかどうかのフラグ
	INPUT_MNG		*m_pInput;
	int			m_DeadNum;			//死亡回数
	//プレイヤーリトライフラグ
	bool		m_bRetry;

public:
	virtual ~PLAYER();
	
	void Init(void);			//初期化
	void Reset(void);			//リセット
	void Load(void);			//読み込み
	void Release(void);			//解放
	void Update(VECTOR3 vecx, VECTOR3 vecy);	//更新
	void Draw(void);			//描画
	void Act(int nState);		//アクション

	//追加
	void DrawCubeMap();
	void DrawCube();

private:
	bool ScaleActCollect(void);	//拡縮元のサイズへ
	bool ScaleAttack(void);		//拡縮攻撃
	void ScaleAct(void);		//拡縮
	void RotateAct(int flg);	//輪の持ち上がり
	bool TransformAct(void);	//変形
	bool CheckVec(VECTOR3 *vec);	//移動方向をチェック
	void CheckField(VECTOR3 *vec);	//フィールド内にいるかどうか
	void DeadAct(void);			//死亡アクション
	void TexFrash(void);		//テクスチャの切り替えでフラッシュ表現
};

//################################################
// End of File
//################################################
#endif _____PLAYER_H______

