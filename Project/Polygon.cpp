//################################################
//<Polygon.cpp>
// 板ポリゴンの出力
//------------------------------------------------
//2012/07/12 ~
//						SekiyamaRumi
//################################################

//================================================
//インクルード
//================================================
#include "Polygon.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++
// カラー指定
//-------------------------------------------------
// カラー値をセット
//--in---------------------------------------------
// 格納データ先
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetCol(POLYGON3D *pol, COLOR col)
{
	pol->col.r = col.r;
	pol->col.g = col.g;
	pol->col.b = col.b;
	pol->col.a = col.a;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 座標設定
//-------------------------------------------------
// テクスチャの使い方は全面１枚のみの場合
//--in---------------------------------------------
// 座標位置
// 横幅
// 縦幅
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetTex(POLYGON3D *pol)
{
	pol->tex[0].x = 0.0f;
	pol->tex[0].y = 1.0f;

	pol->tex[1].x = 0.0f;
	pol->tex[1].y = 0.0f;

	pol->tex[2].x = 1.0f;
	pol->tex[2].y = 0.0f;

	pol->tex[3].x = 1.0f;
	pol->tex[3].y = 1.0f;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// 座標設定
//-------------------------------------------------
// テクスチャの扱いが分割されているときの設定
//--in---------------------------------------------
// POLYGON3D　変更
// X成分　(fx < fy)
// Y成分　(fv < fh)
// 分割数
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetTex(POLYGON3D *pol, float fx, float fy, float fv, float fh, float DivisionNum)
{
	pol->tex[0].x = fx / DivisionNum;
	pol->tex[0].y = 1.0f - (fh / DivisionNum);

	pol->tex[1].x = fx / DivisionNum;
	pol->tex[1].y = 1.0f - (fv / DivisionNum);

	pol->tex[2].x = fy / DivisionNum;
	pol->tex[2].y = 1.0f - (fv / DivisionNum);

	pol->tex[3].x = fy / DivisionNum;
	pol->tex[3].y = 1.0f - (fh / DivisionNum);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// 座標設定
//-------------------------------------------------
// テクスチャは未設定
//--in---------------------------------------------
// POLYGON3D　変更
// 初期位置　X
//			 Y
// 横幅
// 縦幅
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetVer(POLYGON3D *pol, float x, float y, float width, float height)
{
	pol->ver[0].x  = x;
	pol->ver[0].y  = y + height;
	pol->ver[0].z  = 0.0f;

	pol->ver[1].x  = x;
	pol->ver[1].y  = y;
	pol->ver[1].z  = 0.0f;

	pol->ver[2].x  = x + width;
	pol->ver[2].y  = y;
	pol->ver[2].z  = 0.0f;

	pol->ver[3].x  = x + width;
	pol->ver[3].y  = y + height;
	pol->ver[3].z  = 0.0f;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン拡縮
//-------------------------------------------------
// 拡縮
//--in---------------------------------------------
// POLYGON3D　変更
// 拡大率
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetScl(POLYGON3D *pol, float scl)
{
	pol->ver[0] *= scl;
	pol->ver[1] *= scl;
	pol->ver[2] *= scl;
	pol->ver[3] *= scl;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン描画
//--in--------------------------------------------
//POLYGON3D　参照
//回転角
//回転軸
//位置
//テクスチャID
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PlyDrawPoliBillBoard(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos, int m_TexID)
{
	GLdouble	matView[16];

	//初期処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
	glDepthMask(GL_FALSE);		//デプスバッファへの書き込み禁止

	//カラー指定
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//ポリゴン描画
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(m_TexID > 0)
	{
		glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}
	//座標変換
	glPushMatrix();

	//ビルボード変換
	glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
	matView[0] = matView[5] = matView[10] = 1.0f;
	matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
	glLoadMatrixd(&matView[0]);
	
	//マトリックス変換
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	//ポリゴン描画
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//後処理
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Zバッファ無効化
	glDepthMask(GL_TRUE);		//デプスバッファへの書き込み許可
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン描画
//--in--------------------------------------------
//POLYGON3D　参照
//回転角
//回転軸
//位置
//テクスチャID
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PlyDrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos,  int m_TexID)
{
	//初期処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
	glDepthMask(GL_FALSE);		//デプスバッファへの書き込み禁止

	//カラー指定
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//ポリゴン描画
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	//座標変換
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	//ポリゴン描画
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//後処理
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Zバッファ無効化
	glDepthMask(GL_TRUE);		//デプスバッファへの書き込み許可
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}