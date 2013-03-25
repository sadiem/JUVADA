//################################################
// <Time.cpp>
//
//------------------------------------------------
// 2013/01/31 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Time.h"
#include "TexMng.h"
//================================================
//定数定義
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
TIME_MNG::TIME_MNG()
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\2D\\time.png","TIME");
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
TIME_MNG::~TIME_MNG()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void TIME_MNG::Reset(void)
{
	m_NowTime     = 0;	//現在時間
	m_StartTime   = 0;	//開始時間
	m_ElapsedTime = 0;	//経過時間

	m_mm = 0;
	m_m = 0;
	m_s =0;

	SetPos(600, 0, 20, 40);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//スタート
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void TIME_MNG::Start(void)
{
	m_StartTime = timeGetTime();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void TIME_MNG::Update(void)
{
	DWORD tmp = 0;
	m_NowTime = timeGetTime();

	tmp = m_NowTime - m_StartTime;

	//要素を抜き出す(1ms単位)
	//ミリ秒
	m_mm = (tmp - ((tmp / 1000) * 1000)) / 10;
	//秒
	m_m = (tmp / 1000) % 60 ;
	//分
	m_s = (tmp / 1000) / 60;
}

void TIME_MNG::SetPos(float X, float Y, float W, float H)
{
	NUM_VIEW::m_x = X;
	NUM_VIEW::m_y = Y;
	NUM_VIEW::m_num_w = W;
	NUM_VIEW::m_num_h = H;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void TIME_MNG::Draw(GLuint texId)
{
	//テクスチャセット
	NUM_VIEW::SetTex(m_mm, m_m, m_s);
	//NUM_VIEW::SetTex(31, 3, 2);
	NUM_VIEW::DrawTime(texId);

}
void TIME_MNG::Draw(void)
{
	//テクスチャセット
	NUM_VIEW::SetTex(m_mm, m_m, m_s);
	NUM_VIEW::DrawTime(m_TexID);

}	
//################################################
// End of File
//################################################
