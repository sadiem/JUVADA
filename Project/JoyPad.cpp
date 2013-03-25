//################################################
// <JoyPad.h>
// ジョイスティック関連
//------------------------------------------------
// 2012/09/27 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "JoyPad.h"

//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================
//================================================
//プロトタイプ宣言
//================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
C_JOYPAD::C_JOYPAD()
{
	InitJoyPad();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// デストラクタ
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
C_JOYPAD::~C_JOYPAD()
{
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ゲームコントローラのジョイスティックの初期化
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void C_JOYPAD::InitJoyPad(void)
{
	for(int nLoop = 0; nLoop < KEY_NUM; nLoop ++)
	{
		m_JoySate[nLoop].PrevJoyState = 0;
		m_JoySate[nLoop].JoyState = 0;;
	}

	JOYPAD.dwSize = sizeof(JOYINFOEX);	//サイズを取得
	JOYPAD.dwFlags = JOY_RETURNALL;		//すべての情報を取得
	m_Conect = false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 更新処理
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void C_JOYPAD::Update(HWND hWnd)
{
	//ジョイスティック取得
	GetJoyPad(hWnd);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ゲームコントローラのジョイスティック取得関数
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void C_JOYPAD::GetJoyPad(HWND hWnd)
{
	//前の情報を保存
	for(int nLoop = 0; nLoop < KEY_NUM; nLoop ++)
	{
		m_JoySate[nLoop].PrevJoyState = m_JoySate[nLoop].JoyState;
		m_JoySate[nLoop].JoyState = 0;
	}

	//ジョイスティック取得
	switch(joyGetPosEx(JOYSTICKID1, &JOYPAD))
	{
	case JOYERR_NOERROR:	//成功
		m_Conect = true;
		//ジョイスティック　X軸
		m_JoySate[JOYPAD_LEFT_X].StickDate = JOYPAD.dwXpos;
		m_JoySate[JOYPAD_LEFT_Y].StickDate = JOYPAD.dwYpos;

		//ジョイスティック　Z軸
		m_JoySate[JOYPAD_RIGHT_Z].StickDate = JOYPAD.dwZpos;
		m_JoySate[JOYPAD_RIGHT_R].StickDate = JOYPAD.dwRpos;


		//ボタン取得
		if(JOYPAD.dwButtons & JOY_BUTTON1)
			m_JoySate[JOYBUTTON_1].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON2)
			m_JoySate[JOYBUTTON_2].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON3)
			m_JoySate[JOYBUTTON_3].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON4)
			m_JoySate[JOYBUTTON_4].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON5)
			m_JoySate[JOYBUTTON_5].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON6)
			m_JoySate[JOYBUTTON_6].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON7)
			m_JoySate[JOYBUTTON_7].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON8)
			m_JoySate[JOYBUTTON_8].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON9)
			m_JoySate[JOYBUTTON_9].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON10)
			m_JoySate[JOYBUTTON_10].JoyState = 1;
		if(JOYPAD.dwButtons & JOY_BUTTON11)
			m_JoySate[JOYBUTTON_11].JoyState = 1;
		
		break;
	case MMSYSERR_NODRIVER:		//ジョイスティックドライバが存在しません
		m_Conect = false;
		MessageBox(hWnd, _T("ジョイスティックドライバが存在しません"), _T("error"), MB_OK);
		break;
	case MMSYSERR_INVALPARAM:	//無効なパラメータが設定されました
		m_Conect = false;	
		MessageBox(hWnd, _T("無効なパラメータが設定されました"), _T("error"), MB_OK);
		break;
	case MMSYSERR_BADDEVICEID:	//指定されたジョイスティック識別子が存在しません
		m_Conect = false;
		MessageBox(hWnd, _T("指定されたジョイスティック識別子が存在しません"), _T("error"), MB_OK);
		break;
	case JOYERR_UNPLUGGED:		//指定されたジョイスティックはシステムに接続されていません
		m_Conect = false;
		MessageBox(hWnd, _T("指定されたジョイスティックはシステムに接続されていません"), _T("error"), MB_OK);
	default: break;
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
// ゲームコントローラボタン (トリガー)
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
bool C_JOYPAD::GetJoyPadTrigger(int type)
{
	if(type < KEY_NUM){
		if(m_JoySate[type].PrevJoyState == 0 && m_JoySate[type].JoyState == 1)
			return true;
		else
			return false;
	}else
		return false;

}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ゲームコントローラボタン (リリース)
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
bool C_JOYPAD::GetJoyPadRelease(int type)
{
	if(type < KEY_NUM){
		if(m_JoySate[type].PrevJoyState == 1 && m_JoySate[type].JoyState == 0)
			return true;
		else
			return false;
	}else
		return false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// スティック情報
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
int C_JOYPAD::GetJoyPadStick(int nType)
{
	if(nType < KEY_NUM)
		return m_JoySate[nType].StickDate;
	else
		return -1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// スティック情報
//--in---------------------------------------------
// 
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
bool C_JOYPAD::CheckJoyPad(void)
{
	return m_Conect;
}
 
//++++++++++++++++++++++++++++++++++++++++++++++++
//ジョイスティックからの速度計算処理
//--in--------------------------------------------
//　キー情報
//--out-------------------------------------------
//　速度
//++++++++++++++++++++++++++++++++++++++++++++++++
float C_JOYPAD::KeyDownSpeed(DWORD key)
{
	float temp;

	temp = (float)key;
	temp = ((temp - 32767) / 32767);
	return temp;
}

void C_JOYPAD::Debag()
{	
	static int nB_1 = 0;
	static int nB_2 = 0;
	static int nB_3 = 0;
	static int nB_4 = 0;
	static int nB_5 = 0;
	static int nB_6 = 0;
	static int nB_7 = 0;
	static int nB_8 = 0;
	static int nB_9 = 0;
	static int nB_10 = 0;
	static int nB_11 = 0;
	static DWORD S_X = 0;
	static DWORD S_Y = 0;
	static DWORD S_Z = 0;
	static DWORD S_R = 0;

	if( GetJoyPadTrigger(JOYBUTTON_1)) nB_1 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_2)) nB_2 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_3)) nB_3 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_4)) nB_4 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_5)) nB_5 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_6)) nB_6 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_7)) nB_7 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_8)) nB_8 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_9)) nB_9 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_10)) nB_10 ^= 1;
	if( GetJoyPadTrigger(JOYBUTTON_11)) nB_11 ^= 1;
	S_X = GetJoyPadStick(JOYPAD_LEFT_X);
	S_Y = GetJoyPadStick(JOYPAD_LEFT_Y);
	S_Z = GetJoyPadStick(JOYPAD_RIGHT_Z);
	S_R = GetJoyPadStick(JOYPAD_RIGHT_R);

	TCHAR	str[256];
	g_szDebug2[0] = _T('\0');
	_stprintf_s(str, 
		_T("\n \nController:\n 1 => %d\n 2 => %d\n 3 => %d\n 4 => %d\n 5 => %d\n 6 => %d\n 7 => %d\n 8 => %d\n 9 => %d\n 10 => %d\n 11 => %d\n S1X => %lu\n S1Y => %lu\n S1Z => %lu\n S1R => %lu\n"), nB_1, nB_2, nB_3, nB_4, nB_5, nB_6, nB_7, nB_8, nB_9, nB_10, nB_11, S_X, S_Y, S_Z, S_R);
	lstrcat(g_szDebug2, str);


}
//################################################
// End of File
//################################################
