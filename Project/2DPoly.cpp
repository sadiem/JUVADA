//################################################
// <2DPoly.cpp>
//
//------------------------------------------------
// 2013/02/04				Akihito Tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "2DPoly.h"	//プレイヤーＨＰバーヘッダー
#include "TexMng.h"			//テクスチャマネージャ

//================================================
//定数定義
//================================================
#define DSP_TIME	(60)
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SPLITE::SPLITE()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SPLITE::~SPLITE()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SPLITE::Init(void)
{
	Load ();

	//座標位置
	//初期位置の指定
	m_Poly[0].x  = POS_S_X;
	m_Poly[0].y  = POS_S_Y;
	m_Poly[0].z  = 0.0f;

	m_Poly[1].x  = POS_S_X;
	m_Poly[1].y  = POS_S_Y + ST_H;
	m_Poly[1].z  = 0.0f;

	m_Poly[2].x  = POS_S_X + ST_W;
	m_Poly[2].y  = POS_S_Y + ST_H;
	m_Poly[2].z  = 0.0f;

	m_Poly[3].x  = POS_S_X + ST_W;
	m_Poly[3].y  = POS_S_Y;
	m_Poly[3].z  = 0.0f;

	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SPLITE::Reset(void)
{
	m_Poly[0].tu  = 0.0f;
	m_Poly[0].tv  = 1.0f;

	m_Poly[1].tu  = 0.0f;
	m_Poly[1].tv  = 0.0f;

	m_Poly[2].tu  = 1.0f;
	m_Poly[2].tv  = 0.0f;

	m_Poly[3].tu  = 1.0f;
	m_Poly[3].tv  = 1.0f;

	m_Cnt = 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SPLITE::Load (void)
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\OP\\Start.png", "OP");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SPLITE::Update(void)
{

	m_Cnt ++ ;

	m_Poly[0].tu  = 0.0f;
	m_Poly[0].tv  = 1.0f;

	m_Poly[1].tu  = 0.0f;
	m_Poly[1].tv  = 1.0f;

	m_Poly[2].tu  = 1.0f;
	m_Poly[2].tv  = 1.0f;

	m_Poly[3].tu  = 1.0f;
	m_Poly[3].tv  = 1.0f;

	if(m_Cnt > DSP_TIME)
		return true;
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SPLITE::Draw(void)
{
	if(m_Cnt > DSP_TIME)
		return;
	glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	glInterleavedArrays(GL_T2F_V3F, 0, &m_Poly[0]);
	glDrawArrays(GL_QUADS, 0, 4);
}

//################################################
// End of File
//################################################
