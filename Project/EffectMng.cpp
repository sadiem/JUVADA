//################################################
// <EffectMng.cpp>
//
//------------------------------------------------
// 2013/1/6				Akihito Tanaka
//################################################

//================================================
//インクルードヘッダ
//================================================
#include "EffectMng.h"			//シェーダ

//================================================
//定数定義
//================================================

//================================================
//クラス定義
//================================================


//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EFFECT_MNG::EFFECT_MNG()
{
	//Load();
	pSmoke = SMOKE::Instance();
	pImpact = IMPACT::Instance();
	pRock = ROCK::Instance();

	pRock->Remove();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EFFECT_MNG::~EFFECT_MNG()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EFFECT_MNG::Load(void)
{
	//pSmoke->Load();
	//ポイントスプライトのテクスチャを有効化
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	m_TexSpin		= g_TexMng.GetTexture(_T("TEXTURE\\EFFECT\\P_Star100.png"), _T("EFFECT"));
	m_TexBomb		= g_TexMng.GetTexture(_T("TEXTURE\\EFFECT\\P_Bomb.png"), _T("EFFECT"));
	g_MeshMng.GetMesh(&m_MeshLine, "MODEL\\P_Line_z.x", "EFFECT");
	for(int i = 0; i < MAX_LINE; i++)
	{
		pLine[i].Load(&m_MeshLine);
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//アップデート
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EFFECT_MNG::UpDate(void)
{
	pSmoke->UpDate();
	pImpact->UpDate();
	pRock->UpDate();

	for(int i = 0; i < MAX_EMITTER; i++)
	{
		if(!m_Emitter[i].m_Enable)
			continue;
		m_Emitter[i].UpDate();
	}
	for(int i = 0; i < MAX_LINE; i++)
	{
		if(!pLine[i].m_Live)
			continue;
		pLine[i].UpDate();
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EFFECT_MNG::Draw(void)
{
	pSmoke->Draw();
	pRock->Draw();
	pImpact->Draw();

	for(int i = 0; i < MAX_EMITTER; i++)
	{
		if(!m_Emitter[i].m_Enable)
			continue;
		m_Emitter[i].DrawShader();
	}
	for(int i = 0; i < MAX_LINE; i++)
	{
		if(!pLine[i].m_Live)
			continue;
		pLine[i].Draw();
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//エフェクト設置
//--in--------------------------------------------
// エフェクトタイプ、描画位置
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EFFECT_MNG::Set(int type, OBJECT *obj)
{
	switch(type)
	{
	case E_SMOKE_L:
		pSmoke->SetSmoke(obj->m_Pos);
		break;
	case E_IMPACT:
		pImpact->Set(obj->m_Pos);
		break;
	case E_PARTICLE_SPIN:	//forの中で分岐
	case E_PARTICLE_SPLASH:
	case E_PARTICLE_BOMB:
		//エミッターの空きを検索
		for(int i = 0; i < MAX_EMITTER; i++)
		{
			if(m_Emitter[i].m_Enable)
				continue;
			switch(type)
			{
			case E_PARTICLE_SPIN:	//スピン用
				m_Emitter[i].Create(SPIN, m_TexSpin, obj);
				break;
			case E_PARTICLE_SPLASH://噴射用
				m_Emitter[i].Create(SPLASH, m_TexSpin, obj);
				break;
			case E_PARTICLE_BOMB://爆発用
				m_Emitter[i].Create(BOMB, m_TexBomb, obj);
				break;
			}
			break;
		}
		break;
	case E_PARTICLE_LINE:
		for(int i = 0; i < MAX_LINE; i++)
		{
			if(pLine[i].m_Live || obj->m_Effect)
				continue;
			
			pLine[i].Set(obj);
			break;

		}
		break;
	case E_ROCK_LINE:
		pRock->Set(obj, ROCK_TYPE::LINE);
		break;
	case E_ROCK_CIRCLE:
		pRock->Set(obj, ROCK_TYPE::CIRCLE);
		break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//エフェクト撤去
//--in--------------------------------------------
// エフェクトタイプ、描画位置
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EFFECT_MNG::Remove(int type)
{
	switch(type)
	{
	case E_ROCK_LINE:
		pRock->Remove();
		break;
	}
}
//################################################
// End of File
//################################################