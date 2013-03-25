//################################################
//<Main.cpp>
//マインスイーパ作成
//2012/07/12 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#define STRICT
#include "Main.h"

#include "Common.h"		//共通ヘッダ
#include "GameMain.h"
#include "Graphic.h"
#include "resource.h"	//リソースヘッダ
#include "JoyPad.h"		//コントローラ
#include "Random.h"		//ランダム値
//================================================
//定数定義
//================================================
#define CLASS_NAME		_T("JUVADA")		//ウィンドウクラス名
#define CAPTION_NAME	_T("JUVADA")		//キャプション名

#define FRAME_RATE			(1000/60)						//フレームレート
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - SCREEN_WIDTH ) / 2)  //ウィンドウの表示位置
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - SCREEN_HEIGHT ) / 2) //ウィンドウの表示位置


//================================================
//グローバル定義
//================================================
bool g_bWindow;				//ウィンドウモード
bool g_bEnd;				//ゲーム終了フラグ
float g_fFPS;				//FPSカウンタ
DWORD	 dwExecLastTime;
//================================================
//プロトタイプ宣言
//================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//+++++++++++++++++++++++++++++++++++++++++++++++++
//メイン関数
//-------------------------------------------------
//初期化及びメインループ
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	HWND	hWnd;
	MSG		msg;
	DWORD	dwFPSLastTime, dwCurrentTime, dwFrameCount;

	//ウィンドウ クラスを登録
	WNDCLASS wndClass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInst,
		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME
	};
	if (RegisterClass(&wndClass) == 0) return false;

	//ウィンドウ サイズを取得
	RECT rc = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	DWORD dwExStyle = 0;
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	//ウィンドウを作成
	hWnd = CreateWindowEx(
		dwExStyle,
		CLASS_NAME,
		CAPTION_NAME,
		dwStyle,
		WINDOW_X,
		WINDOW_Y,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInst,
		NULL);
	if (hWnd == NULL) return false;

	g_bWindow = true;
	
	if(FAILED(InitializeGraphics(hWnd, g_bWindow))) 
		return 0;	//OpenGL の初期化

	//変数初期化
	timeBeginPeriod(1);									//タイマの分解能を最小にセット
	dwFPSLastTime = dwExecLastTime = timeGetTime();		//現在のシステム タイマを取得
	dwExecLastTime -= FRAME_RATE;
	dwFrameCount = 0;
	g_fFPS = 0.0f;

	//マウスカーソル位置を固定する
	//SetCursorPos( WINDOW_X + SCREEN_WIDTH / 2, WINDOW_Y + SCREEN_HEIGHT / 2 );	//ウィンドウの中心位置に固定
	ShowCursor(false);

	//メイン ウインドウ ループ
	msg.message = WM_NULL;

	//乱数設定
	InitRandom();

	while (WM_QUIT != msg.message && !g_bEnd)	//WM_QUIT がくるか、終了フラグがたつまでループ
	{
		if (PeekMessage(&msg,NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			dwCurrentTime = timeGetTime();					//現在のタイマ値を取得
			if (dwCurrentTime - dwFPSLastTime >= 500)		//0.5 秒ごとに計測
			{
				//フレーム数を計算
				g_fFPS = dwFrameCount * 1000.0f / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//タイマ値を更新
				dwFrameCount = 0;				//フレーム カウンタをリセット
			}
			//この辺で時間管理
			while (dwCurrentTime - dwExecLastTime >= FRAME_RATE)	//一定時間が経過したら・・・
			{
				dwExecLastTime += FRAME_RATE;						//タイマ値を更新
			
				GameMain(hWnd);										//ゲーム メイン処理
			}
			RenderGraphics();								//レンダリング処理を実行
			dwFrameCount++;									//フレーム カウントを＋１
			Sleep(1);										//いったん Windows に制御を戻す
		}

		//終了確認
		if(g_bEnd)
		{
			//if (IDNO == MessageBox(hWnd, _T("ゲームを終了しますか？"), _T("終了確認"), MB_YESNO))
			//	g_bEnd = false;

		}

	}
	timeEndPeriod(1);						//システム タイマの分解能を元に戻す
	return (int)msg.wParam;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//ウィンドウプロシージャ
//-------------------------------------------------
//OSよりのメッセージ受取及び送信
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CLOSE:
		CleanupGraphics(hWnd, g_bWindow);
		break;
	case WM_COMMAND:
		if (OnCommand(hWnd, wParam, lParam)) 
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//case WM_KEYDOWN:
	//	switch (wParam) {
	//	case VK_ESCAPE:
	//		CleanupGraphics(hWnd, g_bWindow);
	//		PostMessage(hWnd, WM_CLOSE, 0, 0);
	//		return 0;
	//	}
	//	break;
	case WM_IME_NOTIFY:
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//メニューのウィンドウ
//-------------------------------------------------
//OSよりのメッセージ受取及び送信
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
BOOL OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD	wNotify	= HIWORD(wParam);	//通知コード
	WORD	wID		= LOWORD(wParam);	//項目ID、コントロールID、アクセラレータID
	HWND	hwndCtl	= (HWND)lParam;		//コントロールのハンドル

	switch (wID) {
	case ID_EXIT:		//終了(X)
		PostMessage(hWnd, WM_CLOSE, 0, 0);
		return TRUE;	//処理済
	case ID_VERSION:	//ヘルプ(H)->バージョン情報(A)
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		MAKEINTRESOURCE(ID_PROPERTY), hWnd, AboutDlgProc);
		return TRUE;	//処理済
	}
	return FALSE;		//未処理

}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//バージョン情報ダイアログ
//-------------------------------------------------
//OSよりのメッセージ受取及び送信
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return TRUE;	//既定のコントロールにフォーカスを設定
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:	//キャンセル　ボタン
		case IDOK:		//OK
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;	//未処理(=デフォルトの処理が実行される)
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//FPS値の受け渡し
//-------------------------------------------------
//FPSを出力するため、Str.cpp及び更新GameMain.cppへ
//--in---------------------------------------------
//なし
//--out---------------------------------------------
//なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
float GetFPS(void)
{
	return g_fFPS;					//フレーム数カウント用
}

void SetExecTime(DWORD time)
{
	dwExecLastTime = time;
}