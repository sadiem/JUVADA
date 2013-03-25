//################################################
// <Impact.cpp>
//
//------------------------------------------------
// 2013/01/10					akihito tanaka
//################################################


//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Impact.h"	//�Ռ��g
//================================================
//�萔��`
//================================================
#define IMPACT_TIME	(60)	//�Ռ��g�̕\������
#define IMPACT_DELAY	(3)	//�x���t���[����
#define ADD_ALPHA	(0.02f)	//���l�̑�����

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
IMPACT::IMPACT()
{
	Reset();
	Load();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
IMPACT::~IMPACT()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Load()
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\EFFECT\\impact_a.png", "EFFECT");
	for(int i = 0; i < IMPACT_NUM; i++)
	{
		g_MeshMng.GetMesh(&m_Impact[i], "MODEL\\EFFECT\\impact.x", "EFFECT");
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Reset()
{	

	m_Live = false;
	m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < IMPACT_NUM; i++)
	{
		m_Time[i] = IMPACT_TIME;
		m_Alpha[i] = 0.0f;
		m_Scale[i] = 0.1f;
	}
	m_ScaleRate = 0.0f;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�ʒu�̃Z�b�g
//--in--------------------------------------------
//	�J�n�ʒu
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Set(VECTOR3 vec)
{
	VECTOR3 v;
	int nCnt = 0;

	if(m_Live)
		return;

	//�����l���Z�b�g
	m_Live = true;
	m_Pos = vec;
	m_Pos.y = 0.1f;
	m_ScaleRate = 0.05f;


	for(int i = 0; i < IMPACT_NUM; i++)
	{
		m_Scale[i] = 0.1f;

		//�؋󎞊�
		m_Time[i] = IMPACT_TIME + i * IMPACT_DELAY;
		//���l
		m_Alpha[i] = 0.0f;	
		m_dsp[i] = false;
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���̍X�V
//--in--------------------------------------------
//	�Ȃ�
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::UpDate(void)
{

	if(!m_Live)
		return;

	for(int i = 0; i < IMPACT_NUM; i++)
	{
		//�X�V����
		m_Time[i] --;	//�؋󎞊Ԍ�
		if(m_Time[i] < IMPACT_TIME)
			m_dsp[i] = true;

		if(!m_dsp[i])
			continue;

		//�g��
		m_Scale[i] += m_ScaleRate;

		//���l
		if(m_Time[i] < 0)
		{
			m_Time[i] = 0;
			m_Live = false;
			m_Alpha[i] = 0.0f;
			m_dsp[i] = false;
		}
		//�����鏈��
		else if(m_Time[i] < IMPACT_TIME / 2.0f)
		{
			m_Alpha[i] -= ADD_ALPHA;
			if(m_Alpha[i] < 0.0f)
				m_Alpha[i] = 0.0f;
		}
		//����鏈��
		else
		{
			m_Alpha[i] += ADD_ALPHA;
			if(m_Alpha[i] > 1.0f)
				m_Alpha[i] = 1.0f;	
		}
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void IMPACT::Draw()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	if(m_Live)
	{
		for(int i = 0; i < IMPACT_NUM; i++)
		{
			glPushMatrix();
			glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
			//���l�Z�b�g
			glColor4f(1.0f, 1.0f, 1.0f, m_Alpha[i]);
			glScalef(m_Scale[i], m_Scale[i], m_Scale[i]);

			DrawMesh(&m_Impact[i]);


			glPopMatrix();
		}
	}

	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//################################################
// End of File
//################################################
