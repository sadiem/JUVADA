//################################################
// <Include.cpp>
// �C���N���[�h����ėp�w�b�_�[
//------------------------------------------------
// 2012/09/25 ~
//						SekiyamaRumi
//################################################
#ifndef ______INCLUDE_H_____
#define ______INCLUDE_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include <windows.h>		//Windows
#include <stdio.h>			//�����񏈗��Ŏg�p
#include <tchar.h>			//�ėp�e�L�X�g
#include <mmsystem.h>		//���ԊǗ��Ŏg�p

#include <GL/glew.h>		//OpenGL �֘A�̃w�b�_
#include <GL/wglew.h>		//OpenGL �֘A�̃w�b�_
#include "wglext.h"

//================================================
//���C�u������`
//================================================
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "winmm.lib")

//�f�o�b�O�p�}�N��
#ifdef _DEBUG
#define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf( c, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#define MyOutputDebugString( str, ... ) // �����
#endif

//################################################
// End of File
//################################################
#endif ______INCLUDE_H_____

