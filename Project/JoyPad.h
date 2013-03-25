//################################################
// <JoyPad.h>
// コントローラ関連
//------------------------------------------------
// 2012/09/27 ~
//						SekiyamaRumi
//################################################
#ifndef _____JOYPAD_H_____
#define _____JOYPAD_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Include.h"	//インクルードヘッダ
//================================================
//定数定義
//================================================
enum JOYPAD_STATE{
	JOYBUTTON_1 = 0,		//ボタン < 1 >
	JOYBUTTON_2,			//ボタン < 2 >
	JOYBUTTON_3,			//ボタン < 3 >
	JOYBUTTON_4,			//ボタン < 4 >
	JOYBUTTON_5,			//ボタン < 5 >
	JOYBUTTON_6,			//ボタン < 6 >
	JOYBUTTON_7,			//ボタン < 7 >
	JOYBUTTON_8,			//ボタン < 8 >
	JOYBUTTON_9,			//ボタン < 9 >
	JOYBUTTON_10,			//ボタン < 10 >
	JOYBUTTON_11,			//ボタン < 11 >
	JOYPAD_LEFT_X,		//スティック左右 < X >
	JOYPAD_LEFT_Y,		//スティック上下 < Y >
	JOYPAD_RIGHT_Z,		//スティック左右 < Z >
	JOYPAD_RIGHT_R,		//スティック上下 < R >

	KEY_NUM					/* キーの総数 */
};
struct JoyInfo
{
	int	JoyState;		//現在の状態
	int	PrevJoyState;	//前の状態
	int	StickState;		//スティック情報
	DWORD StickDate;	//スティックの倒し
};
extern TCHAR g_szDebug2[1028];		//出力文字列バッファ
//================================================
//クラス定義
//================================================
class C_JOYPAD{
public:
	static C_JOYPAD* Instance(){
		static C_JOYPAD inst;
		return &inst;
	};
private:
	C_JOYPAD();
	bool  m_Conect;		//接続状態判定
public:
	~C_JOYPAD();

	JoyInfo m_JoySate[KEY_NUM];
	JOYINFOEX JOYPAD;

	void InitJoyPad(void);				//初期化
	void GetJoyPad(HWND hWnd);			//ジョイスティック情報取得
	bool GetJoyPadTrigger(int type);	//トリガー
	bool GetJoyPadRelease(int type);	//リリース
	int GetJoyPadStick(int nType);		//スティック
	bool CheckJoyPad(void);				//接続確認
	float KeyDownSpeed(DWORD key);		//キーの倒し情報を-1～1の範囲で出す
	void Update(HWND hWnd);				//更新
	
	void Debag(void);	//デバック出力
};
//################################################
// End of File
//################################################
#endif _____JOYPAD_H_____