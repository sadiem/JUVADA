//################################################
// <EnemyNormal.h>
//
//------------------------------------------------
// 2012/12/06 ~								SekiyamaRumi
// 2013/1/18	�G�t�F�N�g�ǉ�				Akihito�@Tanaka
// 2013/1/31	���ꃂ�[�V�����C���@		Akihito�@Tanaka
// 2013/1/31	�֐�����static�ϐ����C��	Akihito  Tanaka 
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "EnemyNormal.h"
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
#include "MeshMng.h"	//���b�V���}�l�[�W��
#include "Random.h"		//�����ݒ�
//================================================
//�萔��`
//================================================
#define N_ENM_SPEED		(0.05f)	//���x
#define N_ENM_LIFE		(10)		//���C�t
#define N_ENM_ATTACK	(1)		//�U����
#define N_ENM_RAD       (0.2f)	//�U������]
#define N_ENM_BACK      (0.7f)	//�o�b�N�X�e�b�v�X�s�[�h
#define N_ENM_ATTACK_AREA	(15.0f)	//�U���͈�
#define N_ENM_DISCOVER		(0.27f)	//�v���C���[���������x
#define ENEMY_N_MORF_TIME	(20)	//�G���[�t�B���O����
#define GRAVITY				(-0.0098f)	//�d��
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_NORMAL::ENEMY_NORMAL()
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out---------------------a----------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_NORMAL::~ENEMY_NORMAL()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Init()
{
	m_pShader = SHADER_MNG::Instance();
	m_pEffectMng = EFFECT_MNG::Instance();
	m_pSE		= SOUND::Instance();
	m_Mesh = NULL;
	m_Mesh = new MESH;
	nCntAtk = 0;
	nCntDmg = 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Reset(void)
{
	MatrixIdentity(&m_Matrix);		//�ϊ��}�g���b�N�X
	Vec3Identity(&m_Pos);			//�ʒu
	Vec3Identity(&m_PosPrev);		//�ʒu���W�O
	Vec3Identity(&m_vec);			//�L�����̌���
	Vec3Identity(&m_vecPrev);		//�L�����̌����O
	m_vecS = 0.0f;					//�ړ����x
	m_Rad = 0.0f;					//��]�p
	m_State = DEAD;					//���
	m_Life  = N_ENM_LIFE;			//�̗�
	m_Live  = false;				//����
	m_Speed = 0.0f;					//���x
	m_Type  = NORMAL;				//�^�C�v
	m_ScaleRate = 1.0f;				//�g�嗦
	m_Timer = 0;					//�^�C�}�[(���S���ȂǂŎg�p)
	m_Attack = N_ENM_ATTACK;		//�U����
	m_Scale = VECTOR3(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	m_ColPlayer = false;			//�v���C���[�Ƃ̏Փ˃t���O
	m_ColRingIn = false;			//�v���C���[�̃����O���Ɋ܂܂�Ă��邩�̃t���O
	m_AtkMotion = false;
	m_DmgMotion = false;
	//�G�t�F�N�g
	m_Effect = false;

	nCntAtk = 0;
	nCntDmg = 0;

	//�����p���b�V���̍쐬�ƃ��Z�b�g
	MeshBomb(&m_MeshBomb, &m_MeshDmg1);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�[�^�̏����l���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::SetData(void)
{
	//���݈ʒu�w��
	m_Pos.x = GetRandom(FIELD_WIDTH, 0) - (FIELD_WIDTH * 0.5f);
	m_Pos.y = 0.0f;
	m_Pos.z = GetRandom(FIELD_WIDTH, 0) - (FIELD_WIDTH * 0.5f);

	//�i�s�����w��
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_vec.z = 1.0f;

	//�ړ����x
	m_Speed = N_ENM_SPEED;		//�W�����x

	//���
	m_State = MOVE;				//�ړ�

	//�̗�
	m_Life = N_ENM_LIFE;

	//����
	m_Live = true;

	//�^�C�v
	m_Type = NORMAL;

	//�g�嗦
	m_ScaleRate = 1.0f;
	m_Scale = VECTOR3(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	//�U����
	m_Attack = N_ENM_ATTACK;

	//�U������]
	m_RotAtc = 0.0f;

	//�U�����[�V�����̎��
	m_AtkState = ROT;

	//�U�����[�V�����t���O
	m_AtkMotion = false;

	//�v���C���[�ւ̍U�������t���O
	m_AtkHitPlayer = false;
	
	//�_���[�W���[�V�����t���O
	m_DmgMotion = false;

	//�G�̎��񂾐�
	m_DeadNum = 0;

	//��
	m_Width = m_Mesh->fRadius * m_ScaleRate;

	//�v���C���[�������ĂȂ��Ƃ��A�i�ޕ���
	m_vecFree = VECTOR3((float)GetRandom(10, -10), 0.0f, (float)GetRandom(10, -10));

	//�G�t�F�N�g
	m_Effect = false;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Load(void)
{
	m_TexID = g_TexMng.GetTexture("TEXTURE\\ENEMY\\enemy01.png", "ENEMY");
	m_TexInside = g_TexMng.GetTexture("TEXTURE\\ENEMY\\player_inner.png", "ENEMY");
	g_MeshMng.GetMesh(&m_MeshNormal, "MODEL\\ENEMY\\Enemy_Normal.x", "ENEMY");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshB, "MODEL\\ENEMY\\enm01_b.x", "ENEMY");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshDmg1, "MODEL\\ENEMY\\Enemy_Normal_bomb.x", "ENEMY");	//���b�V���ǂݍ���
	//g_MeshMng.GetMesh(&m_MeshBomb, "MODEL\\ENEMY\\enm.x", "ENEMY");	//���b�V���ǂݍ���
	//g_MeshMng.GetMesh(&m_MeshDmg2, "MODEL\\ENEMY\\Enemy_Normal_3.x", "ENEMY");	//���b�V���ǂݍ���
	//g_MeshMng.GetMesh(&m_Inside, "MODEL\\ENEMY\\Enemy_Normal_in.x", "ENEMY");	//���b�V���ǂݍ���
	
	SetMorph(m_Mesh, m_MeshNormal);	
	CpyVertex(m_Mesh, m_MeshNormal);		//���_�f�[�^���Ƃ肠�����R�s�[
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Release(void)
{
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�쐬
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Create(void)
{
	SetData();	//�f�[�^�̃Z�b�g
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�폜
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Deleate(void)
{
	//�̗͂��Ȃ�
	if(m_Life <= 0)
	{
		m_Live = false;	//���S
	}
		
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in-------------------------s-------------------
// �v���C���[�̈ʒu
// ��
// �U����
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::Update(VECTOR3 pos, float w, int a)
{
	VECTOR3 tmp, vec;
	//���f���̌��ݕ������߂�
	m_Width = m_Mesh->fRadius;
	
	//�����̑O���Ƀv���C���[������Ƃ��ǂ�������
	//���ƂŁ[

	//===========================================
	//
	//	�ړ��v�Z
	//�^
	//===========================================
	//�v���C���[���߂��ɂ��Ȃ��Ƃ��A�����_���ȕ����ɐi��
	float fl = VecLength(pos - m_Pos);
	if(VecLength(pos - m_Pos) >=  N_ENM_ATTACK_AREA)
	{
		if(GetRandom(100, 0)  == 0)
		{
			m_vecFree.x = (float)GetRandom(10, -10);
			m_vecFree.z = (float)GetRandom(10, -10);

			Vec3Normalize(&m_vecFree, m_vecFree); 
		}
		tmp = m_vecFree;
		m_Speed = N_ENM_SPEED;		//�v���C���[�������X�s�[�h�A�b�v
	}
	else
	{
		//�v���C���[���O���ɂ���Ƃ��A�v���C���[�Ɍ������Đi��
		tmp = pos - m_Pos;
		if(VecLength(tmp) < w * 1.0f)
			tmp = VECTOR3();
		else
		{
			Vec3Normalize(&tmp, tmp);
			m_vec = tmp;			//�i�s�����̒P�ʃx�N�g���ۑ�
		}
		m_Speed = N_ENM_DISCOVER;	//�v���C���[�������X�s�[�h�A�b�v
	}
	vec = tmp * m_Speed;	//���x�����Z

	//�ʒu�␳
	VECTOR3 posT;
	posT = m_Pos + vec;
	float fL = 0.0f;
	fL = VecLength(posT);
	if(VecLength(posT) > (FIELD_WIDTH / 2.0f))
	{
		Vec3Normalize(&tmp , (m_Pos * -1));
		vec = tmp * m_Speed;
	}
	
	//===========================================
	//
	//	�t���O�Ǘ�
	//
	//===========================================
	//�v���C���[�ƏՓ˂��Ă��邩
	if(m_ColPlayer)
	{	//�U�����[�V�����ł��_���[�W���[�V�����ł��Ȃ��Ƃ�
		if( !m_AtkMotion && !m_DmgMotion)
		{
			m_AtkMotion = true;
			m_State = ATTACK;	//�U����Ԃ�
		}
	}
	else
	{	//-----�Փ˂��ĂȂ�
		if( !m_AtkMotion && !m_DmgMotion)
			m_State = MOVE;	//�ړ���Ԃ�
	}

	//�v���C���[����̍U����
	if(m_ColRingIn)	
	{
		//�����U�����[�V�������̏ꍇ
		if(m_AtkMotion)
		{
			m_AtkMotion = false;
			m_State = DAMAGE;
		}
		//�_���[�W���[�V������
		m_DmgMotion = true;
		m_State = DAMAGE;
		//�~�̒��ɓ����Ă܂����Ԃ֖߂�
		m_ColRingIn = false;
	}

	//===========================================
	//
	//	��ԑJ��
	//�^
	//===========================================
	switch(m_State)
	{
	case MOVE:
		//�ړ�����
		m_Effect = false;
		Move(vec);
		break;
	case ATTACK:
		if(MotionAttack())
		{
			m_AtkMotion = false;		//�A�N�V�����I��
			m_AtkHitPlayer = true;		//�v���C���[�ւ̍U������
		}
		break;
	case DAMAGE:
		if(MotionDamage())
		{
			m_DmgMotion = false;		//�A�N�V�����I��
			//�_���[�W���Z
			LifeCount(a);

			if(JudgLife())
			{
				Reset();
				return true;
			}
			else
				return false;

		}
		break;
	default:break;	
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�U�����[�V����
// 
//��]���Ȃ���A�^�b�N���o�b�N�X�e�b�v
//--in-------------------------s-------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::MotionAttack(void)
{
	if(nCntAtk == 0)
	{
		m_pSE->PlaySE(DRILL);
		m_pEffectMng->Set(E_PARTICLE_LINE, this);
	}
	nCntAtk ++;
	if(nCntAtk < 50)
	{
		m_AtkState = ROT;
	}
	else
	{
		Addpos = VECTOR3();
		nCntAtk = 0;
		return true;
	}

	switch(m_AtkState)
	{
	case ROT:	//�U����]
		m_RotAtc += N_ENM_RAD; 
		m_Rad += m_RotAtc;
		break;
	case BACK:	//�o�b�N�X�e�b�v
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�_���[�W���[�V����
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_NORMAL::MotionDamage(void)
{
	if(nCntDmg == 0)
	{
		m_pSE->PlaySE(BOMB);
		m_MeshBomb.vVel = VECTOR3(0.0f,0.0f,0.0f);
	}
	nCntDmg ++;

	if(nCntDmg < ENEMY_N_MORF_TIME)
		Morphing(m_Mesh, m_MeshNormal, m_MeshDmg1, nCntDmg, 0, ENEMY_N_MORF_TIME);	
	if(nCntDmg == ENEMY_N_MORF_TIME)
	{
		m_pEffectMng->Set(E_PARTICLE_SPLASH, this);
		m_pEffectMng->Set(E_PARTICLE_BOMB, this);
	}
	//if(m_ScaleRate < 0.0f)
	
	if(nCntDmg > ENEMY_N_MORF_TIME && nCntDmg <= 60)
	{
		for(int i = 0; i < m_MeshBomb.nVtx; i ++)
		{
			m_MeshBomb.pVtx[i] += m_MeshBomb.pNormal[i] * 0.3f;
			m_MeshBomb.pVtx[i].y += m_MeshBomb.vVel.y;
		}
		m_MeshBomb.vVel.y += GRAVITY;
	}
	if(nCntDmg > 60)
	{
		//����������
		nCntDmg = 0;
		m_ScaleRate = 1.0f;	
		Morphing(m_Mesh, m_MeshNormal, m_MeshDmg1, 0, 0, ENEMY_N_MORF_TIME);	
		m_Mesh->vVel = 0.0f;
		return true;
	}

	//�g�k���s��
	//m_ScaleRate -= nCntDmg * 0.002f;

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_NORMAL::Draw(void)
{
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 512, 512, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
  
	//�ړ�
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rad * 180 / M_PI, (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);	//�U������]
	glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate); 


	//�e�N�X�`���ݒ�
	//�`��
	if(m_Live)
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHT0);

		//DrawMesh(&m_MeshB, (GLuint)1);	
		//glEnable(GL_TEXTURE_2D);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, m_TexInside);
		//DrawMesh(&m_Inside);	
		//�e�N�X�`���ݒ�
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glEnable(GL_BLEND);
		
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		
		//if(m_Life > 25)
		if(nCntDmg < ENEMY_N_MORF_TIME)
			DrawMesh(m_Mesh);
		else
			DrawBomb(&m_MeshBomb);
		//else if(m_Life > 15)
		//	DrawMesh(&m_MeshDmg1);
		//else
			//DrawMesh(&m_MeshDmg2);

		//m_pShader->End();
		//glUseProgram(0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);

}
void ENEMY_NORMAL::SetLive(bool bLive){m_Live = bLive;}

//################################################
// End of File
//################################################
