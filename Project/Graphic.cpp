//################################################
// <Graphic.cpp>
//
//------------------------------------------------
// 2012/09/20 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Graphic.h"		//グラフィックヘッダ
#include "GameMain.h"		//ゲームメインヘッダ
#include "Camera.h"			//カメラマネージャヘッダ
//================================================
//定数定義
//================================================
//================================================
//グローバル変数
//================================================
HDC			g_hDC;					//デバイスコンテキスト
HGLRC		g_hRC;					//カレントコンテキスト
GLfloat		g_MatView[4][4];		//ビュー マトリックス
GLfloat		g_MatViewInv[4][4];		//ビュー マトリックスの逆行列
GLfloat		g_MatProj[4][4];		//プロジェクション マトリックス
CAMERA		*pCamera;
VECTOR3      g_VecLight;				//ライトベクトル保存用
//================================================
//プロトタイプ宣言
//================================================
void GetInvRotationMat(void);

//++++++++++++++++++++++++++++++++++++++++++++++++
//OpenGLの初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitializeGraphics(HWND hWnd, bool bWindow)
{
		//ピクセル フォーマット
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Version
		PFD_DRAW_TO_WINDOW |	//Supports GDI
		PFD_SUPPORT_OPENGL |	//Supports OpenGL
		PFD_DOUBLEBUFFER,		//Use double buffering (more efficient drawing)
		PFD_TYPE_RGBA,			//No pallettes
		24, 					//Number of color planes
		 						//in each color buffer
		8,	0,					//for Red-component
		8,	0,					//for Green-component
		8,	0,					//for Blue-component
		8,	0,					//for Alpha-component
		0,						//Number of planes
								//of Accumulation buffer
		16,						//for Red-component
		16,						//for Green-component
		16,						//for Blue-component
		16,						//for Alpha-component
		24, 					//Depth of Z-buffer
		8,						//Depth of Stencil-buffer
		0,						//Depth of Auxiliary-buffer
		0,						//Now is ignored
		0,						//Number of planes
		0,						//Now is ignored
		0,						//Color of transparent mask
		0						//Now is ignored
	};

	//ウィンドウ／フル スクリーン切り替え
	if (!bWindow) {
		DEVMODE	devmode;
		devmode.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		devmode.dmBitsPerPel	= 32;
		devmode.dmPelsWidth		= SCREEN_WIDTH;
		devmode.dmPelsHeight	= SCREEN_HEIGHT;
		devmode.dmSize			= sizeof devmode;
		if (ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			MessageBox(hWnd, _T("フルスクリーン切り替えに失敗しました"),
				_T("error"), MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT, SWP_SHOWWINDOW);
	}

	//ウィンドウ コンテキストの取得
	g_hDC = GetDC(hWnd);

	//合致する最も近いピクセル フォーマットの選択
	int nPixelFormat = ChoosePixelFormat(g_hDC, &pfd);
	if (!nPixelFormat) {
		MessageBox(hWnd, _T("ピクセルフォーマットの選択に失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//ピクセル フォーマットの設定
	if (!SetPixelFormat(g_hDC, nPixelFormat, &pfd)) {
		MessageBox(hWnd, _T("ピクセルフォーマットの設定に失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//OpenGL レンダリング コンテキストを作成
	g_hRC = wglCreateContext(g_hDC);
	if (!g_hRC) {
		MessageBox(hWnd, _T("レンダリングコンテキストの生成に失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//OpenGL レンダリング コンテキストをメイク
	if (!wglMakeCurrent(g_hDC, g_hRC)) {
		MessageBox(hWnd, _T("レンダリングコンテキストのメイクに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// GLEW 初期化
	if (glewInit() != GLEW_OK) {
		MessageBox(hWnd, _T("GLEW の初期化に失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}



	pCamera = CAMERA::Instance();

	//return S_OK;
	
	
	//データ読み込み
	LoadData();

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//OpenGLクリーンアップ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CleanupGraphics(HWND hWnd, bool bWindow)
{

	wglMakeCurrent(NULL, NULL);
	if (g_hRC) {						// カレントコンテキストを解放
		wglDeleteContext(g_hRC);
		g_hRC = NULL;
	}
	if (g_hDC) {						// デバイスコンテキストを解放
		ReleaseDC(hWnd, g_hDC);
		g_hDC = NULL;
	}
	if (!bWindow)
		ChangeDisplaySettings(NULL, 0);

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//グラフィックのレンダリング
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT RenderGraphics()
{
	// バック バッファと Z バッファをクリア
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearStencil(0);		//クリア値の設定
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

	Init3D();
	//ライトの設定
	glEnable(GL_LIGHTING);	//ライトオン
	glEnable(GL_LIGHT0);	//ライトオン

	DrawMain();				//描画

	Init2D();
	//glColor3f(1.0f, 1.0f, 1.0f);
	DrawPict();
	// デバッグ ストリング描画
	glColor3f(1.0f, 1.0f, 1.0f);
	//DrawStr(0, 0, g_szDebug);

	// バック バッファをプライマリ バッファにコピー
	SwapBuffers(g_hDC);

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//２Ｄ用のレンダリングステートの初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void Init2D()
{

	//ライト無効化
	glDisable(GL_LIGHTING);

	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);

	//ポリゴンの片面だけ描画を無効化
	glDisable(GL_CULL_FACE);

	//深度バッファを無効化
	glDisable(GL_DEPTH_TEST);

	//アルファ ブレンディング有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0);

	//プロジェク ションマトリックスとして正射影を設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);

	//ビュー マトリックス設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



}

//++++++++++++++++++++++++++++++++++++++++++++++++
//３Ｄ用のレンダリングステートの初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void Init3D()
{
	//テクスチャを無効にする
	glDisable(GL_TEXTURE_2D);

	//ポリゴンの片面だけ描画を有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//深度バッファを有効化
	glEnable(GL_DEPTH_TEST);

	//アルファ ブレンディング無効化
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	//プロジェクション マトリックス設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (double)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	glGetFloatv(GL_PROJECTION_MATRIX, g_MatProj[0]);

	//ビュー マトリックス設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f,												//視点位置(X)
	//		  5.0f,											//視点位置(Y)
	//		  //SCREEN_HEIGHT * 0.5f / tanf(RAD * FOVY * 0.5f),	//視点位置(Z)
	//		  -5.0f, 
	//		  0.0f, 0.0f, 0.0f,		//注視点位置
	//		  0.0f, 1.0f, 0.0f);	//アップベクトル
	
	pCamera->SetGameCamera();

	glGetFloatv(GL_MODELVIEW_MATRIX, g_MatView[0]);

	//glViewport(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT);

	//逆行列の生成
	// GetInvRotationMat();
		
	//点光源設定
	g_VecLight.x = 0.0f;
	g_VecLight.y = 50.0f;
	g_VecLight.z = 0.0f;

	GLfloat fLight[4] = {1.0f, 1.0f, 1.0f, 1.0f};			//
	GLfloat fLightPost[4] = {g_VecLight.x, g_VecLight.y, g_VecLight.z, 1.0f};		//
	GLfloat fLightAmbient[4] = {0.5f, 0.5f, 0.5f, 1.0f};	
	GLfloat fLightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, fLightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fLightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPost);


	//ライトの許可
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		//点光源
}

void GetInvRotationMat(void)
{
	g_MatViewInv[0][0] = g_MatView[0][0];
	g_MatViewInv[0][1] = g_MatView[1][0];
	g_MatViewInv[0][2] = g_MatView[2][0];
	g_MatViewInv[1][0] = g_MatView[0][1];
	g_MatViewInv[1][1] = g_MatView[1][1];
	g_MatViewInv[1][2] = g_MatView[2][1];
	g_MatViewInv[2][0] = g_MatView[0][2];
	g_MatViewInv[2][1] = g_MatView[1][2];
	g_MatViewInv[2][2] = g_MatView[2][2];
}

GLfloat* GetViewMat(void)
{
	return &g_MatView[0][0];
}
float* GetLight(void)
{
	return &g_VecLight.v[0];
}
//################################################
// End of File
//################################################