//################################################
//<Main.cpp>
//�}�C���X�C�[�p�쐬
//2012/07/12 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#define STRICT
#include "Main.h"

#include "Common.h"		//���ʃw�b�_
#include "GameMain.h"
#include "Graphic.h"
#include "resource.h"	//���\�[�X�w�b�_
#include "JoyPad.h"		//�R���g���[��
#include "Random.h"		//�����_���l
//================================================
//�萔��`
//================================================
#define CLASS_NAME		_T("JUVADA")		//�E�B���h�E�N���X��
#define CAPTION_NAME	_T("JUVADA")		//�L���v�V������

#define FRAME_RATE			(1000/60)						//�t���[�����[�g
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - SCREEN_WIDTH ) / 2)  //�E�B���h�E�̕\���ʒu
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - SCREEN_HEIGHT ) / 2) //�E�B���h�E�̕\���ʒu


//================================================
//�O���[�o����`
//================================================
bool g_bWindow;				//�E�B���h�E���[�h
bool g_bEnd;				//�Q�[���I���t���O
float g_fFPS;				//FPS�J�E���^
DWORD	 dwExecLastTime;
//================================================
//�v���g�^�C�v�錾
//================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//+++++++++++++++++++++++++++++++++++++++++++++++++
//���C���֐�
//-------------------------------------------------
//�������y�у��C�����[�v
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

	//�E�B���h�E �N���X��o�^
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

	//�E�B���h�E �T�C�Y���擾
	RECT rc = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	DWORD dwExStyle = 0;
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	//�E�B���h�E���쐬
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
		return 0;	//OpenGL �̏�����

	//�ϐ�������
	timeBeginPeriod(1);									//�^�C�}�̕���\���ŏ��ɃZ�b�g
	dwFPSLastTime = dwExecLastTime = timeGetTime();		//���݂̃V�X�e�� �^�C�}���擾
	dwExecLastTime -= FRAME_RATE;
	dwFrameCount = 0;
	g_fFPS = 0.0f;

	//�}�E�X�J�[�\���ʒu���Œ肷��
	//SetCursorPos( WINDOW_X + SCREEN_WIDTH / 2, WINDOW_Y + SCREEN_HEIGHT / 2 );	//�E�B���h�E�̒��S�ʒu�ɌŒ�
	ShowCursor(false);

	//���C�� �E�C���h�E ���[�v
	msg.message = WM_NULL;

	//�����ݒ�
	InitRandom();

	while (WM_QUIT != msg.message && !g_bEnd)	//WM_QUIT �����邩�A�I���t���O�����܂Ń��[�v
	{
		if (PeekMessage(&msg,NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			dwCurrentTime = timeGetTime();					//���݂̃^�C�}�l���擾
			if (dwCurrentTime - dwFPSLastTime >= 500)		//0.5 �b���ƂɌv��
			{
				//�t���[�������v�Z
				g_fFPS = dwFrameCount * 1000.0f / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//�^�C�}�l���X�V
				dwFrameCount = 0;				//�t���[�� �J�E���^�����Z�b�g
			}
			//���̕ӂŎ��ԊǗ�
			while (dwCurrentTime - dwExecLastTime >= FRAME_RATE)	//��莞�Ԃ��o�߂�����E�E�E
			{
				dwExecLastTime += FRAME_RATE;						//�^�C�}�l���X�V
			
				GameMain(hWnd);										//�Q�[�� ���C������
			}
			RenderGraphics();								//�����_�����O���������s
			dwFrameCount++;									//�t���[�� �J�E���g���{�P
			Sleep(1);										//�������� Windows �ɐ����߂�
		}

		//�I���m�F
		if(g_bEnd)
		{
			//if (IDNO == MessageBox(hWnd, _T("�Q�[�����I�����܂����H"), _T("�I���m�F"), MB_YESNO))
			//	g_bEnd = false;

		}

	}
	timeEndPeriod(1);						//�V�X�e�� �^�C�}�̕���\�����ɖ߂�
	return (int)msg.wParam;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//�E�B���h�E�v���V�[�W��
//-------------------------------------------------
//OS���̃��b�Z�[�W���y�ё��M
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
//���j���[�̃E�B���h�E
//-------------------------------------------------
//OS���̃��b�Z�[�W���y�ё��M
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
BOOL OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD	wNotify	= HIWORD(wParam);	//�ʒm�R�[�h
	WORD	wID		= LOWORD(wParam);	//����ID�A�R���g���[��ID�A�A�N�Z�����[�^ID
	HWND	hwndCtl	= (HWND)lParam;		//�R���g���[���̃n���h��

	switch (wID) {
	case ID_EXIT:		//�I��(X)
		PostMessage(hWnd, WM_CLOSE, 0, 0);
		return TRUE;	//������
	case ID_VERSION:	//�w���v(H)->�o�[�W�������(A)
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		MAKEINTRESOURCE(ID_PROPERTY), hWnd, AboutDlgProc);
		return TRUE;	//������
	}
	return FALSE;		//������

}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//�o�[�W�������_�C�A���O
//-------------------------------------------------
//OS���̃��b�Z�[�W���y�ё��M
//--in---------------------------------------------
//
//--out---------------------------------------------
//
//+++++++++++++++++++++++++++++++++++++++++++++++++
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return TRUE;	//����̃R���g���[���Ƀt�H�[�J�X��ݒ�
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:	//�L�����Z���@�{�^��
		case IDOK:		//OK
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;	//������(=�f�t�H���g�̏��������s�����)
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//FPS�l�̎󂯓n��
//-------------------------------------------------
//FPS���o�͂��邽�߁AStr.cpp�y�эX�VGameMain.cpp��
//--in---------------------------------------------
//�Ȃ�
//--out---------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
float GetFPS(void)
{
	return g_fFPS;					//�t���[�����J�E���g�p
}

void SetExecTime(DWORD time)
{
	dwExecLastTime = time;
}