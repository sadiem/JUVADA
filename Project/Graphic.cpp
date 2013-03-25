//################################################
// <Graphic.cpp>
//
//------------------------------------------------
// 2012/09/20 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Graphic.h"		//�O���t�B�b�N�w�b�_
#include "GameMain.h"		//�Q�[�����C���w�b�_
#include "Camera.h"			//�J�����}�l�[�W���w�b�_
//================================================
//�萔��`
//================================================
//================================================
//�O���[�o���ϐ�
//================================================
HDC			g_hDC;					//�f�o�C�X�R���e�L�X�g
HGLRC		g_hRC;					//�J�����g�R���e�L�X�g
GLfloat		g_MatView[4][4];		//�r���[ �}�g���b�N�X
GLfloat		g_MatViewInv[4][4];		//�r���[ �}�g���b�N�X�̋t�s��
GLfloat		g_MatProj[4][4];		//�v���W�F�N�V���� �}�g���b�N�X
CAMERA		*pCamera;
VECTOR3      g_VecLight;				//���C�g�x�N�g���ۑ��p
//================================================
//�v���g�^�C�v�錾
//================================================
void GetInvRotationMat(void);

//++++++++++++++++++++++++++++++++++++++++++++++++
//OpenGL�̏�����
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitializeGraphics(HWND hWnd, bool bWindow)
{
		//�s�N�Z�� �t�H�[�}�b�g
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

	//�E�B���h�E�^�t�� �X�N���[���؂�ւ�
	if (!bWindow) {
		DEVMODE	devmode;
		devmode.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		devmode.dmBitsPerPel	= 32;
		devmode.dmPelsWidth		= SCREEN_WIDTH;
		devmode.dmPelsHeight	= SCREEN_HEIGHT;
		devmode.dmSize			= sizeof devmode;
		if (ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			MessageBox(hWnd, _T("�t���X�N���[���؂�ւ��Ɏ��s���܂���"),
				_T("error"), MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT, SWP_SHOWWINDOW);
	}

	//�E�B���h�E �R���e�L�X�g�̎擾
	g_hDC = GetDC(hWnd);

	//���v����ł��߂��s�N�Z�� �t�H�[�}�b�g�̑I��
	int nPixelFormat = ChoosePixelFormat(g_hDC, &pfd);
	if (!nPixelFormat) {
		MessageBox(hWnd, _T("�s�N�Z���t�H�[�}�b�g�̑I���Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//�s�N�Z�� �t�H�[�}�b�g�̐ݒ�
	if (!SetPixelFormat(g_hDC, nPixelFormat, &pfd)) {
		MessageBox(hWnd, _T("�s�N�Z���t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//OpenGL �����_�����O �R���e�L�X�g���쐬
	g_hRC = wglCreateContext(g_hDC);
	if (!g_hRC) {
		MessageBox(hWnd, _T("�����_�����O�R���e�L�X�g�̐����Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//OpenGL �����_�����O �R���e�L�X�g�����C�N
	if (!wglMakeCurrent(g_hDC, g_hRC)) {
		MessageBox(hWnd, _T("�����_�����O�R���e�L�X�g�̃��C�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// GLEW ������
	if (glewInit() != GLEW_OK) {
		MessageBox(hWnd, _T("GLEW �̏������Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}



	pCamera = CAMERA::Instance();

	//return S_OK;
	
	
	//�f�[�^�ǂݍ���
	LoadData();

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//OpenGL�N���[���A�b�v
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CleanupGraphics(HWND hWnd, bool bWindow)
{

	wglMakeCurrent(NULL, NULL);
	if (g_hRC) {						// �J�����g�R���e�L�X�g�����
		wglDeleteContext(g_hRC);
		g_hRC = NULL;
	}
	if (g_hDC) {						// �f�o�C�X�R���e�L�X�g�����
		ReleaseDC(hWnd, g_hDC);
		g_hDC = NULL;
	}
	if (!bWindow)
		ChangeDisplaySettings(NULL, 0);

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�O���t�B�b�N�̃����_�����O
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT RenderGraphics()
{
	// �o�b�N �o�b�t�@�� Z �o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearStencil(0);		//�N���A�l�̐ݒ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

	Init3D();
	//���C�g�̐ݒ�
	glEnable(GL_LIGHTING);	//���C�g�I��
	glEnable(GL_LIGHT0);	//���C�g�I��

	DrawMain();				//�`��

	Init2D();
	//glColor3f(1.0f, 1.0f, 1.0f);
	DrawPict();
	// �f�o�b�O �X�g�����O�`��
	glColor3f(1.0f, 1.0f, 1.0f);
	//DrawStr(0, 0, g_szDebug);

	// �o�b�N �o�b�t�@���v���C�}�� �o�b�t�@�ɃR�s�[
	SwapBuffers(g_hDC);

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�Q�c�p�̃����_�����O�X�e�[�g�̏�����
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void Init2D()
{

	//���C�g������
	glDisable(GL_LIGHTING);

	//�e�N�X�`����L���ɂ���
	glEnable(GL_TEXTURE_2D);

	//�|���S���̕Жʂ����`��𖳌���
	glDisable(GL_CULL_FACE);

	//�[�x�o�b�t�@�𖳌���
	glDisable(GL_DEPTH_TEST);

	//�A���t�@ �u�����f�B���O�L����
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0);

	//�v���W�F�N �V�����}�g���b�N�X�Ƃ��Đ��ˉe��ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);

	//�r���[ �}�g���b�N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R�c�p�̃����_�����O�X�e�[�g�̏�����
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void Init3D()
{
	//�e�N�X�`���𖳌��ɂ���
	glDisable(GL_TEXTURE_2D);

	//�|���S���̕Жʂ����`���L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�[�x�o�b�t�@��L����
	glEnable(GL_DEPTH_TEST);

	//�A���t�@ �u�����f�B���O������
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	//�v���W�F�N�V���� �}�g���b�N�X�ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (double)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	glGetFloatv(GL_PROJECTION_MATRIX, g_MatProj[0]);

	//�r���[ �}�g���b�N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f,												//���_�ʒu(X)
	//		  5.0f,											//���_�ʒu(Y)
	//		  //SCREEN_HEIGHT * 0.5f / tanf(RAD * FOVY * 0.5f),	//���_�ʒu(Z)
	//		  -5.0f, 
	//		  0.0f, 0.0f, 0.0f,		//�����_�ʒu
	//		  0.0f, 1.0f, 0.0f);	//�A�b�v�x�N�g��
	
	pCamera->SetGameCamera();

	glGetFloatv(GL_MODELVIEW_MATRIX, g_MatView[0]);

	//glViewport(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT);

	//�t�s��̐���
	// GetInvRotationMat();
		
	//�_�����ݒ�
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


	//���C�g�̋���
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		//�_����
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