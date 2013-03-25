//################################################
// <Opening.h>
//
//------------------------------------------------
// 2013/01/14 ~
//						SekiyamaRumi
//################################################

//================================================
//インクルードヘッダ
//================================================
#include "Opening.h"
#include "TexMng.h"		//テクスチャマネージャ
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
//フェード
#define OP_FADE_POS_X (-10)			//フェード板ポリ初期位置
#define OP_FADE_POS_Y (-10)
#define OP_FADE_H (20)				//フェード板ポリ縦幅
#define OP_FADE_W (20)				//　　　　　　　横幅
//ロゴ
#define OP_LOGO_POS_X (-3.0f)		//ロゴ板ポリ初期位置
#define OP_LOGO_POS_Y (-3.0f)
#define OP_LOGO_H (6)				//ロゴ板ポリ	縦幅
#define OP_LOGO_W (7)				//　　　　　s　　横幅
//タイトル
#define OP_TITLE_POS_X (-5)			//タイトル板ポリ初期位置
#define OP_TITLE_POS_Y (-5)
#define OP_TITLE_H (10)				//タイトル板ポリ縦幅
#define OP_TITLE_W (10)				//　　　　　　　横幅
#define OP_TITLE_SCALE_MAX	(1.5f)	//タイトルの拡大率最大値
#define OP_ADD_TILE_SCALE	(OP_TITLE_SCALE_MAX * 0.03f)	//タイトルの拡大率の増減値
//BG
#define OP_BG_H (40)				//フェード板ポリ縦幅
#define OP_BG_W (40)				//　　　　　　　横幅
#define OP_BG_POS_X (-OP_BG_H / 2.0f)	//フェード板ポリ初期位置
#define OP_BG_POS_Y (OP_BG_POS_X)
//PUSH ENTER用ボタン
#define OP_PUSHENTER_H (1)				//PushEnter板ポリ縦幅
#define OP_PUSHENTER_W (3)				//　　　　　　　横幅
#define OP_PUSHENTER_POS_X (-OP_PUSHENTER_W / 2.0f)	//PushEnter板ポリ初期位置
#define OP_PUSHENTER_POS_Y (OP_PUSHENTER_POS_X)


//フェード時間
#define OP_FADE_TIME	(120)		//フェードタイム

//待ち時間
#define OP_WAIT_TIME    (180)		//ウェイト

//リング
#define OP_ADD_RING_SPEED (0.2f)		//リング加算スピード
#define OP_MINUS_RING_SPEED (0.1f)		//リング減算スピード
#define OP_RING_SCALE	(0.3f)			//リング拡縮率スピード
#define OP_RING_JUMP	(0.10f)			//リングジャンプ
#define OP_RING_SCALE_MAX (10.0f)		//拡縮率マックス
#define OP_TITLE_OUT	(20.0f)			//画面外判定
//タイトル
#define OP_TITLE_H_MAX (3.0f)			//タイトルの飛び出し分の高さの最大値
#define OP_ADD_H_TITLE (0.05f)			//タイトルの高さの加算値

//状態遷移
enum {
	LOGO,			//ロゴ
	TITLE,			//タイトル
	PUSH_ENTER,		//プッシュエンター
	OUT_TITLE		//タイトルが掃ける
};
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
OP::OP(){}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
OP::~OP(){}

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Init(void)
{
	m_pShadeMng = SHADER_MNG::Instance();
	m_pSE = SOUND::Instance();
	m_TexID = g_TexMng.GetTexture("TEXTURE\\OP\\Op.png", "OP");
	m_TexIDM = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring.png", "PLAYER");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\OP\\title.png", "PLAYER");
	m_TexIDB = g_TexMng.GetTexture("TEXTURE\\OP\\bg.png", "OP");

	g_MeshMng.GetMesh(&m_MeshR, "MODEL\\PLAYER\\ring.x", "PLAYER");
	g_MeshMng.GetMesh(&m_MeshT, "MODEL\\OP\\title.x", "PLAYER");
	g_MeshMng.GetMesh(&m_MeshD, "MODEL\\OP\\Deco.x","OP"); 
	m_pInput = INPUT_MNG::getInstance();	//インスタンスの取得
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Reset(void)
{
	m_nState = LOGO;
	m_nInState = 0;
	m_nRingState = 0;
	m_nCnt = 0;
	m_bFlgPushStart = false;

	//タイトル
	m_Titlpos = VECTOR3(0.0f, 2.0f, 0.0f);
	m_TAng = -20.0f;
	m_TScl = 0.001f;
	//リング
	m_Ringpos.x = -20.0f;
	m_Ringpos.y =  0.0f;
	m_Ringpos.z =  0.0f;
	m_RAng = 0.0f;
	m_RScl = 1.0f;
	m_RJump = OP_RING_JUMP;	//リングジャンプ
	m_RbDraw = false;		//描画フラグ

	//頂点セット
	SetPoli();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::SetPoli(void)
{
	//------------------------
	//頂点のセット
	//------------------------
	//フェード用
	m_PFade.ver[0].x = OP_FADE_POS_X;
	m_PFade.ver[0].y = OP_FADE_POS_Y + OP_FADE_H;
	m_PFade.ver[0].z = -1.0f;

	m_PFade.ver[1].x = OP_FADE_POS_X;
	m_PFade.ver[1].y = OP_FADE_POS_Y;
	m_PFade.ver[1].z = -1.0f;

	m_PFade.ver[2].x = OP_FADE_POS_X + OP_FADE_W;
	m_PFade.ver[2].y = OP_FADE_POS_Y ;
	m_PFade.ver[2].z = -1.0f;

	m_PFade.ver[3].x = OP_FADE_POS_X + OP_FADE_W;
	m_PFade.ver[3].y = OP_FADE_POS_Y + OP_FADE_H;
	m_PFade.ver[3].z = -1.0f;

	//ロゴ用
	m_PLogo.ver[0].x = OP_LOGO_POS_X;
	m_PLogo.ver[0].y = OP_LOGO_POS_Y + OP_LOGO_H;
	m_PLogo.ver[0].z = 0.0f;

	m_PLogo.ver[1].x = OP_LOGO_POS_X;
	m_PLogo.ver[1].y = OP_LOGO_POS_Y;
	m_PLogo.ver[1].z = 0.0f;

	m_PLogo.ver[2].x = OP_LOGO_POS_X + OP_LOGO_W;
	m_PLogo.ver[2].y = OP_LOGO_POS_Y;
	m_PLogo.ver[2].z = 0.0f;

	m_PLogo.ver[3].x = OP_LOGO_POS_X + OP_LOGO_W;
	m_PLogo.ver[3].y = OP_LOGO_POS_Y + OP_LOGO_H;
	m_PLogo.ver[3].z = 0.0f;


	//BG用
	m_PBg.ver[0].x = OP_BG_POS_X;
	m_PBg.ver[0].y = OP_BG_POS_Y + OP_BG_H;
	m_PBg.ver[0].z = 0.0f;

	m_PBg.ver[1].x = OP_BG_POS_X;
	m_PBg.ver[1].y = OP_BG_POS_Y;
	m_PBg.ver[1].z = 0.0f;

	m_PBg.ver[2].x = OP_BG_POS_X + OP_BG_W;
	m_PBg.ver[2].y = OP_BG_POS_Y;
	m_PBg.ver[2].z = 0.0f;

	m_PBg.ver[3].x = OP_BG_POS_X + OP_BG_W;
	m_PBg.ver[3].y = OP_BG_POS_Y + OP_BG_H;
	m_PBg.ver[3].z = 0.0f;

	//PUSH START用ボタン
	m_PPushEnter.ver[0].x = OP_PUSHENTER_POS_X;
	m_PPushEnter.ver[0].y = OP_PUSHENTER_POS_Y + OP_PUSHENTER_H;
	m_PPushEnter.ver[0].z = 0.0f;

	m_PPushEnter.ver[1].x = OP_PUSHENTER_POS_X;
	m_PPushEnter.ver[1].y = OP_PUSHENTER_POS_Y;
	m_PPushEnter.ver[1].z = 0.0f;

	m_PPushEnter.ver[2].x = OP_PUSHENTER_POS_X + OP_PUSHENTER_W;
	m_PPushEnter.ver[2].y = OP_PUSHENTER_POS_Y;
	m_PPushEnter.ver[2].z = 0.0f;

	m_PPushEnter.ver[3].x = OP_PUSHENTER_POS_X + OP_PUSHENTER_W;
	m_PPushEnter.ver[3].y = OP_PUSHENTER_POS_Y + OP_PUSHENTER_H;
	m_PPushEnter.ver[3].z = 0.0f;

	//------------------------
	//テクスチャのセット
	//------------------------
	//フェード用
	m_PFade.tex[0].x = 7.0f / 16.0f;
	m_PFade.tex[0].y = 1.0f - (6.0f / 16.0f);

	m_PFade.tex[1].x = 7.0f / 16.0f;
	m_PFade.tex[1].y = 1.0f - (5.0f / 16.0f);

	m_PFade.tex[2].x = 8.0f / 16.0f;
	m_PFade.tex[2].y = 1.0f - (5.0f / 16.0f);

	m_PFade.tex[3].x = 8.0f / 16.0f;
	m_PFade.tex[3].y = 1.0f - (6.0f / 16.0f);

	//ロゴ用
	m_PLogo.tex[0].x = 0.0f;
	m_PLogo.tex[0].y = 1.0f - (10.0f / 16.0f);

	m_PLogo.tex[1].x = 0.0f;
	m_PLogo.tex[1].y = 1.0f - (4.0f / 16.0f);

	m_PLogo.tex[2].x = 7.0f / 16.0f;
	m_PLogo.tex[2].y = 1.0f - (4.0f / 16.0f);

	m_PLogo.tex[3].x = 7.0f / 16.0f;
	m_PLogo.tex[3].y = 1.0f - (10.0f / 16.0f);

	//BG用
	m_PBg.tex[0].x = 0.0f;
	m_PBg.tex[0].y = 1.0f;

	m_PBg.tex[1].x = 0.0f;
	m_PBg.tex[1].y = 0.0f;

	m_PBg.tex[2].x = 1.0f;
	m_PBg.tex[2].y = 0.0f;

	m_PBg.tex[3].x = 1.0f;
	m_PBg.tex[3].y = 1.0f;


	//PUSH START用ボタン
	m_PPushEnter.tex[0].x = 0.0f;
	m_PPushEnter.tex[0].y = 1.0f - (12.0f / 16.0f);

	m_PPushEnter.tex[1].x = 0.0f;
	m_PPushEnter.tex[1].y = 1.0f - (10.0f / 16.0f);

	m_PPushEnter.tex[2].x = 6.0f / 16.0f;
	m_PPushEnter.tex[2].y = 1.0f - (10.0f / 16.0f);

	m_PPushEnter.tex[3].x = 6.0f / 16.0f;
	m_PPushEnter.tex[3].y = 1.0f - (12.0f / 16.0f);

	//------------------------
	//カラー
	//------------------------
	//フェード用
	m_PFade.col.r = 0.0f;
	m_PFade.col.g = 0.0f;
	m_PFade.col.b = 0.0f;
	m_PFade.col.a = 1.0f;	

	//ロゴ用
	m_PLogo.col.r = 1.0f;
	m_PLogo.col.g = 1.0f;
	m_PLogo.col.b = 1.0f;
	m_PLogo.col.a = 1.0f;

	//BG用
	m_PBg.col.r = 1.0f;
	m_PBg.col.g = 1.0f;
	m_PBg.col.b = 1.0f;
	m_PBg.col.a = 1.0f;	

	//PUSH START用ボタン
	m_PPushEnter.col.r = 1.0f;
	m_PPushEnter.col.g = 1.0f;
	m_PPushEnter.col.b = 1.0f;
	m_PPushEnter.col.a = 1.0f;	

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::Update(void)
{
	static int nCnt = -1;
	m_nCnt ++;	//フレームカウント
	//nCnt = m_nCnt;

	switch(m_nState)
	{
	case LOGO:	//（ロゴ表示済み）
		switch(m_nInState)
		{
		case 0:	
			//ウェイト
			if((m_nCnt - nCnt) > (OP_WAIT_TIME * 0.5f)){
				m_nInState = 1;
				nCnt = -1;	//初期化
			}
			break;
		case 1:		//フェードアウト
			if(FadeOut(&m_PFade))
			{
				m_nInState = 2;
				nCnt = m_nCnt;		//次のウェイト時の時間を計算
			}
			break;
		case 2:		//ウェイト
			if((m_nCnt - nCnt) > OP_WAIT_TIME){
				m_nInState = 3;
				nCnt = -1;	//初期化
			}
			break;
		case 3:		//フェードイン
			if(FadeIn(&m_PFade))
			{
				m_nInState = 0;
				m_nState = TITLE;		//タイトル出力へ
				m_RbDraw = true;		//描画開始
			}
			break;
		default: break;
		}
		break;
	case TITLE:
		//---------------------------------------------
		//①フェードイン
		//②左からリングが流れて真ん中で停止
		//③拡大値まで拡大(リング回転、軽く上下する)
		//④タイトルロゴが真ん中からにょきっと出てくる
		//---------------------------------------------
		switch(m_nInState)
		{
		case 0:		//①フェードイン
			if(FadeOut(&m_PFade))
				m_nInState = 1;
			break;
		case 1:		
		
			
			//②左からリングが流れて真ん中で停止
			switch(m_nRingState)
			{
			case 0:
				if(m_Ringpos.x < 3.0f)
				{
					m_Ringpos.x += OP_ADD_RING_SPEED;
				}
				else
				{
					m_pSE->PlaySE(BG_TITLE);
					m_nRingState = 1;	//次の状態へ
				}
				break;
			case 1:
				if(m_Ringpos.x > 0.0f)
				{
					m_Ringpos.x -= OP_MINUS_RING_SPEED;

					m_Ringpos.y += m_RJump;
					if(m_Ringpos.y >= 0.8f)
						m_RJump *= -1;
					if(m_Ringpos.y < 0)
						m_Ringpos.y = 0.0f;

				}else
				{
					m_nRingState = 2;	//次の状態へ
					m_Ringpos.y = 0.0f;
					m_Ringpos.x = 0.0f;
				}
				break;
			case 2:	
				//リング拡大
				if(m_RScl < OP_RING_SCALE_MAX)
					m_RScl += OP_RING_SCALE;
				if(m_RScl > OP_RING_SCALE_MAX)
				{
					m_RScl = OP_RING_SCALE_MAX;
					m_nRingState = 4;
				}

				//タイトル拡大
				if(m_TScl < OP_TITLE_SCALE_MAX)
					m_TScl += OP_ADD_TILE_SCALE;
				if(m_TScl > OP_TITLE_SCALE_MAX)
					m_TScl = OP_TITLE_SCALE_MAX;
				//タイトル飛び出し
				if(m_Titlpos.y < OP_TITLE_H_MAX)
					m_Titlpos.y += OP_ADD_H_TITLE;
				if(m_Titlpos.y > OP_TITLE_H_MAX)
				{
					m_Titlpos.y = OP_TITLE_H_MAX;
				}
				break;
			case 3:

				break;
			case 4: //縮小
				if(m_RScl > 1.0f)
					m_RScl -= OP_RING_SCALE;
				if(m_RScl < 1.0f)
				{
					m_RScl = 1.0f;
					m_nRingState = 5;
				}
			case 5:	//画面外へ流れる
				if(m_Ringpos.x < OP_TITLE_OUT)
					m_Ringpos.x += OP_ADD_RING_SPEED;
				if(m_Ringpos.x > OP_TITLE_OUT)
				{
					m_RbDraw = false;
					m_nInState = 0;
					nCnt = m_nCnt - 1;
					m_nState = PUSH_ENTER;
				}
				break;
			default: break;
			}
		break;
		default:break;
		}
		break;
	case PUSH_ENTER:
		//プッシュエンター　点滅
		int n;
		n = m_nCnt - nCnt;
		switch(n)
		{
		case 1:
			m_PPushEnter.col.a = 0.0f;
			break;
		case 30:
			m_PPushEnter.col.a = 1.0f;
			break;
		case 60:
			nCnt = m_nCnt;
			break;
		default:break;
		}

		//キー入力待ち
		if(m_pInput->GetBtnState(BTN_A) == TRG)
		{
			nCnt = -1;	
			m_nState = OUT_TITLE;
			m_pSE->PlaySE(BUTTON_ON);
		}
		break;
	case OUT_TITLE:
		//タイトル拡大
		if(m_TScl < OP_TITLE_SCALE_MAX * 4)
			m_TScl += OP_ADD_TILE_SCALE;
		if(m_TScl > OP_TITLE_SCALE_MAX * 4)
			m_TScl = OP_TITLE_SCALE_MAX * 4;
		//フェードアウト
		if(FadeIn(&m_PFade))
		{
			m_TScl = 1.0f;
			return true;
		}
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// 描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Draw(void)
{
	switch(m_nState)
	{
	case LOGO:
		DrawPoli(m_PLogo, 0, VECTOR3(0.0f, 0.0f, 0.0f),VECTOR3(0.0f, 0.0f, 0.0f), m_TexID, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	case TITLE:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	case PUSH_ENTER:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		DrawPoli(m_PPushEnter, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, -2.0f, 3.0f), m_TexID, true);
		break;
	case OUT_TITLE:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	default: break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン描画
//--in--------------------------------------------
//POLYGON3D　参照
//回転角
//回転軸
//位置
//テクスチャID
//ビルボードフラグ
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::DrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos,  int m_TexID, bool flg)
{
	GLdouble	matView[16];

	//初期処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
	glDepthMask(GL_FALSE);		//デプスバッファへの書き込み禁止

	//カラー指定
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//ポリゴン描画
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	//座標変換
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	if(flg)
	{
		//ビルボード変換
		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
		glLoadMatrixd(&matView[0]);
	}
	//ポリゴン描画
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//後処理
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Zバッファ無効化
	glDepthMask(GL_TRUE);		//デプスバッファへの書き込み許可
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


//++++++++++++++++++++++++++++++++++++++++++++++++
// モデル描画
//--in--------------------------------------------
//メッシュデータ　(参照)
//位置
//軸
//回転角度
//拡大率
//テクスチャID
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::DrawModel(void)
{
	//初期処理
	glEnable(GL_LIGHTING);		//ライトON
	glDisable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化

	//リングの描画
	if(m_RbDraw)
	{
		m_pShadeMng->UseShader(PHONG);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexIDM);
		glPushMatrix();
		glTranslatef(m_Ringpos.x, m_Ringpos.y, m_Ringpos.z);
		glRotatef((GLfloat)m_RAng, 0.0f, 1.0f, 0.0f);
		glScalef(m_RScl, m_RScl, m_RScl);
		m_pShadeMng->SetTexUnit(PHONG ,0);
		DrawMesh(&m_MeshR);
		glPopMatrix();
		m_pShadeMng->UnUseShader();
	}

	//タイトルの描画
	m_pShadeMng->UseShader(PHONG);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDT);
	glPushMatrix();
	glTranslatef(m_Titlpos.x, m_Titlpos.y, m_Titlpos.z);
	glRotatef((GLfloat)m_TAng, 1.0f, 0.0f, 0.0f);
	glScalef(m_TScl, m_TScl, m_TScl);
	m_pShadeMng->SetTexUnit(PHONG, 0);
	DrawMesh(&m_MeshT);
	glPopMatrix();
	m_pShadeMng->UnUseShader();


	//後処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// フェードイン　透明→有色
//--in--------------------------------------------
//
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::FadeIn(POLYGON3D *pol)
{
	static int nCnt = -1;

	//初回時
	if(nCnt < 0){
		nCnt = m_nCnt;	//現在のフレームカウント数を保存
		pol->col.a = 0.0f;
	}

	//α値を上げる
	if((m_nCnt - nCnt) < OP_FADE_TIME)
		pol->col.a += (1.0f / OP_FADE_TIME);
	else{
		pol->col.a = 1.0f;
		nCnt = -1;
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// フェードアウト　有色→透明
//--in--------------------------------------------
//
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::FadeOut(POLYGON3D *pol)
{
	static int nCnt = -1;

	//初回時
	if(nCnt < 0){
		nCnt = m_nCnt;	//現在のフレームカウント数を保存
		pol->col.a = 1.0f;
	}

	//α値を上げる
	if((m_nCnt - nCnt) < OP_FADE_TIME && pol->col.a > 0.05f)
	{
		pol->col.a -= (1.0f / OP_FADE_TIME);
	}
	else{
		pol->col.a = 0.0f;
		nCnt = -1;
		return true;
	}
	return false;
}

//################################################
// End of File
//################################################
