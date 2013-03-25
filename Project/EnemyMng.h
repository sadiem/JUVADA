//################################################
// <EnemyMng.h>
//
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMYMNG_H_____
#define _____ENEMYMNG_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Object.h"
#include "Enemy.h"				//敵の基本クラス
#include "EnemyCommon.h"		//エネミー共通ヘッダ
#include "Player.h"				//プレイヤー
#include "Smoke.h"				//煙
#include "EffectMng.h"
#include "Score.h"
#include "Sound.h"

//================================================
//ライブラリ定義
//================================================

class PLAYER;
//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//================================================
class ENEMYMNG
{
public:
	static ENEMYMNG *Instance()
	{
		static ENEMYMNG Inst;
		return &Inst;
	};

private:
	ENEMYMNG();
	PLAYER *m_pPlayer;		//プレイヤーポインタ
	EFFECT_MNG	*m_pEffectMng;
public:
	~ENEMYMNG();
	ENEMY  *m_pEnemy[ENEMY_NOMAL_NUM];		//ザコキャラ等
	ENEMY  *m_pEnemyBoss;	//ボス
	SCORE  *m_pScore;
	SOUND  *m_pSE;
	int    m_nGameEnd;						//ゲームエンドフラグ

	int m_DeadCnt;						//倒した数
	int m_BossCnt;						//倒したボスの数

	void Init(PLAYER *pPlayer);			//初期化
	void Reset(void);		//リセット
	void Load(void);		//読み込み
	void Release(void);		//解放
	void Create(void);		//作成
	void Deleate(void);		//削除
	void Draw(void);		//描画
	void Update(void);		//更新
};

//################################################
// End of File
//################################################
#endif _____ENEMYMNG_H_____

