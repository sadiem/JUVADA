//################################################
// <EnemyBoss.cpp>
//
//------------------------------------------------
// 2013/1/7					akihito tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "EnemyBoss.h"
#include "MeshMng.h"		//メッシュマネージャ
#include "Random.h"			//乱数設定

//================================================
//定数定義
//================================================
#define E_BOSS_LIFE		(100)			//ボスの体力
#define E_BOSS_ATK		(10)			//ボスの攻撃力
#define E_BOSS_INIT_POS (VECTOR3(0.0f, 100.0f, 0.0f))	//ボスの初期位置
#define E_BOSS_SCALE	(0.7f)			//ボスのスケール
#define FALL_SPEED		(0.8f)			//落下スピード
#define OFFSET_Y		(12.0f * E_BOSS_SCALE)				//地面からのオフセット
#define ROT_THL			(0.03f)			//回転角度しきい値
#define ATTACK_SPIN_RAD	(0.2f)			//スピン攻撃時の回転角度
#define ATTACK_SPIN_ADD	(0.002f)		//スピン攻撃時の回転角度加算値
#define ATTACK_TIME		(60)			//攻撃時間
#define WAIT_TIME		(180)			//待機移行後の硬直時間
#define JUMP_SPEED		(1.5f)			//ジャンプ初速
#define COL_RADIUS		(0.2f)			//当たり判定大きさ
#define PRESS_TIME		(15)			//プレスの時間
#define PRESS_RATE		(1.5f)			//モデルの潰れ具合の係数
#define ATTACK_DST		(25.0f)			//攻撃距離
#define DEAD_MOTION_COUNT	(600)		//死亡モーションカウント

//ボス攻撃値
enum 
{
	ATK_JUMP = 2,	//ジャンプ
	ATK_SPIN = 2	//スピン
};
//================================================
//定数定義
//================================================
#define BOSS_APPEAR_NUM (30)		//ボス出現のための討伐敵数
//================================================
//グローバル変数
//================================================

//パーツのm_Posからのオフセット
#define PARTS_OFFSET	(1.0f * E_BOSS_SCALE)

//外パーツの位置設定
const VECTOR3 vPartsPos[BOSS_STATE_NUM][BOSS_PARTS] = 
{	
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f)},
	{VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f)},
	{VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-0.0f,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET)},
	{VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},	
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},	
	//{VECTOR3(PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET)},
};		
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
ENEMY_BOSS::ENEMY_BOSS()
{
	//初期化
	Init();

	////メッシュの初期化
	//m_Mesh = NULL;
	//m_Mesh = new MESH;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_BOSS::~ENEMY_BOSS()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Init(void)
{
	//エフェクトマネージャのインスタンス取得
	m_EffectMng = EFFECT_MNG::Instance();
	//サウンドマネージャのインスタンス取得
	m_pSE	= SOUND::Instance();
	//メッシュの初期化
	m_Mesh = NULL;
	m_Mesh = new MESH;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Reset()
{
	//初期化処理
	MatrixIdentity(&m_Matrix);		//変換マトリックス
	Vec3Identity(&m_Pos);			//位置
	Vec3Identity(&m_PosPrev);		//位置座標前
	Vec3Identity(&m_vec);			//キャラの向き
	Vec3Identity(&m_vecPrev);		//キャラの向き前
	m_vecS = 0.0f;					//移動速度
	m_Rad = 0.0f;					//回転角
	m_Live  = false;				//生存
	m_Speed = 0.0f;					//速度
	m_Type  = BOSS;					//タイプ
	m_ScaleRate = 1.0f;				//拡大率
	m_EyeScale = E_BOSS_SCALE;		//目玉の拡大率
	m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);		//スケールの設定
	m_Timer = 0;					//タイマー(死亡時などで使用)
	m_ColPlayer = false;			//プレイヤーとの衝突フラグ
	m_ColRingIn = false;			//プレイヤーのリング内に含まれているかのフラグ
	m_Pos    = E_BOSS_INIT_POS;		//原点上空
	m_State	 = BOSS_START;			//落下
	m_Life   = E_BOSS_LIFE;			//体力の設定
	m_Attack = E_BOSS_ATK;			//攻撃力の設定
	m_Width = m_MeshEye.fRadius;	//半径の設定
	m_Count	 = 0;					//カウントの初期化
	m_First = false;				//プレス時の初回フラグをOFF
	m_SpinRad = 0.0f;				//スピン回転角の初期化
	m_SpinAdd = 0.0f;				//スピン回転角加算値の初期化
	m_JumpFlg = false;				//ジャンプしていない
	m_AppearBoss = BOSS_APPEAR_NUM;	//出現数

	memset(m_PartsOffset, 0, sizeof(m_PartsOffset));	//パーツ位置初期化
	m_EffectMng = EFFECT_MNG::Instance();				//エフェクトマネージャのインスタンス取得
	m_ShaderMng = SHADER_MNG::Instance();				//シェーダマネージャのインスタンス取得
	m_pCamera  = CAMERA::Instance();					//カメラのインスタンス取得

	m_TexID			= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\boss_armor.png"), _T("BOSS"));			//外パーツテクスチャ
	m_TexBumpID		= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\boss_armor_bump.png"), _T("BOSS"));	//外パーツバンプ
	m_TexEyeID		= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\Boss_Eye.png"), _T("BOSS"));			//目玉テクスチャ
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Load(void)
{
	g_MeshMng.GetMesh(&m_MeshArmor[0], "MODEL\\BOSS\\boss_u1.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[1], "MODEL\\BOSS\\boss_u2.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[2], "MODEL\\BOSS\\boss_u3.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[3], "MODEL\\BOSS\\boss_u4.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[4], "MODEL\\BOSS\\boss_d1.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[5], "MODEL\\BOSS\\boss_d2.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[6], "MODEL\\BOSS\\boss_d3.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshArmor[7], "MODEL\\BOSS\\boss_d4.x", "BOSS");	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshEye, "MODEL\\BOSS\\boss_eye.x", "BOSS");		//メッシュ読み込み
	memcpy(m_Mesh, &m_MeshEye, sizeof(MESH));								//メッシュのコピー

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_BOSS::Update(VECTOR3 pos, float w, int a)
{
	VECTOR3 vPPos;	//パーツ座標
	VECTOR3 vWork;	//計算用ワーク

	//------------------------------
	// プレイヤーからの攻撃
	//------------------------------
	if(m_ColRingIn)	//リング内
	{
		m_State = DAMAGE_HIT;		//ダメージモーションへ
		m_ColRingIn = false;		//衝突フラグオフ
	}

	//ボスアクション分岐
	switch(m_State)
	{
	//ボス初期設定
	case BOSS_START:		
		m_pSE->StopBG(BG_GAME_NORMAL);			//通常フィールドBGMストップ
		m_pSE->PlaySE(WARNING);					//警報音
		m_pCamera->SetOperatable(false);		//カメラ固定
		m_State = FALL;							//落下行動へ
		//スルー
	//落下モーション
	case FALL: 				//上空から落下
		m_Pos.y -= FALL_SPEED;					//落下移動
		if(m_Pos.y <= OFFSET_Y)					//モデルが地面に接触したら
		{
			m_State = APPEAR;					//着地モーション
			m_Pos.y = OFFSET_Y;					//モデル表示位置
			m_Count = 0;						//カウント初期化
		}
		break;
	//出現モーション
	case APPEAR: 	
		m_Count++;								//フレーム数をカウント

		if(m_Count <= PRESS_TIME)				//着地した時の潰れた表現
		{
			if(!m_First)
			{
				m_pSE->StopSE(WARNING);					//警報SE停止
				m_pSE->PlayBG(BG_GAME_BOSS);			//ボスBGM再生
				m_Pos.y = 0.0f;							//エフェクト発生位置
				m_EffectMng->Set(E_ROCK_CIRCLE, this);	//着地地点に岩のエフェクト
				m_EffectMng->Set(E_IMPACT, this);		//衝撃波エフェクト
				m_EffectMng->Set(E_SMOKE_L, this);		//煙エフェクト
				m_Pos.y = OFFSET_Y;						//モデル表示位置に戻す
				m_First = true;							//初回通過フラグ
			}
			m_ScaleRate -= PRESS_RATE / PRESS_TIME;		//潰れる方向に縮小
		}
		else if(m_Count < PRESS_TIME*2)			//もとの大きさに戻る
		{
			m_ScaleRate += PRESS_RATE / PRESS_TIME;		//拡大率をもどす
		}
		if(m_Count > APPEAR_WAIT)						//次のモーションへ移行
		{
			//待機モーションの外パーツ位置を設定
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = 
					VECTOR3(vPartsPos[WAIT][i].x/TRANSCOUNT, 
							vPartsPos[WAIT][i].y/TRANSCOUNT, 
							vPartsPos[WAIT][i].z/TRANSCOUNT);
			}
			m_pCamera->SetOperatable(true);		//カメラ固定解除
			m_State = WAIT;						//待機モーションへ
			m_Count = 0;						//カウント初期化
		}
		break;
	//待機モーション
	case WAIT:
		if(m_Count < TRANSCOUNT)				//待機状態に変形
		{
			//外パーツの移動
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			m_Count++;				//カウント加算
			break;
		}
		else if(m_Count < WAIT_TIME)			//待機硬直
		{
			EyeMove(pos);			//目玉の移動
			m_Count++;				//カウント加算
			break;
		}


		EyeMove(pos);				//目玉の移動

		//プレイヤーとの距離を計算
		vWork = m_Pos;		//プレイヤー位置をワークに代入		
		vWork.y = 0.0f;		//高さ補正

		//攻撃分岐
		if(Vec3Length(vWork, pos) < ATTACK_DST)		//プレスの範囲内
		{
			//外パーツ移動量セット
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				//ジャンプモーションの外パーツ位置を設定
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[PRE_JUMP_ATTACK][i].x - vPartsPos[WAIT][i].x)/TRANSCOUNT, 
							(vPartsPos[PRE_JUMP_ATTACK][i].y - vPartsPos[WAIT][i].y)/TRANSCOUNT, 
							(vPartsPos[PRE_JUMP_ATTACK][i].z - vPartsPos[WAIT][i].z)/TRANSCOUNT);
			}
			m_State = PRE_JUMP_ATTACK;				//ジャンプモーションへ
			m_Attack = ATK_JUMP;					//攻撃種類をジャンプ攻撃に設定
			m_Count = 0;							//カウント初期化
			break;
		}
		if(Vec3Length(vWork, pos) > ATTACK_DST)		//プレスの範囲外
		{
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				//突撃モーションの外パーツ位置を設定
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[PRE_SPIN_ATTACK][i].x - vPartsPos[WAIT][i].x)/TRANSCOUNT, 
							(vPartsPos[PRE_SPIN_ATTACK][i].y - vPartsPos[WAIT][i].y)/TRANSCOUNT, 
							(vPartsPos[PRE_SPIN_ATTACK][i].z - vPartsPos[WAIT][i].z)/TRANSCOUNT);
			}
			m_State = PRE_SPIN_ATTACK;				//スピン攻撃へ
			m_Attack = ATK_SPIN;					//攻撃種類をスピン攻撃に設定
			m_Count = 0;							//カウント初期化
			break;
		}
		break;
	//ジャンプ攻撃準備
	case PRE_JUMP_ATTACK:
		//変形
		if(m_Count < TRANSCOUNT)
		{
			//外パーツの移動
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			m_Count++;			//カウント加算
			EyeMove(pos);		//目玉回転
			break;
		}
		else
		{
			m_vAttack = pos - m_Pos;			//攻撃方向決定
			m_vAttack.y = 0.0f;					//XZ平面で固定
			m_vAttack /= (float)ATTACK_TIME;	//単位時間あたりの移動量を設定
			m_vAttack.y = JUMP_SPEED;			//ジャンプ速度の初期値を設定
			m_State = JUMP_ATTACK;				//ジャンプ攻撃モーションへ
			m_First = false;
			m_Count = 0;
		}
		break;
	//ジャンプ攻撃モーション
	case JUMP_ATTACK:
		if(	m_Count <= ATTACK_TIME)		//攻撃方向に移動
		{
			m_Pos += m_vAttack;			//移動
			m_vAttack.y -= JUMP_SPEED/(ATTACK_TIME/2.0f);	//Y軸方向移動量計算
			m_Count++;
		}
		else if(m_Count <= ATTACK_TIME + PRESS_TIME/2)		//着地したら潰れる表現
		{
			if(!m_First)
			{
				//セフェクトのセット
				m_EffectMng->Set(E_ROCK_CIRCLE, this);
				m_EffectMng->Set(E_IMPACT, this);
				m_First = true;
			}

			m_vAttack.y = OFFSET_Y/(PRESS_TIME/PRESS_RATE);
			m_ScaleRate -= PRESS_RATE / PRESS_TIME;
			m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);
			m_Pos.y -= m_vAttack.y;
			m_JumpFlg = true;
			m_Count++;
		}
		else if(m_Count < ATTACK_TIME + PRESS_TIME)		//もとの大きさに戻る
		{
			m_vAttack.y = OFFSET_Y/(PRESS_TIME/PRESS_RATE);
			m_ScaleRate += PRESS_RATE / PRESS_TIME;
			m_Pos.y += m_vAttack.y;
			m_Count++;
		}
		else											//次の行動へ
		{
			//パーツの移動量設定
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[WAIT][i].x - vPartsPos[JUMP_ATTACK][i].x)/TRANSCOUNT, 
							(vPartsPos[WAIT][i].y - vPartsPos[JUMP_ATTACK][i].y)/TRANSCOUNT, 
							(vPartsPos[WAIT][i].z - vPartsPos[JUMP_ATTACK][i].z)/TRANSCOUNT);
			}
			//拡大率の初期化
			m_ScaleRate = 1.0f;
			m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);
			m_State = WAIT;
			m_Count = 0;
			m_JumpFlg = false;

		}
		break;
	//回転攻撃準備
	case PRE_SPIN_ATTACK:
		m_Count++;
		if(m_Count < TRANSCOUNT)
		{
			//外パーツ移動
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			break;
		}
		else if(m_Count == TRANSCOUNT)
		{
			//エフェクトセット
			m_EffectMng->Set(E_PARTICLE_SPIN, this);
		}
		EyeMove(pos);								//目玉の移動


		if(m_SpinAdd < ATTACK_SPIN_RAD)				//回転速度の増加
		{
			m_SpinAdd += ATTACK_SPIN_ADD;
		}
		else
		{

			//攻撃方向決定
			m_vAttack = pos - m_Pos;
			m_vAttack.y = 0.0f;
			Vec3Normalize(&m_vAttack, m_vAttack);
			m_AtkMove = m_vAttack;
			m_EffectMng->Set(E_ROCK_LINE, this);	//岩エフェクトセット

			//攻撃開始
			m_State = SPIN_ATTACK;
			m_Count = 0;
		}
		m_SpinRad += m_SpinAdd;						//回転
		break;
	//回転攻撃
	case SPIN_ATTACK:

		if(m_Count < ATTACK_TIME)
		{
			m_Pos += m_AtkMove;						//移動
		}
		else if(m_Count == ATTACK_TIME)
		{
			m_EffectMng->Remove(E_ROCK_LINE);		//岩エフェクト消去
		}
		else
		{
			//スピン減速
			if(m_SpinAdd > 0.05f)
			{
				m_SpinAdd -= ATTACK_SPIN_ADD;
			}
			if(m_SpinRad <= 0.1f)
			{
				m_SpinRad = 0.0f;
			}
		}

		//角度補正
		if(m_SpinRad > 2.0f * M_PI)
		{
			m_SpinRad -= 2.0f * M_PI;
		}
		if(m_SpinRad < 0.0f)
		{
			m_SpinRad += 2.0f * M_PI;
		}

		//減速終わりで待機に戻る
		if(m_SpinRad == 0.0f)
		{

			//パーツの移動量設定
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = VECTOR3(	(vPartsPos[WAIT][i].x - vPartsPos[SPIN_ATTACK][i].x)/TRANSCOUNT, 
					(vPartsPos[WAIT][i].y - vPartsPos[SPIN_ATTACK][i].y)/TRANSCOUNT, 
					(vPartsPos[WAIT][i].z - vPartsPos[SPIN_ATTACK][i].z)/TRANSCOUNT);
			}
			m_State = WAIT;
			m_Count = 0;
			break;
		}

		m_SpinRad += m_SpinAdd;
		m_Count ++;
		break;
	//ダメージモーション
	case DAMAGE_HIT:
		if(MotionDamage())
		{
			//ダメージ加算
			LifeCount(a);
			if(JudgLife())
			{
				m_State = DEAD_BOSS;
				break;
			}

			//パーツの移動量設定
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = VECTOR3(	(vPartsPos[WAIT][i].x - vPartsPos[DEAD_BOSS][i].x)/TRANSCOUNT, 
											(vPartsPos[WAIT][i].y - vPartsPos[DEAD_BOSS][i].y)/TRANSCOUNT, 
											(vPartsPos[WAIT][i].z - vPartsPos[DEAD_BOSS][i].z)/TRANSCOUNT);
			}
			m_State = WAIT;
		}
		break;
	//死亡モーション
	case DEAD_BOSS:

		//パーツの移動量設定
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			m_PartsOffset[i] += m_PartsMove[i] * (GetRandom(120, 80) / 100.0f);
			m_PartsMove[i].y -= 0.02f;
		}

		//拡大率設定
		m_EyeScale -= E_BOSS_SCALE / (DEAD_MOTION_COUNT * 0.66f);		//目玉縮小
		if(m_EyeScale < 0.0f)
			m_EyeScale = 0.0f;
		m_ScaleRate = m_EyeScale;
		m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);

		//爆発エフェクト設定
		if(m_Count < (DEAD_MOTION_COUNT * 0.7) &&  m_Count % 60 == 0)
		{
			m_EffectMng->Set(E_PARTICLE_BOMB, this);
		}

		//死亡モーション終了
		if(m_Count > DEAD_MOTION_COUNT)		
		{
			Init();
			return true;
		}

		m_Count ++;	
		break;
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
bool ENEMY_BOSS::MotionDamage(void)
{

	VECTOR3 vWork;	//計算用ワーク
	if(m_Count < 30)
	{
		//外パーツ位置設定
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			m_PartsOffset[i] = vPartsPos[DEAD_BOSS][i];
		}
		m_Count ++;
		return false;
	}
	m_Count = 0;
	return true;	//モーション終了
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Draw(void)
{

	//テクスチャ設定
	//描画
	if(m_Live)
	{
		
		glDisable(GL_ALPHA_TEST);					//透過設定
		glEnable(GL_DEPTH_TEST);					//深度テスト有効化
		glEnable(GL_CULL_FACE);						//カリング有効化
		glEnable(GL_LIGHTING);						//ライトON
		glEnable(GL_TEXTURE_2D);					//テクスチャ２D
		glActiveTexture(GL_TEXTURE0);				//テクスチャユニット０番
		glBindTexture(GL_TEXTURE_2D, m_TexEyeID);	//目玉テクスチャバインド
		m_ShaderMng->UseShader(PHONG);				//フォンシェーダ有効化
		m_ShaderMng->SetTexUnit(PHONG, 0);			//テクスチャ番号セット

		//目玉描画
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
		glRotatef(m_Rad * 180 / M_PI , (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);
		glScalef(1.0f, m_ScaleRate, 1.0f);						//潰れ具合
		glScalef(m_EyeScale, m_EyeScale, m_EyeScale);			//全体の拡大率
		m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);	//目玉の拡大率保存
		DrawMesh(&m_MeshEye);									//メッシュ描画
		glPopMatrix();	

		m_ShaderMng->UnUseShader();								//シェーダ無効化

		glActiveTexture(GL_TEXTURE0);				//テクスチャユニット０番
		glBindTexture(GL_TEXTURE_2D, m_TexID);		//外側テクスチャバインド
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);				//テクスチャユニット１番
		glBindTexture(GL_TEXTURE_2D, m_TexBumpID);	//外側バンプ用テクスチャバインド
		m_ShaderMng->UseShader(BUMP);				//バンプシェーダ有効化
		m_ShaderMng->SetTexUnit(BUMP, 0);			//バンプカラーテクスチャ
		m_ShaderMng->SetBumpUnit(BUMP, 1);			//バンプ法線テクスチャ

		//パーツ描画
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			glPushMatrix();
			glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
			glTranslatef(m_PartsOffset[i].x,m_PartsOffset[i].y,m_PartsOffset[i].z);
			glRotatef(m_SpinRad * 180 / M_PI , (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);
			glScalef(1.0f, m_ScaleRate, 1.0f); 
			glScalef(E_BOSS_SCALE, E_BOSS_SCALE, E_BOSS_SCALE); 
			DrawMesh(&m_MeshArmor[i],(GLuint)1);
			glPopMatrix();
		}

		m_ShaderMng->UnUseShader();

	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//生存フラグセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::SetLive(bool bLive)
{
	m_Live = bLive;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//視線追従
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::EyeMove(VECTOR3 pos)
{
	float fRotEye = 0.0f;	//目玉回転用

	VECTOR3 vP;		//プレイヤーへのベクトル
	vP = pos - m_Pos;
	vP.y = 0.0f;
	//Vec3Normalize(&vP, vP);
	fRotEye = VectoVec(VECTOR3(0.0f, 0.0f, 1.0f), vP);

	//角度補正
	if(fRotEye > 2.0f * M_PI)
		fRotEye -= 2.0f * M_PI;
	if(fRotEye < 0.0f)
		fRotEye += 2.0f * M_PI;


	if(fRotEye - m_Rad > ROT_THL )
	{
		if(fRotEye - m_Rad <= M_PI)
			m_Rad += ROT_THL;
		else
			m_Rad -= ROT_THL;

	}
	else if(fRotEye - m_Rad >= 0.0f)
		m_Rad += (fRotEye - m_Rad);
	else if(fRotEye - m_Rad < -ROT_THL)
	{
		if(fRotEye - m_Rad >= -M_PI)
			m_Rad -= ROT_THL;
		else
			m_Rad += ROT_THL;
	}
	else
		m_Rad += (fRotEye - m_Rad);

	//角度補正
	if(m_Rad > 2.0f * M_PI)
		m_Rad -= 2.0f * M_PI;
	if(m_Rad < 0.0f)
		m_Rad += 2.0f * M_PI;
}
void ENEMY_BOSS::Create(){}
void ENEMY_BOSS::Deleate(){}
void ENEMY_BOSS::Release(){}
void ENEMY_BOSS::SetData(){}
//################################################
// End of File
//################################################
