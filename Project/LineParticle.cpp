//################################################
// <LINE_PARTICLE.cpp>
//
//------------------------------------------------
// 2013/01/10					akihito tanaka
//################################################


//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Random.h"	//����
#include "Matrix.h"	//���w
#include "TexMng.h"	//�e�N�X�`���}�l�[�W��
#include "LineParticle.h"	//�Ռ��g
//================================================
//�萔��`
//================================================
#define LINE_PARTICLE_TIME	(60)	//�Ռ��g�̕\������
#define LINE_PARTICLE_DELAY	(3)	//�x���t���[����
#define ADD_ALPHA	(0.02f)	//���l�̑�����
#define TEX_SLIDE	(-0.06f)
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
LINE_PARTICLE::LINE_PARTICLE()
{
	Reset();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
LINE_PARTICLE::~LINE_PARTICLE()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::Load(MESH *mesh)
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\LineTex.png", "EFFECT");
	for(int i = 0; i < LINE_NUM; i++)
	{
		m_Line[i] = mesh;
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::Reset()
{	

	m_Live = false;
	m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < LINE_NUM; i++)
	{
		m_Time[i] = 0;
		m_Alpha[i] = 1.0f;
		m_Scale[i] = 0.0f;
		m_RadY[i] = 0.0f;
		m_RadX[i] = 0.0f;
		m_TexOffset[i] = 0.0f;
	}
	m_ScaleRate = 0.0f;
	m_Obj = NULL;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ʒu�̃Z�b�g
//--in--------------------------------------------
//	�J�n�ʒu
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::Set(OBJECT *obj)
{

	if(m_Live)
		return;

	m_Obj = obj;

	obj->m_Effect = true;



	//�����l���Z�b�g
	m_Live = true;
	
	//m_ScaleRate = 0.05f;


}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�p�[�e�B�N���̐���
//--in--------------------------------------------
//	�J�n�ʒu
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::Gen(void)
{
	VECTOR3 v;
	VECTOR3 vWork;		//�\���ʒu�v�Z�p���[�N
		//�\���ʒu�v�Z
	vWork = m_Obj->m_Pos + VECTOR3(m_Obj->m_MatrixRot._31, 0.0f, m_Obj->m_MatrixRot._33) * m_Obj->m_Width / 2.0f;

	//m_ObjRad = VectoVec(vWork, VECTOR3(0.0f, 0.0f, 1.0f));
	vWork.y = 1.0f;
	m_Pos = vWork;


	for(int i = 0; i < LINE_NUM; i++)
	{
		if(m_Time[i] > 0)
			continue;
		m_Time[i] = LINE_PARTICLE_TIME;
		m_Alpha[i] = 1.0f;
		m_Scale[i] = GetRandom(20,3) / 100.0f;
		m_RadY[i] = GetRandom(360,0) * M_PI / 180.0f;
		m_RadX[i] = (GetRandom(180,0) - 90) * M_PI / 180.0f;
		//m_dsp[i] = true;
		m_TexOffset[i] = GetRandom(50,0) / 100.0f;
		break;
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���̍X�V
//--in--------------------------------------------
//	�Ȃ�
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::UpDate(void)
{

	if(!m_Live)
		return;

	for(int i = 0; i < LINE_NUM; i++)
	{
		//�X�V����
		m_Time[i] --;	//�\�����ԃJ�E���g�_�E��
		m_TexOffset[i] += TEX_SLIDE;		//UV���ړ�

	}

	if(m_Obj->m_Live == false || m_Obj->m_Effect == false)
	{
		Reset();
		return;
	}

	Gen();

	//�^�C�}�[�����ׂĂO�ɂȂ����珉����
	for(int i = 0; i < LINE_NUM; i++)
	{
		if(m_Time[i] > 0)	//��ł��^�C�}�[���c���Ă���Ί֐��𔲂���
		{
			return;
		}
		else
			m_Time[i] = 0;
	}

	//������
	m_Obj->m_Effect = false;
	Reset();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void LINE_PARTICLE::Draw()
{

	int a;
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);	
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_ALPHA_TEST);

	glActiveTexture(GL_TEXTURE0);

	VECTOR3 vWork =  m_Obj->m_Pos - m_Pos;

	if(GetAsyncKeyState(VK_F1) & 0x8000)
	{
		a = 11111;
	}

	if(m_Live)
	{
		for(int i = 0; i < LINE_NUM; i++)
		{
			glPushMatrix();
			glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
			//glRotatef(((GLfloat)m_Rad[i] * 180 / M_PI), (GLfloat)vWork.x, (GLfloat)vWork.y , (GLfloat)vWork.z);	//Y����]
			//glRotatef(90.0f, (GLfloat)1.0, (GLfloat)0.0f , (GLfloat)0.0f);	//X����]
			glRotatef(((GLfloat)m_RadY[i] * 180 / M_PI), (GLfloat)0.0, (GLfloat)1.0f , (GLfloat)0);	//Y����]
			glRotatef(((GLfloat)m_RadX[i] * 180 / M_PI), (GLfloat)1.0f, (GLfloat)0.0f , (GLfloat)0.0f);	//X����]
			//glRotatef(m_ObjRad, (GLfloat)0.0, (GLfloat)1.0f , (GLfloat)0);	//Y����]
			//���l�Z�b�g
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(0.3f, 0.3f, 0.3f);
			//glScalef(0.5f, 0.5f, 0.5f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_TexID);
			DrawMesh(m_Line[i], m_TexOffset[i]);


			glPopMatrix();
		}
	}

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
}
//################################################
// End of File
//################################################
