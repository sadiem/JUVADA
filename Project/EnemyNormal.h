//################################################
// <EnemyNormal.h>
//①プレイヤーが傍にいるとき、自分の向いている方向
// から、前方にいるとき、プレイヤーの方向へ突撃していく。
//②プレイヤーが遠ざかった時、ランダムな方向へ進んでいく
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
#ifndef _____ENEMY_NORMAL_H_____
#define _____ENEMY_NORMAL_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Enemy.h"
#include "ShaderMng.h"	//シェーダ
#include "Matrix.h"		//数学
#include "EffectMng.h"
#include "Sound.h"

//================================================
//定数定義
//================================================
//敵の攻撃種類
enum ENEMY_ATK_STATE
{
	ROT,	//回転
	BACK,	//後ろ下がり
	JUMP	//飛びあがり
};
//================================================
//クラス定義
//================================================
class ENEMY_NORMAL:public ENEMY
{
public:
	ENEMY_NORMAL();
	virtual ~ENEMY_NORMAL();

	void Init(void);		//初期化
	void Reset(void);		//リセット
	void SetData(void);		//データの初期値をセット
	void Load(void);		//読み込み
	void Release(void);		//解放
	void Create(void);		//作成
	void Deleate(void);		//削除
	void Draw(void);		//描画
	bool Update(VECTOR3 pos, float w, int a);		//更新
	void SetLive(bool);
	VECTOR3 m_vecFree;
private:
	SHADER_MNG *m_pShader;
	EFFECT_MNG *m_pEffectMng;
	SOUND	   *m_pSE;
	float m_RotAtc;				//攻撃時回転
	bool MotionAttack(void);	//攻撃モーション
	bool MotionDamage(void);	//ダメージモーション

	MESH	m_MeshDmg1;
	MESH	m_MeshNormal;
	MESH	m_Inside;
	MESH	m_MeshBomb;		//爆発用メッシュ
	GLuint	m_TexInside;
	
	VECTOR3 Addpos;
	int nCntAtk;
	int nCntDmg;
};

//################################################
// End of File
//################################################
#endif _____ENEMY_NORMAL_H_____

