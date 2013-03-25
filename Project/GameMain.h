//################################################
//<GameMain.cpp>
// �Q�[�����C���֘A����
//------------------------------------------------
//JUVADA����
//2012/11/12 ~					SekiyamaRumi
//################################################
#ifndef _____GAMEMAIN_H_____
#define _____GAMEMAIN_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//���C���w�b�_�[
#include "Common.h"		//���C���w�b�_�[
#include "Object.h"		//�I�u�W�F�N�g
//================================================
//�萔��`
//================================================

//================================================
//�\���̒�`
//================================================

//================================================
//�\���̒�`
//================================================
enum STATE{
 INIT,						//������
 LOADING,					//���[�h��
 STARTINIT,					//�J�n������
 START,						//�J�n
 MENU_INIT,					//�Z���N�g������
 MENU,						//�Z���N�g
 GAME_INIT_START,					//���C��������
 GAME_INIT,					//���C��������
 GAME_FILLER_START,			//���C���̂Ȃ�
 GAME_RESET,				//���Z�b�g
 GAME,						//���C��
 GAME_FILLER_END,			//���C���Ȃ�
 RESULT_INIT,				//���ʏ�����	���s
 RESULT,					//����
 ENDINIT,					//�I��������
 END						//�I��
};

//================================================
//�v���g�^�C�v�錾
//================================================
void GameMain(HWND hWnd);
void DrawMain();
void DrawPict();		//�QD�\��
void CreateClass();		//�N���X�̍쐬
void DeCreateClass();	//�N���X�̉��



void LoadData(void);	//�f�[�^
int GetGMState();		//�V�[���󂯓n���p
#endif _____GAMEMAIN_H_____