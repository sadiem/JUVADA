//################################################
// <Emitter.cpp>
//
//------------------------------------------------
// 2013/1/16
//						Akihito Tanaka
//################################################


//================================================
//インクルードヘッダ
//================================================
#include "Emitter.h"
#include "Random.h"
//================================================
//定数定義
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EMITTER::EMITTER()
{
	m_pShaderMng = SHADER_MNG::Instance();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EMITTER::~EMITTER()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Init()
{
	m_ParticleCount = 0;
	m_Enable = false;
	m_Pos	= VECTOR3(0.0f, 0.0f, 0.0f);
	m_LifeTime = 0;
	m_Color = VECTOR3(1.0f, 1.0f, 1.0f);
	
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i].Init();
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::UpDate()
{

	if(m_LifeTime > 0)
		CreatePrticle();

	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		if(!m_Particle[i].m_Live)
			continue;
		m_Particle[i].UpDate();

		if(!m_Particle[i].m_Live)
			DeleteParticle(&m_Particle[i]);
	}

	if(m_ParticleCount <= 0)
	{
		m_Enable = false;
		Init();
	}

	m_LifeTime--;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//発生位置のセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::CreatePrticle(void)
{
	VECTOR3 vec;
	// 最大数を超えていたら作成しない
	if(m_ParticleCount> MAX_PARTICLE)
	{
		return;
	}
	PARTICLE* particle = SearchBlankParticle();
	// 空き領域がなければ作成しない
	if(particle == NULL)
	{
		return;
	}

	//オブジェクトが存在していなければ作成しない
	if(!m_obj || m_obj->m_Live == false)
	{
		m_obj = NULL;		//オブジェクト初期化
		return;
	}

	switch(m_Type)
	{
	case SPIN:
		for(int i = 0; i < SPIN_GEN_NUM; i++)  //毎フレーム指定数生成
		{
			if(particle->Set(m_obj->m_Pos, m_Type))	//１個生成
			{
				m_ParticleCount++;					//パーティクルを生成したらカウント＋
				particle = SearchBlankParticle();	//新しいパーティクルを検索
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		//if(particle->Set(m_obj->m_Pos, m_Type))	//毎フレーム１個生成
		//	m_ParticleCount++;					//パーティクルを生成したらカウント＋
		m_PointSize = 30.0f;
		break;
	case SPLASH:
		for(int i = 0; i < SPLASH_GEN_NUM; i++)  //毎フレーム指定数生成
		{
			if(particle->Set(m_obj->m_Pos, m_Type))	//１個生成
			{
				m_ParticleCount++;					//パーティクルを生成したらカウント＋
				particle = SearchBlankParticle();	//新しいパーティクルを検索
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		m_PointSize = 30.0f;
		break;
	case BOMB:
		for(int i = 0; i < BOMB_GEN_NUM; i++)  //毎フレーム指定数生成
		{
			//パーティクル発生位置計算
			vec = m_obj->m_Mesh->pVtx[GetRandom(m_obj->m_Mesh->nVtx, 0)] * m_obj->m_ScaleRate;		//メッシュ上の頂点から発生
			vec += m_obj->m_Pos;			//オブジェクトの位置へ移動
			if(particle->Set(vec, m_Type))	//１個生成
			{
				m_ParticleCount++;					//パーティクルを生成したらカウント＋
				particle = SearchBlankParticle();	//新しいパーティクルを検索
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		m_PointSize = 64.0f;
		break;
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Draw(void)	//描画
{
	//glPushMatrix();
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	glPointSize(m_PointSize);
	glBegin(GL_POINTS);
	
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Particle[i].m_Alpha);
		if(m_Particle[i].m_Live)
			glVertex3fv(m_Particle[i].m_Pos.v);
	}
	glEnd();
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

	//glPopMatrix();

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//描画(シェーダ)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::DrawShader(void)	//描画
{
  	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	//glPointSize(m_PointSize);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	//シェーダの適用
	m_pShaderMng->UseShader(POINTSPL);
	m_pShaderMng->SetTexUnit(POINTSPL, 0);
	m_pShaderMng->SetPSize(POINTSPL, m_PointSize);		//ポイントサイズ
			
	//α値セット
	glBegin(GL_POINTS);
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
	
		//glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Particle[i].m_Alpha);
		if(m_Particle[i].m_Live)
		{	
			m_pShaderMng->setColor(m_Color, m_Particle[i].m_Alpha,POINTSPL);
			glVertex3fv(m_Particle[i].m_Pos.v);
		}
	}
	glEnd();

	m_pShaderMng->UnUseShader();
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PARTICLE *EMITTER::SearchBlankParticle(void)	//描画
{
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		if(m_Particle[i].m_Live == true)
		{
			continue;
		}
		return &m_Particle[i];
	}
	
	return NULL;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//削除
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::DeleteParticle(PARTICLE *particle)	//描画
{
	particle->Reset();
	m_ParticleCount--;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//エミッター有効化
//--in--------------------------------------------
//type	:エフェクトタイプ
//obj	:オブジェクトに追従する場合のみobjのポインタ、それ以外はNULL
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Create(int type, GLuint texID, OBJECT *obj)
{	
	m_Enable = true;
	m_obj = obj;
	m_TexID = texID;
	m_Type = type;

	switch(type)
	{
	case SPIN:
		m_LifeTime = EM_SPIN_TIME;
		m_Color = VECTOR3(0.1f, 0.1f, GetRandom(100,50)/100.0f);		//青
		break;
	case SPLASH:
		m_LifeTime = EM_SPLSH_TIME;
		m_Color = VECTOR3(GetRandom(100,10)/100.0f,
			GetRandom(100,10)/100.0f, 
			GetRandom(100,10)/100.0f);		//青GetRandom(50,10)

		break;
	case BOMB:
		m_LifeTime = EM_BOMB_TIME;
		m_Color = VECTOR3(1.0f, 1.0f, 1.0f);
			//0.7f, 
			//0.1f);		//白
	}
}