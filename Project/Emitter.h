//################################################
// <Emitter.h>
//
//------------------------------------------------
// 2012/01/15 ~
//						Akihito Tanaka
//################################################
#ifndef _____EMITTER_H_____
#define _____EMITTER_H_____

//================================================
//インクルードヘッダ
//================================================
#include "include.h"
#include "Common.h"
#include "Particle.h"
#include "Object.h"
#include "ShaderMng.h"
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define MAX_PARTICLE (500)
#define SPLASH_GEN_NUM (100)
#define SPIN_GEN_NUM (3)
#define BOMB_GEN_NUM (10)

//エミッタ生存時間
#define EM_SPIN_TIME	(200)
#define EM_SPLSH_TIME	(60)
#define EM_BOMB_TIME	(100)
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
class EMITTER
{
public:
	EMITTER();
	~EMITTER();
private:
	GLuint		m_TexID;									//テクスチャID
	PARTICLE	m_Particle[MAX_PARTICLE];					//パーティクル
	PARTICLE	*SearchBlankParticle(void);					//空きの検索
	void		DeleteParticle(PARTICLE *particle);			//消去
	void		CreatePrticle(void);						//発生位置のセット
	int			m_ParticleCount;							//パーティクルの数
	int			m_LifeTime;									//エミッターの生存時間
	VECTOR3		m_Pos;										//エミッターの座標
	int			m_Type;										//パーティクルタイプ
	OBJECT		*m_obj;										//追従するオブジェクト
	float		m_PointSize;								//ポイントスプライトのサイズ
	VECTOR3		m_Color;									//パーティクルの色

	SHADER_MNG	*m_pShaderMng;								//シェーダマネージャ	

public:
	bool		m_Enable;									//エミッタが有効かのフラグ
	void		Init(void);	//初期化
	void		UpDate(void);	//更新
	void		Draw(void);	//描画
	void		DrawShader(void);
	void		Create(int type, GLuint texID, OBJECT *obj);
};

//################################################
// End of File
//################################################
#endif _____EMITTER_H_____
