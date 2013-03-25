//################################################
//<GameMain.cpp>
// ゲームメイン関連処理
//------------------------------------------------
//JUVADA制作
//2012/07/12 ~						SekiyamaRumi
//2013/1/22		環境マップ追加		Akihito Tanaka
//2013/1/27		タイトル部分マージ	Akihito Tanaka
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "GameMain.h"	//GameMainヘッダー
#include "TexMng.h"		//テクスチャ管理関連( 2D )
#include "Common.h"		//共通定義関連
#include "Camera.h"		//カメラ関連
#include "Graphic.h"
#include "Shadow.h"		//影

//ゲームアクセサリー
#include "Score.h"		//スコア
#include "Player.h"		//プレイヤー
#include "EnemyMng.h"	//エネミー
#include "Field.h"		//フィールド
#include "Collision.h"	//衝突判定
#include "Ambient.h"	//環境エフェクト
#include "PlayerHpBar.h"	//プレイヤーのＨＰバー
#include "EnemyBossHpBar.h"	//ボスのＨＰバー
#include "EffectMng.h"	//エフェクトマネージャー
#include "Time.h"		//時間
#include "2DPoly.h"		//ポリゴン
#include "Sound.h"

//ゲーム遷移
#include "Opening.h"	//オープニング
#include "Select.h"		//セレクト
#include "Ending.h"		//エンディング
#include "Result.h"		//結果

#include "Input.h"		//入力制御

#include <process.h>

//================================================
//構造体定義
//================================================

//================================================
//定数定義
//================================================
#define FONT_WIDTH			(10)	//フォント幅
#define FONT_HEIGHT			(16)	//フォント高さ

//================================================
//グローバル変数
//================================================
//デバッグ文字列
GLuint		g_uFontTexID;			//フォントテクスチャ ID
TCHAR		g_szDebug[1028];		//出力文字列バッファ
TCHAR		g_szDebug2[1028];		//出力文字列バッファ
int			g_nStatus = INIT;		//ゲームの状態変化

bool		g_CubeFlg = true;		//キューブマップ表示フラグ		
bool		g_loadFlg = false;

//クラスポインタ定義
SCORE		*p_Score;
PLAYER		*p_Player;
CAMERA		*p_Camera;
FIELD		*p_Field;
ENEMYMNG	*p_Enemy;
COLLISION   *p_Collision;
SHADOW		*p_Shadow;
AMBIENT		*p_Ambient;
PLAYER_HP_BAR *p_PlayerHpBar;
BOSS_HP_BAR *p_BossHpBar;
EFFECT_MNG	*p_EffectMng;
INPUT_MNG	*pInput;
OP			*p_Op;
SELECT		*p_Select;
RESULT_MNG	*p_Result;
TIME_MNG	*p_Time;
SPLITE		*p_2D;
SOUND		*p_SE;

float x = 0.0f;
float y = 0.0f;
float z = 0.0f;
float num1 = 0.0f;
float num2 = 0.0f;
float num3 = 0.0f;

//ロードスレッド
HANDLE	Loadhandle;

void SetThread(void);
unsigned int WINAPI Loading (void *arg);
//================================================
//プロトタイプ宣言
//================================================
void DrawChar(int x, int y, int c);
void DrawStr(int x, int y, LPCTSTR psz);
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ゲーム本編の更新処理
//-------------------------------------------------
// ゲームのメイン処理部分
//--in---------------------------------------------
// ウィンドウハンドル
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void GameMain(HWND hWnd)
{
#if (DEBUG_ON)

	TCHAR	str[256];
	g_szDebug[0] = _T('\0');	//デバッグ ストリング バッファ初期化
	_stprintf_s(str, _T("FPS = %.1f PLAYER_POS: X:%.1f Y:%.1f Z:%.1f \n NUM: 1:%f 2:%f 3:%f \n"), GetFPS(), x, y, z, num1, num2, num3);
	lstrcat(g_szDebug, str);

#endif
	VECTOR3 vecx, vecy;
	//画面遷移
	switch(g_nStatus)
	{
	case INIT:
		CreateClass();			//クラス領域の確保とロード
		p_Field->Init();			//フィールド
		p_Result->Init();
		g_loadFlg = false;
		SetThread();
		g_nStatus = LOADING;	//スルー
	case LOADING:
		if(g_loadFlg)
		{
			g_nStatus = STARTINIT;
			CloseHandle(Loadhandle);
		}
		break;
	case STARTINIT:
		p_Op->Init();				//オープニング
		p_Camera->ResetOp();		//カメラのリセット
		g_nStatus = START;

		break;
	case START:
		p_Camera->SetOpCamera();	//カメラのセット
		if(p_Op->Update())
			g_nStatus = MENU_INIT;
		break;
	case MENU_INIT:
		p_Camera->ResetOp();		//カメラのリセット
		p_Select->Init();
		g_nStatus = MENU;
		break;
	case MENU:
		p_Camera->SetOpCamera();	//カメラのセット
		if(p_Select->Update())
		{
			switch(p_Select->GetSelect())
			{
			case 0:
				p_SE->PlaySE(YES);
				g_nStatus = GAME_INIT_START;
				p_Select->Release();
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				g_nStatus = END;
				p_Select->Release();
				break;
			default:break;
			}
		}
		num3 = (float)p_Select->GetSelect();
		break;
	case GAME_INIT_START:
		g_loadFlg = false;
		p_Ambient->Init();			//環境
		p_Score->Init();			//スコアの初期化
		p_Player->Init();			//プレイヤー
		p_Enemy->Init(p_Player);	//エネミー
		p_PlayerHpBar->Init();		//プレイヤーバー
		p_BossHpBar->Init();		//ボスバー
		p_2D->Init();
		
		//SetThread();
		g_nStatus = GAME_INIT;	//スルー
	case GAME_INIT:
		//生成
		//p_Score->Load();
		//p_Ambient->Load();
		//p_Player->Load();
		//p_Enemy->Load();
		//p_BossHpBar->Load();
		p_2D->Load();
		p_EffectMng->Load();

		//リセット
		p_Ambient->Reset();			//環境のリセット
		p_Player->Reset();			//プレイヤーのリセット
		p_Score->Reset();			//スコアのリセット
		p_Enemy->Reset();			//エネミーのリセット
		p_Camera->ResetGame();		//カメラのリセット
		p_PlayerHpBar->Reset();
		p_BossHpBar->Reset();
		p_Time->Reset();
		g_CubeFlg = true;
		//SetExecTime(timeGetTime());
		//if(g_loadFlg)
		//{
		//	CloseHandle(Loadhandle);
			g_nStatus = GAME_FILLER_START;
		//}
		break;
	case GAME_FILLER_START:
		if(p_2D->Update())
		{
			g_nStatus = GAME;
			p_2D->Reset();
			p_Time->Start();
			p_2D->m_Cnt = 0;
			p_SE->PlayBG(BG_GAME_NORMAL);
		}

		break;
	case GAME_RESET:	//リセット
		p_Player->Reset();			//プレイヤーのリセット
		p_Camera->ResetGame();		//カメラのリセット
		p_PlayerHpBar->Reset();
		p_BossHpBar->Reset();
		g_nStatus = GAME;
		break;
	case GAME:
		if(GetAsyncKeyState(VK_F12)&0x0001)
			g_CubeFlg ^= 1;
		p_Time->Update();
		p_Score->Update(p_Enemy->m_DeadCnt, p_Enemy->m_BossCnt);	//スコア
		p_Field->Update();			//地形
		p_Camera->GetVecCamera();	//カメラ
		p_Enemy->Update();			//エネミー
		p_Player->Update(p_Camera->vecx, p_Camera->vecz);	//プレイヤー
		p_Collision->Update();		//衝突判定
		p_Ambient->Update(p_Enemy->m_DeadCnt, p_Enemy->m_pEnemyBoss->m_AppearBoss);
		p_PlayerHpBar->Update(p_Player->m_Life, 100);	//プレイヤーのＨＰバー
		p_BossHpBar->Update(p_Enemy->m_pEnemyBoss->m_Life, 100);	//ボスのＨＰバー

		//ボスが生きていてL1が押された時Z注目をする
		if(pInput->GetBtnState(BTN_L1) == PRESS && p_Enemy->m_pEnemyBoss->m_Live)
		{
			p_Camera->SetOperatable(false);
		}
		//L1が離されたときは通常処理に戻す
		else if( pInput->GetBtnState(BTN_L1) == RLS )
		{
			p_Camera->SetOperatable(true);
		}

		if(pInput->GetBtnState(BTN_L2) == PRESS && pInput->GetBtnState(BTN_B) == PRESS )
		{
			p_Enemy->m_DeadCnt = 100; //デバグボス出現用
		}
		p_Camera->Update(p_Player->m_Pos, p_Enemy->m_pEnemyBoss->m_Pos);
		p_EffectMng->UpDate();
		
		{	
			//デバック表示用
			x = p_Player->m_Pos.x;
			y = p_Player->m_Pos.y;
			z = p_Player->m_Pos.z;
			num1 = p_Player->m_Matrix._11;
			num2 = (float)p_Enemy->m_pEnemyBoss->m_Life;
			//rad = p_Player->m_Matrix._13;
			//num3 = (float)p_Player->m_Life;
			num3 = p_PlayerHpBar->nM;
		}
		

		//結果
		if(p_Enemy->m_BossCnt)
			g_nStatus = GAME_FILLER_END;
		
		if(p_Player->m_bRetry)
			g_nStatus = GAME_FILLER_END;

#if (DEBUG_ON)
		//デバック用
		if(GetAsyncKeyState(VK_RETURN) & 0x0001)
			g_nStatus = GAME_FILLER_END;
#endif
		break;
	case GAME_FILLER_END:
			g_nStatus = RESULT_INIT;

		break;
	case RESULT_INIT:
		
		p_SE->StopBG(BG_GAME_BOSS);
		p_SE->PlayBG(BG_RESULT);
		p_Camera->ResetOp();		//カメラのリセット	OPと同じ
		p_Camera->SetOpCamera();	//カメラのセット
		
		p_Result->Init();
		g_nStatus = RESULT;
		break;
	case RESULT:
		if(p_Result->Update())
		{
			p_SE->StopBG(BG_RESULT);
			p_Result->Release();
			g_nStatus = MENU_INIT;
		}
		break;
	case ENDINIT:
			//g_nStatus = MENU_INIT;
		break;
	case END:
		p_SE->del();			//サウンドの開放
		DeCreateClass();		//クラスの解放
		g_bEnd = true;			//ゲーム終了
		return;
	default:break;
	}
	
	if(pInput != NULL)
	{
		pInput->Update();
		
		//プレゼン用
		if(pInput->GetBtnState(BTN_L1) == PRESS && pInput->GetBtnState(BTN_R1) == PRESS
		&& pInput->GetBtnState(BTN_L2) == PRESS && pInput->GetBtnState(BTN_R2) == PRESS)
		{
			p_SE->Reset();		//サウンドリセット
			g_nStatus = STARTINIT;
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 3D描画本体
//-------------------------------------------------
// 描画の3D部分の描画を行う関数
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMain()
{
	GLfloat fogCol[] = {0.7f, 0.7f, 0.7f, 0.3f};	
	//3D用描画ゲーム遷移
	switch(g_nStatus)
	{
	case INIT:
		break;
	case STARTINIT:

		break;
	case START:
		p_Op->Draw();
		break;
	case MENU_INIT:
		break;
	case MENU:
		p_Select->Draw();
		break;
		

	case GAME_INIT:
		break;
	case GAME_RESET:		//スルー
	case GAME_FILLER_START://スルー
	case GAME:
		//if(g_CubeFlg)
		//{
		//	//キューブマップ描画
		//	p_Player->DrawCubeMap();

		//	Init3D();
		//}

		//フォグ
		glEnable(GL_FOG);

		//モデル描画
		p_Field->Draw();
		//if(g_CubeFlg)
		//	p_Player->DrawCube();
		//else
			p_Player->Draw();

		p_Enemy->Draw();
		p_Ambient->Draw();
		p_Field->DrawFence();
		glDisable(GL_FOG);
		//影描画
		//p_Shadow->CreateShadow((OBJECT *)p_Player);	//プレイヤー

		for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
		{
			if(p_Enemy->m_pEnemy[i]->m_Live == false)
				continue;
			p_Shadow->CreateShadow((OBJECT *)p_Enemy->m_pEnemy[i]);	//エネミー
		}

		for(int i = 0; i < 9; i ++)
		{
			if(p_Enemy->m_pEnemy[i]->m_Live == false)
				continue;
			p_Shadow->CreateShadow((OBJECT *)p_Enemy->m_pEnemy[i]);	//エネミー
		}

		//エフェクト
		p_EffectMng->Draw();
		glColor4f(1.0f, 1.0f, 1.0f,1.0f);

		break;

	case RESULT_INIT:
		break;
	case RESULT:
		p_Result->Draw();
		break;
	case ENDINIT:

		break;
	/*case ENDINIT:

		break;*/
	case END:

		break;
	default:break;
	}


}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 2D描画本体
//-------------------------------------------------
// 描画の2D部分の描画を行う関数
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawPict()
{
	//テクスチャ有効化
	glEnable(GL_TEXTURE_2D);	

	//2D用描画ゲーム遷移
	switch(g_nStatus)
	{
	case INIT:
		
		break;
	case STARTINIT:
		
		break;
	case START:

		break;
	case GAME_INIT:
	
		break;

	case GAME_FILLER_START:
		p_2D->Draw();
		break;
	case GAME_RESET:
		break;
	case GAME:
		//p_Score->Draw();		//スコアの出力
		p_BossHpBar->Draw();	//プレイヤーのＨＰバー
		p_PlayerHpBar->Draw();	//プレイヤーのＨＰバー
		p_Time->Draw();
		break;
	case RESULT_INIT:
		
		break;
	case RESULT:
		p_Result->Draw2D();
		break;
	/*case ENDINIT:
		
		break;*/
	case END:
		break;
	default:break;
	}



#if (DEBUG_OFF)

	DrawStr(0, 0, g_szDebug);	//FPS情報
	DrawStr(0, 0, g_szDebug2);	//コントローラ情報

#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// データの読み込み
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void LoadData(void)
{
	//フォント セットアップ
	g_uFontTexID = g_TexMng.GetTexture("TEXTURE\\2D\\font.tga", "FPS");
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// クラスの作成
//-------------------------------------------------
// クラスの生成領域の確保
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CreateClass(void)
{
	switch(g_nStatus)
	{
	case INIT:
		//クラス生成
		p_Player = PLAYER::Instance();	//プレイヤー
		p_Enemy = ENEMYMNG::Instance();	//エネミー
		p_Camera = CAMERA::Instance();
		p_Collision = COLLISION::Instance();	//衝突判定
		p_Shadow = SHADOW::Instance();
		p_Ambient = new AMBIENT;
		p_PlayerHpBar = PLAYER_HP_BAR::Instance();	//プレイヤーＨＰバー
		p_BossHpBar = BOSS_HP_BAR::Instance();	//プレイヤーＨＰバー
		p_EffectMng = EFFECT_MNG::Instance();
		p_Field = FIELD::Instance();			//フィールド
		p_Result = RESULT_MNG::Instance();
		p_Score = SCORE::Instance();	//スコア
		pInput = INPUT_MNG::getInstance();		//入力制御
		p_Time = TIME_MNG::Instance();
		p_2D = new SPLITE;
		p_SE = SOUND::Instance();
		p_Op = new OP;
		p_Select = new SELECT;		//セレクト画面


		break;
	case STARTINIT:
		break;
	case MENU_INIT:
		break;
	case GAME_INIT:
	
		break;
	case RESULT_INIT:
		break;
	case RESULT:
		break;
	case ENDINIT:
		
		break;
	case END:
		
		break;
	default:break;
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
// クラスの解放
//-------------------------------------------------
// クラスの生成領域の解放処理
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DeCreateClass(void)
{

	if(p_Ambient)
		delete p_Ambient;

	if(p_Op)
		delete p_Op;
	if(p_Select)
		delete p_Select;
	p_Ambient = NULL;
	p_Op = NULL;
	p_Select = NULL;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 文字描画
//-------------------------------------------------
// FPS出力用テクスチャからの抜き出し
//--in---------------------------------------------
// 座標位置
// 数値
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawChar(int x, int y, int c)
{
	FVERTEX	vtxQuad[4];

	vtxQuad[0].tu = (float)(c & 15) / FONT_HEIGHT;
	vtxQuad[0].tv = (float)(15 - (c >> 4)) / FONT_HEIGHT;
	vtxQuad[0].x  = (float)x;
	vtxQuad[0].y  = (float)y + FONT_HEIGHT;
	vtxQuad[0].z  = 0.0f;
	vtxQuad[1].tu = (float)((c & 15) + 1.0f) / FONT_HEIGHT;
	vtxQuad[1].tv = (float)(15 - (c >> 4)) / FONT_HEIGHT;
	vtxQuad[1].x  = (float)x + FONT_HEIGHT;
	vtxQuad[1].y  = (float)y + FONT_HEIGHT;
	vtxQuad[1].z  = 0.0f;
	vtxQuad[2].tu = (float)((c & 15) + 1.0f) / FONT_HEIGHT;
	vtxQuad[2].tv = (float)(15 - (c >> 4) + 1.0f) / FONT_HEIGHT;
	vtxQuad[2].x  = (float)x + FONT_HEIGHT;
	vtxQuad[2].y  = (float)y;
	vtxQuad[2].z  = 0.0f;
	vtxQuad[3].tu = (float)(c & 15) / FONT_HEIGHT;
	vtxQuad[3].tv = (float)(15 - (c >> 4) + 1.0f) / FONT_HEIGHT;
	vtxQuad[3].x  = (float)x;
	vtxQuad[3].y  = (float)y;
	vtxQuad[3].z  = 0.0f;

	glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
	glBindTexture(GL_TEXTURE_2D, g_uFontTexID);
	glInterleavedArrays(GL_T2F_V3F, 0, vtxQuad);
	glDrawArrays(GL_QUADS, 0, 4);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 文字列の描画
//-------------------------------------------------
// 文字列として出力
//--in---------------------------------------------
// 位置座標
// 文字列
//--out---------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawStr(int x, int y, LPCTSTR psz)
{
	for (; *psz; ++psz) {
		switch (*psz) {
		case _T('\n'):
			x = 0;
			y += FONT_HEIGHT;
			break;
		default:
			DrawChar(x, y, *psz);
			x += FONT_WIDTH;
			break;
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// シーン情報を受け渡す
//-------------------------------------------------
// シーンによる作業の分岐に使用
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// シーン情報
//+++++++++++++++++++++++++++++++++++++++++++++++++
int GetGMState(void)
{
	return g_nStatus;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ロードスレッドのセット
//-------------------------------------------------
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++
void SetThread(void)
{
	Loadhandle = (HANDLE)_beginthreadex(NULL, 0, Loading, NULL, 0, NULL);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ロードスレッド
//-------------------------------------------------
//--in---------------------------------------------
// なし
//--out--------------------------------------------
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++
unsigned int WINAPI Loading (void *arg)
{

	switch(g_nStatus)
	{
	case INIT:
		break;
	case LOADING:
		p_SE->LoadSE();
		p_SE->LoadBG();
		break;
	case STARTINIT:
		break;
	case START:

		break;
	case GAME_INIT:
		//ロード
		//p_Score->Load();
		//p_Ambient->Load();
		//p_Player->Load();
		//p_Enemy->Load();
		//p_BossHpBar->Load();
		//p_2D->Load();
		//p_EffectMng->Load();

		////リセット
		//p_Ambient->Reset();			//環境のリセット
		//p_Player->Reset();			//プレイヤーのリセット
		//p_Score->Reset();			//スコアのリセット
		//p_Enemy->Reset();			//エネミーのリセット
		//p_Camera->ResetGame();		//カメラのリセット
		//p_PlayerHpBar->Reset();
		//p_BossHpBar->Reset();
		//p_Time->Reset();
		//g_CubeFlg = true;
		break;

	case GAME_FILLER_START:
	
		break;
	case GAME_RESET:
		break;
	case GAME:

		break;
	case RESULT_INIT:
		
		break;
	case RESULT:
		break;
	/*case ENDINIT:
		
		break;*/
	case END:
		break;
	default:break;
	}
	
	g_loadFlg = true;
	return 0;
}