//################################################
//<CubeMap.cpp>
// ���I�L���[�u�}�b�s���O
//------------------------------------------------
//2012/01/22 ~
//						Akihito Tanaka
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "CubeMap.h"

//================================================
//�O���[�o���ϐ�
//================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
CUBEMAP::CUBEMAP()
{
	pCamera = CAMERA::Instance();
	pPlayer = PLAYER::Instance();
	pEnemyMng = ENEMYMNG::Instance();
	pField = FIELD::Instance();

}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
CUBEMAP::~CUBEMAP()
{
	Release(uTexID);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�L���[�u�}�b�v�����ݒ�
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�e�N�X�`��ID
//+++++++++++++++++++++++++++++++++++++++++++++++++
GLuint CUBEMAP::InitCubeMap(void)
{
	//�e�N�X�`���T�C�Y
	int width  = TEXWIDTH;
	int height = TEXHEIGHT;

	//�e�N�X�`���̃A�h���X�w��
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glGenTextures(1, &uTexID);					//�e�N�X�`������
	glBindTexture(GL_TEXTURE_CUBE_MAP, uTexID);	//�L���[�u�}�b�v�Ƃ��ăo�C���h

	//�L���[�u�}�b�v�p�����[�^�ݒ�
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );


	//�L���[�u�}�b�s���O�p�̃e�N�X�`�����W�𐶐�����
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	//�e�N�X�`����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA,
				  TEXWIDTH, TEXHEIGHT,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

	//�@�����_�[�o�b�t�@�̐ݒ�
	glGenRenderbuffersEXT(1, &uRB);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, uRB);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	
	//�@�t���[���o�b�t�@�̐ݒ�
	glGenFramebuffersEXT(1, &uFB);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, uFB);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, uRB);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	return uTexID;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�L���[�u�}�b�v����
//-------------------------------------------------
//
//--in---------------------------------------------
//�I�u�W�F�N�g���W
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CUBEMAP::MakeCubeMap(VECTOR3 vPos)
{
	m_Center = vPos;
	SaveFramebufferStatus();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, uFB);

	RenderToTex( GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						  -1.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f );
	RenderToTex( GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						  1.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f );
	RenderToTex( GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						  0.0f, -1.0f, 0.0f,
						  0.0f, 0.0f, 1.0f );
	RenderToTex( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						  0.0f, 1.0f, 0.0f,
						  0.0f, 0.0f, -1.0f );
	RenderToTex( GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						  0.0f, 0.0f ,1.0f,
						 0.0f, 1.0f, 0.0f );
	RenderToTex( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
						  0.0f, 0.0f, -1.0f,
						  0.0f, 1.0f, 0.0f );
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	RestoreFramebufferStatus();

	//��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, (double)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�e�N�X�`���̊J��
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CUBEMAP::Release(GLuint uTexID)
{
	if (uTexID == 0)
		return;
	glDeleteTextures(1, &uTexID);	// �e�N�X�`���I�u�W�F�N�g�����
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�t���[���o�b�t�@�ɕ`��
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CUBEMAP::RenderToTex(GLenum target, double vx, double vy, double vz, 
										 double ux, double uy, double uz)
{
	//�����_�����O����w��
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, target, uTexID, 0);
	// ��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ�
	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 10000.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0.0, 0.0f, 0.0f, vx, vy, vz, ux, uy, uz );
	glLightfv(GL_LIGHT0, GL_POSITION, GetLight());
	glTranslatef(m_Center.x, m_Center.y + 0.5f, m_Center.z);
	MATRIX mat = pCamera->m_CameraMat;
	mat._41 = mat._42 = mat._43 = 0.0f;
	glMultMatrixf((GLfloat *)mat.m);

	glPushMatrix();

	pField->Draw();
	//pPlayer->Draw();
	pEnemyMng->Draw();

	glPopMatrix();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
//�t���[���o�b�t�@�̏�ԕۑ�
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CUBEMAP::SaveFramebufferStatus( void )
{
	glGetIntegerv( GL_VIEWPORT, (GLint *)viewport );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//�t���[���o�b�t�@�̏�Ԃ𕜌�
//-------------------------------------------------
//
//--in---------------------------------------------
//�Ȃ�
//--out--------------------------------------------
//�Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void CUBEMAP::RestoreFramebufferStatus( void )
{
	glViewport( viewport[ 0 ], viewport[ 1 ], viewport[ 2 ], viewport[ 3 ] );
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}