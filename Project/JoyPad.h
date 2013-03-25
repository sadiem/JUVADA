//################################################
// <JoyPad.h>
// �R���g���[���֘A
//------------------------------------------------
// 2012/09/27 ~
//						SekiyamaRumi
//################################################
#ifndef _____JOYPAD_H_____
#define _____JOYPAD_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//�C���N���[�h�w�b�_
//================================================
//�萔��`
//================================================
enum JOYPAD_STATE{
	JOYBUTTON_1 = 0,		//�{�^�� < 1 >
	JOYBUTTON_2,			//�{�^�� < 2 >
	JOYBUTTON_3,			//�{�^�� < 3 >
	JOYBUTTON_4,			//�{�^�� < 4 >
	JOYBUTTON_5,			//�{�^�� < 5 >
	JOYBUTTON_6,			//�{�^�� < 6 >
	JOYBUTTON_7,			//�{�^�� < 7 >
	JOYBUTTON_8,			//�{�^�� < 8 >
	JOYBUTTON_9,			//�{�^�� < 9 >
	JOYBUTTON_10,			//�{�^�� < 10 >
	JOYBUTTON_11,			//�{�^�� < 11 >
	JOYPAD_LEFT_X,		//�X�e�B�b�N���E < X >
	JOYPAD_LEFT_Y,		//�X�e�B�b�N�㉺ < Y >
	JOYPAD_RIGHT_Z,		//�X�e�B�b�N���E < Z >
	JOYPAD_RIGHT_R,		//�X�e�B�b�N�㉺ < R >

	KEY_NUM					/* �L�[�̑��� */
};
struct JoyInfo
{
	int	JoyState;		//���݂̏��
	int	PrevJoyState;	//�O�̏��
	int	StickState;		//�X�e�B�b�N���
	DWORD StickDate;	//�X�e�B�b�N�̓|��
};
extern TCHAR g_szDebug2[1028];		//�o�͕�����o�b�t�@
//================================================
//�N���X��`
//================================================
class C_JOYPAD{
public:
	static C_JOYPAD* Instance(){
		static C_JOYPAD inst;
		return &inst;
	};
private:
	C_JOYPAD();
	bool  m_Conect;		//�ڑ���Ԕ���
public:
	~C_JOYPAD();

	JoyInfo m_JoySate[KEY_NUM];
	JOYINFOEX JOYPAD;

	void InitJoyPad(void);				//������
	void GetJoyPad(HWND hWnd);			//�W���C�X�e�B�b�N���擾
	bool GetJoyPadTrigger(int type);	//�g���K�[
	bool GetJoyPadRelease(int type);	//�����[�X
	int GetJoyPadStick(int nType);		//�X�e�B�b�N
	bool CheckJoyPad(void);				//�ڑ��m�F
	float KeyDownSpeed(DWORD key);		//�L�[�̓|������-1�`1�͈̔͂ŏo��
	void Update(HWND hWnd);				//�X�V
	
	void Debag(void);	//�f�o�b�N�o��
};
//################################################
// End of File
//################################################
#endif _____JOYPAD_H_____