//################################################
// <EnemyBoss.cpp>
//
//------------------------------------------------
// 2013/1/7					akihito tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "EnemyBoss.h"
#include "MeshMng.h"		//���b�V���}�l�[�W��
#include "Random.h"			//�����ݒ�

//================================================
//�萔��`
//================================================
#define E_BOSS_LIFE		(100)			//�{�X�̗̑�
#define E_BOSS_ATK		(10)			//�{�X�̍U����
#define E_BOSS_INIT_POS (VECTOR3(0.0f, 100.0f, 0.0f))	//�{�X�̏����ʒu
#define E_BOSS_SCALE	(0.7f)			//�{�X�̃X�P�[��
#define FALL_SPEED		(0.8f)			//�����X�s�[�h
#define OFFSET_Y		(12.0f * E_BOSS_SCALE)				//�n�ʂ���̃I�t�Z�b�g
#define ROT_THL			(0.03f)			//��]�p�x�������l
#define ATTACK_SPIN_RAD	(0.2f)			//�X�s���U�����̉�]�p�x
#define ATTACK_SPIN_ADD	(0.002f)		//�X�s���U�����̉�]�p�x���Z�l
#define ATTACK_TIME		(60)			//�U������
#define WAIT_TIME		(180)			//�ҋ@�ڍs��̍d������
#define JUMP_SPEED		(1.5f)			//�W�����v����
#define COL_RADIUS		(0.2f)			//�����蔻��傫��
#define PRESS_TIME		(15)			//�v���X�̎���
#define PRESS_RATE		(1.5f)			//���f���ׂ̒��̌W��
#define ATTACK_DST		(25.0f)			//�U������
#define DEAD_MOTION_COUNT	(600)		//���S���[�V�����J�E���g

//�{�X�U���l
enum 
{
	ATK_JUMP = 2,	//�W�����v
	ATK_SPIN = 2	//�X�s��
};
//================================================
//�萔��`
//================================================
#define BOSS_APPEAR_NUM (30)		//�{�X�o���̂��߂̓����G��
//================================================
//�O���[�o���ϐ�
//================================================

//�p�[�c��m_Pos����̃I�t�Z�b�g
#define PARTS_OFFSET	(1.0f * E_BOSS_SCALE)

//�O�p�[�c�̈ʒu�ݒ�
const VECTOR3 vPartsPos[BOSS_STATE_NUM][BOSS_PARTS] = 
{	
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},
	{VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f)},
	{VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f),	VECTOR3(0.0f,-PARTS_OFFSET,0.0f)},
	{VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-0.0f,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET)},
	{VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,0.0f,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,0.0f,-PARTS_OFFSET)},
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},	
	{VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f),	VECTOR3(0.0f,0.0f,0.0f)},	
	//{VECTOR3(PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,PARTS_OFFSET),	VECTOR3(-PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET),	VECTOR3(PARTS_OFFSET,-PARTS_OFFSET,-PARTS_OFFSET)},
};		
//================================================
//�v���g�^�C�v�錾
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_BOSS::ENEMY_BOSS()
{
	//������
	Init();

	////���b�V���̏�����
	//m_Mesh = NULL;
	//m_Mesh = new MESH;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMY_BOSS::~ENEMY_BOSS()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Init(void)
{
	//�G�t�F�N�g�}�l�[�W���̃C���X�^���X�擾
	m_EffectMng = EFFECT_MNG::Instance();
	//�T�E���h�}�l�[�W���̃C���X�^���X�擾
	m_pSE	= SOUND::Instance();
	//���b�V���̏�����
	m_Mesh = NULL;
	m_Mesh = new MESH;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Reset()
{
	//����������
	MatrixIdentity(&m_Matrix);		//�ϊ��}�g���b�N�X
	Vec3Identity(&m_Pos);			//�ʒu
	Vec3Identity(&m_PosPrev);		//�ʒu���W�O
	Vec3Identity(&m_vec);			//�L�����̌���
	Vec3Identity(&m_vecPrev);		//�L�����̌����O
	m_vecS = 0.0f;					//�ړ����x
	m_Rad = 0.0f;					//��]�p
	m_Live  = false;				//����
	m_Speed = 0.0f;					//���x
	m_Type  = BOSS;					//�^�C�v
	m_ScaleRate = 1.0f;				//�g�嗦
	m_EyeScale = E_BOSS_SCALE;		//�ڋʂ̊g�嗦
	m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);		//�X�P�[���̐ݒ�
	m_Timer = 0;					//�^�C�}�[(���S���ȂǂŎg�p)
	m_ColPlayer = false;			//�v���C���[�Ƃ̏Փ˃t���O
	m_ColRingIn = false;			//�v���C���[�̃����O���Ɋ܂܂�Ă��邩�̃t���O
	m_Pos    = E_BOSS_INIT_POS;		//���_���
	m_State	 = BOSS_START;			//����
	m_Life   = E_BOSS_LIFE;			//�̗͂̐ݒ�
	m_Attack = E_BOSS_ATK;			//�U���͂̐ݒ�
	m_Width = m_MeshEye.fRadius;	//���a�̐ݒ�
	m_Count	 = 0;					//�J�E���g�̏�����
	m_First = false;				//�v���X���̏���t���O��OFF
	m_SpinRad = 0.0f;				//�X�s����]�p�̏�����
	m_SpinAdd = 0.0f;				//�X�s����]�p���Z�l�̏�����
	m_JumpFlg = false;				//�W�����v���Ă��Ȃ�
	m_AppearBoss = BOSS_APPEAR_NUM;	//�o����

	memset(m_PartsOffset, 0, sizeof(m_PartsOffset));	//�p�[�c�ʒu������
	m_EffectMng = EFFECT_MNG::Instance();				//�G�t�F�N�g�}�l�[�W���̃C���X�^���X�擾
	m_ShaderMng = SHADER_MNG::Instance();				//�V�F�[�_�}�l�[�W���̃C���X�^���X�擾
	m_pCamera  = CAMERA::Instance();					//�J�����̃C���X�^���X�擾

	m_TexID			= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\boss_armor.png"), _T("BOSS"));			//�O�p�[�c�e�N�X�`��
	m_TexBumpID		= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\boss_armor_bump.png"), _T("BOSS"));	//�O�p�[�c�o���v
	m_TexEyeID		= g_TexMng.GetTexture(_T("TEXTURE\\BOSS\\Boss_Eye.png"), _T("BOSS"));			//�ڋʃe�N�X�`��
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Load(void)
{
	g_MeshMng.GetMesh(&m_MeshArmor[0], "MODEL\\BOSS\\boss_u1.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[1], "MODEL\\BOSS\\boss_u2.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[2], "MODEL\\BOSS\\boss_u3.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[3], "MODEL\\BOSS\\boss_u4.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[4], "MODEL\\BOSS\\boss_d1.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[5], "MODEL\\BOSS\\boss_d2.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[6], "MODEL\\BOSS\\boss_d3.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshArmor[7], "MODEL\\BOSS\\boss_d4.x", "BOSS");	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshEye, "MODEL\\BOSS\\boss_eye.x", "BOSS");		//���b�V���ǂݍ���
	memcpy(m_Mesh, &m_MeshEye, sizeof(MESH));								//���b�V���̃R�s�[

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool ENEMY_BOSS::Update(VECTOR3 pos, float w, int a)
{
	VECTOR3 vPPos;	//�p�[�c���W
	VECTOR3 vWork;	//�v�Z�p���[�N

	//------------------------------
	// �v���C���[����̍U��
	//------------------------------
	if(m_ColRingIn)	//�����O��
	{
		m_State = DAMAGE_HIT;		//�_���[�W���[�V������
		m_ColRingIn = false;		//�Փ˃t���O�I�t
	}

	//�{�X�A�N�V��������
	switch(m_State)
	{
	//�{�X�����ݒ�
	case BOSS_START:		
		m_pSE->StopBG(BG_GAME_NORMAL);			//�ʏ�t�B�[���hBGM�X�g�b�v
		m_pSE->PlaySE(WARNING);					//�x��
		m_pCamera->SetOperatable(false);		//�J�����Œ�
		m_State = FALL;							//�����s����
		//�X���[
	//�������[�V����
	case FALL: 				//��󂩂痎��
		m_Pos.y -= FALL_SPEED;					//�����ړ�
		if(m_Pos.y <= OFFSET_Y)					//���f�����n�ʂɐڐG������
		{
			m_State = APPEAR;					//���n���[�V����
			m_Pos.y = OFFSET_Y;					//���f���\���ʒu
			m_Count = 0;						//�J�E���g������
		}
		break;
	//�o�����[�V����
	case APPEAR: 	
		m_Count++;								//�t���[�������J�E���g

		if(m_Count <= PRESS_TIME)				//���n�������ׂ̒ꂽ�\��
		{
			if(!m_First)
			{
				m_pSE->StopSE(WARNING);					//�x��SE��~
				m_pSE->PlayBG(BG_GAME_BOSS);			//�{�XBGM�Đ�
				m_Pos.y = 0.0f;							//�G�t�F�N�g�����ʒu
				m_EffectMng->Set(E_ROCK_CIRCLE, this);	//���n�n�_�Ɋ�̃G�t�F�N�g
				m_EffectMng->Set(E_IMPACT, this);		//�Ռ��g�G�t�F�N�g
				m_EffectMng->Set(E_SMOKE_L, this);		//���G�t�F�N�g
				m_Pos.y = OFFSET_Y;						//���f���\���ʒu�ɖ߂�
				m_First = true;							//����ʉ߃t���O
			}
			m_ScaleRate -= PRESS_RATE / PRESS_TIME;		//�ׂ������ɏk��
		}
		else if(m_Count < PRESS_TIME*2)			//���Ƃ̑傫���ɖ߂�
		{
			m_ScaleRate += PRESS_RATE / PRESS_TIME;		//�g�嗦�����ǂ�
		}
		if(m_Count > APPEAR_WAIT)						//���̃��[�V�����ֈڍs
		{
			//�ҋ@���[�V�����̊O�p�[�c�ʒu��ݒ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = 
					VECTOR3(vPartsPos[WAIT][i].x/TRANSCOUNT, 
							vPartsPos[WAIT][i].y/TRANSCOUNT, 
							vPartsPos[WAIT][i].z/TRANSCOUNT);
			}
			m_pCamera->SetOperatable(true);		//�J�����Œ����
			m_State = WAIT;						//�ҋ@���[�V������
			m_Count = 0;						//�J�E���g������
		}
		break;
	//�ҋ@���[�V����
	case WAIT:
		if(m_Count < TRANSCOUNT)				//�ҋ@��Ԃɕό`
		{
			//�O�p�[�c�̈ړ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			m_Count++;				//�J�E���g���Z
			break;
		}
		else if(m_Count < WAIT_TIME)			//�ҋ@�d��
		{
			EyeMove(pos);			//�ڋʂ̈ړ�
			m_Count++;				//�J�E���g���Z
			break;
		}


		EyeMove(pos);				//�ڋʂ̈ړ�

		//�v���C���[�Ƃ̋������v�Z
		vWork = m_Pos;		//�v���C���[�ʒu�����[�N�ɑ��		
		vWork.y = 0.0f;		//�����␳

		//�U������
		if(Vec3Length(vWork, pos) < ATTACK_DST)		//�v���X�͈͓̔�
		{
			//�O�p�[�c�ړ��ʃZ�b�g
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				//�W�����v���[�V�����̊O�p�[�c�ʒu��ݒ�
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[PRE_JUMP_ATTACK][i].x - vPartsPos[WAIT][i].x)/TRANSCOUNT, 
							(vPartsPos[PRE_JUMP_ATTACK][i].y - vPartsPos[WAIT][i].y)/TRANSCOUNT, 
							(vPartsPos[PRE_JUMP_ATTACK][i].z - vPartsPos[WAIT][i].z)/TRANSCOUNT);
			}
			m_State = PRE_JUMP_ATTACK;				//�W�����v���[�V������
			m_Attack = ATK_JUMP;					//�U����ނ��W�����v�U���ɐݒ�
			m_Count = 0;							//�J�E���g������
			break;
		}
		if(Vec3Length(vWork, pos) > ATTACK_DST)		//�v���X�͈̔͊O
		{
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				//�ˌ����[�V�����̊O�p�[�c�ʒu��ݒ�
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[PRE_SPIN_ATTACK][i].x - vPartsPos[WAIT][i].x)/TRANSCOUNT, 
							(vPartsPos[PRE_SPIN_ATTACK][i].y - vPartsPos[WAIT][i].y)/TRANSCOUNT, 
							(vPartsPos[PRE_SPIN_ATTACK][i].z - vPartsPos[WAIT][i].z)/TRANSCOUNT);
			}
			m_State = PRE_SPIN_ATTACK;				//�X�s���U����
			m_Attack = ATK_SPIN;					//�U����ނ��X�s���U���ɐݒ�
			m_Count = 0;							//�J�E���g������
			break;
		}
		break;
	//�W�����v�U������
	case PRE_JUMP_ATTACK:
		//�ό`
		if(m_Count < TRANSCOUNT)
		{
			//�O�p�[�c�̈ړ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			m_Count++;			//�J�E���g���Z
			EyeMove(pos);		//�ڋʉ�]
			break;
		}
		else
		{
			m_vAttack = pos - m_Pos;			//�U����������
			m_vAttack.y = 0.0f;					//XZ���ʂŌŒ�
			m_vAttack /= (float)ATTACK_TIME;	//�P�ʎ��Ԃ�����̈ړ��ʂ�ݒ�
			m_vAttack.y = JUMP_SPEED;			//�W�����v���x�̏����l��ݒ�
			m_State = JUMP_ATTACK;				//�W�����v�U�����[�V������
			m_First = false;
			m_Count = 0;
		}
		break;
	//�W�����v�U�����[�V����
	case JUMP_ATTACK:
		if(	m_Count <= ATTACK_TIME)		//�U�������Ɉړ�
		{
			m_Pos += m_vAttack;			//�ړ�
			m_vAttack.y -= JUMP_SPEED/(ATTACK_TIME/2.0f);	//Y�������ړ��ʌv�Z
			m_Count++;
		}
		else if(m_Count <= ATTACK_TIME + PRESS_TIME/2)		//���n������ׂ��\��
		{
			if(!m_First)
			{
				//�Z�t�F�N�g�̃Z�b�g
				m_EffectMng->Set(E_ROCK_CIRCLE, this);
				m_EffectMng->Set(E_IMPACT, this);
				m_First = true;
			}

			m_vAttack.y = OFFSET_Y/(PRESS_TIME/PRESS_RATE);
			m_ScaleRate -= PRESS_RATE / PRESS_TIME;
			m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);
			m_Pos.y -= m_vAttack.y;
			m_JumpFlg = true;
			m_Count++;
		}
		else if(m_Count < ATTACK_TIME + PRESS_TIME)		//���Ƃ̑傫���ɖ߂�
		{
			m_vAttack.y = OFFSET_Y/(PRESS_TIME/PRESS_RATE);
			m_ScaleRate += PRESS_RATE / PRESS_TIME;
			m_Pos.y += m_vAttack.y;
			m_Count++;
		}
		else											//���̍s����
		{
			//�p�[�c�̈ړ��ʐݒ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = 
					VECTOR3((vPartsPos[WAIT][i].x - vPartsPos[JUMP_ATTACK][i].x)/TRANSCOUNT, 
							(vPartsPos[WAIT][i].y - vPartsPos[JUMP_ATTACK][i].y)/TRANSCOUNT, 
							(vPartsPos[WAIT][i].z - vPartsPos[JUMP_ATTACK][i].z)/TRANSCOUNT);
			}
			//�g�嗦�̏�����
			m_ScaleRate = 1.0f;
			m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);
			m_State = WAIT;
			m_Count = 0;
			m_JumpFlg = false;

		}
		break;
	//��]�U������
	case PRE_SPIN_ATTACK:
		m_Count++;
		if(m_Count < TRANSCOUNT)
		{
			//�O�p�[�c�ړ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsOffset[i] += m_PartsMove[i];
			}
			break;
		}
		else if(m_Count == TRANSCOUNT)
		{
			//�G�t�F�N�g�Z�b�g
			m_EffectMng->Set(E_PARTICLE_SPIN, this);
		}
		EyeMove(pos);								//�ڋʂ̈ړ�


		if(m_SpinAdd < ATTACK_SPIN_RAD)				//��]���x�̑���
		{
			m_SpinAdd += ATTACK_SPIN_ADD;
		}
		else
		{

			//�U����������
			m_vAttack = pos - m_Pos;
			m_vAttack.y = 0.0f;
			Vec3Normalize(&m_vAttack, m_vAttack);
			m_AtkMove = m_vAttack;
			m_EffectMng->Set(E_ROCK_LINE, this);	//��G�t�F�N�g�Z�b�g

			//�U���J�n
			m_State = SPIN_ATTACK;
			m_Count = 0;
		}
		m_SpinRad += m_SpinAdd;						//��]
		break;
	//��]�U��
	case SPIN_ATTACK:

		if(m_Count < ATTACK_TIME)
		{
			m_Pos += m_AtkMove;						//�ړ�
		}
		else if(m_Count == ATTACK_TIME)
		{
			m_EffectMng->Remove(E_ROCK_LINE);		//��G�t�F�N�g����
		}
		else
		{
			//�X�s������
			if(m_SpinAdd > 0.05f)
			{
				m_SpinAdd -= ATTACK_SPIN_ADD;
			}
			if(m_SpinRad <= 0.1f)
			{
				m_SpinRad = 0.0f;
			}
		}

		//�p�x�␳
		if(m_SpinRad > 2.0f * M_PI)
		{
			m_SpinRad -= 2.0f * M_PI;
		}
		if(m_SpinRad < 0.0f)
		{
			m_SpinRad += 2.0f * M_PI;
		}

		//�����I���őҋ@�ɖ߂�
		if(m_SpinRad == 0.0f)
		{

			//�p�[�c�̈ړ��ʐݒ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = VECTOR3(	(vPartsPos[WAIT][i].x - vPartsPos[SPIN_ATTACK][i].x)/TRANSCOUNT, 
					(vPartsPos[WAIT][i].y - vPartsPos[SPIN_ATTACK][i].y)/TRANSCOUNT, 
					(vPartsPos[WAIT][i].z - vPartsPos[SPIN_ATTACK][i].z)/TRANSCOUNT);
			}
			m_State = WAIT;
			m_Count = 0;
			break;
		}

		m_SpinRad += m_SpinAdd;
		m_Count ++;
		break;
	//�_���[�W���[�V����
	case DAMAGE_HIT:
		if(MotionDamage())
		{
			//�_���[�W���Z
			LifeCount(a);
			if(JudgLife())
			{
				m_State = DEAD_BOSS;
				break;
			}

			//�p�[�c�̈ړ��ʐݒ�
			for(int i = 0; i < BOSS_PARTS; i++)
			{
				m_PartsMove[i] = VECTOR3(	(vPartsPos[WAIT][i].x - vPartsPos[DEAD_BOSS][i].x)/TRANSCOUNT, 
											(vPartsPos[WAIT][i].y - vPartsPos[DEAD_BOSS][i].y)/TRANSCOUNT, 
											(vPartsPos[WAIT][i].z - vPartsPos[DEAD_BOSS][i].z)/TRANSCOUNT);
			}
			m_State = WAIT;
		}
		break;
	//���S���[�V����
	case DEAD_BOSS:

		//�p�[�c�̈ړ��ʐݒ�
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			m_PartsOffset[i] += m_PartsMove[i] * (GetRandom(120, 80) / 100.0f);
			m_PartsMove[i].y -= 0.02f;
		}

		//�g�嗦�ݒ�
		m_EyeScale -= E_BOSS_SCALE / (DEAD_MOTION_COUNT * 0.66f);		//�ڋʏk��
		if(m_EyeScale < 0.0f)
			m_EyeScale = 0.0f;
		m_ScaleRate = m_EyeScale;
		m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);

		//�����G�t�F�N�g�ݒ�
		if(m_Count < (DEAD_MOTION_COUNT * 0.7) &&  m_Count % 60 == 0)
		{
			m_EffectMng->Set(E_PARTICLE_BOMB, this);
		}

		//���S���[�V�����I��
		if(m_Count > DEAD_MOTION_COUNT)		
		{
			Init();
			return true;
		}

		m_Count ++;	
		break;
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
bool ENEMY_BOSS::MotionDamage(void)
{

	VECTOR3 vWork;	//�v�Z�p���[�N
	if(m_Count < 30)
	{
		//�O�p�[�c�ʒu�ݒ�
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			m_PartsOffset[i] = vPartsPos[DEAD_BOSS][i];
		}
		m_Count ++;
		return false;
	}
	m_Count = 0;
	return true;	//���[�V�����I��
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::Draw(void)
{

	//�e�N�X�`���ݒ�
	//�`��
	if(m_Live)
	{
		
		glDisable(GL_ALPHA_TEST);					//���ߐݒ�
		glEnable(GL_DEPTH_TEST);					//�[�x�e�X�g�L����
		glEnable(GL_CULL_FACE);						//�J�����O�L����
		glEnable(GL_LIGHTING);						//���C�gON
		glEnable(GL_TEXTURE_2D);					//�e�N�X�`���QD
		glActiveTexture(GL_TEXTURE0);				//�e�N�X�`�����j�b�g�O��
		glBindTexture(GL_TEXTURE_2D, m_TexEyeID);	//�ڋʃe�N�X�`���o�C���h
		m_ShaderMng->UseShader(PHONG);				//�t�H���V�F�[�_�L����
		m_ShaderMng->SetTexUnit(PHONG, 0);			//�e�N�X�`���ԍ��Z�b�g

		//�ڋʕ`��
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
		glRotatef(m_Rad * 180 / M_PI , (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);
		glScalef(1.0f, m_ScaleRate, 1.0f);						//�ׂ�
		glScalef(m_EyeScale, m_EyeScale, m_EyeScale);			//�S�̂̊g�嗦
		m_Scale = VECTOR3(m_EyeScale, m_EyeScale, m_EyeScale);	//�ڋʂ̊g�嗦�ۑ�
		DrawMesh(&m_MeshEye);									//���b�V���`��
		glPopMatrix();	

		m_ShaderMng->UnUseShader();								//�V�F�[�_������

		glActiveTexture(GL_TEXTURE0);				//�e�N�X�`�����j�b�g�O��
		glBindTexture(GL_TEXTURE_2D, m_TexID);		//�O���e�N�X�`���o�C���h
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);				//�e�N�X�`�����j�b�g�P��
		glBindTexture(GL_TEXTURE_2D, m_TexBumpID);	//�O���o���v�p�e�N�X�`���o�C���h
		m_ShaderMng->UseShader(BUMP);				//�o���v�V�F�[�_�L����
		m_ShaderMng->SetTexUnit(BUMP, 0);			//�o���v�J���[�e�N�X�`��
		m_ShaderMng->SetBumpUnit(BUMP, 1);			//�o���v�@���e�N�X�`��

		//�p�[�c�`��
		for(int i = 0; i < BOSS_PARTS; i++)
		{
			glPushMatrix();
			glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
			glTranslatef(m_PartsOffset[i].x,m_PartsOffset[i].y,m_PartsOffset[i].z);
			glRotatef(m_SpinRad * 180 / M_PI , (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f);
			glScalef(1.0f, m_ScaleRate, 1.0f); 
			glScalef(E_BOSS_SCALE, E_BOSS_SCALE, E_BOSS_SCALE); 
			DrawMesh(&m_MeshArmor[i],(GLuint)1);
			glPopMatrix();
		}

		m_ShaderMng->UnUseShader();

	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�����t���O�Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::SetLive(bool bLive)
{
	m_Live = bLive;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�����Ǐ]
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMY_BOSS::EyeMove(VECTOR3 pos)
{
	float fRotEye = 0.0f;	//�ڋʉ�]�p

	VECTOR3 vP;		//�v���C���[�ւ̃x�N�g��
	vP = pos - m_Pos;
	vP.y = 0.0f;
	//Vec3Normalize(&vP, vP);
	fRotEye = VectoVec(VECTOR3(0.0f, 0.0f, 1.0f), vP);

	//�p�x�␳
	if(fRotEye > 2.0f * M_PI)
		fRotEye -= 2.0f * M_PI;
	if(fRotEye < 0.0f)
		fRotEye += 2.0f * M_PI;


	if(fRotEye - m_Rad > ROT_THL )
	{
		if(fRotEye - m_Rad <= M_PI)
			m_Rad += ROT_THL;
		else
			m_Rad -= ROT_THL;

	}
	else if(fRotEye - m_Rad >= 0.0f)
		m_Rad += (fRotEye - m_Rad);
	else if(fRotEye - m_Rad < -ROT_THL)
	{
		if(fRotEye - m_Rad >= -M_PI)
			m_Rad -= ROT_THL;
		else
			m_Rad += ROT_THL;
	}
	else
		m_Rad += (fRotEye - m_Rad);

	//�p�x�␳
	if(m_Rad > 2.0f * M_PI)
		m_Rad -= 2.0f * M_PI;
	if(m_Rad < 0.0f)
		m_Rad += 2.0f * M_PI;
}
void ENEMY_BOSS::Create(){}
void ENEMY_BOSS::Deleate(){}
void ENEMY_BOSS::Release(){}
void ENEMY_BOSS::SetData(){}
//################################################
// End of File
//################################################
