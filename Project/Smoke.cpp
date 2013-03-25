//################################################
// <Smoke.cpp>
//
//------------------------------------------------
// 2013/01/06 ~
//						SekiyamaRumi
//################################################


//================================================
//インクルードヘッダ
//================================================
#include "Smoke.h"	//煙
#include "Random.h"	//乱数
#include "Matrix.h"	//数学
#include "TexMng.h"	//テクスチャマネージャ
//================================================
//定数定義
//================================================
#define SMOKE_TIME	(200)	//煙の滞空時間
#define ADD_ALPHA_SMOKE	(0.01f)	//煙のα値の増加量

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SMOKE::SMOKE()
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
SMOKE::~SMOKE()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SMOKE::Load()
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\AMBIENT\\kemuri.png", "AMBIENT");
	g_MeshMng.GetMesh(&m_Mesh, "MODEL\\AMBIENT\\poli1.x", "AMBIENT");

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SMOKE::Reset()
{	
	for(int i = 0; i < SMOKE_NUM; i ++)
	{
		m_Smoke[i].m_Live = false;
		m_Smoke[i].m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
		m_Smoke[i].m_Time = SMOKE_TIME;
		m_Smoke[i].m_Alpha = 0.0f;
		m_Smoke[i].m_ScaleRate = 0.0f;
		m_Smoke[i].m_Scale = 1.0f;
		m_Smoke[i].m_SpeedY = 0.0f;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
//void SMOKE::UpDate(void)
//{
//	//エフェクト開始フラグがあるとき
//	UpdateSmoke();	//更新
//}

//++++++++++++++++++++++++++++++++++++++++++++++++
//煙のセット
//--in--------------------------------------------
//	開始位置
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SMOKE::SetSmoke(VECTOR3 vec)
{
	VECTOR3 v;
	int nCnt = 0;

	for(int i = 0; i < SMOKE_NUM; i ++)
	{
		
		if(m_Smoke[i].m_Live)
			continue;
	
		//100個単位で出力
		if(nCnt > 200)
		{
			nCnt = 0;
			break;
		}
		else
			nCnt ++;

		//初期値をセット
		m_Smoke[i].m_Live = true;
		m_Smoke[i].m_Pos = VECTOR3(vec.x, vec.y, vec.z);
		m_Smoke[i].m_Pos.y = 0.1f;
		m_Smoke[i].m_Angle = (float)(360 / 100) * nCnt;
		m_Smoke[i].m_Speed = 0.001f * GetRandom(50, 1) + 0.15f;
		m_Smoke[i].m_ScaleRate = GetRandom(10, 1) * 0.01f;
		m_Smoke[i].m_Scale = 1.0f;
		m_Smoke[i].m_SpeedY = GetRandom(10, 1) * 0.0025f;

		//方向ベクトルを算出
		v.x = 1.0f * cos((float)m_Smoke[i].m_Angle / 180.0f * M_PI);
		v.y = 0.0f;
		v.z = 1.0f * sin((float)m_Smoke[i].m_Angle / 180.0f * M_PI);
		m_Smoke[i].m_vec = v;
		m_Smoke[i].m_Pos = vec;

		//滞空時間
		m_Smoke[i].m_Time = SMOKE_TIME;
		//α値
		m_Smoke[i].m_Alpha = 0.0f;	
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//煙の更新
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SMOKE::UpDate(void)
{
	for(int i = 0; i < SMOKE_NUM; i ++)
	{
		if(!m_Smoke[i].m_Live)
			continue;

		//更新処理
		m_Smoke[i].m_Time --;	//滞空時間減

		//移動
		m_Smoke[i].m_Pos += m_Smoke[i].m_vec * m_Smoke[i].m_Speed;
		m_Smoke[i].m_Speed *= 0.9998f;

		//拡大
		m_Smoke[i].m_Scale += m_Smoke[i].m_ScaleRate;

		//α値
		if(m_Smoke[i].m_Time < 0)
		{
			m_Smoke[i].m_Time = 0;
			m_Smoke[i].m_Live = false;
			m_Smoke[i].m_Alpha = 0.0f;
		}
		//消える処理
		else if(m_Smoke[i].m_Time < 100)
		{
			
			//高度
			m_Smoke[i].m_Pos.y +=  m_Smoke[i].m_SpeedY;
		
			m_Smoke[i].m_Alpha -= ADD_ALPHA_SMOKE;
			if(m_Smoke[i].m_Alpha < 0.0f)
				m_Smoke[i].m_Alpha = 0.0f;
		}
		//現れる処理
		else
		{
			m_Smoke[i].m_Alpha += ADD_ALPHA_SMOKE;
			if(m_Smoke[i].m_Alpha > 1.0f)
				m_Smoke[i].m_Alpha = 1.0f;	
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
void SMOKE::Draw()
{
	GLdouble	matView[16];

	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	
	glActiveTexture(GL_TEXTURE0);

	for(int i = 0; i < SMOKE_NUM; i ++)
	{
		if(!m_Smoke[i].m_Live)
			continue;

		glPushMatrix();
		glTranslatef(m_Smoke[i].m_Pos.x, m_Smoke[i].m_Pos.y, m_Smoke[i].m_Pos.z);
		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
		glLoadMatrixd(&matView[0]);
		//α値セット
		glColor4f(1.0f, 1.0f, 1.0f, m_Smoke[i].m_Alpha);
		glScalef(m_Smoke[i].m_Scale, m_Smoke[i].m_Scale, m_Smoke[i].m_Scale);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		DrawMesh(&m_Mesh);
	
		
		glPopMatrix();
	}
	
	glDepthMask(GL_TRUE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//################################################
// End of File
//################################################
