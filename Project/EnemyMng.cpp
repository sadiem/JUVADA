//################################################
// <EnemyMng.h>
//
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "EnemyMng.h"

//================================================
//定数定義
//================================================
#define COL_RATE_MAX (1.0f)		//衝突判定の範囲
#define COL_RATE_1   (0.8f)		//衝突判定の範囲
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMYMNG::ENEMYMNG()
{	
	//ザコ敵
	for(int i = 0; i < ENEMY_NOMAL_NUM; i++)
	{
		m_pEnemy[i] = NULL;
		m_pEnemy[i] = new ENEMY_NORMAL;
	}
	//ボス

		m_pEnemyBoss = NULL;
		m_pEnemyBoss = new ENEMY_BOSS;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMYMNG::~ENEMYMNG()
{
	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
	{
		//データがあれば消す
		if(m_pEnemy[i])
		{
			delete m_pEnemy[i];				//データを削除
			m_pEnemy[i] = NULL;
		}
	}
	//ボス敵

		//データがあれば消す
		if(m_pEnemyBoss)
		{
			delete m_pEnemyBoss;				//データを削除
			m_pEnemyBoss = NULL;
		}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//作成
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Init(PLAYER *pPlayer)
{
	//プレイヤーのポインタを貰う
	m_pPlayer = pPlayer;		//アタリ判定用

	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Init();
	//ボス敵
		m_pEnemyBoss->Init();

	m_pEffectMng = EFFECT_MNG::Instance();
	m_pScore = SCORE::Instance();
	m_pSE = SOUND::Instance();

	Load();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//作成
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Reset(void)
{
	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Reset();
	//ボス敵
	m_pEnemyBoss->Reset();

	//カウント
	m_DeadCnt = 0;
	m_BossCnt = 0;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Load(void)
{
	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Load();
	//ボス敵

		m_pEnemyBoss->Load();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//作成
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Create(void)
{
	static int nCount = 0;

	nCount ++;

	if(nCount < 60)
		return;
	nCount = 0;

	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
	{
		if(m_pEnemy[i]->m_Live)
			continue;
		m_pEnemy[i]->Create();	//作成
		break;
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//削除
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG:: Deleate(void)
{
	//ザコ敵
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Deleate();
	//ボス敵
	m_pEnemyBoss->Deleate();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Update(void)
{
	bool bDead = false;

	//敵の生成
	if(m_BossCnt == 0)	//ボスが倒されていなければ敵を生成
		Create();

	//ザコ敵
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		if(!m_pEnemy[i]->m_Live)
			continue;
		bDead = m_pEnemy[i]->Update(m_pPlayer->m_Pos, m_pPlayer->m_Width, m_pPlayer->m_Attack);

		//死亡数カウント
		if(bDead)
		{
			m_pEffectMng->Set(E_PARTICLE_SPLASH, m_pEnemy[i]);
			 m_DeadCnt ++; 
		
			//m_pScore->addEnemyDeathScore(m_DeadCnt);//スコア加算
			bDead = false;
		}

	}
	//フラグ初期化
	bDead = false;

	if(m_DeadCnt > m_pEnemyBoss->m_AppearBoss)
	{
		m_pEnemyBoss->SetLive(true);
	}
	//ボス敵

		if(!m_pEnemyBoss->m_Live)
			return;
		bDead = m_pEnemyBoss->Update(m_pPlayer->m_Pos, m_pPlayer->m_Width, m_pPlayer->m_Attack);

		if(m_pEnemyBoss->m_Life <= 0)
		{
			//すべての敵をダメージモーションへ
			for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
			{
				if(!m_pEnemy[i]->m_Live)
					continue;
				//もし攻撃モーション時の場合
				m_pEnemy[i]->m_ColRingIn = true;
			}

		//死亡数カウント
		if(bDead)
		{
			m_BossCnt ++;
			bDead = false;
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
void ENEMYMNG::Draw(void)
{
	//ザコ敵
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		if(!m_pEnemy[i]->m_Live)
			continue;
		m_pEnemy[i]->Draw();
	}
	//ボス敵

		if(!m_pEnemyBoss->m_Live)
			return;
		m_pEnemyBoss->Draw();

}
//################################################
// End of File
//################################################
