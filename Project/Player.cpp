//################################################
// <Player.cpp>
//
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
// 2013/1/15	入力処理部分修正	akihtio tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Player.h"		//プレイヤー
#include "Matrix.h"		//数学関数群
#include "Camera.h"		//カメラクラス
#include "math.h"
#include "TexMng.h"		//テクスチャマネージャ
#include "MeshMng.h"	//テクスチャマネージャ
#include "Shader.h"		//シェーダー
//================================================
//定数定義
//================================================
enum MESH_NO{
	PLAYER_M = 0
};
#define P_RADIUS		(15.0f)	//移動半径
#define P_SPEED			(0.02f)	//基本速度
#define	P_SPEED_MAX		(0.3f)	//速度最大値
#define P_SCALE			(0.2f)	//拡縮率
#define P_SCALE_MIN		(0.5f)	//拡大率MIN
#define P_SCALE_MAX		(5.0f)	//拡大率MAX
#define P_SCALE_TIMER	(10)	//敵が中にいるときの待ち時間
#define P_LIFE			(100)	//体力
#define P_ATTACK		(10)		//攻撃
#define P_TRANCEFORM_TIME	(20)//変形時間
#define P_SINK_RATE		(0.9f)	//沈む深さ
#define P_SINK_ADD		(0.1f)	//沈んでいく量
#define P_SCALE_WAIT	(60)	//拡大時間　それ以降すぎるとその大きさで固まる
#define P_FLAT_RATE		(0.1f)	//薄さ
#define P_FLAT_ADD		(0.2f)	//平たくする量
#define P_MAX_RAD		(30.0f / 180.0f * M_PI)		//行動範囲角度
#define P_DEAD_ACT_TIME	(120)	//死亡アクション時間
#define P_FLASH_COL_TIME (20)	//点滅間隔（ディフューズ遷移）
#define P_FLASH_TEX_TIME (10)	//点滅（テクスチャ切り替え）
#define P_FIELD_MAX		(97.0f)	//移動範囲(半径)

//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PLAYER::PLAYER()
{
	m_pInput = INPUT_MNG::getInstance();
	p_ShadeMng = SHADER_MNG::Instance();
	m_pCamera   = CAMERA::Instance();
	m_pCube = new CUBEMAP();
	m_EnemyMng = ENEMYMNG::Instance();
	m_Mesh = NULL;
	m_Mesh = new MESH;

	m_pSE = SOUND::Instance();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PLAYER::~PLAYER()
{
	Release();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Init(void){
	m_TexID = 0;		//テクスチャID
	Load(); 
		
	MatrixIdentity(&m_Matrix);	//変換マトリックス
	Vec3Identity(&m_Pos);		//位置座標
	Vec3Identity(&m_PosPrev);	//位置座標前
	Reset();
	//位置座標
	Vec3Identity(&m_Pos);	
	m_Pos.y =1.0f;
	//移動方向
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_vec.z = 1.0f;
	m_vecPrev = m_vec;	
	//移動速度
	VecScale(&m_vecS, 0.0f);
	//角度
	m_Rad = 0.0f;
	//死亡回数
	m_DeadNum = 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Reset(void)
{
	m_State = P_NORMAL;			//状態
	m_Live = true;				//生存
	m_Life = P_LIFE;			//体力
	m_Attack = P_ATTACK;
	m_DeadNum =0;
	m_bAtkFlg = false;

	//拡大率
	m_ScaleRate = 1.0f;		//全体拡大率
	m_ScaleFlg = 1;			//拡縮フラグ
	m_InEnemyFlg = 0;		//敵が範囲内にいるかどうかのフラグ
	m_Width = 0.0f;			//幅
	m_Scale = VECTOR3(1.0f, 1.0f, 1.0f);
	m_ScaleWaitTime = 0;
	//変形アクション用
	m_nDirect = 0;			//変形方向
	m_nCntFrame = 0;		//フレームカウンタ
	m_nStartTrans = false;	//トランスフォームスタート
	//沈みアクション
	m_nDct_Sink = 0;		//フラグ
	m_fSink		= 0.0f;		//高さ
	m_bSflg		= false;
	//平たくするアクション
	m_bFflg = false;
	m_nDct_Flat = 0;
	//死亡アクション
	m_nDeadActFrame = 0;
	m_nFrameCnt = 0;
	m_nFrashTimeCnt = 0;
	m_x = 0.0f;
	m_nColDIrect = 0;
	//プレイヤーのリトライフラグ
	m_bRetry = false;
	//テクスチャ切り替え
	m_TexFrashDirect = 0;
	m_nTexFrashCnt = 0;
	//ダメージ受け
	m_bDamage = false;
	m_Accel = VECTOR3();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Load(void)
{
	//テクスチャの読み込み
	m_TexNormal = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring.png", "PLAYER");	//通常テクスチャ
	m_TexRed = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring0.png", "PLAYER");	//通常テクスチャ
	m_TexID = m_TexNormal;
	//キューブマップ初期化
	//m_CubeTexID = m_pCube->InitCubeMap();

	//メッシュの読み込み
	g_MeshMng.GetMesh(&m_MeshA, "MODEL\\PLAYER\\ring.x", _T("PLAYER"));	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshB, "MODEL\\PLAYER\\player2.x", _T("PLAYER"));	//メッシュ読み込み
	g_MeshMng.GetMesh(&m_MeshC, "MODEL\\PLAYER\\player3.x", _T("PLAYER"));	//メッシュ読み込み

	SetMorph(m_Mesh, m_MeshA);	
	CpyVertex(m_Mesh, m_MeshA);		//頂点データをとりあえずコピー
	//カラーを一時保存
	m_col.r = m_Mesh->pMaterial->Diffuse.x;
	m_col.g = m_Mesh->pMaterial->Diffuse.y;
	m_col.b = m_Mesh->pMaterial->Diffuse.z;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//解放
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Release(void)
{
	//ReleaseMesh(m_Mesh);
	g_MeshMng.ReleaseCat("PLAYER");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Update(VECTOR3 vecx, VECTOR3 vecy)
{
	VECTOR3 vec, vecX, vecY;
	
	//モデルの現在幅を求める
	m_Width = m_Mesh->fRadius * m_ScaleRate;

	//生きている時移動可能
	if(m_Live)
	{
		//プレイヤー移動処理
		if(m_pInput->GetBtnState(BTN_LEFT))	//左
			vecX = vecx * -m_pInput->GetAxis(BTN_LEFT);
		if(m_pInput->GetBtnState(BTN_RIGHT))//右
			vecX = vecx * -m_pInput->GetAxis(BTN_RIGHT);
		if(m_pInput->GetBtnState(BTN_UP))	//上
			vecY = vecy * -m_pInput->GetAxis(BTN_UP);
		if(m_pInput->GetBtnState(BTN_DOWN))	//下
			vecY = vecy * -m_pInput->GetAxis(BTN_DOWN);
	}
	//スピード加算
	m_Accel += (vecX + vecY) * P_SPEED;

	vec += m_Accel;

	m_Accel *= 0.95f;
	//移動方向に敵がいないかチェック
	//if(!m_bAtkFlg)
	//	CheckVec(&vec);

	//範囲補正
	if(vec.x != 0.0f || vec.y != 0.0f || vec.z != 0.0f)
		CheckField(&vec);

	//状態遷移
	switch(m_State)
	{
	case P_WAIT:
		//１度アクションすると次のアクションがしばらくできなくなる
		if(++m_WaitTime < 60){
			Move(vec);
		}else{
			m_State = P_NORMAL;
			m_WaitTime = 0;
		}
		break;
	case P_NORMAL:
		////もし死んでたら
		if(!m_Live){
			m_State = P_ATC_DEAD;
			break;
		}
		//もし攻撃を受けていたら
		if(m_bDamage)
		{
			m_State = P_DAMEGE_ACT;
			break;
		}

		//移動
		Move(vec);
		//拡縮開始
		if((m_pInput->GetBtnState(BTN_A) == TRG || m_pInput->GetBtnState(BTN_A) == PRESS )
			&& (m_pInput->GetBtnState(BTN_R1) != PRESS))
		{
			m_State = P_ATC_SCALE;
			m_bAtkFlg = true;
		}
		
		//変形アクション
		if((m_pInput->GetBtnState(BTN_A) == TRG || m_pInput->GetBtnState(BTN_A) == PRESS)
			&& (m_pInput->GetBtnState(BTN_R1) == PRESS))
			m_State = P_ATC_TRANSFORM;
		break;
	case P_ATC_SCALE:
		//---------------------------
		// 拡縮アクション
		//---------------------------
		ScaleAct();

		//平たくする
		if(m_Scale.y > P_FLAT_RATE){
			m_Scale.y -= P_FLAT_ADD;
			Move(vec);
		}else
			m_Scale.y = P_FLAT_RATE;
		
		//沈む 
		if(m_fSink < P_SINK_RATE){
			m_fSink += P_SINK_ADD;
		}else
			m_fSink = P_SINK_RATE;

		//拡大停止時間
		/*if(++m_ScaleWaitTime < P_SCALE_WAIT)
		{*/
			//拡縮終了
			if(m_pInput->GetBtnState(BTN_A) == RLS || m_pInput->GetBtnState(BTN_A) == NONE)
			{
				if(m_InEnemyFlg)				//輪の中に敵が入っている時
				{
					m_pSE->PlaySE(SE_ATTACK);
					m_State = P_ENEMY_IN_COLLECT;
				}
				else
					m_State = P_NORMAL_COLLECT;	//通常サイズへ戻す
				m_ScaleWaitTime = 0;
				m_bSflg = false; 
				m_bFflg = false;
			}
		//}else
		//{	
		//	if(m_InEnemyFlg)				//輪の中に敵が入っている時
		//	{
		//		m_State = P_ENEMY_IN_COLLECT;
		//	}else
		//		m_State = P_NORMAL_FLAT;	//通常サイズへ戻さない

		//	m_bSflg = false; 
		//	m_bFflg = false;
		//	m_ScaleWaitTime = 0;
		//}
		//沈む処理
		
		break;

	case P_ATC_TRANSFORM:
		//---------------------------
		// 変形アクション
		//---------------------------
		ScaleAct();
		//拡縮終了
		if(m_pInput->GetBtnState(BTN_A) == RLS || m_pInput->GetBtnState(BTN_A) == NONE)
		{
			m_nStartTrans = true;
		}
		
		if(m_nStartTrans)
		{
			if(TransformAct()){
				if(m_InEnemyFlg)				//輪の中に敵が入っている時
				{
					m_State = P_ENEMY_IN_COLLECT;
				}else
					m_State = P_NORMAL_COLLECT;	//通常サイズへ戻す
				m_bSflg = false;	
				m_bFflg = false;
				m_nStartTrans = false;
			}
		}
		////元の厚さに戻す
		//if(m_Scale.y < m_Scale.x){
		//	m_Scale.y += P_FLAT_ADD;
		//}else
		//	m_Scale.y = m_Scale.x;

		////元の高さに戻す
		//if(m_fSink > 0){
		//	m_fSink -= P_SINK_ADD;
		//}else
		//	m_fSink = 0;
		break;
	case P_ENEMY_IN_COLLECT:
		//元の高さに戻す
		if(m_fSink > 0){
			m_fSink -= P_SINK_ADD;
		}else
			m_fSink = 0;

		//元の厚さに戻す
		if(m_Scale.y < m_Scale.x){
			m_Scale.y += P_FLAT_ADD;
		}else
			m_Scale.y = m_Scale.x;
	
		if(ScaleAttack())
		{
			m_InEnemyFlg = false;
			m_bFflg = false;
			if(m_Scale.y >= m_Scale.x && m_Pos.y >= 0.5f)
				m_State = P_NORMAL_COLLECT;	//通常サイズへ戻す
		}
		break; 
	case P_NORMAL_COLLECT:		//通常サイズへ戻す	敵が範囲外であるとき
		//元の高さに戻す
		if(m_fSink > 0){
			m_fSink -= P_SINK_ADD;
		}else
			m_fSink = 0;

		//元の厚さに戻す
		if(m_Scale.y < m_Scale.x){
			m_Scale.y += P_FLAT_ADD;
		}else
		{	
			m_Scale.y = m_Scale.x;
		}
		if(ScaleActCollect()){
			if(m_Pos.y >= 0.5f)
			{
				m_State = P_NORMAL;
				m_bAtkFlg = false;
			}
		}

		break;
	//case P_NORMAL_FLAT:
	//	//元の高さに戻す
	//	if(m_fSink > 0){
	//		m_fSink -= P_SINK_ADD;
	//	}else
	//		m_fSink = 0;

	//	//元の厚さに戻す
	//	if(m_Scale.y < m_Scale.x){
	//		m_Scale.y += P_FLAT_ADD;
	//	}else{
	//		m_Scale.y = m_Scale.x;
	//		
	//		if(m_Pos.y >= 0.5f && m_fSink == 0){
	//			m_State = P_NORMAL;
	//		}
	//	}
	
	case P_ATC_DEAD:	//死亡アクション
		if(++m_nFrameCnt < P_DEAD_ACT_TIME)
		{
			TexFrash();
			//DeadAct();
		}else{
			//SetDiffuse(m_Mesh, m_col);
			
			m_TexID = m_TexNormal;
			m_bRetry = true;
			m_DeadNum ++;
		}
		break;
	default: break;
	}

	//生存判定を行う
	JudgLife();

}

//++++++++++++++++++++++++++++++++++++++++++++++++
// フィールド内にいるかどうかのチェック
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::CheckField(VECTOR3 *vec)
{
	VECTOR3 posV, vecV;		//
	VECTOR3 vecX, vecZ;	//ベクトルの成分分け	
	VECTOR3 crsPV, vNorm;
	float	rad = 0;

	if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
	{
		//単位ベクトルへ
		Vec3Normalize(&posV, m_Pos);	//①位置
		Vec3Normalize(&vecV, *vec);		//②次のベクトル

		//今の中心からの位置でのベクトルの直角ベクトルを求める
		Vec3Cross(&crsPV, posV, VECTOR3(0.0f, 1.0f, 0.0f));

		//現在移動しようとしてるベクトルと円の接線ベクトルとの内積から角度を求める
		rad = Vec3Dot(*vec, crsPV);
		if(crsPV.y > 0)
		{
			//ベクトル成分を分解する
			vecX = *vec * cos(rad);
			vecZ = *vec * sin(rad);
		//X成分のみ
		*vec = vecZ;
		}else if(crsPV.y < 0)
		{
			//ベクトル成分を分解する
			vecX = *vec * cos(- rad);
			vecZ = *vec * sin(- rad);
		//X成分のみ
		*vec = vecZ;
		}

		//もしそれでも範囲外になるようなら補正
		if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
		{
			Vec3Normalize(&vNorm, m_Pos + *vec);
			*vec -= vNorm * (VecLength(m_Pos + *vec) - P_FIELD_MAX);
			vec->y = 0.0f;
		}
	}
	
	//float fR = VecLength(m_Pos);
	//VECTOR3	posV, vecV, crsPV, veccrs;
	//MATRIX  mat;
	//VECTOR3 vecWorld;
	//m_pCamera->GetMatrixInv(&mat);
	//Vec3TransformCoord(&vecWorld, mat, *vec);
	//vecWorld.y = 0.0f;
	//if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
	//{
	//	//単位ベクトルへ
	//	Vec3Normalize(&posV, m_Pos);	//①位置
	//	Vec3Normalize(&vecV, vecWorld);		//②次のベクトル

	//	//今の中心からの位置でのベクトルの直角ベクトルを求める
	//	Vec3Cross(&crsPV, posV, VECTOR3(0.0f, 1.0f, 0.0f));

	//	//①と②のベクトルの外積から右側か左側かを調べる
	//	Vec3Cross(&veccrs, posV, vecWorld);

	//	//右側の時
	//	if(veccrs.y > 0)
	//	{	
	//		VECTOR3 tmp;
	//		Vec3Normalize(&crsPV, crsPV);
	//		tmp = vecV * Vec3Dot(vecV, crsPV);
	//		tmp = crsPV - tmp;
	//		Vec3TransformCoord(vec, m_pCamera->m_CameraMat, vecWorld);
	//	}
	//	//左側の時
	//	else if(veccrs.y < 0)
	//	{	
	//		VECTOR3 tmp1;
	//		Vec3Normalize(&crsPV, crsPV);
	//		tmp1 = vecV * Vec3Dot(vecV, crsPV);
	//		tmp1 = crsPV  - tmp1;
	//		Vec3TransformCoord(vec, m_pCamera->m_CameraMat, vecWorld);

	//	}
	//	//平行または逆向き
	//	else
	//	{
	//		//処理しない
	//		*vec = VECTOR3(0.0f, 0.0f, 0.0f);
	//	}
	//}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ダメージを受けた時の点滅処理
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::TexFrash(void)
{
	switch(m_TexFrashDirect)
	{
	case 0:
		if(++m_nTexFrashCnt > P_FLASH_TEX_TIME){
			m_TexID = m_TexRed;
			m_TexFrashDirect = 1;
		}
		break;
	case 1:
		if(--m_nTexFrashCnt < 0){
			m_TexID = m_TexNormal;
			m_TexFrashDirect = 0;
		}
		break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ダメージを受けた時の点滅処理
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DeadAct(void)
{
	COLOR colChenge = {1.0f, 0.0f, 0.0f, 1.0f};

	//色を置き換え
	switch(m_nColDIrect)
	{
	case 0:
		if(++m_nFrashTimeCnt < P_FLASH_COL_TIME)
			FlashDiffuse(m_Mesh, m_col, colChenge, P_FLASH_COL_TIME, m_nFrashTimeCnt);
		else
			m_nColDIrect = 1;
		break;
	case 1:
		if(--m_nFrashTimeCnt < 0)
			m_nColDIrect = 0;
		else			
			FlashDiffuse(m_Mesh, m_col, colChenge, P_FLASH_COL_TIME, m_nFrashTimeCnt);
		break;
	default:break;
	}


	////微振動
	//switch(m_nDirectDeadAct)
	//{
	//case 0:
	//	m_x += 0.2f;
	//	if(m_x > 0.3f)
	//		m_nDirectDeadAct = 1;

	//	break;
	//case 1:
	//	m_x -= 0.2f;
	//	if(m_x < -0.3f)
	//		m_nDirectDeadAct = 0;
	//	break;
	//}
	
	

}
//++++++++++++++++++++++++++++++++++++++++++++++++
// 敵とぶつかってた時の移動方向の修正
//--in--------------------------------------------
// 現在ベクトル
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::CheckVec(VECTOR3 *vec)
{
	VECTOR3	vecEnemy;	//敵へのベクトル
	VECTOR3 vecCross;
	VECTOR3 vecCpy;
	VECTOR3	vecMix;		//合成
	float   fRad;

	//ベクトルが更新されているかどうか
	if(VecLength(*vec) != 0)
		Vec3Normalize(&vecCpy, *vec);
	else
		return false;

	//通常敵
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		//死んでる敵は飛ばす
		if(!m_EnemyMng->m_pEnemy[i]->m_Live)
			continue;
		
		//ぶつかっている敵をチェック
		if((VecLength(this->m_Pos - m_EnemyMng->m_pEnemy[i]->m_Pos) < m_EnemyMng->m_pEnemy[i]->m_Width * 0.5f + this->m_Width * 0.5f))	//外側の縁
		{
			//①敵とプレイヤーのベクトル
			vecEnemy = m_EnemyMng->m_pEnemy[i]->m_Pos - this->m_Pos;
			//ベクトルの正規化
			Vec3Normalize(&vecEnemy, vecEnemy);
			
			//ベクトルが平行
			if(((vecCpy.x * vecEnemy.y - vecCpy.y * vecEnemy.x) * (vecCpy.x * vecEnemy.y - vecCpy.y * vecEnemy.x)) + ((vecCpy.y * vecEnemy.z - vecCpy.z * vecEnemy.y)* (vecCpy.y * vecEnemy.z - vecCpy.z * vecEnemy.y)) + ((vecCpy.z * vecEnemy.x - vecCpy.x * vecEnemy.z) * (vecCpy.z * vecEnemy.x - vecCpy.x * vecEnemy.z))  == 0)
			{
				*vec = VECTOR3(0.0f, 0.0f, 0.0f);	//移動しない
				continue;
			}	
			//①と②の外積から右側か左側かを見る。
			Vec3Cross(&vecCross, vecCpy, vecEnemy);

			//②現在の向きと①のベクトルのなす角が設定角度より大きかったらそのまま今のベクトル
			if(vecCross.y == 0.0f)	//ベクトルが平行
				*vec = VECTOR3(0.0f, 0.0f, 0.0f);	//移動しない

			//内積から行動可能範囲内かどうかを調べる
			fRad = Vec3Dot(vecCpy, vecEnemy);
			/*if(fRad > 0.0f)
				*vec =  VECTOR3(0.0f, 0.0f, 0.0f);*/
			if(vecCross.y > 0.0f)	//移動方向が左より
			{
				if(fRad < P_MAX_RAD)
				{	//②でベクトルが設定角度内になっていたら、新しいベクトルを設定
					vecMix = (vecEnemy * -1) + vecCpy + vecCpy;
					vecMix.y = 0.0f;
					*vec = vecMix ; 
				}

			}
			if(vecCross.y < 0.0f)	//移動方向が右より
			{
				if(fRad > -P_MAX_RAD)
				{	//②でベクトルが設定角度内になっていたら、新しいベクトルを設定
					vecMix = (vecEnemy * -1) + vecCpy + vecCpy;
					vecMix.y = 0.0f;
					*vec = vecMix ; 
				}
			}
		}
		else
		{
		
		}

	}
	return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//プレイヤーアクション
// リング変形アクション
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::TransformAct(void)
{
	switch(m_nDirect)
	{
	case 0:
		if(++m_nCntFrame > P_TRANCEFORM_TIME)			//リングから半円形に
		{
			m_nDirect = 1; 
			m_nCntFrame = 0;
			break;
		}
		Morphing(m_Mesh, m_MeshA, m_MeshB, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 1:
		if(++m_nCntFrame > P_TRANCEFORM_TIME)			//半円形から球
		{
			m_nDirect = 2;	
			m_nCntFrame = P_TRANCEFORM_TIME;
			break;
		}
		Morphing(m_Mesh, m_MeshB, m_MeshC, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 2:
		if(--m_nCntFrame < 0)	//半円形から球
		{
			m_nDirect = 3; 
			m_nCntFrame = P_TRANCEFORM_TIME;
			break;
		}
		Morphing(m_Mesh, m_MeshB, m_MeshC, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 3:
		if(--m_nCntFrame < 0)	//半円形から球
		{
			m_nDirect = 0;
			m_nCntFrame = 0;
			//Morphing(m_Mesh, m_MeshA, m_MeshB, 0, 0, P_TRANCEFORM_TIME);
			return true;
		}
		Morphing(m_Mesh, m_MeshA, m_MeshB,m_nCntFrame, 0, P_TRANCEFORM_TIME);
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//プレイヤーアクション
// プレイヤーのアクションを管理
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Act(int State)
{
	m_State = State;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//拡大
// プレイヤーの拡大縮小
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::ScaleAct(void)
{
	float fScale = 0.0f;
	//拡縮
	m_ScaleRate += P_SCALE * m_ScaleFlg;
	
	if(m_ScaleRate < P_SCALE_MIN)
	{
		m_ScaleRate = P_SCALE_MIN;
		m_ScaleFlg ^= -1;
	}
	if(m_ScaleRate > P_SCALE_MAX)
	{
		m_ScaleRate = P_SCALE_MAX;
		//m_ScaleFlg ^= -1;
	}

	m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
	m_Scale.z = m_ScaleRate;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//拡縮
// プレイヤーの拡大縮小サイズを元のサイズに戻す
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::ScaleActCollect(void)
{
	unsigned int tmp;
	tmp = unsigned int(m_ScaleRate * 100);
	//拡縮が通常時でないとき
	if(!(tmp > 80 && tmp < 120))
	{
		if(tmp < 100){
			m_ScaleRate += (P_SCALE * 0.2f);
		}
		else{
			m_ScaleRate -= (P_SCALE);
		}

		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return false;
	}else{
		m_ScaleRate = 1.0f;
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return true;
	}
}//++++++++++++++++++++++++++++++++++++++++++++++++
//拡縮
// プレイヤーの拡大縮小サイズを元のサイズに戻す
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::ScaleAttack(void)
{
	//縮小
	if((m_ScaleRate * 100) > 5)
	{
		m_ScaleRate -= (P_SCALE * 2.0f);
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return false;
	}else{
		m_ScaleRate = 0.05f;
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return true;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Draw(void)
{
	////アタリ判定用球の出力準備
	//GLUquadricObj *pSphere;		//オブジェクトポインタを準備
	//pSphere = gluNewQuadric();	//オブジェクトの生成
	//gluQuadricDrawStyle(pSphere, GLU_FILL);	//オブジェクトの描画タイプを設定

	//実態描画
	glPushMatrix();	

	//プレイヤーアクション
	glTranslatef((GLfloat)m_x, (GLfloat)0.0f, (GLfloat)0.0f);	
	glTranslatef((GLfloat)0.0f, (GLfloat)-m_fSink, (GLfloat)0.0f);	
	glTranslatef((GLfloat)m_Pos.x, (GLfloat)m_Pos.y, (GLfloat)m_Pos.z);	
	glRotatef(((GLfloat)m_Rad * 180 / M_PI), (GLfloat)0, (GLfloat)1.0f , (GLfloat)0);	//Y軸回転
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);
	//glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	glEnable(GL_DEPTH_TEST);
	//マトリックスの合成
	//MATRIX mat1, mat2, mat3;
	//MatrixTranslation(&mat1, m_Pos.x, m_Pos.y, m_Pos.z);
	//MatrixRotationY(&mat2, (GLfloat)(m_Rad));
	//MatrixScaling(&mat3, m_Scale.x, m_Scale.y, m_Scale.z);
	////MatrixScaling(&mat3, m_ScaleRate, m_ScaleRate, m_ScaleRate);
	//MatrixMultiply(&mat1, mat1, mat2);
	//MatrixMultiply(&m_Matrix, mat3, mat1);


	//	DrawMesh(m_Mesh[1]);

	//GLint prm;
	//glGetIntegerv(GL_MAX_TEXTURE_UNITS, &prm);

	//シェーダの適用
	p_ShadeMng->UseShader(COOK);
	//描画
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	p_ShadeMng->SetAlpha(COOK,1.0f);		//透過なし

	//生存してたら描画
	
	// テクスチャユニットを指定する
	p_ShadeMng->SetTexUnit(COOK, 0);	//ノーマルテクスチャ
	DrawMesh(m_Mesh);
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	p_ShadeMng->UnUseShader();

	//設定を元に戻す
	glEnable(GL_ALPHA_TEST);	//αテスト無効化
	glDisable(GL_BLEND);		//
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画(環境マップ)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DrawCube(void)
{
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScaled(-1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexID);

	/* テクスチャ環境 */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	/* キューブマッピングを有効にする */
	glEnable(GL_TEXTURE_CUBE_MAP);
	//テクスチャ座標を自動生成する
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	//描画
	glPushMatrix();	

	//プレイヤーアクション
	glTranslatef((GLfloat)m_Pos.x + m_x, (GLfloat)m_Pos.y + m_fSink, (GLfloat)m_Pos.z);	
	glRotatef(((GLfloat)m_Rad * 180 / M_PI), (GLfloat)0, (GLfloat)1.0f , (GLfloat)0);	//Y軸回転
	glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	glEnable(GL_DEPTH_TEST);
	//マトリックスの合成
	MATRIX mat1, mat2, mat3;
	m_Pos.y = 0.5f;
	MatrixTranslation(&mat1, m_Pos.x, m_Pos.y, m_Pos.z);
	MatrixRotationY(&mat2, (GLfloat)(m_Rad));
	MatrixScaling(&mat3, m_ScaleRate, m_ScaleRate, m_ScaleRate);
	MatrixMultiply(&mat1, mat1, mat2);
	MatrixMultiply(&m_Matrix, mat3, mat1);


	//	DrawMesh(m_Mesh[1]);

	//GLint prm;
	//glGetIntegerv(GL_MAX_TEXTURE_UNITS, &prm);

	////シェーダの適用
	p_ShadeMng->UseShader(REFLECT);
	p_ShadeMng->SetCamPos(REFLECT, m_pCamera->ViewPos);
	////描画
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexID);

	//生存してたら描画
	if(m_Live)
	{
		// テクスチャユニットを指定する
		//p_ShadeMng->SetTexUnit(PHONG, 0);	//ノーマルテクスチャ
		DrawMesh(m_Mesh);
	}
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	//p_ShadeMng->UnUseShader();

	//設定を元に戻す
	glEnable(GL_ALPHA_TEST);	//αテスト無効化
	glDisable(GL_BLEND);		//
	//
	//テクスチャ座標の自動生成を無効にする
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	/* テクスチャマッピング終了 */
	glDisable(GL_TEXTURE_CUBE_MAP);

	/* テクスチャ変換行列の設定 */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//キューブマップ描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DrawCubeMap(void)
{
	if(m_pCube)
		m_pCube->MakeCubeMap(m_Pos);
}

//################################################
// End of File
//################################################
