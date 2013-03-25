//=======================================================================================
//
//	 ���͏���
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
	NONE,		//������Ă��Ȃ�
	TRG,		//�g���K
	PRESS,		//��������
	RLS,		//�����[�X
};

//extern TCHAR g_szDebug[4096];

class INPUT_MNG{
//�V���O���g��
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
	void BtnJudge(int nFncNum, int nBtnVal);	//�{�^����������
//	void _DrawDbgStr();

	int nKeyAssign[MAX_BUTTON];					//�L�[�{�[�h�L�[�R���t�B�O
	int	nJoyAssign[MAX_BUTTON];					//�Q�[���p�b�h�L�[�R���t�B�O

	bool bJoyStickConnect;			//�W���C�X�e�B�b�N���ڑ����Ă��邩
	int nJoyBtnState[MAX_BUTTON];	//�W���C�X�e�B�b�N�{�^�����
	int nKeyBtnState[MAX_BUTTON];	//�L�[�{�[�h�{�^�����
	int nBtnState[MAX_BUTTON];		//�{�^�����
	int nLastJoyBtnState[MAX_BUTTON];	//�O�t���[���{�^�����
	int nLastKeyBtnState[MAX_BUTTON];	//�O�t���[���{�^�����
	int nLastBtnState[MAX_BUTTON];	//�O�t���[���{�^�����
	int nStickAxis[MAX_AXIS];		//�X�e�B�b�N���
	JOYINFOEX JoyInfoEx;
	bool _debugInfo;
};

#endif