//################################################
//<FBO.cpp>
// �t���[���o�b�t�@
//------------------------------------------------
//2012/01/30 ~
//						Akihito Tanaka
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "FBO.h"

FBO::FBO()
{
    fbID = 0;
    rbID = 0;
    texID = 0;
	//Init();
}

FBO::~FBO()
{
	glDeleteFramebuffersEXT(1, &fbID);
    glDeleteRenderbuffersEXT(1, &rbID);
    glDeleteTextures(1, &texID);

    fbID = 0;
    rbID = 0;
    texID = 0;
}

void FBO::Init()
{
	//�e�N�X�`���̃A�h���X�w��
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glGenTextures(1, &texID);					//�e�N�X�`������
	glBindTexture(GL_TEXTURE_2D, texID);		//2D�e�N�X�`���Ƃ��ăo�C���h

	//�e�N�X�`���p�����[�^�ݒ�
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
    //�@�����_�[�o�b�t�@�̐ݒ�
    glGenRenderbuffersEXT(1, &rbID);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbID);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT);

	
    //�@�t���[���o�b�t�@�̐ݒ�			FBO�g�p���ŏ���
    //glGenFramebuffersEXT(1, &fbID);
    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);
    //glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texID, 0);
    //glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbID);
    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::Start(void)
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);
}

void FBO::End(void)
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}