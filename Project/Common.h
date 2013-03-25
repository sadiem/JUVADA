//################################################
// <Main.cpp>
// 
//------------------------------------------------
//
//						SekiyamaRumi
//################################################
#ifndef _____COMMON_H_____
#define _____COMMON_H_____

//================================================
//インクルードヘッダ
//================================================
#include <windows.h>			//メインヘッダ
#include "Matrix.h"

#include <GL/glew.h>		//OpenGL 関連のヘッダ
#include <GL/wglew.h>		//OpenGL 関連のヘッダ

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
//================================================
//定数定義
//================================================
#define SCREEN_WIDTH		(800)		//スクリーンの幅
#define SCREEN_HEIGHT		(600)		//スクリーンの高さ

#define FOVY				45.0f							//視野角
#define NEAR_CLIP			1.0f							//ニアクリップを行う距離
#define FAR_CLIP			10000.0f						//ファークリップを行う距離

#define M_PI				(3.141592f)			//ＰＩ
#define M_PI_H				(M_PI / 2.0f)		//90度
#define RAD					(float)(M_PI/180.0)	//ラジアン変換用定数

//デバッグ用
#define DEBUG_ON			(1)		//デバッグ時に実行
#define DEBUG_OFF			(0)		//デバッグ時に未実行

#define FIELD_WIDTH         (110)	//フィールド幅

//================================================
//構造体定義
//================================================

//頂点フォーマット定義 2D
struct FVERTEX{
	// GL_T2F_V3F
	GLfloat		tu, tv;			// テクスチャ座標
	GLfloat		x, y, z;		// 頂点座標
};

//ベクトル型　２
struct VECTOR2D{
	float x, y;
};


//頂点カラ―
struct COLOR{
	float r, g, b, a;
};
//面
struct FACE{
	int				nMaterialNo;	//マテリアルナンバー
	unsigned short	usNum;		//頂点数
	unsigned short	usIdx[3];	//頂点インデックス
};

//影
struct SHADOWVOLUME{
	VECTOR3 vecEdge[32768];		//頂点	十分な量の頂点を確保しておく
	int		nEdgeNum;			//エッジ数
};

//ビルボード用
struct BILLBOARD
{
	VECTOR3	m_Pos;			//位置
	VECTOR3 m_vec;			//移動方向ベクトル
	bool	m_Live;			//生存
	int		m_Time;			//生存時間
	float   m_Alpha;		//雲のα値
	float   m_Angle;		//角度
	float   m_Speed;		//速度
	float	m_ScaleRate;	//拡大率
	float   m_Scale;		//拡大
	float	m_SpeedY;		//高さの速度
};
//２Dビルボード用
struct BILLBOARD2D
{
	VECTOR3	pos;		//位置
	VECTOR3 axis;		//回転軸
	VECTOR3 vec;		//移動方向ベクトル
	float   Angle;		//角度
	float	ScaleRate;	//拡大率
};
//板ポリ
struct POLYGON3D
{
	VECTOR3  ver[4];		//頂点
	VECTOR2D tex[4];		//テクスチャ
	COLOR  col;				//色情報
};
//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
void SetExecTime(DWORD time);		//実行時間セット


//################################################
// End of File
//################################################
#endif _____COMMON_H_____