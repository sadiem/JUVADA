//################################################
//<Number.cpp>
// 数字一文字を出力する
//------------------------------------------------
//マインスイーパ作成
//2012/06/11 ~
//						SekiyamaRumi
//################################################
#ifndef _____NUMBER_H______
#define _____NUMBER_H______

//================================================
//インクルード
//================================================
#include <windows.h>		//Windows プログラムにはこれを付ける
#include <tchar.h>			//汎用テキスト マッピング

#include "Include.h"		//インクルード

//================================================
//構造体定義
//================================================
struct FVERTEX_SCORE{
	GLfloat	tu, tv;			//テクスチャ座標
	GLfloat x, y, z;		//頂点座標
};

//================================================
//クラス定義
//================================================
class NUMBER
{
private:
	FVERTEX_SCORE		m_Ver[4];	//頂点情報
	GLfloat				m_fPosX;	//位置	X
	GLfloat				m_fPosY;	//位置	Y
	int					m_Number;	//出力する数字

public:
	NUMBER();						//コンストラクタ
	virtual ~NUMBER();						//デストラクタ

	void Disp(GLuint fID);			//描画
	void SetNum(int num);			//表示する数字
	void SetPos(float x, float y,int nD, float m_num_w, float m_num_h);		//座標をセットする
	
};

#endif _____NUMBER_H______
