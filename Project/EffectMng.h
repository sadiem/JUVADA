//################################################
// <EffectMng.h>
//
//------------------------------------------------
// 2013/1/7
//						Akihito Tanaka
//################################################
#ifndef _____EFFECT_MNG_H_____
#define _____EFFECT_MNG_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "Smoke.h"			//シェーダ
#include "Impact.h"
#include "Emitter.h"
#include "Matrix.h"
#include "Object.h"
#include "TexMng.h"
#include "LineParticle.h"
#include "MeshMng.h"
#include "Rock.h"

//================================================
//定数定義
//================================================
enum EFFECT_TYPE
{
	E_SMOKE_L,		//煙(大)
	E_SMOKE_S,		//煙(小)
	E_IMPACT,			//衝撃波
	E_PARTICLE_SPIN,	//スピンパーティクル
	E_PARTICLE_SPLASH,	//噴射パーティクル
	E_PARTICLE_BOMB,	//噴射パーティクル
	E_PARTICLE_LINE,	//ラインパーティクル
	E_ROCK_LINE,		//岩の軌跡
	E_ROCK_CIRCLE,		//円形に岩を配置
};

#define MAX_EMITTER	(30)	//パーティクル発生位置最大数
#define MAX_LINE	(20)	//ラインパーティクル発生位置最大数
//================================================
//クラス定義
//================================================
class EFFECT_MNG
{
public:
	static EFFECT_MNG* Instance()
	{
		static EFFECT_MNG Inst;
		return &Inst;
	};
private:
	EFFECT_MNG();
	SMOKE *pSmoke;
	IMPACT	*pImpact;
	ROCK	*pRock;
	EMITTER	m_Emitter[MAX_EMITTER];
	LINE_PARTICLE pLine[MAX_LINE];
	GLuint	m_TexSpin;
	GLuint	m_TexBomb;
	MESH	m_MeshLine;


public:
	~EFFECT_MNG();

	void Load(void);	//エフェクト読み込み
	void Set(int type, OBJECT *obj); //描画位置指定
	void Remove(int type);
	void UpDate();	//アップデート
	void Draw(void);	//描画
};

//################################################
// End of File
//################################################
#endif _____EFFECT_MNG_H_____
