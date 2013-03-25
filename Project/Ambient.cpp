//################################################
// <Ambient.cpp>
//
//------------------------------------------------
// 2013/01/05 ~					SekiyamaRumi
//################################################


//================================================
//インクルードヘッダ
//================================================
#include "Ambient.h"	//環境ヘッダ
#include "Random.h"		//乱数
#include "TexMng.h"		//テクスチャマネージャ

//================================================
//定数定義
//================================================
#define FOG_MIN_EXP	(0.0002f)
#define FOG_MAX_EXP	(0.001f)
#define FOG_ADD		(0.0001f)	//フォグ濃度増加値

#define CLOUD_TIME		(300)	//雲の滞空時間
#define ADD_ALPHA_CLOUD	(0.01f)	//雲のα値の増加量

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
AMBIENT::AMBIENT()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
AMBIENT::~AMBIENT()
{

}
void AMBIENT::Init()
{
	Load();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Load()
{
	m_TexIDCloud = g_TexMng.GetTexture("TEXTURE\\AMBIENT\\kumo.png", "AMBIENT");
	g_MeshMng.GetMesh(&m_MeshCloud, "MODEL\\AMBIENT\\poli1.x", "AMBIENT");
	
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Reset()
{
	m_fogExp = FOG_MIN_EXP;
	GLfloat fogCol[] = {0.7f, 0.7f, 0.7f, 0.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 100.0f);			//開始点
	glFogf(GL_FOG_END, 500.0f);		//終了点
	glFogi(GL_FOG_MODE, GL_EXP);		//濃度
	glFogf(GL_FOG_DENSITY, m_fogExp);
	glFogfv(GL_FOG_COLOR, fogCol);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		m_Cloud[i].m_Live = false;
		m_Cloud[i].m_Pos = VECTOR3(0.0f, 5.0f, 0.0f);
		m_Cloud[i].m_Time = CLOUD_TIME;
		m_Cloud[i].m_Alpha = 0.0f;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Update(int num, int fogStart)
{
	FogUpdate(num, fogStart);		//フォグ
	CloudUpdate();		//雲	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//霧の更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::FogUpdate(int num, int fogStart)
{
	if(m_fogExp > FOG_MAX_EXP)
		m_fogExp = FOG_MAX_EXP;
	else
	{
		if(num > fogStart)
			m_fogExp += FOG_ADD;	//濃度計算
	}
	//フォグ
	glFogi(GL_FOG_MODE, GL_EXP);	//濃度
	glFogf(GL_FOG_DENSITY, m_fogExp);
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//雲セット
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::CloudSet(void)		//雲効果
{
	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		if(m_Cloud[i].m_Live)
			continue;

		//各種値をセット
		m_Cloud[i].m_Live = true;							//生存
		m_Cloud[i].m_Time = CLOUD_TIME + GetRandom(200, 0);	//滞空時間セット
		m_Cloud[i].m_Pos.x = (float)GetRandom(60, -60);			//出現位置
		m_Cloud[i].m_Pos.y = (float)GetRandom(40, 5);
		m_Cloud[i].m_Pos.z = (float)GetRandom(60, -60);
		

		break;
	}

	//メッシュデータのα値を０に設定
	for(int nLoop = 0; nLoop < m_MeshCloud.nFace; nLoop ++)	
		m_MeshCloud.pMaterial[m_MeshCloud.pFace[nLoop].nMaterialNo].Diffuse.w = 0.0f;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//霧の更新
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::CloudUpdate(void)		//雲効果
{
	CloudSet();

	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		if(!m_Cloud[i].m_Live)
			continue;

		m_Cloud[i].m_Time --;	//滞空時間
		
		//α値
		if(m_Cloud[i].m_Time < 0)
		{
			m_Cloud[i].m_Live = false;
			m_Cloud[i].m_Alpha = 0.0f;
			m_Cloud[i].m_Time = 0;
		}
		//消える処理開始
		else if(m_Cloud[i].m_Time < 120)
		{
			//α値をセット
			m_Cloud[i].m_Alpha -= ADD_ALPHA_CLOUD;
			if(m_Cloud[i].m_Alpha < 0.0f)
				m_Cloud[i].m_Alpha = 0.0f;
		}
		//現れる処理
		else
		{
			//α値をセット
			m_Cloud[i].m_Alpha += ADD_ALPHA_CLOUD;
			if(m_Cloud[i].m_Alpha > 1.0f)
				m_Cloud[i].m_Alpha = 1.0f;
		}
		//位置を左右にずらす
		m_Cloud[i].m_Pos.x += 0.05f;			//出現位置
	}
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Draw()
{
	GLdouble	matView[16];

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	
	glActiveTexture(GL_TEXTURE0);

	for(int i = 0; i < CLOUD_NUM; i ++)
	{	
		if(!m_Cloud[i].m_Live)
			continue;

		glPushMatrix();
		glTranslatef(m_Cloud[i].m_Pos.x, m_Cloud[i].m_Pos.y, m_Cloud[i].m_Pos.z);

		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;

		glLoadMatrixd(&matView[0]);
		glScalef(10.0f, 10.0f, 10.0f);

		//α値セット
		glColor4f(1.0f, 1.0f, 1.0f, m_Cloud[i].m_Alpha);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TexIDCloud);
		DrawMesh(&m_MeshCloud);
	
		
		glPopMatrix();
	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//################################################
// End of File
//################################################
