//################################################
//<NumView.h>
// 数値描画
//------------------------------------------------
//2012/06/11 ~
//2013/01/31  修正
//						SekiyamaRumi
//################################################
#ifndef _____NUM_VIEW_H______
#define _____NUM_VIEW_H______
//================================================
//インクルード
//================================================
#include <windows.h>		//Windows プログラムにはこれを付ける
#include <tchar.h>			//汎用テキスト マッピング

#include "Include.h"		//インクルード
#include "Number.h"			//数字ヘッダ

//================================================
//定数定義
//================================================

#define DIGIT	(5)
#define DIGIT_TIME	(8)

//================================================
//クラス定義
//================================================
class NUM_VIEW
{
private:
	NUMBER		m_Num[DIGIT];	//スコア表示用
	NUMBER		m_NumT[DIGIT_TIME];	//スコア表示用


public:
	NUM_VIEW();				//コンストラクタ
	virtual ~NUM_VIEW();			//デストラクタ

protected:
	float		m_x;		//初期位置_x
	float		m_y;		//初期位置_y
	float		m_num_w;	//数値テクスチャの横幅
	float		m_num_h;	//数値テクスチャの縦幅

	void Load(char *pszFName);		//ロード
	void Draw(GLuint TexID);		//描画
	void DrawTime(GLuint TexID);	//描画　タイム
	void Updata(int nNum1);			//更新
	void SetTex(int nNum);			//テクスチャセット
	void SetTex(DWORD s, DWORD m, DWORD mm);	//時間用
};

#endif _____NUM_VIEW_H______
