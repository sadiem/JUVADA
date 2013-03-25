//################################################
// <Include.cpp>
// インクルードする汎用ヘッダー
//------------------------------------------------
// 2012/09/25 ~
//						SekiyamaRumi
//################################################
#ifndef ______INCLUDE_H_____
#define ______INCLUDE_H_____

//================================================
//インクルードヘッダ
//================================================
#include <windows.h>		//Windows
#include <stdio.h>			//文字列処理で使用
#include <tchar.h>			//汎用テキスト
#include <mmsystem.h>		//時間管理で使用

#include <GL/glew.h>		//OpenGL 関連のヘッダ
#include <GL/wglew.h>		//OpenGL 関連のヘッダ
#include "wglext.h"

//================================================
//ライブラリ定義
//================================================
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "winmm.lib")

//デバッグ用マクロ
#ifdef _DEBUG
#define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf( c, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#define MyOutputDebugString( str, ... ) // 空実装
#endif

//################################################
// End of File
//################################################
#endif ______INCLUDE_H_____

