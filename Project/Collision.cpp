//################################################
// <Collision.h>
//
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
// 2013/1/9		:ボス当たり判定追加
//						Akihito Tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Collision.h"
#include "Matrix.h"
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
COLLISION::COLLISION()
{
	m_pPlayer = PLAYER::Instance();
	m_pEnemy  = ENEMYMNG::Instance();
	m_pEffect = EFFECT_MNG::Instance();
	m_flgAtk = false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
COLLISION::~COLLISION()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//衝突判定
// 触れている
//--in--------------------------------------------
// 1匹目の位置
// 2匹目の位置
// 1匹目の幅
// 2匹目の幅
//--out-------------------------------------------
// 判定
//++++++++++++++++++++++++++++++++++++++++++++++++
bool COLLISION::CollsionSphere(VECTOR3 pos, VECTOR3 pos2, float w, float w2)	//衝突判定
{
	//バウンディングスフィア
	VECTOR3 tmp;
	tmp.x = pos.x - pos2.x;
	tmp.y = pos.y - pos2.y;
	tmp.z = pos.z - pos2.z;

	if(VecLength(tmp) < (w + w2))
	{
		return true;	//衝突
	}
	return false;		//未衝突
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::Update()
{
	CollisionEnemyAndPlayer();
	CollisionBossAndPlayer();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//敵とプレイヤーの衝突判定
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::CollisionEnemyAndPlayer(void)
{
	//----------------------------------
	//	ノーマルな敵とのアタリ判定
	//----------------------------------
	for(int nLoop = 0; nLoop < ENEMY_NOMAL_NUM; nLoop ++)
	{
		//死んでたら次の敵を見る
		if(!m_pEnemy->m_pEnemy[nLoop]->m_Live)
			continue;

		//プレイヤーと敵の衝突判定
		if((VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) < m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + m_pPlayer->m_Width * 0.5f)	//外側の縁
			&&
			(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) > m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + ((m_pPlayer->m_Width * 0.5f) * 0.8f)))	//内側の縁
		{
			m_pEffect->Set(E_PARTICLE_LINE, m_pEnemy->m_pEnemy[nLoop]);	//エフェクトセット
			m_pEnemy->m_pEnemy[nLoop]->m_ColPlayer = true;
			
			//プレイヤーが敵からダメージを受ける
			if(m_pEnemy->m_pEnemy[nLoop]->m_AtkHitPlayer)
			{
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemy[nLoop]->m_Attack);	//プレイヤーへダメージ
				m_pEnemy->m_pEnemy[nLoop]->m_AtkHitPlayer = false;
			}
		}
		else
			m_pEnemy->m_pEnemy[nLoop]->m_ColPlayer = false;	//衝突していない状態へ
		if(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) < m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + ((m_pPlayer->m_Width * 0.5f) * 0.8f))
		{
			//プレイヤー側
			if(!m_pPlayer->m_InEnemyFlg)
				m_pPlayer->m_InEnemyFlg = true;		//敵が中にいる
			//敵側
			if(m_pPlayer->m_State == P_ENEMY_IN_COLLECT)
				m_pEnemy->m_pEnemy[nLoop]->m_ColRingIn = true;	//攻撃を受ける
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//敵とプレイヤーの衝突判定
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::CollisionBossAndPlayer(void)
{
	//死んでたら処理しない
	if(!m_pEnemy->m_pEnemyBoss->m_Live)
			return;

		
	//敵がWAITのときアタックフラグを折る
	if(m_pEnemy->m_pEnemyBoss->m_State == WAIT)
		m_flgAtk = false;

	
//if(m_pEnemy->m_pEnemyBoss->m_State == SPIN_ATTACK)
//{	
//	float a;
//	a = 1.0f;
//}
	//プレイヤーと敵の衝突判定
	if(CollsionSphere(m_pPlayer->m_Pos, m_pEnemy->m_pEnemyBoss->m_Pos, m_pPlayer->m_Width * 0.5f, m_pEnemy->m_pEnemyBoss->m_Width))
	{
		if(!m_pPlayer->m_InEnemyFlg)
				m_pPlayer->m_InEnemyFlg = true;

		//ジャンプアタック時
		if(m_pEnemy->m_pEnemyBoss->m_JumpFlg)	//ジャンプ着地時
		{
			if(!m_flgAtk)
			{
				m_flgAtk = true;		//攻撃
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemyBoss->m_Attack);	//プレイヤーへダメージ
			}
		}
		//スピンアタック時
		if(m_pEnemy->m_pEnemyBoss->m_State == SPIN_ATTACK)
		{	
			if(!m_flgAtk)
			{
				m_flgAtk = true;	//攻撃
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemyBoss->m_Attack);	//プレイヤーへダメージ
			}
		}

		if(!m_pPlayer->m_InEnemyFlg)
			m_pPlayer->m_InEnemyFlg = true;
	}


	//プレイヤーと敵のリング内衝突判定
	if(m_pEnemy->m_pEnemyBoss->m_State == WAIT)
	{
		if(m_pPlayer->m_State == P_ENEMY_IN_COLLECT)	//攻撃時
		{
			float f0, f1;
			f0 = VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemyBoss->m_Pos);
			f1 = (m_pPlayer->m_Width + m_pEnemy->m_pEnemyBoss->m_Width);
			if(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemyBoss->m_Pos) < (m_pPlayer->m_Width + m_pEnemy->m_pEnemyBoss->m_Width))
			{
				m_pEnemy->m_pEnemyBoss->m_ColRingIn = true;	//プレイヤーからの攻撃
			}
		}
	}
}

//################################################
// End of File
//################################################