//################################################
// <Emitter.cpp>
//
//------------------------------------------------
// 2013/1/16
//						Akihito Tanaka
//################################################


//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Emitter.h"
#include "Random.h"
//================================================
//�萔��`
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EMITTER::EMITTER()
{
	m_pShaderMng = SHADER_MNG::Instance();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
EMITTER::~EMITTER()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Init()
{
	m_ParticleCount = 0;
	m_Enable = false;
	m_Pos	= VECTOR3(0.0f, 0.0f, 0.0f);
	m_LifeTime = 0;
	m_Color = VECTOR3(1.0f, 1.0f, 1.0f);
	
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i].Init();
	}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::UpDate()
{

	if(m_LifeTime > 0)
		CreatePrticle();

	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		if(!m_Particle[i].m_Live)
			continue;
		m_Particle[i].UpDate();

		if(!m_Particle[i].m_Live)
			DeleteParticle(&m_Particle[i]);
	}

	if(m_ParticleCount <= 0)
	{
		m_Enable = false;
		Init();
	}

	m_LifeTime--;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�����ʒu�̃Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::CreatePrticle(void)
{
	VECTOR3 vec;
	// �ő吔�𒴂��Ă�����쐬���Ȃ�
	if(m_ParticleCount> MAX_PARTICLE)
	{
		return;
	}
	PARTICLE* particle = SearchBlankParticle();
	// �󂫗̈悪�Ȃ���΍쐬���Ȃ�
	if(particle == NULL)
	{
		return;
	}

	//�I�u�W�F�N�g�����݂��Ă��Ȃ���΍쐬���Ȃ�
	if(!m_obj || m_obj->m_Live == false)
	{
		m_obj = NULL;		//�I�u�W�F�N�g������
		return;
	}

	switch(m_Type)
	{
	case SPIN:
		for(int i = 0; i < SPIN_GEN_NUM; i++)  //���t���[���w�萔����
		{
			if(particle->Set(m_obj->m_Pos, m_Type))	//�P����
			{
				m_ParticleCount++;					//�p�[�e�B�N���𐶐�������J�E���g�{
				particle = SearchBlankParticle();	//�V�����p�[�e�B�N��������
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		//if(particle->Set(m_obj->m_Pos, m_Type))	//���t���[���P����
		//	m_ParticleCount++;					//�p�[�e�B�N���𐶐�������J�E���g�{
		m_PointSize = 30.0f;
		break;
	case SPLASH:
		for(int i = 0; i < SPLASH_GEN_NUM; i++)  //���t���[���w�萔����
		{
			if(particle->Set(m_obj->m_Pos, m_Type))	//�P����
			{
				m_ParticleCount++;					//�p�[�e�B�N���𐶐�������J�E���g�{
				particle = SearchBlankParticle();	//�V�����p�[�e�B�N��������
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		m_PointSize = 30.0f;
		break;
	case BOMB:
		for(int i = 0; i < BOMB_GEN_NUM; i++)  //���t���[���w�萔����
		{
			//�p�[�e�B�N�������ʒu�v�Z
			vec = m_obj->m_Mesh->pVtx[GetRandom(m_obj->m_Mesh->nVtx, 0)] * m_obj->m_ScaleRate;		//���b�V����̒��_���甭��
			vec += m_obj->m_Pos;			//�I�u�W�F�N�g�̈ʒu�ֈړ�
			if(particle->Set(vec, m_Type))	//�P����
			{
				m_ParticleCount++;					//�p�[�e�B�N���𐶐�������J�E���g�{
				particle = SearchBlankParticle();	//�V�����p�[�e�B�N��������
				if(particle == NULL)
					break;
			}
			else
				break;
		}
		m_PointSize = 64.0f;
		break;
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Draw(void)	//�`��
{
	//glPushMatrix();
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	glPointSize(m_PointSize);
	glBegin(GL_POINTS);
	
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Particle[i].m_Alpha);
		if(m_Particle[i].m_Live)
			glVertex3fv(m_Particle[i].m_Pos.v);
	}
	glEnd();
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

	//glPopMatrix();

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��(�V�F�[�_)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::DrawShader(void)	//�`��
{
  	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	//glPointSize(m_PointSize);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	//�V�F�[�_�̓K�p
	m_pShaderMng->UseShader(POINTSPL);
	m_pShaderMng->SetTexUnit(POINTSPL, 0);
	m_pShaderMng->SetPSize(POINTSPL, m_PointSize);		//�|�C���g�T�C�Y
			
	//���l�Z�b�g
	glBegin(GL_POINTS);
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
	
		//glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Particle[i].m_Alpha);
		if(m_Particle[i].m_Live)
		{	
			m_pShaderMng->setColor(m_Color, m_Particle[i].m_Alpha,POINTSPL);
			glVertex3fv(m_Particle[i].m_Pos.v);
		}
	}
	glEnd();

	m_pShaderMng->UnUseShader();
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PARTICLE *EMITTER::SearchBlankParticle(void)	//�`��
{
	for(int i = 0; i < MAX_PARTICLE; i++)
	{
		if(m_Particle[i].m_Live == true)
		{
			continue;
		}
		return &m_Particle[i];
	}
	
	return NULL;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�폜
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::DeleteParticle(PARTICLE *particle)	//�`��
{
	particle->Reset();
	m_ParticleCount--;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�G�~�b�^�[�L����
//--in--------------------------------------------
//type	:�G�t�F�N�g�^�C�v
//obj	:�I�u�W�F�N�g�ɒǏ]����ꍇ�̂�obj�̃|�C���^�A����ȊO��NULL
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void EMITTER::Create(int type, GLuint texID, OBJECT *obj)
{	
	m_Enable = true;
	m_obj = obj;
	m_TexID = texID;
	m_Type = type;

	switch(type)
	{
	case SPIN:
		m_LifeTime = EM_SPIN_TIME;
		m_Color = VECTOR3(0.1f, 0.1f, GetRandom(100,50)/100.0f);		//��
		break;
	case SPLASH:
		m_LifeTime = EM_SPLSH_TIME;
		m_Color = VECTOR3(GetRandom(100,10)/100.0f,
			GetRandom(100,10)/100.0f, 
			GetRandom(100,10)/100.0f);		//��GetRandom(50,10)

		break;
	case BOMB:
		m_LifeTime = EM_BOMB_TIME;
		m_Color = VECTOR3(1.0f, 1.0f, 1.0f);
			//0.7f, 
			//0.1f);		//��
	}
}