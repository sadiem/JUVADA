//################################################
// <Ambient.cpp>
//
//------------------------------------------------
// 2013/01/05 ~					SekiyamaRumi
//################################################


//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Ambient.h"	//���w�b�_
#include "Random.h"		//����
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��

//================================================
//�萔��`
//================================================
#define FOG_MIN_EXP	(0.0002f)
#define FOG_MAX_EXP	(0.001f)
#define FOG_ADD		(0.0001f)	//�t�H�O�Z�x�����l

#define CLOUD_TIME		(300)	//�_�̑؋󎞊�
#define ADD_ALPHA_CLOUD	(0.01f)	//�_�̃��l�̑�����

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
AMBIENT::AMBIENT()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
AMBIENT::~AMBIENT()
{

}
void AMBIENT::Init()
{
	Load();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Load()
{
	m_TexIDCloud = g_TexMng.GetTexture("TEXTURE\\AMBIENT\\kumo.png", "AMBIENT");
	g_MeshMng.GetMesh(&m_MeshCloud, "MODEL\\AMBIENT\\poli1.x", "AMBIENT");
	
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Reset()
{
	m_fogExp = FOG_MIN_EXP;
	GLfloat fogCol[] = {0.7f, 0.7f, 0.7f, 0.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 100.0f);			//�J�n�_
	glFogf(GL_FOG_END, 500.0f);		//�I���_
	glFogi(GL_FOG_MODE, GL_EXP);		//�Z�x
	glFogf(GL_FOG_DENSITY, m_fogExp);
	glFogfv(GL_FOG_COLOR, fogCol);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		m_Cloud[i].m_Live = false;
		m_Cloud[i].m_Pos = VECTOR3(0.0f, 5.0f, 0.0f);
		m_Cloud[i].m_Time = CLOUD_TIME;
		m_Cloud[i].m_Alpha = 0.0f;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Update(int num, int fogStart)
{
	FogUpdate(num, fogStart);		//�t�H�O
	CloudUpdate();		//�_	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���̍X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::FogUpdate(int num, int fogStart)
{
	if(m_fogExp > FOG_MAX_EXP)
		m_fogExp = FOG_MAX_EXP;
	else
	{
		if(num > fogStart)
			m_fogExp += FOG_ADD;	//�Z�x�v�Z
	}
	//�t�H�O
	glFogi(GL_FOG_MODE, GL_EXP);	//�Z�x
	glFogf(GL_FOG_DENSITY, m_fogExp);
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//�_�Z�b�g
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::CloudSet(void)		//�_����
{
	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		if(m_Cloud[i].m_Live)
			continue;

		//�e��l���Z�b�g
		m_Cloud[i].m_Live = true;							//����
		m_Cloud[i].m_Time = CLOUD_TIME + GetRandom(200, 0);	//�؋󎞊ԃZ�b�g
		m_Cloud[i].m_Pos.x = (float)GetRandom(60, -60);			//�o���ʒu
		m_Cloud[i].m_Pos.y = (float)GetRandom(40, 5);
		m_Cloud[i].m_Pos.z = (float)GetRandom(60, -60);
		

		break;
	}

	//���b�V���f�[�^�̃��l���O�ɐݒ�
	for(int nLoop = 0; nLoop < m_MeshCloud.nFace; nLoop ++)	
		m_MeshCloud.pMaterial[m_MeshCloud.pFace[nLoop].nMaterialNo].Diffuse.w = 0.0f;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���̍X�V
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::CloudUpdate(void)		//�_����
{
	CloudSet();

	for(int i = 0; i < CLOUD_NUM; i ++)
	{
		if(!m_Cloud[i].m_Live)
			continue;

		m_Cloud[i].m_Time --;	//�؋󎞊�
		
		//���l
		if(m_Cloud[i].m_Time < 0)
		{
			m_Cloud[i].m_Live = false;
			m_Cloud[i].m_Alpha = 0.0f;
			m_Cloud[i].m_Time = 0;
		}
		//�����鏈���J�n
		else if(m_Cloud[i].m_Time < 120)
		{
			//���l���Z�b�g
			m_Cloud[i].m_Alpha -= ADD_ALPHA_CLOUD;
			if(m_Cloud[i].m_Alpha < 0.0f)
				m_Cloud[i].m_Alpha = 0.0f;
		}
		//����鏈��
		else
		{
			//���l���Z�b�g
			m_Cloud[i].m_Alpha += ADD_ALPHA_CLOUD;
			if(m_Cloud[i].m_Alpha > 1.0f)
				m_Cloud[i].m_Alpha = 1.0f;
		}
		//�ʒu�����E�ɂ��炷
		m_Cloud[i].m_Pos.x += 0.05f;			//�o���ʒu
	}
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void AMBIENT::Draw()
{
	GLdouble	matView[16];

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	
	glActiveTexture(GL_TEXTURE0);

	for(int i = 0; i < CLOUD_NUM; i ++)
	{	
		if(!m_Cloud[i].m_Live)
			continue;

		glPushMatrix();
		glTranslatef(m_Cloud[i].m_Pos.x, m_Cloud[i].m_Pos.y, m_Cloud[i].m_Pos.z);

		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;

		glLoadMatrixd(&matView[0]);
		glScalef(10.0f, 10.0f, 10.0f);

		//���l�Z�b�g
		glColor4f(1.0f, 1.0f, 1.0f, m_Cloud[i].m_Alpha);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TexIDCloud);
		DrawMesh(&m_MeshCloud);
	
		
		glPopMatrix();
	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//################################################
// End of File
//################################################
