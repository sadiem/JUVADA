//################################################
// <EnemyNormal.h>
//
//------------------------------------------------
// 2012/12/06 ~								SekiyamaRumi
// 2013/1/18	エフェクト追加				Akihito　Tanaka
// 2013/1/31	やられモーション修正　		Akihito　Tanaka
// 2013/1/31	関数内のstatic変数を修正	Akihito  Tanaka 
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "EnemyNormal.h"
#include "TexMng.h"		//テクスチャマネージャ
#include "MeshMng.h"	//メッシュマネージャ
#include "Random.h"		//乱数設定
//================================================
//定数定義
//================================================
#define N_ENM_SPEED		(0.05f)	//速度
#define N_ENM_LIFE		(10)		//ライフ
#define N_ENM_ATTACK	(1)		//攻撃力
#define N_ENM_RAD       (0.2f)	//攻撃時回転
#define N_ENM_BACK      (0.7f)	//バックステップスピード
#define N_ENM_ATTACK_AREA	(15.0f)	//攻撃範囲
#define N_ENM_DISCOVER		(0.27f)	//プレイヤー発見時速度
#define ENEMY_N_MORF_TIME	(20)	//敵モーフィング時間
#define GRAVITY				(-0.0098f)	//重力
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_NORMAL::ENEMY_NORMAL()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out---------------------a----------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_NORMAL::~ENEMY_NORMAL()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Init()
{
	m_pShader = SHADER_MNG::Instance();
	m_pEffectMng = EFFECT_MNG::Instance();
	m_pSE		= SOUND::Instance();
	m_Mesh = NULL;
	m_Mesh = new MESH;
	nCntAtk = 0;
	nCntDmg = 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Reset(void)
{
	MatrixIdentity(&m_Matrix);		//変換マトリックス
	Vec3Identity(&m_Pos);			//位置
	Vec3Identity(&m_PosPrev);		//位置座標前
	Vec3Identity(&m_vec);			//キャラの向き
	Vec3Identity(&m_vecPrev);		//キャラの向き前
	m_vecS = 0.0f;					//移動速度
	m_Rad = 0.0f;					//回転角
	m_State = DEAD;					//状態
	m_Life  = N_ENM_LIFE;			//体力
	m_Live  = false;				//生存
	m_Speed = 0.0f;					//速度
	m_Type  = NORMAL;				//タイプ
	m_ScaleRate = 1.0f;				//拡大率
	m_Timer = 0;					//タイマー(死亡時などで使用)
	m_Attack = N_ENM_ATTACK;		//攻撃力
	m_Scale = VECTOR3(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	m_ColPlayer = false;			//プレイヤーとの衝突フラグ
	m_ColRingIn = false;			//プレイヤーのリング内に含まれているかのフラグ
	m_AtkMotion = false;
	m_DmgMotion = false;
	//エフェクト
	m_Effect = false;

	nCntAtk = 0;
	nCntDmg = 0;

	//爆発用メッシュの作成とリセット
	MeshBomb(&m_MeshBomb, &m_MeshDmg1);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//データの初期値をセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::SetData(void)
{
	//現在位置指定
	m_Pos.x = GetRandom(FIELD_WIDTH, 0) - (FIELD_WIDTH * 0.5f);
	m_Pos.y = 0.0f;
	m_Pos.z = GetRandom(FIELD_WIDTH, 0) - (FIELD_WIDTH * 0.5f);

	//進行方向指定
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_vec.z = 1.0f;

	//移動速度
	m_Speed = N_ENM_SPEED;		//標準速度

	//状態
	m_State = MOVE;				//移動

	//体力
	m_Life = N_ENM_LIFE;

	//生存
	m_Live = true;

	//タイプ
	m_Type = NORMAL;

	//拡大率
	m_ScaleRate = 1.0f;
	m_Scale = VECTOR3(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	//攻撃力
	m_Attack = N_ENM_ATTACK;

	//攻撃時回転
	m_RotAtc = 0.0f;

	//攻撃モーションの種類
	m_AtkState = ROT;

	//攻撃モーションフラグ
	m_AtkMotion = false;

	//プレイヤーへの攻撃成功フラグ
	m_AtkHitPlayer = false;
	
	//ダメージモーションフラグ
	m_DmgMotion = false;

	//敵の死んだ数
	m_DeadNum = 0;

	//幅
	m_Width = m_Mesh->fRadius * m_ScaleRate;

	//プレイヤーを見つけてないとき、進む方向
	m_vecFree = VECTOR3((float)GetRandom(10, -10), 0.0f, (float)GetRandom(10, -10));

	//エフェクト
	m_Effect = false;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Load(void)
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\ENEMY\\enemy01.png", "ENEMY");
	m_TexInside = g_TexMng.GetTexture("TEXTURE\\ENEMY\\player_inner.png", "ENEMY");
	g_MeshMng.GetMesh(&m_MeshNormal, "MODEL\\ENEMY\\Enemy_Normal.x", "ENEMY");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshB, "MODEL\\ENEMY\\enm01_b.x", "ENEMY");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshDmg1, "MODEL\\ENEMY\\Enemy_Normal_bomb.x", "ENEMY");	//メッシュ読み込み
	//g_MeshMng.GetMesh(&m_MeshBomb, "MODEL\\ENEMY\\enm.x", "ENEMY");	//メッシュ読み込み
	//g_MeshMng.GetMesh(&m_MeshDmg2, "MODEL\\ENEMY\\Enemy_Normal_3.x", "ENEMY");	//メッシュ読み込み
	//g_MeshMng.GetMesh(&m_Inside, "MODEL\\ENEMY\\Enemy_Normal_in.x", "ENEMY");	//メッシュ読み込み
	
	SetMorph(m_Mesh, m_MeshNormal);	
	CpyVertex(m_Mesh, m_MeshNormal);		//頂点データをとりあえずコピー
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//解放
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Release(void)
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//作成
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Create(void)
{
	SetData();	//データのセット
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//削除
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Deleate(void)
{
	//体力がない
	if(m_Life <= 0)
	{
		m_Live = false;	//死亡
	}
		
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in-------------------------s-------------------
// プレイヤーの位置
// 幅
// 攻撃力
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::Update(VECTOR3 pos, float w, int a)
{
	VECTOR3 tmp, vec;
	//モデルの現在幅を求める
	m_Width = m_Mesh->fRadius;
	
	//自分の前方にプレイヤーがいるとき追いかける
	//あとでー

	//===========================================
	//
	//	移動計算
	//／
	//===========================================
	//プレイヤーが近くにいないとき、ランダムな方向に進む
	float fl = VecLength(pos - m_Pos);
	if(VecLength(pos - m_Pos) >=  N_ENM_ATTACK_AREA)
	{
		if(GetRandom(100, 0)  == 0)
		{
			m_vecFree.x = (float)GetRandom(10, -10);
			m_vecFree.z = (float)GetRandom(10, -10);

			Vec3Normalize(&m_vecFree, m_vecFree); 
		}
		tmp = m_vecFree;
		m_Speed = N_ENM_SPEED;		//プレイヤー発見時スピードアップ
	}
	else
	{
		//プレイヤーが前方にいるとき、プレイヤーに向かって進む
		tmp = pos - m_Pos;
		if(VecLength(tmp) < w * 1.0f)
			tmp = VECTOR3();
		else
		{
			Vec3Normalize(&tmp, tmp);
			m_vec = tmp;			//進行方向の単位ベクトル保存
		}
		m_Speed = N_ENM_DISCOVER;	//プレイヤー発見時スピードアップ
	}
	vec = tmp * m_Speed;	//速度を加算

	//位置補正
	VECTOR3 posT;
	posT = m_Pos + vec;
	float fL = 0.0f;
	fL = VecLength(posT);
	if(VecLength(posT) > (FIELD_WIDTH / 2.0f))
	{
		Vec3Normalize(&tmp , (m_Pos * -1));
		vec = tmp * m_Speed;
	}
	
	//===========================================
	//
	//	フラグ管理
	//
	//===========================================
	//プレイヤーと衝突しているか
	if(m_ColPlayer)
	{	//攻撃モーションでもダメージモーションでもないとき
		if( !m_AtkMotion && !m_DmgMotion)
		{
			m_AtkMotion = true;
			m_State = ATTACK;	//攻撃状態へ
		}
	}
	else
	{	//-----衝突してない
		if( !m_AtkMotion && !m_DmgMotion)
			m_State = MOVE;	//移動状態へ
	}

	//プレイヤーからの攻撃時
	if(m_ColRingIn)	
	{
		//もし攻撃モーション時の場合
		if(m_AtkMotion)
		{
			m_AtkMotion = false;
			m_State = DAMAGE;
		}
		//ダメージモーションへ
		m_DmgMotion = true;
		m_State = DAMAGE;
		//円の中に入ってません状態へ戻す
		m_ColRingIn = false;
	}

	//===========================================
	//
	//	状態遷移
	//／
	//===========================================
	switch(m_State)
	{
	case MOVE:
		//移動処理
		m_Effect = false;
		Move(vec);
		break;
	case ATTACK:
		if(MotionAttack())
		{
			m_AtkMotion = false;		//アクション終了
			m_AtkHitPlayer = true;		//プレイヤーへの攻撃成功
		}
		break;
	case DAMAGE:
		if(MotionDamage())
		{
			m_DmgMotion = false;		//アクション終了
			//ダメージ加算
			LifeCount(a);

			if(JudgLife())
			{
				Reset();
				return true;
			}
			else
				return false;

		}
		break;
	default:break;	
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//攻撃モーション
// 
//回転しながらアタック→バックステップ
//--in-------------------------s-------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::MotionAttack(void)
{
	if(nCntAtk == 0)
	{
		m_pSE->PlaySE(DRILL);
		m_pEffectMng->Set(E_PARTICLE_LINE, this);
	}
	nCntAtk ++;
	if(nCntAtk < 50)
	{
		m_AtkState = ROT;
	}
	else
	{
		Addpos = VECTOR3();
		nCntAtk = 0;
		return true;
	}

	switch(m_AtkState)
	{
	case ROT:	//攻撃回転
		m_RotAtc += N_ENM_RAD; 
		m_Rad += m_RotAtc;
		break;
	case BACK:	//バックステップ
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//ダメージモーション
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::MotionDamage(void)
{
	if(nCntDmg == 0)
	{
		m_pSE->PlaySE(BOMB);
		m_MeshBomb.vVel = VECTOR3(0.0f,0.0f,0.0f);
	}
	nCntDmg ++;

	if(nCntDmg < ENEMY_N_MORF_TIME)
		Morphing(m_Mesh, m_MeshNormal, m_MeshDmg1, nCntDmg, 0, ENEMY_N_MORF_TIME);	
	if(nCntDmg == ENEMY_N_MORF_TIME)
	{
		m_pEffectMng->Set(E_PARTICLE_SPLASH, this);
		m_pEffectMng->Set(E_PARTICLE_BOMB, this);
	}
	//if(m_ScaleRate < 0.0f)
	
	if(nCntDmg > ENEMY_N_MORF_TIME && nCntDmg <= 60)
	{
		for(int i = 0; i < m_MeshBomb.nVtx; i ++)
		{
			m_MeshBomb.pVtx[i] += m_MeshBomb.pNormal[i] * 0.3f;
			m_MeshBomb.pVtx[i].y += m_MeshBomb.vVel.y;
		}
		m_MeshBomb.vVel.y += GRAVITY;
	}
	if(nCntDmg > 60)
	{
		//初期化処理
		nCntDmg = 0;
		m_ScaleRate = 1.0f;	
		Morphing(m_Mesh, m_MeshNormal, m_MeshDmg1, 0, 0, ENEMY_N_MORF_TIME);	
		m_Mesh->vVel = 0.0f;
		return true;
	}

	//拡縮を行う
	//m_ScaleRate -= nCntDmg * 0.002f;

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Draw(void)
{
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 512, 512, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
  
	//移動
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rad * 180 / M_PI, (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);	//攻撃時回転
	glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate); 


	//テクスチャ設定
	//描画
	if(m_Live)
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHT0);

		//DrawMesh(&m_MeshB, (GLuint)1);	
		//glEnable(GL_TEXTURE_2D);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, m_TexInside);
		//DrawMesh(&m_Inside);	
		//テクスチャ設定
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glEnable(GL_BLEND);
		
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		
		//if(m_Life > 25)
		if(nCntDmg < ENEMY_N_MORF_TIME)
			DrawMesh(m_Mesh);
		else
			DrawBomb(&m_MeshBomb);
		//else if(m_Life > 15)
		//	DrawMesh(&m_MeshDmg1);
		//else
			//DrawMesh(&m_MeshDmg2);

		//m_pShader->End();
		//glUseProgram(0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);

}
void ENEMY_NORMAL::SetLive(bool bLive){m_Live = bLive;}

//################################################
// End of File
//################################################
