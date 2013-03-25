//################################################
// <Field.h>
// 背景制作
//------------------------------------------------
// 2012/11/26 ~					SekiyamaRumi
// 2013/1/29	柵の描画を分離　Akihito Tanaka
//################################################
#ifndef _____FIELD_H_____
#define _____FIELD_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Common.h"
#include "Mesh.h"
#include "Matrix.h"
#include "ShaderMng.h"

//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
#define SKY_POS (VECTOR3(0.0f, 0.0f, 0.0f))
#define FENCE_NUM	(20)	//フェンス数
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
//================================================
class FIELD
{
public:
	static FIELD* Instance()
	{
		static FIELD Inst;
		return &Inst;
	};

private:
	FIELD();
	VECTOR3 m_skypos;		//スカイドーム座標
	SHADER_MNG *m_Shade;	//シェーダマネージャ
	GLuint  m_TexIDField;	//テクスチャ番号
	GLuint  m_TexIDFieldB;	//テクスチャ番号
	GLuint  m_TexIDFieldBack;	//テクスチャ番号
	GLuint  m_TexIDSky;		//テクスチャ番号
	GLuint  m_TexIDSaku;	//テクスチャ番号
	MESH    m_Mesh;			//メッシュデータ
	MESH    m_MeshfieldBack;	//メッシュデータ
	MESH    m_Meshsky;		//メッシュデータ
	MESH	m_MeshSaku;		//メッシュデータ
	GLuint  m_nShdID;		//シェーダID

public:

	~FIELD();
	VECTOR3 m_FencePos[FENCE_NUM];	//柵の位置
	float   m_FenceRot[FENCE_NUM];	//柵の回転

	void Init();			//初期化
	void Load();			//読み込み
	void Release();			//解放
	void Update();			//更新
	void Draw();			//描画
	void DrawFence();		//柵の描画

};
//################################################
// End of File
//################################################
#endif _____FIELD_H_____

