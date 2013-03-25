//################################################
//<GameMain.cpp>
// ゲームメイン関連処理
//------------------------------------------------
//JUVADA制作
//2012/11/12 ~					SekiyamaRumi
//################################################
#ifndef _____GAMEMAIN_H_____
#define _____GAMEMAIN_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"	//メインヘッダー
#include "Common.h"		//メインヘッダー
#include "Object.h"		//オブジェクト
//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================

//================================================
//構造体定義
//================================================
enum STATE{
 INIT,						//初期化
 LOADING,					//ロード中
 STARTINIT,					//開始初期化
 START,						//開始
 MENU_INIT,					//セレクト初期化
 MENU,						//セレクト
 GAME_INIT_START,					//メイン初期化
 GAME_INIT,					//メイン初期化
 GAME_FILLER_START,			//メインのつなぎ
 GAME_RESET,				//リセット
 GAME,						//メイン
 GAME_FILLER_END,			//メインつなぎ
 RESULT_INIT,				//結果初期化	失敗
 RESULT,					//結果
 ENDINIT,					//終了初期化
 END						//終了
};

//================================================
//プロトタイプ宣言
//================================================
void GameMain(HWND hWnd);
void DrawMain();
void DrawPict();		//２D表示
void CreateClass();		//クラスの作成
void DeCreateClass();	//クラスの解放



void LoadData(void);	//データ
int GetGMState();		//シーン受け渡し用
#endif _____GAMEMAIN_H_____