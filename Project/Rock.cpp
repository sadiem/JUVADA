//################################################
// <Rock.cpp>
//
//------------------------------------------------
// 2012/01/06 ~
//						SekiyamaRumi
//################################################


//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Rock.h"	//��
#include "Random.h"	//����
#include "Matrix.h"	//���w
#include "TexMng.h"	//�e�N�X�`���}�l�[�W��
//================================================
//�萔��`
//================================================
#define ROCK_TIME	(200)	//���̑؋󎞊�
#define ADD_ALPHA_ROCK	(1.0f / (ROCK_TIME / 4.0f))	//���̃��l�̑�����
#define INIT_POS		(VECTOR3(0.0f, 0.0f, 0.0f))
#define START_Y			(-10.0f)
#define ROCK_ANGLE		(30.0f)
#define MOVE			(1.0f)
#define SCALE			(0.5f)
#define INTERVAL (5)
#define	MAX_ALPHA		(0.8f)
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ROCK::ROCK()
{
	Reset();
	Load();

	m_pShaderMng = SHADER_MNG::Instance();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ROCK::~ROCK()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Load()
{
	m_TexID		= g_TexMng.GetTexture("TEXTURE\\EFFECT\\Crystal.png", "EFFECT");
	//m_TexBumpID	= g_TexMng.GetTexture("TEXTURE\\sample01.png", "EFFECT");
	g_MeshMng.GetMesh(&m_Mesh, "MODEL\\EFFECT\\Rock.x", "EFFECT");


}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Reset()
{	
	for(int i = 0; i < ROCK_NUM; i ++)
	{
		m_Rock[i].m_Live = false;
		m_Rock[i].m_Pos = VECTOR3(0.0f, 0.0f, 0.0f);
		m_Rock[i].m_Time = ROCK_TIME;
		m_Rock[i].m_Alpha = 0.0f;
		m_Rock[i].m_ScaleRate = 0.0f;
		m_Rock[i].m_Scale = 1.0f;
		m_Rock[i].m_SpeedY = 0.0f;
		m_AngX[i] = 0.0f;
		m_MaxScale[i] = 0.0f;
	}
	m_Obj = NULL;
	m_interval = 0;
	m_Type = 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
//void ROCK::UpDate(void)
//{
//	//�G�t�F�N�g�J�n�t���O������Ƃ�
//	UpdateRock();	//�X�V
//}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���̃Z�b�g
//--in--------------------------------------------
//	�J�n�ʒu
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Set(OBJECT *obj, int type)
{
	VECTOR3 v;
	int nCnt = 0;

	m_Obj = obj;
	m_Set = true;
	m_Type = type;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�␶��
//--in--------------------------------------------
//	�J�n�ʒu
//--out-------------------------------------------
//	�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Gen(int type)
{
	if(m_Obj == NULL || !m_Set)
		return;

	for(int i = 0; i < ROCK_NUM; i ++)
	{

		if(m_Rock[i].m_Live)
			continue;

		m_Rock[i].m_Live = true;

		switch(type)
		{
		case LINE:
			//�����l���Z�b�g
			m_Rock[i].m_Pos = VECTOR3(m_Obj->m_Pos.x, m_Obj->m_Pos.y, m_Obj->m_Pos.z);
			m_Rock[i].m_Pos.y = START_Y;
			m_Rock[i].m_Angle = GetRandom(90, 0) - 45;
			m_Rock[i].m_Scale = SCALE - GetRandom(20, 0) * 0.01f;
			m_Rad[i] = m_Obj->m_Rad * 180 / M_PI;	//�I�u�W�F�N�g�̌���
			m_AngX[i] = -ROCK_ANGLE + GetRandom(30, 0) - 15;
			m_MaxScale[i] = SCALE - GetRandom(20, 0) * 0.01f;
			m_LR ^= 1;
			break;
		case CIRCLE:
			m_Rock[i].m_Pos = VECTOR3(m_Obj->m_Pos.x, m_Obj->m_Pos.y, m_Obj->m_Pos.z);
			m_Rock[i].m_Pos.y = 0.0f;
			m_Rock[i].m_Angle = 0.0f;
			m_Rock[i].m_Scale = 0.01f;
			m_MaxScale[i] = SCALE - GetRandom(20, 0) * 0.01f;
			m_Rad[i] = GetRandom(360, 0);
			m_AngX[i] = GetRandom(80, 60);
		}

		//�؋󎞊�
		m_Rock[i].m_Time = ROCK_TIME;
		//���l
		m_Rock[i].m_Alpha = MAX_ALPHA;	
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
void ROCK::UpDate(void)
{
	switch(m_Type)
	{
	case LINE:
		if(m_interval <= 0)
		{
			Gen(m_Type);
			m_interval = INTERVAL;
		}
		m_interval--;
		break;
	case CIRCLE:
		if(m_Set)
		{
			for(int i = 0; i < ROCK_NUM; i++)
			{
				Gen(m_Type);
			}
		}
		m_Set = false;
		break;
	}

	for(int i = 0; i < ROCK_NUM; i ++)
	{
		if(!m_Rock[i].m_Live)
			continue;

		//�X�V����
		m_Rock[i].m_Time --;	//�؋󎞊Ԍ�

		//���l
		if(m_Rock[i].m_Time < 0)
		{
			m_Rock[i].m_Time = 0;
			m_Rock[i].m_Live = false;
			m_Rock[i].m_Alpha = MAX_ALPHA;
		}
		//�����鏈��
		else if(m_Rock[i].m_Time < ROCK_TIME / 4.0f)
		{

			//���x
			m_Rock[i].m_Pos.y +=  m_Rock[i].m_SpeedY;

			m_Rock[i].m_Alpha -= ADD_ALPHA_ROCK;
			if(m_Rock[i].m_Alpha < 0.0f)
				m_Rock[i].m_Alpha = 0.0f;
		}
		//�o������
		else if(m_Rock[i].m_Time > (ROCK_TIME / 2.0f))
		{
			switch(m_Type)
			{
			case LINE:
				m_Rock[i].m_Pos.y += MOVE;
				if(m_Rock[i].m_Pos.y >= 0.0f)
					m_Rock[i].m_Pos.y = 0.0f;
				break;
			case CIRCLE:
				m_Rock[i].m_Scale += 0.03f;
				if(m_Rock[i].m_Scale > m_MaxScale[i])
					m_Rock[i].m_Scale = m_MaxScale[i];
				break;
			}
		}

	}


	//���ׂď�������I�u�W�F�N�g�������Z�b�g
	for(int i = 0; i < ROCK_NUM; i ++)
	{
		if(m_Rock[i].m_Live)
			return;
	}
	Reset();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�P��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Remove()
{
	m_Set = false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ROCK::Draw()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	m_pShaderMng->UseShader(COOK);
	m_pShaderMng->SetTexUnit(COOK, 0);

	for(int i = 0; i < ROCK_NUM; i ++)
	{
		if(!m_Rock[i].m_Live)
			continue;

		m_pShaderMng->SetAlpha(COOK,m_Rock[i].m_Alpha);		//���l�Z�b�g
		glPushMatrix();
		glTranslatef(m_Rock[i].m_Pos.x, m_Rock[i].m_Pos.y, m_Rock[i].m_Pos.z);
		glRotatef(m_Rad[i], 0.0f, 1.0f, 0.0f);	//Y����]
		glRotatef(m_Rock[i].m_Angle, 0.0f, 0.0f, 1.0f);		//Z����]
		glRotatef(m_AngX[i], 1.0f, 0.0f, 0.0f);			//X����]
		glScalef(m_Rock[i].m_Scale, m_Rock[i].m_Scale, m_Rock[i].m_Scale);

		DrawMesh(&m_Mesh);

		glPopMatrix();
	}


	m_pShaderMng->UnUseShader();

	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);

}
//################################################
// End of File
//################################################
