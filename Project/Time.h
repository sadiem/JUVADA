//################################################
// <Time.h>
//
//------------------------------------------------
// 2013/01/31 ~
//						SekiyamaRumi
//################################################
#ifndef _____TIME_H_____
#define _____TIME_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include <time.h>
#include "NumView.h"
//================================================
//定数定義
//================================================

//================================================
//クラス宣言
//================================================
class TIME_MNG :public NUM_VIEW
{
public:
	static TIME_MNG* Instance()
	{
		static TIME_MNG Inst;
		return &Inst;
	}
	~TIME_MNG();
private:
	TIME_MNG();
	GLuint  m_TexID;
	DWORD   m_NowTime;		//現在時間
	DWORD   m_StartTime;	//開始時間
	DWORD   m_ElapsedTime;	//経過時間

	DWORD   m_mm;			//ミリ秒
	DWORD   m_m;			//秒
	DWORD   m_s;			//分
public:
	void Load (void);
	void Release(void);
	void Reset(void);	//リセット
	void Start(void);	//スタート
	void Update(void);	//更新
	void SetPos(float X, float Y, float W, float H);		//初期指定
	void Draw (GLuint texId);	//描画
	void Draw ();	//描画
};

//################################################
// End of File
//################################################
#endif _____TIME_H_____
