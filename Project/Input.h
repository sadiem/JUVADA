//=======================================================================================
//
//	 入力処理
//
//=======================================================================================
#ifndef __INPUT_H___
#define __INPUT_H___

#include "include.h"
#include "Matrix.h"

#define STICK_THRESHOLD	(4096)
#define STICK_BORDER	(32767)

enum{
	BTN_RIGHT,	//x+
	BTN_LEFT,	//x-
	BTN_DOWN,	//z+
	BTN_UP,		//z-
	BTN_CAM_RIGHT,	//x+
	BTN_CAM_DOWN,
	BTN_CAM_LEFT,	//x-
	BTN_CAM_UP,
	BTN_A,
	BTN_B,
	BTN_C,
	BTN_D,
	BTN_R1,
	BTN_R2,
	BTN_L1,
	BTN_L2,
	BTN_START,
	BTN_SELECT,
	MAX_BUTTON,
};



enum{
	L_X,
	L_Y,
	R_X,
	R_Y,
	MAX_AXIS,
};
enum{
	NONE,		//押されていない
	TRG,		//トリガ
	PRESS,		//押し続け
	RLS,		//リリース
};

//extern TCHAR g_szDebug[4096];

class INPUT_MNG{
//シングルトン
 public:
     static INPUT_MNG* getInstance() {
         static INPUT_MNG inst;
         return &inst;
     }
 
 private:
     INPUT_MNG();
public:
	void	Update();
	int		GetBtnState(int name);
	float	GetAxis(int name);
	bool	isMove();
private:
	void Init();
	void UpdateJoyStick();
	void UpdateKeybord();
	void BtnJudge(int nFncNum, int nBtnVal);	//ボタン押下判定
//	void _DrawDbgStr();

	int nKeyAssign[MAX_BUTTON];					//キーボードキーコンフィグ
	int	nJoyAssign[MAX_BUTTON];					//ゲームパッドキーコンフィグ

	bool bJoyStickConnect;			//ジョイスティックが接続しているか
	int nJoyBtnState[MAX_BUTTON];	//ジョイスティックボタン状態
	int nKeyBtnState[MAX_BUTTON];	//キーボードボタン状態
	int nBtnState[MAX_BUTTON];		//ボタン状態
	int nLastJoyBtnState[MAX_BUTTON];	//前フレームボタン状態
	int nLastKeyBtnState[MAX_BUTTON];	//前フレームボタン状態
	int nLastBtnState[MAX_BUTTON];	//前フレームボタン状態
	int nStickAxis[MAX_AXIS];		//スティック情報
	JOYINFOEX JoyInfoEx;
	bool _debugInfo;
};

#endif