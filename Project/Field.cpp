//################################################
// <Field.cpp>
// �n�ʐ���
//------------------------------------------------
// 2012/11/26 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Field.h"		//�t�B�[���h�w�b�_
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
#include "MeshMng.h"	//���b�V���}�l�[�W��
#include "Matrix.h"		//���w

//================================================
//�萔��`
//================================================
#define F_W (300)	//�t�B�[���h��
#define F_H (300)	//�t�B�[���h��
#define F_RANGE (40.0f)	//�t�B�[���h�͈�

//================================================
//�N���X��`
//================================================
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
FIELD::FIELD()
{
	m_skypos = SKY_POS;
	m_Shade = SHADER_MNG::Instance();
	//SetFence();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
FIELD::~FIELD()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Init()
{
	m_skypos = SKY_POS;
	m_Shade = SHADER_MNG::Instance();
	Load();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Load()
{
	//�e�N�X�`��
	m_TexIDField = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\field1-fix.png"), _T("FIELD"));
	m_TexIDFieldB = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\fieldbmp.png"), _T("FIELD"));
	m_TexIDSky = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\sky.png"), _T("FIELD"));
	m_TexIDSaku = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\saku.png"), _T("FIELD"));
	m_TexIDFieldBack = g_TexMng.GetTexture(_T("TEXTURE\\AMBIENT\\fieldBack.png"), _T("FIELD"));

	//���b�V��
	g_MeshMng.GetMesh(&m_Mesh, _T("MODEL\\AMBIENT\\fieldback.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_Meshsky, _T("MODEL\\AMBIENT\\sky.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_MeshSaku, _T("MODEL\\AMBIENT\\saku.x"), _T("FIELD"));
	g_MeshMng.GetMesh(&m_MeshfieldBack, _T("MODEL\\AMBIENT\\fieldback.x"), _T("FIELD"));
}			
//++++++++++++++++++++++++++++++++++++++++++++++++
//���
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Release()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Update()
{
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::Draw()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//�X�J�C�h�[��
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDSky);
	glPushMatrix();
	glTranslatef(m_skypos.x, m_skypos.y, m_skypos.z);
	glScalef(60.0f, 60.0f, 60.0f);
	DrawMesh(&m_Meshsky);
	glPopMatrix();

	//�t�B�[���h
	GLuint tangent = 0;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glScalef(150.0f, 1.0f, 150.0f);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDField);
	glScalef(0.7f, 1.0f, 0.7f);
	DrawMesh(&m_Mesh);
	glPopMatrix();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	////�t�B�[���h��̊p����������
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPushMatrix();
	//glTranslatef(0.0f, 0.1f, 0.0f);
	//glScalef(150.0f, 1.0f, 150.0f);
	//glBindTexture(GL_TEXTURE_2D, m_TexIDFieldBack);
	//DrawMesh(&m_MeshfieldBack);
	//glPopMatrix();
	glDisable(GL_BLEND);				//�u�����h����

	glEnable(GL_LIGHTING);

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//��̕`��
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FIELD::DrawFence()
{
	//��
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexIDSaku);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	DrawMesh(&m_MeshSaku);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

//################################################
// End of File
//################################################
