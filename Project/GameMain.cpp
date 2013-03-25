//################################################
//<GameMain.cpp>
// �Q�[�����C���֘A����
//------------------------------------------------
//JUVADA����
//2012/07/12 ~						SekiyamaRumi
//2013/1/22		���}�b�v�ǉ�		Akihito Tanaka
//2013/1/27		�^�C�g�������}�[�W	Akihito Tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "GameMain.h"	//GameMain�w�b�_�[
#include "TexMng.h"		//�e�N�X�`���Ǘ��֘A( 2D )
#include "Common.h"		//���ʒ�`�֘A
#include "Camera.h"		//�J�����֘A
#include "Graphic.h"
#include "Shadow.h"		//�e

//�Q�[���A�N�Z�T���[
#include "Score.h"		//�X�R�A
#include "Player.h"		//�v���C���[
#include "EnemyMng.h"	//�G�l�~�[
#include "Field.h"		//�t�B�[���h
#include "Collision.h"	//�Փ˔���
#include "Ambient.h"	//���G�t�F�N�g
#include "PlayerHpBar.h"	//�v���C���[�̂g�o�o�[
#include "EnemyBossHpBar.h"	//�{�X�̂g�o�o�[
#include "EffectMng.h"	//�G�t�F�N�g�}�l�[�W���[
#include "Time.h"		//����
#include "2DPoly.h"		//�|���S��
#include "Sound.h"

//�Q�[���J��
#include "Opening.h"	//�I�[�v�j���O
#include "Select.h"		//�Z���N�g
#include "Ending.h"		//�G���f�B���O
#include "Result.h"		//����

#include "Input.h"		//���͐���

#include <process.h>

//================================================
//�\���̒�`
//================================================

//================================================
//�萔��`
//================================================
#define FONT_WIDTH			(10)	//�t�H���g��
#define FONT_HEIGHT			(16)	//�t�H���g����

//================================================
//�O���[�o���ϐ�
//================================================
//�f�o�b�O������
GLuint		g_uFontTexID;			//�t�H���g�e�N�X�`�� ID
TCHAR		g_szDebug[1028];		//�o�͕�����o�b�t�@
TCHAR		g_szDebug2[1028];		//�o�͕�����o�b�t�@
int			g_nStatus = INIT;		//�Q�[���̏�ԕω�

bool		g_CubeFlg = true;		//�L���[�u�}�b�v�\���t���O		
bool		g_loadFlg = false;

//�N���X�|�C���^��`
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

//���[�h�X���b�h
HANDLE	Loadhandle;

void SetThread(void);
unsigned int WINAPI Loading (void *arg);
//================================================
//�v���g�^�C�v�錾
//================================================
void DrawChar(int x, int y, int c);
void DrawStr(int x, int y, LPCTSTR psz);
//+++++++++++++++++++++++++++++++++++++++++++++++++
// �Q�[���{�҂̍X�V����
//-------------------------------------------------
// �Q�[���̃��C����������
//--in---------------------------------------------
// �E�B���h�E�n���h��
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void GameMain(HWND hWnd)
{
#if (DEBUG_ON)

	TCHAR	str[256];
	g_szDebug[0] = _T('\0');	//�f�o�b�O �X�g�����O �o�b�t�@������
	_stprintf_s(str, _T("FPS = %.1f PLAYER_POS: X:%.1f Y:%.1f Z:%.1f \n NUM: 1:%f 2:%f 3:%f \n"), GetFPS(), x, y, z, num1, num2, num3);
	lstrcat(g_szDebug, str);

#endif
	VECTOR3 vecx, vecy;
	//��ʑJ��
	switch(g_nStatus)
	{
	case INIT:
		CreateClass();			//�N���X�̈�̊m�ۂƃ��[�h
		p_Field->Init();			//�t�B�[���h
		p_Result->Init();
		g_loadFlg = false;
		SetThread();
		g_nStatus = LOADING;	//�X���[
	case LOADING:
		if(g_loadFlg)
		{
			g_nStatus = STARTINIT;
			CloseHandle(Loadhandle);
		}
		break;
	case STARTINIT:
		p_Op->Init();				//�I�[�v�j���O
		p_Camera->ResetOp();		//�J�����̃��Z�b�g
		g_nStatus = START;

		break;
	case START:
		p_Camera->SetOpCamera();	//�J�����̃Z�b�g
		if(p_Op->Update())
			g_nStatus = MENU_INIT;
		break;
	case MENU_INIT:
		p_Camera->ResetOp();		//�J�����̃��Z�b�g
		p_Select->Init();
		g_nStatus = MENU;
		break;
	case MENU:
		p_Camera->SetOpCamera();	//�J�����̃Z�b�g
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
		p_Ambient->Init();			//��
		p_Score->Init();			//�X�R�A�̏�����
		p_Player->Init();			//�v���C���[
		p_Enemy->Init(p_Player);	//�G�l�~�[
		p_PlayerHpBar->Init();		//�v���C���[�o�[
		p_BossHpBar->Init();		//�{�X�o�[
		p_2D->Init();
		
		//SetThread();
		g_nStatus = GAME_INIT;	//�X���[
	case GAME_INIT:
		//����
		//p_Score->Load();
		//p_Ambient->Load();
		//p_Player->Load();
		//p_Enemy->Load();
		//p_BossHpBar->Load();
		p_2D->Load();
		p_EffectMng->Load();

		//���Z�b�g
		p_Ambient->Reset();			//���̃��Z�b�g
		p_Player->Reset();			//�v���C���[�̃��Z�b�g
		p_Score->Reset();			//�X�R�A�̃��Z�b�g
		p_Enemy->Reset();			//�G�l�~�[�̃��Z�b�g
		p_Camera->ResetGame();		//�J�����̃��Z�b�g
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
	case GAME_RESET:	//���Z�b�g
		p_Player->Reset();			//�v���C���[�̃��Z�b�g
		p_Camera->ResetGame();		//�J�����̃��Z�b�g
		p_PlayerHpBar->Reset();
		p_BossHpBar->Reset();
		g_nStatus = GAME;
		break;
	case GAME:
		if(GetAsyncKeyState(VK_F12)&0x0001)
			g_CubeFlg ^= 1;
		p_Time->Update();
		p_Score->Update(p_Enemy->m_DeadCnt, p_Enemy->m_BossCnt);	//�X�R�A
		p_Field->Update();			//�n�`
		p_Camera->GetVecCamera();	//�J����
		p_Enemy->Update();			//�G�l�~�[
		p_Player->Update(p_Camera->vecx, p_Camera->vecz);	//�v���C���[
		p_Collision->Update();		//�Փ˔���
		p_Ambient->Update(p_Enemy->m_DeadCnt, p_Enemy->m_pEnemyBoss->m_AppearBoss);
		p_PlayerHpBar->Update(p_Player->m_Life, 100);	//�v���C���[�̂g�o�o�[
		p_BossHpBar->Update(p_Enemy->m_pEnemyBoss->m_Life, 100);	//�{�X�̂g�o�o�[

		//�{�X�������Ă���L1�������ꂽ��Z���ڂ�����
		if(pInput->GetBtnState(BTN_L1) == PRESS && p_Enemy->m_pEnemyBoss->m_Live)
		{
			p_Camera->SetOperatable(false);
		}
		//L1�������ꂽ�Ƃ��͒ʏ폈���ɖ߂�
		else if( pInput->GetBtnState(BTN_L1) == RLS )
		{
			p_Camera->SetOperatable(true);
		}

		if(pInput->GetBtnState(BTN_L2) == PRESS && pInput->GetBtnState(BTN_B) == PRESS )
		{
			p_Enemy->m_DeadCnt = 100; //�f�o�O�{�X�o���p
		}
		p_Camera->Update(p_Player->m_Pos, p_Enemy->m_pEnemyBoss->m_Pos);
		p_EffectMng->UpDate();
		
		{	
			//�f�o�b�N�\���p
			x = p_Player->m_Pos.x;
			y = p_Player->m_Pos.y;
			z = p_Player->m_Pos.z;
			num1 = p_Player->m_Matrix._11;
			num2 = (float)p_Enemy->m_pEnemyBoss->m_Life;
			//rad = p_Player->m_Matrix._13;
			//num3 = (float)p_Player->m_Life;
			num3 = p_PlayerHpBar->nM;
		}
		

		//����
		if(p_Enemy->m_BossCnt)
			g_nStatus = GAME_FILLER_END;
		
		if(p_Player->m_bRetry)
			g_nStatus = GAME_FILLER_END;

#if (DEBUG_ON)
		//�f�o�b�N�p
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
		p_Camera->ResetOp();		//�J�����̃��Z�b�g	OP�Ɠ���
		p_Camera->SetOpCamera();	//�J�����̃Z�b�g
		
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
		p_SE->del();			//�T�E���h�̊J��
		DeCreateClass();		//�N���X�̉��
		g_bEnd = true;			//�Q�[���I��
		return;
	default:break;
	}
	
	if(pInput != NULL)
	{
		pInput->Update();
		
		//�v���[���p
		if(pInput->GetBtnState(BTN_L1) == PRESS && pInput->GetBtnState(BTN_R1) == PRESS
		&& pInput->GetBtnState(BTN_L2) == PRESS && pInput->GetBtnState(BTN_R2) == PRESS)
		{
			p_SE->Reset();		//�T�E���h���Z�b�g
			g_nStatus = STARTINIT;
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// 3D�`��{��
//-------------------------------------------------
// �`���3D�����̕`����s���֐�
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMain()
{
	GLfloat fogCol[] = {0.7f, 0.7f, 0.7f, 0.3f};	
	//3D�p�`��Q�[���J��
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
	case GAME_RESET:		//�X���[
	case GAME_FILLER_START://�X���[
	case GAME:
		//if(g_CubeFlg)
		//{
		//	//�L���[�u�}�b�v�`��
		//	p_Player->DrawCubeMap();

		//	Init3D();
		//}

		//�t�H�O
		glEnable(GL_FOG);

		//���f���`��
		p_Field->Draw();
		//if(g_CubeFlg)
		//	p_Player->DrawCube();
		//else
			p_Player->Draw();

		p_Enemy->Draw();
		p_Ambient->Draw();
		p_Field->DrawFence();
		glDisable(GL_FOG);
		//�e�`��
		//p_Shadow->CreateShadow((OBJECT *)p_Player);	//�v���C���[

		for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
		{
			if(p_Enemy->m_pEnemy[i]->m_Live == false)
				continue;
			p_Shadow->CreateShadow((OBJECT *)p_Enemy->m_pEnemy[i]);	//�G�l�~�[
		}

		for(int i = 0; i < 9; i ++)
		{
			if(p_Enemy->m_pEnemy[i]->m_Live == false)
				continue;
			p_Shadow->CreateShadow((OBJECT *)p_Enemy->m_pEnemy[i]);	//�G�l�~�[
		}

		//�G�t�F�N�g
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
// 2D�`��{��
//-------------------------------------------------
// �`���2D�����̕`����s���֐�
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawPict()
{
	//�e�N�X�`���L����
	glEnable(GL_TEXTURE_2D);	

	//2D�p�`��Q�[���J��
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
		//p_Score->Draw();		//�X�R�A�̏o��
		p_BossHpBar->Draw();	//�v���C���[�̂g�o�o�[
		p_PlayerHpBar->Draw();	//�v���C���[�̂g�o�o�[
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

	DrawStr(0, 0, g_szDebug);	//FPS���
	DrawStr(0, 0, g_szDebug2);	//�R���g���[�����

#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// �f�[�^�̓ǂݍ���
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void LoadData(void)
{
	//�t�H���g �Z�b�g�A�b�v
	g_uFontTexID = g_TexMng.GetTexture("TEXTURE\\2D\\font.tga", "FPS");
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X�̍쐬
//-------------------------------------------------
// �N���X�̐����̈�̊m��
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CreateClass(void)
{
	switch(g_nStatus)
	{
	case INIT:
		//�N���X����
		p_Player = PLAYER::Instance();	//�v���C���[
		p_Enemy = ENEMYMNG::Instance();	//�G�l�~�[
		p_Camera = CAMERA::Instance();
		p_Collision = COLLISION::Instance();	//�Փ˔���
		p_Shadow = SHADOW::Instance();
		p_Ambient = new AMBIENT;
		p_PlayerHpBar = PLAYER_HP_BAR::Instance();	//�v���C���[�g�o�o�[
		p_BossHpBar = BOSS_HP_BAR::Instance();	//�v���C���[�g�o�o�[
		p_EffectMng = EFFECT_MNG::Instance();
		p_Field = FIELD::Instance();			//�t�B�[���h
		p_Result = RESULT_MNG::Instance();
		p_Score = SCORE::Instance();	//�X�R�A
		pInput = INPUT_MNG::getInstance();		//���͐���
		p_Time = TIME_MNG::Instance();
		p_2D = new SPLITE;
		p_SE = SOUND::Instance();
		p_Op = new OP;
		p_Select = new SELECT;		//�Z���N�g���


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
// �N���X�̉��
//-------------------------------------------------
// �N���X�̐����̈�̉������
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �Ȃ�
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
// �����`��
//-------------------------------------------------
// FPS�o�͗p�e�N�X�`������̔����o��
//--in---------------------------------------------
// ���W�ʒu
// ���l
//--out---------------------------------------------
// �Ȃ�
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

	glEnable(GL_TEXTURE_2D);	//�e�N�X�`���L����
	glBindTexture(GL_TEXTURE_2D, g_uFontTexID);
	glInterleavedArrays(GL_T2F_V3F, 0, vtxQuad);
	glDrawArrays(GL_QUADS, 0, 4);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ������̕`��
//-------------------------------------------------
// ������Ƃ��ďo��
//--in---------------------------------------------
// �ʒu���W
// ������
//--out---------------------------------------------
// �Ȃ�
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
// �V�[�������󂯓n��
//-------------------------------------------------
// �V�[���ɂ���Ƃ̕���Ɏg�p
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// �V�[�����
//+++++++++++++++++++++++++++++++++++++++++++++++++
int GetGMState(void)
{
	return g_nStatus;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���[�h�X���b�h�̃Z�b�g
//-------------------------------------------------
//--in---------------------------------------------
// �Ȃ�
//--out--------------------------------------------
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++
void SetThread(void)
{
	Loadhandle = (HANDLE)_beginthreadex(NULL, 0, Loading, NULL, 0, NULL);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���[�h�X���b�h
//-------------------------------------------------
//--in---------------------------------------------
// �Ȃ�
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
		//���[�h
		//p_Score->Load();
		//p_Ambient->Load();
		//p_Player->Load();
		//p_Enemy->Load();
		//p_BossHpBar->Load();
		//p_2D->Load();
		//p_EffectMng->Load();

		////���Z�b�g
		//p_Ambient->Reset();			//���̃��Z�b�g
		//p_Player->Reset();			//�v���C���[�̃��Z�b�g
		//p_Score->Reset();			//�X�R�A�̃��Z�b�g
		//p_Enemy->Reset();			//�G�l�~�[�̃��Z�b�g
		//p_Camera->ResetGame();		//�J�����̃��Z�b�g
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