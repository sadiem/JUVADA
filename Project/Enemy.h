//################################################
// <Enemy.h>
// エネミーの基本クラス
//------------------------------------------------
// 2012/12/06 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMY_H_____
#define _____ENEMY_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Object.h"
#include "Mesh.h"
#include "Common.h"
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
enum ENEMY_STATE{
	DEAD = -1,	//生存してない
	MOVE,		//移動
	ATTACK,		//攻撃する
	DAMAGE,		//攻撃を受ける
	SPLIT,		//分割
	ACT1,		//アクション1
	ACT2,		//アクション2
	ACT3,		//アクション3

	STATE_NUM	//状態数
};
//敵の種類
enum ENEMY_TYPE{
	NORMAL,			//ノーマルな敵
	BOSS,			//ボス

	TYPE_NUM       //
};

//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//================================================
class ENEMY:public OBJECT
{
protected:
	MESH	m_MeshB;				//メッシュデータ
	int     m_DeadNum;				//死亡数
	int     m_AtkState;				//攻撃状態

	bool    m_AtkMotion;			//攻撃モーションフラグ
	bool    m_DmgMotion;			//ダメージモーションフラグ
	VECTOR3 m_vecFree;				//プレイヤーが近くにいないときの進む移動ベクトル
public:
	ENEMY();
	virtual ~ENEMY();
	bool    m_ColPlayer;			//プレイヤーとの衝突フラグ
	bool    m_ColRingIn;			//プレイヤーのリング内に含まれているかのフラグ
	bool    m_AtkHitPlayer;			//プレイヤーへの攻撃成功フラグ
	bool	m_JumpFlg;				//ジャンプフラグ

	int     m_AppearBoss;			//ボス専用出現数
	virtual void Init(void)		= 0;		//初期化
	virtual void Reset(void)	= 0;		//リセット
	virtual void SetData(void)	= 0;		//データの初期値をセット
	virtual void Load(void)		= 0;		//読み込み
	virtual void Release(void)	= 0;		//解放
	virtual void Create(void)	= 0;		//作成
	virtual void Deleate(void)	= 0;		//削除
	virtual void Draw(void)		= 0;		//描画
	virtual void SetLive(bool)		= 0;	//生存フラグセッタ
	virtual bool Update(VECTOR3 pos, float w, int a)	= 0;		//更新
	
};

//################################################
// End of File
//################################################
#endif _____ENEMY_H_____

