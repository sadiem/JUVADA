#include "Input.h"

INPUT_MNG::INPUT_MNG()
{	
	Init();

}
void INPUT_MNG::Update()
{
	if(bJoyStickConnect)	//初期化時にジョイスティックが接続していれば更新
		UpdateJoyStick();
	
	UpdateKeybord();

	for(int i = 0; i < MAX_BUTTON; i++)
	{
		//ジョイスティックの情報がなければキーボードの情報を入力
		if(nJoyBtnState[i] == NONE)
			nBtnState[i] = nKeyBtnState[i];
		else
			nBtnState[i] = nJoyBtnState[i];
	}

	
	//状態を保存
	for(int i = 0; i < MAX_BUTTON; i++)
		nLastBtnState[i] = nBtnState[i];

//	if(_debugInfo)
//		_DrawDbgStr();
}
void INPUT_MNG::UpdateJoyStick()
{	
	switch(joyGetPosEx(0, &JoyInfoEx))
	{
	case JOYERR_NOERROR: //成功
	//-----------左スティック
		MyOutputDebugString( _T("Input JoyUp: %d\n"),  nJoyBtnState[BTN_UP]);
		if(JoyInfoEx.dwYpos < STICK_BORDER - STICK_THRESHOLD) //上;
		{
			if(nLastJoyBtnState[BTN_UP] == NONE || nLastJoyBtnState[BTN_UP] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_UP] = TRG;
			else
				nJoyBtnState[BTN_UP] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_UP] == PRESS || nLastJoyBtnState[BTN_UP] == TRG)
				nJoyBtnState[BTN_UP] = RLS;
			else
				nJoyBtnState[BTN_UP] = NONE;
		}
		MyOutputDebugString( _T("Input JoyUp: %d\n"),  nJoyBtnState[BTN_UP]);
		
		if(JoyInfoEx.dwYpos > STICK_BORDER + STICK_THRESHOLD) //下;
		{
			if(nLastJoyBtnState[BTN_DOWN] == NONE || nLastJoyBtnState[BTN_DOWN] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_DOWN] = TRG;
			else
				nJoyBtnState[BTN_DOWN] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_DOWN] == PRESS || nLastJoyBtnState[BTN_DOWN] == TRG)
				nJoyBtnState[BTN_DOWN] = RLS;
			else
				nJoyBtnState[BTN_DOWN] = NONE;
		}

		if(JoyInfoEx.dwXpos > STICK_BORDER + STICK_THRESHOLD) //右;
		{
			if(nLastJoyBtnState[BTN_RIGHT] == NONE || nLastJoyBtnState[BTN_RIGHT] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_RIGHT] = TRG;
			else
				nJoyBtnState[BTN_RIGHT] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_RIGHT] == PRESS || nLastJoyBtnState[BTN_RIGHT] == TRG)
				nJoyBtnState[BTN_RIGHT] = RLS;
			else
				nJoyBtnState[BTN_RIGHT] = NONE;
		}

		if(JoyInfoEx.dwXpos < STICK_BORDER - STICK_THRESHOLD) //左;
		{
			if(nLastJoyBtnState[BTN_LEFT] == NONE || nLastJoyBtnState[BTN_LEFT] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_LEFT] = TRG;
			else
				nJoyBtnState[BTN_LEFT] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_LEFT] == PRESS || nLastJoyBtnState[BTN_LEFT] == TRG)
				nJoyBtnState[BTN_LEFT] = RLS;
			else
				nJoyBtnState[BTN_LEFT] = NONE;
		}
	//----------------------右スティック
		if(JoyInfoEx.dwZpos < STICK_BORDER - STICK_THRESHOLD) //上;
		{
			if(nLastJoyBtnState[BTN_CAM_UP] == NONE || nLastJoyBtnState[BTN_CAM_UP] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_CAM_UP] = TRG;
			else
				nJoyBtnState[BTN_CAM_UP] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_CAM_UP] == PRESS || nLastJoyBtnState[BTN_CAM_UP] == TRG)
				nJoyBtnState[BTN_CAM_UP] = RLS;
			else
				nJoyBtnState[BTN_CAM_UP] = NONE;
		}
		
		if(JoyInfoEx.dwZpos > STICK_BORDER + STICK_THRESHOLD) //下;
		{
			if(nLastJoyBtnState[BTN_CAM_DOWN] == NONE || nLastJoyBtnState[BTN_CAM_DOWN] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_CAM_DOWN] = TRG;
			else
				nJoyBtnState[BTN_CAM_DOWN] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_CAM_DOWN] == PRESS || nLastJoyBtnState[BTN_CAM_DOWN] == TRG)
				nJoyBtnState[BTN_CAM_DOWN] = RLS;
			else
				nJoyBtnState[BTN_CAM_DOWN] = NONE;
		}

		if(JoyInfoEx.dwRpos > STICK_BORDER + STICK_THRESHOLD) //右;
		{
			if(nLastJoyBtnState[BTN_CAM_RIGHT] == NONE || nLastJoyBtnState[BTN_CAM_RIGHT] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_CAM_RIGHT] = TRG;
			else
				nJoyBtnState[BTN_CAM_RIGHT] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_CAM_RIGHT] == PRESS || nLastJoyBtnState[BTN_CAM_RIGHT] == TRG)
				nJoyBtnState[BTN_CAM_RIGHT] = RLS;
			else
				nJoyBtnState[BTN_CAM_RIGHT] = NONE;
		}

		if(JoyInfoEx.dwRpos < STICK_BORDER - STICK_THRESHOLD) //左;
		{
			if(nLastJoyBtnState[BTN_CAM_LEFT] == NONE || nLastJoyBtnState[BTN_CAM_LEFT] == RLS) //前フレームに押されていないときトリガ
				nJoyBtnState[BTN_CAM_LEFT] = TRG;
			else
				nJoyBtnState[BTN_CAM_LEFT] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastJoyBtnState[BTN_CAM_LEFT] == PRESS || nLastJoyBtnState[BTN_CAM_LEFT] == TRG)
				nJoyBtnState[BTN_CAM_LEFT] = RLS;
			else
				nJoyBtnState[BTN_CAM_LEFT] = NONE;
		}

		//ボタン
		for(int i = BTN_A; i < MAX_BUTTON; i++ )
		{
			if(JoyInfoEx.dwButtons & nJoyAssign[i]) //ボタン1;
			{
				if(nLastJoyBtnState[i] == NONE || nLastJoyBtnState[i] == RLS) //前フレームに押されていないときトリガ
					nJoyBtnState[i] = TRG;
				else
					nJoyBtnState[i] = PRESS;	  //それ以外の時は押され続けている
			}
			else
			{
				if(nLastJoyBtnState[i] == PRESS || nLastJoyBtnState[i] == TRG)
					nJoyBtnState[i] = RLS;
				else
					nJoyBtnState[i] = NONE;
			}
		}

	for(int i = 0; i < MAX_BUTTON; i++)
		nLastJoyBtnState[i] = nJoyBtnState[i];
		//if(JoyInfoEx.dwButtons & nJoyAssign[BTN_A]) //ボタン1;
		//{
		//	if(nLastJoyBtnState[BTN_A] == NONE || nLastJoyBtnState[BTN_A] == RLS) //前フレームに押されていないときトリガ
		//		nJoyBtnState[BTN_A] = TRG;
		//	else
		//		nJoyBtnState[BTN_A] = PRESS;	  //それ以外の時は押され続けている
		//}
		//else
		//{
		//	if(nLastJoyBtnState[BTN_A] == PRESS || nLastJoyBtnState[BTN_A] == TRG)
		//		nJoyBtnState[BTN_A] = RLS;
		//	else
		//		nJoyBtnState[BTN_A] = NONE;
		//}
		//if(JoyInfoEx.dwButtons & nJoyAssign[BTN_B]) //ボタン2;
		//{
		//	if(nLastJoyBtnState[BTN_B] == NONE || nLastJoyBtnState[BTN_B] == RLS) //前フレームに押されていないときトリガ
		//		nJoyBtnState[BTN_B] = TRG;
		//	else
		//		nJoyBtnState[BTN_B] = PRESS;	  //それ以外の時は押され続けている
		//}
		//else
		//{
		//	if(nLastJoyBtnState[BTN_B] == PRESS || nLastJoyBtnState[BTN_B] == TRG)
		//		nJoyBtnState[BTN_B] = RLS;
		//	else
		//		nJoyBtnState[BTN_B] = NONE;
		//}

		//スティックの数値を保存
		nStickAxis[L_X] = JoyInfoEx.dwXpos;
		nStickAxis[L_Y] = JoyInfoEx.dwYpos;
		nStickAxis[R_X] = JoyInfoEx.dwUpos;
		nStickAxis[R_Y] = JoyInfoEx.dwVpos;

		break;
	case JOYERR_UNPLUGGED://繋がっていない
		break;
	case MMSYSERR_NODRIVER: //ドライバが存在しない
		break;
    case MMSYSERR_INVALPARAM://無効なパラメーター        
		break;
    case MMSYSERR_BADDEVICEID: //指定されたジョイスティック識別子が無効
		break;
	}
}
void INPUT_MNG::UpdateKeybord()
{
	for(int i = 0; i < MAX_BUTTON; i++)
	{
		SHORT KeyInfo = GetAsyncKeyState(nKeyAssign[i]) ;
		if(KeyInfo & 0x8000) //上;
		{
			if(KeyInfo & 0x0001) //前フレームに押されていないときトリガ
				nKeyBtnState[i] = TRG;
			else
				nKeyBtnState[i] = PRESS;	  //それ以外の時は押され続けている
		}
		else
		{
			if(nLastKeyBtnState[i] == PRESS || nLastKeyBtnState[i] == TRG)
				nKeyBtnState[i] = RLS;
			else
				nKeyBtnState[i] = NONE;
		}
	}

	for(int i = 0; i < MAX_BUTTON; i++)
		nLastKeyBtnState[i] = nKeyBtnState[i];
	////----------カメラ回転

	//if(	GetAsyncKeyState(nKeyAssign[BTN_CAM_UP]) & 0x8000 )
	//{
	//	nKeyBtnState[BTN_UP] = NONE;
	//	nKeyBtnState[BTN_CAM_UP] = PRESS;
	//}
	//else
	//	nKeyBtnState[BTN_CAM_UP] = NONE;

	//if(	GetAsyncKeyState(nKeyAssign[BTN_CAM_DOWN]) & 0x8000 )
	//{
	//	nKeyBtnState[BTN_DOWN] = NONE;
	//	nKeyBtnState[BTN_CAM_DOWN] = PRESS;
	//}
	//else
	//	nKeyBtnState[BTN_CAM_DOWN] = NONE;

	//if(	GetAsyncKeyState(nKeyAssign[BTN_CAM_LEFT]) & 0x8000 )
	//{
	//	nKeyBtnState[BTN_LEFT] = NONE;
	//	nKeyBtnState[BTN_CAM_LEFT] = PRESS;
	//}
	//else
	//	nKeyBtnState[BTN_CAM_LEFT] = NONE;

	//if(	GetAsyncKeyState(nKeyAssign[BTN_CAM_RIGHT]) & 0x8000 )
	//{
	//	nKeyBtnState[BTN_RIGHT] = NONE;
	//	nKeyBtnState[BTN_CAM_RIGHT] = PRESS;
	//}
	//else
	//	nKeyBtnState[BTN_CAM_RIGHT] = NONE;
			

//	//デバッグ情報表示
//#ifdef _DEBUG
//	if(GetAsyncKeyState(VK_F2) & 1) //ボタン2;
//		_debugInfo ^= 1;
//#endif
}
void INPUT_MNG::Init()
{
	JoyInfoEx.dwSize = sizeof(JOYINFOEX);
	JoyInfoEx.dwFlags = JOY_RETURNALL; // 全ての情報を取得

	if(joyGetPosEx(0, &JoyInfoEx) == JOYERR_NOERROR)
	{
		bJoyStickConnect =true;		//ジョイスティック接続済み
	}
	else
	{	
		bJoyStickConnect =false;
	}

	nKeyAssign[BTN_RIGHT]		= VK_RIGHT;
	nKeyAssign[BTN_LEFT]		= VK_LEFT;
	nKeyAssign[BTN_DOWN]		= VK_DOWN;
	nKeyAssign[BTN_UP]			= VK_UP;
	nKeyAssign[BTN_CAM_RIGHT]	= 'D';
	nKeyAssign[BTN_CAM_LEFT]	= 'A';
	nKeyAssign[BTN_CAM_DOWN]	= 'S';
	nKeyAssign[BTN_CAM_UP]		= 'W';
	nKeyAssign[BTN_A]			= VK_SPACE;
	nKeyAssign[BTN_B]			= VK_SHIFT;
	nKeyAssign[BTN_C]			= 'Z';
	nKeyAssign[BTN_D]			= 'X';
	nKeyAssign[BTN_R1]			= 'N';
	nKeyAssign[BTN_R2]			= 'B';
	nKeyAssign[BTN_L1]			= 'M';
	nKeyAssign[BTN_L2]			= '<';


	nJoyAssign[BTN_RIGHT]		= VK_RIGHT;
	nJoyAssign[BTN_LEFT]		= VK_LEFT;
	nJoyAssign[BTN_DOWN]		= VK_DOWN;
	nJoyAssign[BTN_UP]			= VK_UP;
	nJoyAssign[BTN_CAM_RIGHT]	= 'D';
	nJoyAssign[BTN_CAM_LEFT]	= 'A';
	nJoyAssign[BTN_CAM_DOWN]	= 'S';
	nJoyAssign[BTN_CAM_UP]		= 'W';
	nJoyAssign[BTN_A]			= JOY_BUTTON3;
	nJoyAssign[BTN_B]			= JOY_BUTTON4;
	nJoyAssign[BTN_C]			= JOY_BUTTON1;
	nJoyAssign[BTN_D]			= JOY_BUTTON2;
	nJoyAssign[BTN_R1]			= JOY_BUTTON6;
	nJoyAssign[BTN_R2]			= JOY_BUTTON8;
	nJoyAssign[BTN_L1]			= JOY_BUTTON5;
	nJoyAssign[BTN_L2]			= JOY_BUTTON7;

	_debugInfo = 0;

}
//void INPUT::_DrawDbgStr()
//{
//	char str[256];
//	char *btnName[] = {
//	"BTN_RIGHT",
//	"BTN_LEFT",
//	"BTN_DOWN",
//	"BTN_UP",
//	"BTN_CAM_RIGHT",	//x+
//	"BTN_CAM_LEFT",	//x-
//	"BTN_CAM_DOWN",
//	"BTN_CAM_UP",
//	"BTN_A",
//	"BTN_B",
//	"BTN_C",
//	"BTN_D",
//	"BTN_START",
//	"BTN_SELECT",
//	};
//	sprintf_s(str,"Axis LX:%d\nAxis LY:%d\n", JoyInfoEx.dwXpos, JoyInfoEx.dwYpos);
//	strcat_s(g_szDebug,str);
//	sprintf_s(str,"Axis RX:%d\nAxis RY:%d\n", JoyInfoEx.dwRpos, JoyInfoEx.dwZpos);
//	strcat_s(g_szDebug,str);
//
//	for(int i=0; i<MAX_BUTTON;i++)
//	{
//		sprintf_s(str,"%s:%d\n", btnName[i], nBtnState[i]);
//		strcat_s(g_szDebug,str);
//	}
//
//	sprintf_s(str,"GetU:%f\n", GetAxis(BTN_UP));
//	strcat_s(g_szDebug,str);
//	sprintf_s(str,"GetD:%f\n", GetAxis(BTN_DOWN));
//	strcat_s(g_szDebug,str);
//	sprintf_s(str,"GetR:%f\n", GetAxis(BTN_RIGHT));
//	strcat_s(g_szDebug,str);
//	sprintf_s(str,"GetL:%f\n", GetAxis(BTN_LEFT));
//	strcat_s(g_szDebug,str);
//	
//}
int INPUT_MNG::GetBtnState(int name)
{
	if(name < MAX_BUTTON)
		return nBtnState[name];
	return -1;
}

//---------------------------------------------------------
//引数：	欲しい方向 BTN_UP,BTN_RIGHT ect.
//戻り値：	スティック入力を-1.0f～1.0fに変換
float INPUT_MNG::GetAxis(int name)
{
	if(name <= BTN_UP)
	{

		if(nBtnState[name])	//スティックがしきい値以上なら数値を返す
		{
			if(nJoyBtnState[name])
				return -(nStickAxis[name / 2]-STICK_BORDER)/(float)STICK_BORDER;

			if(name % 2)
				return 1.0f;	//マイナス方向
			else
				return -1.0f;	//プラス方向
		}
		else
			return 0.0f;

	}
	return -999;
}
//動いているか
bool INPUT_MNG::isMove()
{
	return (nBtnState[BTN_UP] || nBtnState[BTN_DOWN] || nBtnState[BTN_RIGHT] || nBtnState[BTN_LEFT]);
}