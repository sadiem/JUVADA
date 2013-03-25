//################################################
//<Polygon.cpp>
// �|���S���̏o��
//------------------------------------------------
//2012/07/12 ~
//						SekiyamaRumi
//################################################

//================================================
//�C���N���[�h
//================================================
#include "Polygon.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++
// �J���[�w��
//-------------------------------------------------
// �J���[�l���Z�b�g
//--in---------------------------------------------
// �i�[�f�[�^��
//--out---------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetCol(POLYGON3D *pol, COLOR col)
{
	pol->col.r = col.r;
	pol->col.g = col.g;
	pol->col.b = col.b;
	pol->col.a = col.a;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���W�ݒ�
//-------------------------------------------------
// �e�N�X�`���̎g�����͑S�ʂP���݂̂̏ꍇ
//--in---------------------------------------------
// ���W�ʒu
// ����
// �c��
//--out---------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetTex(POLYGON3D *pol)
{
	pol->tex[0].x = 0.0f;
	pol->tex[0].y = 1.0f;

	pol->tex[1].x = 0.0f;
	pol->tex[1].y = 0.0f;

	pol->tex[2].x = 1.0f;
	pol->tex[2].y = 0.0f;

	pol->tex[3].x = 1.0f;
	pol->tex[3].y = 1.0f;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���W�ݒ�
//-------------------------------------------------
// �e�N�X�`���̈�������������Ă���Ƃ��̐ݒ�
//--in---------------------------------------------
// POLYGON3D�@�ύX
// X�����@(fx < fy)
// Y�����@(fv < fh)
// ������
//--out---------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetTex(POLYGON3D *pol, float fx, float fy, float fv, float fh, float DivisionNum)
{
	pol->tex[0].x = fx / DivisionNum;
	pol->tex[0].y = 1.0f - (fh / DivisionNum);

	pol->tex[1].x = fx / DivisionNum;
	pol->tex[1].y = 1.0f - (fv / DivisionNum);

	pol->tex[2].x = fy / DivisionNum;
	pol->tex[2].y = 1.0f - (fv / DivisionNum);

	pol->tex[3].x = fy / DivisionNum;
	pol->tex[3].y = 1.0f - (fh / DivisionNum);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���W�ݒ�
//-------------------------------------------------
// �e�N�X�`���͖��ݒ�
//--in---------------------------------------------
// POLYGON3D�@�ύX
// �����ʒu�@X
//			 Y
// ����
// �c��
//--out---------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetVer(POLYGON3D *pol, float x, float y, float width, float height)
{
	pol->ver[0].x  = x;
	pol->ver[0].y  = y + height;
	pol->ver[0].z  = 0.0f;

	pol->ver[1].x  = x;
	pol->ver[1].y  = y;
	pol->ver[1].z  = 0.0f;

	pol->ver[2].x  = x + width;
	pol->ver[2].y  = y;
	pol->ver[2].z  = 0.0f;

	pol->ver[3].x  = x + width;
	pol->ver[3].y  = y + height;
	pol->ver[3].z  = 0.0f;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
// �|���S���g�k
//-------------------------------------------------
// �g�k
//--in---------------------------------------------
// POLYGON3D�@�ύX
// �g�嗦
//--out---------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void PlySetScl(POLYGON3D *pol, float scl)
{
	pol->ver[0] *= scl;
	pol->ver[1] *= scl;
	pol->ver[2] *= scl;
	pol->ver[3] *= scl;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
// �|���S���`��
//--in--------------------------------------------
//POLYGON3D�@�Q��
//��]�p
//��]��
//�ʒu
//�e�N�X�`��ID
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void PlyDrawPoliBillBoard(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos, int m_TexID)
{
	GLdouble	matView[16];

	//��������
	glDisable(GL_LIGHTING);		//���C�g�I�t
	glEnable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����
	glDepthMask(GL_FALSE);		//�f�v�X�o�b�t�@�ւ̏������݋֎~

	//�J���[�w��
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//�|���S���`��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(m_TexID > 0)
	{
		glEnable(GL_TEXTURE_2D);	//�e�N�X�`���L����
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}
	//���W�ϊ�
	glPushMatrix();

	//�r���{�[�h�ϊ�
	glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
	matView[0] = matView[5] = matView[10] = 1.0f;
	matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
	glLoadMatrixd(&matView[0]);
	
	//�}�g���b�N�X�ϊ�
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	//�|���S���`��
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//�㏈��
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Z�o�b�t�@������
	glDepthMask(GL_TRUE);		//�f�v�X�o�b�t�@�ւ̏������݋���
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �|���S���`��
//--in--------------------------------------------
//POLYGON3D�@�Q��
//��]�p
//��]��
//�ʒu
//�e�N�X�`��ID
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void PlyDrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos,  int m_TexID)
{
	//��������
	glDisable(GL_LIGHTING);		//���C�g�I�t
	glEnable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����
	glDepthMask(GL_FALSE);		//�f�v�X�o�b�t�@�ւ̏������݋֎~

	//�J���[�w��
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//�|���S���`��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);	//�e�N�X�`���L����
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	//���W�ϊ�
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	//�|���S���`��
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//�㏈��
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Z�o�b�t�@������
	glDepthMask(GL_TRUE);		//�f�v�X�o�b�t�@�ւ̏������݋���
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}