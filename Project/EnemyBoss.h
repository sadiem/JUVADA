//################################################
// <EnemyBossl.h>
//------------------------------------------------
// 2013/1/7
//					akihito tanaka
//################################################
#ifndef _____ENEMY_BOSS_H_____
#define _____ENEMY_BOSS_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Enemy.h"
#include "EffectMng.h"
#include "ShaderMng.h"
#include "TexMng.h"		//テクスチャマネージャ
#include "Sound.h"
#include "Camera.h"
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
enum BOSS_STATE{
	BOSS_START,			//ボス出現開始
	FALL,				//落下
	APPEAR,				//登場
	WAIT,				//待機
	PRE_JUMP_ATTACK,	//ジャンプ攻撃準備
	JUMP_ATTACK,		//ジャンプ攻撃
	PRE_SPIN_ATTACK,	//スピン攻撃準備
	SPIN_ATTACK,		//スピン攻撃
	PRE_BEAM_ATTACK,	//ビーム攻撃準備
	BEAM_ATTACK,		//ビーム攻撃
	DAMAGE_HIT,			//ダメージモーション
	DEAD_BOSS,			//死亡
	BOSS_STATE_NUM,		//状態数

};

#define BOSS_PARTS	(8)			//ボスのパーツ数
#define APPEAR_WAIT	(250)		//落下後の静止時間
#define TRANSCOUNT	(30)		//変形時間

//================================================
//クラス定義
//================================================
class ENEMY_BOSS:public ENEMY
{
public:
	ENEMY_BOSS();
	virtual ~ENEMY_BOSS();

	void Init(void);					//初期化
	void Reset(void);					//リセット
	void Load(void);					//読み込み
	void Release(void);					//解放
	void Create(void);					//作成
	void Deleate(void);					//削除
	void SetData(void);					//データの初期値をセット
	bool Update(VECTOR3 pos, float w, int a);		//更新
	void Draw(void);					//描画
	void SetLive(bool);					//生存フラグセット

private:
	MESH m_MeshArmor[BOSS_PARTS];		//外メッシュ
	MESH m_MeshEye;						//内側メッシュ
	GLuint	m_TexID;					//外テクスチャID
	GLuint	m_TexBumpID;				//バンプテクスチャID
	GLuint	m_TexEyeID;					//目玉のテクスチャID

	EFFECT_MNG	*m_EffectMng;			//エフェクトマネージャ
	SHADER_MNG	*m_ShaderMng;			//シェーダマネージャ
	SOUND		*m_pSE;					//サウンドマネージャ
	CAMERA		*m_pCamera;				//カメラ

	VECTOR3	m_PartsOffset[BOSS_PARTS];	//パーツオフセット
	VECTOR3	m_PartsMove[BOSS_PARTS];	//パーツ移動スピード
	int		m_Count;					//汎用カウンタ
	float   m_SpinRad;					//スピン回転角
	float   m_SpinAdd;					//スピン回転角加算値
	VECTOR3 m_vAttack;					//攻撃方向
	VECTOR3 m_AtkMove;					//攻撃移動距離
	float	m_EyeScale;					//目玉の大きさ
	
	void EyeMove(VECTOR3 pos);			//目玉の移動
	bool MotionDamage(void);			//ダメージモーション

	bool	m_First;					//プレス時の初回フラグ
};

//################################################
// End of File
//################################################
#endif _____ENEMY_BOSS_H_____

