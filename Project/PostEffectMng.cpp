//################################################
//<PostEffect.cpp>
// �|�X�g�G�t�F�N�g����
//------------------------------------------------
//2013/2/4						Akihito Tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "PostEffectMng.h"

void POST_EFFECT_MNG::Init()
{
	RenderBuffer.Init();
	    
	//�@�t���[���o�b�t�@�̐ݒ�			FBO�g�p���ŏ���
    //glGenFramebuffersEXT(1, &fbID);
    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);
    //glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texID, 0);
    //glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbID);
    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
void POST_EFFECT_MNG::StartRenderMain()
{
	RenderBuffer.Start();
}
void POST_EFFECT_MNG::EndRenderMain()
{
	RenderBuffer.End();
}
void POST_EFFECT_MNG::Draw()
{

}