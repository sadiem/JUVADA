//################################################
// <Rock.h>
//
//------------------------------------------------
// 2013/01/22
//						Akihito Tanaka
//################################################
#ifndef _____ROCK_H_____
#define _____ROCK_H_____

//================================================
//インクルードヘッダ
//================================================
#include "include.h"
#include "Common.h"
#include "MeshMng.h"
#include "Effect.h"
#include "Object.h"
#include "ShaderMng.h"	//シェーダマネージャ
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define ROCK_NUM	(20)

enum ROCK_TYPE{
	LINE,
	CIRCLE,
	MAX_TYPE,
};
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
class ROCK:public EFFECT
{
public:
	static ROCK* Instance(void)
	{
		static ROCK inst;
		return &inst;
	};
	~ROCK();
private:
	ROCK();
	void Gen(int type);
	
	int		m_Type;			//岩のタイプ
	GLuint	m_TexID;		//テクスチャID
	GLuint	m_TexBumpID;	//バンプテクスチャID
	MESH	m_Mesh;
	OBJECT *m_Obj;
	int		m_interval;
	bool	m_Set;		//新たにセットするか
	bool	m_LR;		//左右反転フラグ
	float	m_Rad[ROCK_NUM];
	float	m_AngX[ROCK_NUM];	//X軸回転（倒れ）
	float	m_MaxScale[ROCK_NUM];
	SHADER_MNG *m_pShaderMng;

public:
	BILLBOARD m_Rock[ROCK_NUM];

	void Init(void);	//初期化
	void Load(void);	//読み込み
	void Reset(void);	//リセット
	void UpDate(void);	//更新
	void Set(OBJECT *obj, int type);	//岩のセット
	void Remove(void);	//岩のセット
	void Draw(void);	//描画
	
};

//################################################
// End of File
//################################################
#endif _____ROCK_H_____
