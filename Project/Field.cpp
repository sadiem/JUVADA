//################################################
// <Field.cpp>
// 地面制作
//------------------------------------------------
// 2012/11/26 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Field.h"		//フィールドヘッダ
#include "TexMng.h"		//テクスチャマネージャ
#include "MeshMng.h"	//メッシュマネージャ
#include "Matrix.h"		//数学

//================================================
//定数定義
//================================================
#define F_W (300)	//フィールド幅
#define F_H (300)	//フィールド高
#define F_RANGE (40.0f)	//フィールド範囲

//================================================
//クラス定義
//================================================
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
FIELD::FIELD()
{
	m_skypos = SKY_POS;
	m_Shade = SHADER_MNG::Instance();
	//SetFence();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
FIELD::~FIELD()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Init()
{
	m_skypos = SKY_POS;
	m_Shade = SHADER_MNG::Instance();
	Load();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Load()
{
	//テクスチャ
	m_TexIDField = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\field1-fix.png"), _T("FIELD"));
	m_TexIDFieldB = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\fieldbmp.png"), _T("FIELD"));
	m_TexIDSky = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\sky.png"), _T("FIELD"));
	m_TexIDSaku = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\saku.png"), _T("FIELD"));
	m_TexIDFieldBack = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\fieldBack.png"), _T("FIELD"));

	//メッシュ
	g_MeshMng.GetMesh(&m_Mesh, _T("MODEL\\AMBIENT\\fieldback.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_Meshsky, _T("MODEL\\AMBIENT\\sky.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_MeshSaku, _T("MODEL\\AMBIENT\\saku.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_MeshfieldBack, _T("MODEL\\AMBIENT\\fieldback.x"), _T("FIELD"));
}			
//++++++++++++++++++++++++++++++++++++++++++++++++
//解放
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Release()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Update()
{
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Draw()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//スカイドーム
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDSky);
	glPushMatrix();
	glTranslatef(m_skypos.x, m_skypos.y, m_skypos.z);
	glScalef(60.0f, 60.0f, 60.0f);
	DrawMesh(&m_Meshsky);
	glPopMatrix();

	//フィールド
	GLuint tangent = 0;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glScalef(150.0f, 1.0f, 150.0f);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDField);
	glScalef(0.7f, 1.0f, 0.7f);
	DrawMesh(&m_Mesh);
	glPopMatrix();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	////フィールド上の角を黒くする
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPushMatrix();
	//glTranslatef(0.0f, 0.1f, 0.0f);
	//glScalef(150.0f, 1.0f, 150.0f);
	//glBindTexture(GL_TEXTURE_2D, m_TexIDFieldBack);
	//DrawMesh(&m_MeshfieldBack);
	//glPopMatrix();
	glDisable(GL_BLEND);				//ブレンド無効

	glEnable(GL_LIGHTING);

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//柵の描画
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::DrawFence()
{
	//柵
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexIDSaku);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	DrawMesh(&m_MeshSaku);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

//################################################
// End of File
//################################################
