//################################################
// <Impact.cpp>
//
//------------------------------------------------
// 2013/01/10					akihito tanaka
//################################################


//================================================
//インクルードヘッダ
//================================================
#include "Impact.h"	//衝撃波
//================================================
//定数定義
//================================================
#define IMPACT_TIME	(60)	//衝撃波の表示時間
#define IMPACT_DELAY	(3)	//遅延フレーム数
#define ADD_ALPHA	(0.02f)	//α値の増加量

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
IMPACT::IMPACT()
{
	Reset();
	Load();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
IMPACT::~IMPACT()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Load()
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\EFFECT\\impact_a.png", "EFFECT");
	for(int i = 0; i < IMPACT_NUM; i++)
	{
		g_MeshMng.GetMesh(&m_Impact[i], "MODEL\\EFFECT\\impact.x", "EFFECT");
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Reset()
{	

	m_Live = false;
	m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < IMPACT_NUM; i++)
	{
		m_Time[i] = IMPACT_TIME;
		m_Alpha[i] = 0.0f;
		m_Scale[i] = 0.1f;
	}
	m_ScaleRate = 0.0f;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//位置のセット
//--in--------------------------------------------
//	開始位置
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Set(VECTOR3 vec)
{
	VECTOR3 v;
	int nCnt = 0;

	if(m_Live)
		return;

	//初期値をセット
	m_Live = true;
	m_Pos = vec;
	m_Pos.y = 0.1f;
	m_ScaleRate = 0.05f;


	for(int i = 0; i < IMPACT_NUM; i++)
	{
		m_Scale[i] = 0.1f;

		//滞空時間
		m_Time[i] = IMPACT_TIME + i * IMPACT_DELAY;
		//α値
		m_Alpha[i] = 0.0f;	
		m_dsp[i] = false;
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//煙の更新
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::UpDate(void)
{

	if(!m_Live)
		return;

	for(int i = 0; i < IMPACT_NUM; i++)
	{
		//更新処理
		m_Time[i] --;	//滞空時間減
		if(m_Time[i] < IMPACT_TIME)
			m_dsp[i] = true;

		if(!m_dsp[i])
			continue;

		//拡大
		m_Scale[i] += m_ScaleRate;

		//α値
		if(m_Time[i] < 0)
		{
			m_Time[i] = 0;
			m_Live = false;
			m_Alpha[i] = 0.0f;
			m_dsp[i] = false;
		}
		//消える処理
		else if(m_Time[i] < IMPACT_TIME / 2.0f)
		{
			m_Alpha[i] -= ADD_ALPHA;
			if(m_Alpha[i] < 0.0f)
				m_Alpha[i] = 0.0f;
		}
		//現れる処理
		else
		{
			m_Alpha[i] += ADD_ALPHA;
			if(m_Alpha[i] > 1.0f)
				m_Alpha[i] = 1.0f;	
		}
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Draw()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	if(m_Live)
	{
		for(int i = 0; i < IMPACT_NUM; i++)
		{
			glPushMatrix();
			glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
			//α値セット
			glColor4f(1.0f, 1.0f, 1.0f, m_Alpha[i]);
			glScalef(m_Scale[i], m_Scale[i], m_Scale[i]);

			DrawMesh(&m_Impact[i]);


			glPopMatrix();
		}
	}

	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//################################################
// End of File
//################################################
