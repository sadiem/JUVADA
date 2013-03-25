//################################################
//<Polygon.h>
// 板ポリゴンの出力
//------------------------------------------------
//2012/07/12 ~
//						SekiyamaRumi
//################################################
#ifndef ______POLYGON_H_____
#define ______POLYGON_H_____

//================================================
//インクルード
//================================================
#include <windows.h>		//Windows
#include <tchar.h>			//汎用テキスト マッピング

#include "Include.h"		//インクルード
#include "Common.h"			//共通

//================================================
//構造体
//================================================

//================================================
//クラス定義
//================================================
void PlySetCol(POLYGON3D *pol, COLOR col);		//カラー設定
void PlySetTex(POLYGON3D *pol);					//テクスチャ１枚＝１ポリゴン　座標をセット
void PlySetTex(POLYGON3D *pol, float x, float y, float width, float height, float DivisionNum);		//テクスチャ１枚＝ 自由座標をセット
void PlySetVer(POLYGON3D *pol, float x, float y, float width, float height);				//頂点のセット
void PlySetScl(POLYGON3D *pol, float scl);	//拡縮

void PlyDrawPoliBillBoard(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID);	//ビルボード描画
void PlyDrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID);			//ポリゴン描画

#endif ______POLYGON_H_____
