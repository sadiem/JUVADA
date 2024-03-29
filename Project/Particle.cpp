//################################################
// <Particle.cpp>
//
//------------------------------------------------
// 2013/1/15						Akihito Tanaka
//################################################


//================================================
//インクルードヘッダ
//================================================
#include "Random.h"	//乱数
#include "Particle.h"	
#include <math.h>
//================================================
//定数定義
//================================================
#define ADD_ALPHA	(0.05f)	//α値の増加量
#define LIFE_TIME	(100)	//生存時間
#define ADD_DST		(1.0f)	//中心からの距離の加算値
#define ADD_Y		(0.1f)	//上昇量

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PARTICLE::PARTICLE()
{
	Reset();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PARTICLE::~PARTICLE()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::Init()
{
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::Reset()
{	

	m_Live = false;
	m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
	m_AddDst = 0.0f;
	m_Time = 0;
	m_Alpha = 0.0f;
	m_Dst	= 0.0f;	
	m_Alpha = 0.0f;
	m_Scale = 0.0f;
	m_Live = false;
	m_Time = 0;
	m_Type = 0;
	m_Rad = 0;		//角度
	m_AddRad = 0;	//角度加算値
	m_MaxLifeTime = 0;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//位置のセット
//--in--------------------------------------------
//	開始位置 ,パーティクルタイプ
//--out-------------------------------------------
//	新たに生成したかのフラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PARTICLE::Set(VECTOR3 pos, int type)
{
	VECTOR3 v;
	//int nCnt = 0;

	if(m_Live)
		return false;

	//初期値をセット
	m_Live = true;
	m_Type  = type;

	switch(m_Type)
	{
	case SPIN:
		m_Center = pos;
		m_Pos.y = 0.1f;
		m_Scale = 0.1f;	
		m_AddDst = GetRandom(10,5) / 10.0f;
		m_Time = LIFE_TIME;		//滞空時間
		m_MaxLifeTime = LIFE_TIME;
		m_Alpha = 0.0f;			//α値
		m_Rad = GetRandom(360,0) * M_PI / 180.0f;
		m_AddRad = GetRandom(10,1) / 100.0f;
		break;
	case SPLASH:
		m_Pos	= pos;
		m_Scale = 0.1f;	
		m_Time = LIFE_TIME;		//滞空時間
		m_MaxLifeTime = LIFE_TIME;
		m_Alpha = 0.0f;			//α値
		m_Move  = VECTOR3(	(GetRandom(100,0) - 50) / 500.0f,		//X移動量	-0.05 〜　0.05
							GetRandom(50,10)		  / 100.0f,		//Y移動量	 0.0 〜　0.5
							(GetRandom(100,0) - 50) / 500.0f);		//Z移動量	-0.05 〜　0.05
		break;
	case BOMB:
		m_Pos	= pos;
		m_Scale = 0.1f;	
		m_Time = LIFE_TIME;		//滞空時間
		m_MaxLifeTime = LIFE_TIME;
		m_Alpha = 0.0f;			//α値
		m_Move  = VECTOR3(	(GetRandom(100,0) - 50) / 1000.0f,		//X移動量	-0.05 〜　0.05
							(GetRandom(100,0) - 50)	/ 1000.0f,		//Y移動量	 0.0 〜　0.5
							(GetRandom(100,0) - 50) / 1000.0f);		//Z移動量	-0.05 〜　0.05
		Vec3Normalize(&m_Move, m_Move);			//単位行列化で球系になるように補正
		m_Move *= (GetRandom(100,40) / 1000.0f);
		break;
	}

	return true;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//煙の更新
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::UpDate(void)
{

	if(!m_Live)
		return;


	//更新処理
	m_Time --;	//滞空時間減

	//α値
	if(m_Time < 0)		//タイマーが０になったら消す
	{
		m_Time = 0;
		m_Live = false;
		m_Alpha = 0.0f;
	}
	//残り４分の１になったら消える処理
	else if(m_Time < m_MaxLifeTime / 4.0f)
	{
		m_Alpha -= ADD_ALPHA;
		if(m_Alpha < 0.0f)
			m_Alpha = 0.0f;
	}
	//現れる処理
	else
	{
		m_Alpha += ADD_ALPHA;
		if(m_Alpha > 1.0f)
			m_Alpha = 1.0f;	
	}

	switch(m_Type)
	{
	case SPIN:
		MoveSpin();
		break;
	case SPLASH:
		MoveSplash();
		break;
	case BOMB:
		MoveBomb();
		break;
	}


}
//++++++++++++++++++++++++++++++++++++++++++++++++
//スピン移動
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::MoveSpin(void)
{
	m_AddDst *= 0.95f;
	m_Pos.y += ADD_Y;
	m_Rad += m_AddRad;		//角度を加算
	m_Dst	+= m_AddDst;

	//2πを超えたら０に補正
	if(m_Rad > 2 * M_PI)
		m_Rad = 0.0f;
	m_Pos.x = m_Dst * sin(m_Rad) + m_Center.x;
	m_Pos.z = m_Dst * cos(m_Rad) + m_Center.z;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//スピン移動
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::MoveSplash(void)
{
	m_Pos += m_Move;

	m_Move.y -= 0.005f;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//スピン移動
//--in--------------------------------------------
//	なし
//--out-------------------------------------------
//	なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::MoveBomb(void)
{
	m_Pos += m_Move;
	m_Move *= 0.97f;
	m_Move.y += 0.001f;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PARTICLE::Draw()
{

}
//################################################
// End of File
//################################################
