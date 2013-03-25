//################################################
// <Player.cpp>
//
//------------------------------------------------
// 2012/11/19 ~
//						SekiyamaRumi
// 2013/1/15	���͏��������C��	akihtio tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Player.h"		//�v���C���[
#include "Matrix.h"		//���w�֐��Q
#include "Camera.h"		//�J�����N���X
#include "math.h"
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
#include "MeshMng.h"	//�e�N�X�`���}�l�[�W��
#include "Shader.h"		//�V�F�[�_�[
//================================================
//�萔��`
//================================================
enum MESH_NO{
	PLAYER_M = 0
};
#define P_RADIUS		(15.0f)	//�ړ����a
#define P_SPEED			(0.02f)	//��{���x
#define	P_SPEED_MAX		(0.3f)	//���x�ő�l
#define P_SCALE			(0.2f)	//�g�k��
#define P_SCALE_MIN		(0.5f)	//�g�嗦MIN
#define P_SCALE_MAX		(5.0f)	//�g�嗦MAX
#define P_SCALE_TIMER	(10)	//�G�����ɂ���Ƃ��̑҂�����
#define P_LIFE			(100)	//�̗�
#define P_ATTACK		(10)		//�U��
#define P_TRANCEFORM_TIME	(20)//�ό`����
#define P_SINK_RATE		(0.9f)	//���ސ[��
#define P_SINK_ADD		(0.1f)	//����ł�����
#define P_SCALE_WAIT	(60)	//�g�厞�ԁ@����ȍ~������Ƃ��̑傫���Ōł܂�
#define P_FLAT_RATE		(0.1f)	//����
#define P_FLAT_ADD		(0.2f)	//�����������
#define P_MAX_RAD		(30.0f / 180.0f * M_PI)		//�s���͈͊p�x
#define P_DEAD_ACT_TIME	(120)	//���S�A�N�V��������
#define P_FLASH_COL_TIME (20)	//�_�ŊԊu�i�f�B�t���[�Y�J�ځj
#define P_FLASH_TEX_TIME (10)	//�_�Łi�e�N�X�`���؂�ւ��j
#define P_FIELD_MAX		(97.0f)	//�ړ��͈�(���a)

//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PLAYER::PLAYER()
{
	m_pInput = INPUT_MNG::getInstance();
	p_ShadeMng = SHADER_MNG::Instance();
	m_pCamera   = CAMERA::Instance();
	m_pCube = new CUBEMAP();
	m_EnemyMng = ENEMYMNG::Instance();
	m_Mesh = NULL;
	m_Mesh = new MESH;

	m_pSE = SOUND::Instance();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
PLAYER::~PLAYER()
{
	Release();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Init(void){
	m_TexID = 0;		//�e�N�X�`��ID
	Load(); 
		
	MatrixIdentity(&m_Matrix);	//�ϊ��}�g���b�N�X
	Vec3Identity(&m_Pos);		//�ʒu���W
	Vec3Identity(&m_PosPrev);	//�ʒu���W�O
	Reset();
	//�ʒu���W
	Vec3Identity(&m_Pos);	
	m_Pos.y =1.0f;
	//�ړ�����
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_vec.z = 1.0f;
	m_vecPrev = m_vec;	
	//�ړ����x
	VecScale(&m_vecS, 0.0f);
	//�p�x
	m_Rad = 0.0f;
	//���S��
	m_DeadNum = 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Reset(void)
{
	m_State = P_NORMAL;			//���
	m_Live = true;				//����
	m_Life = P_LIFE;			//�̗�
	m_Attack = P_ATTACK;
	m_DeadNum =0;
	m_bAtkFlg = false;

	//�g�嗦
	m_ScaleRate = 1.0f;		//�S�̊g�嗦
	m_ScaleFlg = 1;			//�g�k�t���O
	m_InEnemyFlg = 0;		//�G���͈͓��ɂ��邩�ǂ����̃t���O
	m_Width = 0.0f;			//��
	m_Scale = VECTOR3(1.0f, 1.0f, 1.0f);
	m_ScaleWaitTime = 0;
	//�ό`�A�N�V�����p
	m_nDirect = 0;			//�ό`����
	m_nCntFrame = 0;		//�t���[���J�E���^
	m_nStartTrans = false;	//�g�����X�t�H�[���X�^�[�g
	//���݃A�N�V����
	m_nDct_Sink = 0;		//�t���O
	m_fSink		= 0.0f;		//����
	m_bSflg		= false;
	//����������A�N�V����
	m_bFflg = false;
	m_nDct_Flat = 0;
	//���S�A�N�V����
	m_nDeadActFrame = 0;
	m_nFrameCnt = 0;
	m_nFrashTimeCnt = 0;
	m_x = 0.0f;
	m_nColDIrect = 0;
	//�v���C���[�̃��g���C�t���O
	m_bRetry = false;
	//�e�N�X�`���؂�ւ�
	m_TexFrashDirect = 0;
	m_nTexFrashCnt = 0;
	//�_���[�W��
	m_bDamage = false;
	m_Accel = VECTOR3();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	m_TexNormal = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring.png", "PLAYER");	//�ʏ�e�N�X�`��
	m_TexRed = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring0.png", "PLAYER");	//�ʏ�e�N�X�`��
	m_TexID = m_TexNormal;
	//�L���[�u�}�b�v������
	//m_CubeTexID = m_pCube->InitCubeMap();

	//���b�V���̓ǂݍ���
	g_MeshMng.GetMesh(&m_MeshA, "MODEL\\PLAYER\\ring.x", _T("PLAYER"));	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshB, "MODEL\\PLAYER\\player2.x", _T("PLAYER"));	//���b�V���ǂݍ���
	g_MeshMng.GetMesh(&m_MeshC, "MODEL\\PLAYER\\player3.x", _T("PLAYER"));	//���b�V���ǂݍ���

	SetMorph(m_Mesh, m_MeshA);	
	CpyVertex(m_Mesh, m_MeshA);		//���_�f�[�^���Ƃ肠�����R�s�[
	//�J���[���ꎞ�ۑ�
	m_col.r = m_Mesh->pMaterial->Diffuse.x;
	m_col.g = m_Mesh->pMaterial->Diffuse.y;
	m_col.b = m_Mesh->pMaterial->Diffuse.z;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Release(void)
{
	//ReleaseMesh(m_Mesh);
	g_MeshMng.ReleaseCat("PLAYER");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Update(VECTOR3 vecx, VECTOR3 vecy)
{
	VECTOR3 vec, vecX, vecY;
	
	//���f���̌��ݕ������߂�
	m_Width = m_Mesh->fRadius * m_ScaleRate;

	//�����Ă��鎞�ړ��\
	if(m_Live)
	{
		//�v���C���[�ړ�����
		if(m_pInput->GetBtnState(BTN_LEFT))	//��
			vecX = vecx * -m_pInput->GetAxis(BTN_LEFT);
		if(m_pInput->GetBtnState(BTN_RIGHT))//�E
			vecX = vecx * -m_pInput->GetAxis(BTN_RIGHT);
		if(m_pInput->GetBtnState(BTN_UP))	//��
			vecY = vecy * -m_pInput->GetAxis(BTN_UP);
		if(m_pInput->GetBtnState(BTN_DOWN))	//��
			vecY = vecy * -m_pInput->GetAxis(BTN_DOWN);
	}
	//�X�s�[�h���Z
	m_Accel += (vecX + vecY) * P_SPEED;

	vec += m_Accel;

	m_Accel *= 0.95f;
	//�ړ������ɓG�����Ȃ����`�F�b�N
	//if(!m_bAtkFlg)
	//	CheckVec(&vec);

	//�͈͕␳
	if(vec.x != 0.0f || vec.y != 0.0f || vec.z != 0.0f)
		CheckField(&vec);

	//��ԑJ��
	switch(m_State)
	{
	case P_WAIT:
		//�P�x�A�N�V��������Ǝ��̃A�N�V���������΂炭�ł��Ȃ��Ȃ�
		if(++m_WaitTime < 60){
			Move(vec);
		}else{
			m_State = P_NORMAL;
			m_WaitTime = 0;
		}
		break;
	case P_NORMAL:
		////��������ł���
		if(!m_Live){
			m_State = P_ATC_DEAD;
			break;
		}
		//�����U�����󂯂Ă�����
		if(m_bDamage)
		{
			m_State = P_DAMEGE_ACT;
			break;
		}

		//�ړ�
		Move(vec);
		//�g�k�J�n
		if((m_pInput->GetBtnState(BTN_A) == TRG || m_pInput->GetBtnState(BTN_A) == PRESS )
			&& (m_pInput->GetBtnState(BTN_R1) != PRESS))
		{
			m_State = P_ATC_SCALE;
			m_bAtkFlg = true;
		}
		
		//�ό`�A�N�V����
		if((m_pInput->GetBtnState(BTN_A) == TRG || m_pInput->GetBtnState(BTN_A) == PRESS)
			&& (m_pInput->GetBtnState(BTN_R1) == PRESS))
			m_State = P_ATC_TRANSFORM;
		break;
	case P_ATC_SCALE:
		//---------------------------
		// �g�k�A�N�V����
		//---------------------------
		ScaleAct();

		//����������
		if(m_Scale.y > P_FLAT_RATE){
			m_Scale.y -= P_FLAT_ADD;
			Move(vec);
		}else
			m_Scale.y = P_FLAT_RATE;
		
		//���� 
		if(m_fSink < P_SINK_RATE){
			m_fSink += P_SINK_ADD;
		}else
			m_fSink = P_SINK_RATE;

		//�g���~����
		/*if(++m_ScaleWaitTime < P_SCALE_WAIT)
		{*/
			//�g�k�I��
			if(m_pInput->GetBtnState(BTN_A) == RLS || m_pInput->GetBtnState(BTN_A) == NONE)
			{
				if(m_InEnemyFlg)				//�ւ̒��ɓG�������Ă��鎞
				{
					m_pSE->PlaySE(SE_ATTACK);
					m_State = P_ENEMY_IN_COLLECT;
				}
				else
					m_State = P_NORMAL_COLLECT;	//�ʏ�T�C�Y�֖߂�
				m_ScaleWaitTime = 0;
				m_bSflg = false; 
				m_bFflg = false;
			}
		//}else
		//{	
		//	if(m_InEnemyFlg)				//�ւ̒��ɓG�������Ă��鎞
		//	{
		//		m_State = P_ENEMY_IN_COLLECT;
		//	}else
		//		m_State = P_NORMAL_FLAT;	//�ʏ�T�C�Y�֖߂��Ȃ�

		//	m_bSflg = false; 
		//	m_bFflg = false;
		//	m_ScaleWaitTime = 0;
		//}
		//���ޏ���
		
		break;

	case P_ATC_TRANSFORM:
		//---------------------------
		// �ό`�A�N�V����
		//---------------------------
		ScaleAct();
		//�g�k�I��
		if(m_pInput->GetBtnState(BTN_A) == RLS || m_pInput->GetBtnState(BTN_A) == NONE)
		{
			m_nStartTrans = true;
		}
		
		if(m_nStartTrans)
		{
			if(TransformAct()){
				if(m_InEnemyFlg)				//�ւ̒��ɓG�������Ă��鎞
				{
					m_State = P_ENEMY_IN_COLLECT;
				}else
					m_State = P_NORMAL_COLLECT;	//�ʏ�T�C�Y�֖߂�
				m_bSflg = false;	
				m_bFflg = false;
				m_nStartTrans = false;
			}
		}
		////���̌����ɖ߂�
		//if(m_Scale.y < m_Scale.x){
		//	m_Scale.y += P_FLAT_ADD;
		//}else
		//	m_Scale.y = m_Scale.x;

		////���̍����ɖ߂�
		//if(m_fSink > 0){
		//	m_fSink -= P_SINK_ADD;
		//}else
		//	m_fSink = 0;
		break;
	case P_ENEMY_IN_COLLECT:
		//���̍����ɖ߂�
		if(m_fSink > 0){
			m_fSink -= P_SINK_ADD;
		}else
			m_fSink = 0;

		//���̌����ɖ߂�
		if(m_Scale.y < m_Scale.x){
			m_Scale.y += P_FLAT_ADD;
		}else
			m_Scale.y = m_Scale.x;
	
		if(ScaleAttack())
		{
			m_InEnemyFlg = false;
			m_bFflg = false;
			if(m_Scale.y >= m_Scale.x && m_Pos.y >= 0.5f)
				m_State = P_NORMAL_COLLECT;	//�ʏ�T�C�Y�֖߂�
		}
		break; 
	case P_NORMAL_COLLECT:		//�ʏ�T�C�Y�֖߂�	�G���͈͊O�ł���Ƃ�
		//���̍����ɖ߂�
		if(m_fSink > 0){
			m_fSink -= P_SINK_ADD;
		}else
			m_fSink = 0;

		//���̌����ɖ߂�
		if(m_Scale.y < m_Scale.x){
			m_Scale.y += P_FLAT_ADD;
		}else
		{	
			m_Scale.y = m_Scale.x;
		}
		if(ScaleActCollect()){
			if(m_Pos.y >= 0.5f)
			{
				m_State = P_NORMAL;
				m_bAtkFlg = false;
			}
		}

		break;
	//case P_NORMAL_FLAT:
	//	//���̍����ɖ߂�
	//	if(m_fSink > 0){
	//		m_fSink -= P_SINK_ADD;
	//	}else
	//		m_fSink = 0;

	//	//���̌����ɖ߂�
	//	if(m_Scale.y < m_Scale.x){
	//		m_Scale.y += P_FLAT_ADD;
	//	}else{
	//		m_Scale.y = m_Scale.x;
	//		
	//		if(m_Pos.y >= 0.5f && m_fSink == 0){
	//			m_State = P_NORMAL;
	//		}
	//	}
	
	case P_ATC_DEAD:	//���S�A�N�V����
		if(++m_nFrameCnt < P_DEAD_ACT_TIME)
		{
			TexFrash();
			//DeadAct();
		}else{
			//SetDiffuse(m_Mesh, m_col);
			
			m_TexID = m_TexNormal;
			m_bRetry = true;
			m_DeadNum ++;
		}
		break;
	default: break;
	}

	//����������s��
	JudgLife();

}

//++++++++++++++++++++++++++++++++++++++++++++++++
// �t�B�[���h���ɂ��邩�ǂ����̃`�F�b�N
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::CheckField(VECTOR3 *vec)
{
	VECTOR3 posV, vecV;		//
	VECTOR3 vecX, vecZ;	//�x�N�g���̐�������	
	VECTOR3 crsPV, vNorm;
	float	rad = 0;

	if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
	{
		//�P�ʃx�N�g����
		Vec3Normalize(&posV, m_Pos);	//�@�ʒu
		Vec3Normalize(&vecV, *vec);		//�A���̃x�N�g��

		//���̒��S����̈ʒu�ł̃x�N�g���̒��p�x�N�g�������߂�
		Vec3Cross(&crsPV, posV, VECTOR3(0.0f, 1.0f, 0.0f));

		//���݈ړ����悤�Ƃ��Ă�x�N�g���Ɖ~�̐ڐ��x�N�g���Ƃ̓��ς���p�x�����߂�
		rad = Vec3Dot(*vec, crsPV);
		if(crsPV.y > 0)
		{
			//�x�N�g�������𕪉�����
			vecX = *vec * cos(rad);
			vecZ = *vec * sin(rad);
		//X�����̂�
		*vec = vecZ;
		}else if(crsPV.y < 0)
		{
			//�x�N�g�������𕪉�����
			vecX = *vec * cos(- rad);
			vecZ = *vec * sin(- rad);
		//X�����̂�
		*vec = vecZ;
		}

		//��������ł��͈͊O�ɂȂ�悤�Ȃ�␳
		if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
		{
			Vec3Normalize(&vNorm, m_Pos + *vec);
			*vec -= vNorm * (VecLength(m_Pos + *vec) - P_FIELD_MAX);
			vec->y = 0.0f;
		}
	}
	
	//float fR = VecLength(m_Pos);
	//VECTOR3	posV, vecV, crsPV, veccrs;
	//MATRIX  mat;
	//VECTOR3 vecWorld;
	//m_pCamera->GetMatrixInv(&mat);
	//Vec3TransformCoord(&vecWorld, mat, *vec);
	//vecWorld.y = 0.0f;
	//if(VecLength(m_Pos + *vec) >= P_FIELD_MAX)
	//{
	//	//�P�ʃx�N�g����
	//	Vec3Normalize(&posV, m_Pos);	//�@�ʒu
	//	Vec3Normalize(&vecV, vecWorld);		//�A���̃x�N�g��

	//	//���̒��S����̈ʒu�ł̃x�N�g���̒��p�x�N�g�������߂�
	//	Vec3Cross(&crsPV, posV, VECTOR3(0.0f, 1.0f, 0.0f));

	//	//�@�ƇA�̃x�N�g���̊O�ς���E�����������𒲂ׂ�
	//	Vec3Cross(&veccrs, posV, vecWorld);

	//	//�E���̎�
	//	if(veccrs.y > 0)
	//	{	
	//		VECTOR3 tmp;
	//		Vec3Normalize(&crsPV, crsPV);
	//		tmp = vecV * Vec3Dot(vecV, crsPV);
	//		tmp = crsPV - tmp;
	//		Vec3TransformCoord(vec, m_pCamera->m_CameraMat, vecWorld);
	//	}
	//	//�����̎�
	//	else if(veccrs.y < 0)
	//	{	
	//		VECTOR3 tmp1;
	//		Vec3Normalize(&crsPV, crsPV);
	//		tmp1 = vecV * Vec3Dot(vecV, crsPV);
	//		tmp1 = crsPV  - tmp1;
	//		Vec3TransformCoord(vec, m_pCamera->m_CameraMat, vecWorld);

	//	}
	//	//���s�܂��͋t����
	//	else
	//	{
	//		//�������Ȃ�
	//		*vec = VECTOR3(0.0f, 0.0f, 0.0f);
	//	}
	//}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �_���[�W���󂯂����̓_�ŏ���
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::TexFrash(void)
{
	switch(m_TexFrashDirect)
	{
	case 0:
		if(++m_nTexFrashCnt > P_FLASH_TEX_TIME){
			m_TexID = m_TexRed;
			m_TexFrashDirect = 1;
		}
		break;
	case 1:
		if(--m_nTexFrashCnt < 0){
			m_TexID = m_TexNormal;
			m_TexFrashDirect = 0;
		}
		break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �_���[�W���󂯂����̓_�ŏ���
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DeadAct(void)
{
	COLOR colChenge = {1.0f, 0.0f, 0.0f, 1.0f};

	//�F��u������
	switch(m_nColDIrect)
	{
	case 0:
		if(++m_nFrashTimeCnt < P_FLASH_COL_TIME)
			FlashDiffuse(m_Mesh, m_col, colChenge, P_FLASH_COL_TIME, m_nFrashTimeCnt);
		else
			m_nColDIrect = 1;
		break;
	case 1:
		if(--m_nFrashTimeCnt < 0)
			m_nColDIrect = 0;
		else			
			FlashDiffuse(m_Mesh, m_col, colChenge, P_FLASH_COL_TIME, m_nFrashTimeCnt);
		break;
	default:break;
	}


	////���U��
	//switch(m_nDirectDeadAct)
	//{
	//case 0:
	//	m_x += 0.2f;
	//	if(m_x > 0.3f)
	//		m_nDirectDeadAct = 1;

	//	break;
	//case 1:
	//	m_x -= 0.2f;
	//	if(m_x < -0.3f)
	//		m_nDirectDeadAct = 0;
	//	break;
	//}
	
	

}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �G�ƂԂ����Ă����̈ړ������̏C��
//--in--------------------------------------------
// ���݃x�N�g��
//--out-------------------------------------------
// �I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::CheckVec(VECTOR3 *vec)
{
	VECTOR3	vecEnemy;	//�G�ւ̃x�N�g��
	VECTOR3 vecCross;
	VECTOR3 vecCpy;
	VECTOR3	vecMix;		//����
	float   fRad;

	//�x�N�g�����X�V����Ă��邩�ǂ���
	if(VecLength(*vec) != 0)
		Vec3Normalize(&vecCpy, *vec);
	else
		return false;

	//�ʏ�G
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		//����ł�G�͔�΂�
		if(!m_EnemyMng->m_pEnemy[i]->m_Live)
			continue;
		
		//�Ԃ����Ă���G���`�F�b�N
		if((VecLength(this->m_Pos - m_EnemyMng->m_pEnemy[i]->m_Pos) < m_EnemyMng->m_pEnemy[i]->m_Width * 0.5f + this->m_Width * 0.5f))	//�O���̉�
		{
			//�@�G�ƃv���C���[�̃x�N�g��
			vecEnemy = m_EnemyMng->m_pEnemy[i]->m_Pos - this->m_Pos;
			//�x�N�g���̐��K��
			Vec3Normalize(&vecEnemy, vecEnemy);
			
			//�x�N�g�������s
			if(((vecCpy.x * vecEnemy.y - vecCpy.y * vecEnemy.x) * (vecCpy.x * vecEnemy.y - vecCpy.y * vecEnemy.x)) + ((vecCpy.y * vecEnemy.z - vecCpy.z * vecEnemy.y)* (vecCpy.y * vecEnemy.z - vecCpy.z * vecEnemy.y)) + ((vecCpy.z * vecEnemy.x - vecCpy.x * vecEnemy.z) * (vecCpy.z * vecEnemy.x - vecCpy.x * vecEnemy.z))  == 0)
			{
				*vec = VECTOR3(0.0f, 0.0f, 0.0f);	//�ړ����Ȃ�
				continue;
			}	
			//�@�ƇA�̊O�ς���E����������������B
			Vec3Cross(&vecCross, vecCpy, vecEnemy);

			//�A���݂̌����Ƈ@�̃x�N�g���̂Ȃ��p���ݒ�p�x���傫�������炻�̂܂܍��̃x�N�g��
			if(vecCross.y == 0.0f)	//�x�N�g�������s
				*vec = VECTOR3(0.0f, 0.0f, 0.0f);	//�ړ����Ȃ�

			//���ς���s���\�͈͓����ǂ����𒲂ׂ�
			fRad = Vec3Dot(vecCpy, vecEnemy);
			/*if(fRad > 0.0f)
				*vec =  VECTOR3(0.0f, 0.0f, 0.0f);*/
			if(vecCross.y > 0.0f)	//�ړ������������
			{
				if(fRad < P_MAX_RAD)
				{	//�A�Ńx�N�g�����ݒ�p�x���ɂȂ��Ă�����A�V�����x�N�g����ݒ�
					vecMix = (vecEnemy * -1) + vecCpy + vecCpy;
					vecMix.y = 0.0f;
					*vec = vecMix ; 
				}

			}
			if(vecCross.y < 0.0f)	//�ړ��������E���
			{
				if(fRad > -P_MAX_RAD)
				{	//�A�Ńx�N�g�����ݒ�p�x���ɂȂ��Ă�����A�V�����x�N�g����ݒ�
					vecMix = (vecEnemy * -1) + vecCpy + vecCpy;
					vecMix.y = 0.0f;
					*vec = vecMix ; 
				}
			}
		}
		else
		{
		
		}

	}
	return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�v���C���[�A�N�V����
// �����O�ό`�A�N�V����
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::TransformAct(void)
{
	switch(m_nDirect)
	{
	case 0:
		if(++m_nCntFrame > P_TRANCEFORM_TIME)			//�����O���甼�~�`��
		{
			m_nDirect = 1; 
			m_nCntFrame = 0;
			break;
		}
		Morphing(m_Mesh, m_MeshA, m_MeshB, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 1:
		if(++m_nCntFrame > P_TRANCEFORM_TIME)			//���~�`���狅
		{
			m_nDirect = 2;	
			m_nCntFrame = P_TRANCEFORM_TIME;
			break;
		}
		Morphing(m_Mesh, m_MeshB, m_MeshC, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 2:
		if(--m_nCntFrame < 0)	//���~�`���狅
		{
			m_nDirect = 3; 
			m_nCntFrame = P_TRANCEFORM_TIME;
			break;
		}
		Morphing(m_Mesh, m_MeshB, m_MeshC, m_nCntFrame, 0, P_TRANCEFORM_TIME);	
		break;
	case 3:
		if(--m_nCntFrame < 0)	//���~�`���狅
		{
			m_nDirect = 0;
			m_nCntFrame = 0;
			//Morphing(m_Mesh, m_MeshA, m_MeshB, 0, 0, P_TRANCEFORM_TIME);
			return true;
		}
		Morphing(m_Mesh, m_MeshA, m_MeshB,m_nCntFrame, 0, P_TRANCEFORM_TIME);
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�v���C���[�A�N�V����
// �v���C���[�̃A�N�V�������Ǘ�
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Act(int State)
{
	m_State = State;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�g��
// �v���C���[�̊g��k��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::ScaleAct(void)
{
	float fScale = 0.0f;
	//�g�k
	m_ScaleRate += P_SCALE * m_ScaleFlg;
	
	if(m_ScaleRate < P_SCALE_MIN)
	{
		m_ScaleRate = P_SCALE_MIN;
		m_ScaleFlg ^= -1;
	}
	if(m_ScaleRate > P_SCALE_MAX)
	{
		m_ScaleRate = P_SCALE_MAX;
		//m_ScaleFlg ^= -1;
	}

	m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
	m_Scale.z = m_ScaleRate;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�g�k
// �v���C���[�̊g��k���T�C�Y�����̃T�C�Y�ɖ߂�
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::ScaleActCollect(void)
{
	unsigned int tmp;
	tmp = unsigned int(m_ScaleRate * 100);
	//�g�k���ʏ펞�łȂ��Ƃ�
	if(!(tmp > 80 && tmp < 120))
	{
		if(tmp < 100){
			m_ScaleRate += (P_SCALE * 0.2f);
		}
		else{
			m_ScaleRate -= (P_SCALE);
		}

		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return false;
	}else{
		m_ScaleRate = 1.0f;
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return true;
	}
}//++++++++++++++++++++++++++++++++++++++++++++++++
//�g�k
// �v���C���[�̊g��k���T�C�Y�����̃T�C�Y�ɖ߂�
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool PLAYER::ScaleAttack(void)
{
	//�k��
	if((m_ScaleRate * 100) > 5)
	{
		m_ScaleRate -= (P_SCALE * 2.0f);
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return false;
	}else{
		m_ScaleRate = 0.05f;
		m_Scale.x = m_ScaleRate;
		m_Scale.y = m_ScaleRate;
		m_Scale.z = m_ScaleRate;
		return true;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::Draw(void)
{
	////�A�^������p���̏o�͏���
	//GLUquadricObj *pSphere;		//�I�u�W�F�N�g�|�C���^������
	//pSphere = gluNewQuadric();	//�I�u�W�F�N�g�̐���
	//gluQuadricDrawStyle(pSphere, GLU_FILL);	//�I�u�W�F�N�g�̕`��^�C�v��ݒ�

	//���ԕ`��
	glPushMatrix();	

	//�v���C���[�A�N�V����
	glTranslatef((GLfloat)m_x, (GLfloat)0.0f, (GLfloat)0.0f);	
	glTranslatef((GLfloat)0.0f, (GLfloat)-m_fSink, (GLfloat)0.0f);	
	glTranslatef((GLfloat)m_Pos.x, (GLfloat)m_Pos.y, (GLfloat)m_Pos.z);	
	glRotatef(((GLfloat)m_Rad * 180 / M_PI), (GLfloat)0, (GLfloat)1.0f , (GLfloat)0);	//Y����]
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);
	//glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	glEnable(GL_DEPTH_TEST);
	//�}�g���b�N�X�̍���
	//MATRIX mat1, mat2, mat3;
	//MatrixTranslation(&mat1, m_Pos.x, m_Pos.y, m_Pos.z);
	//MatrixRotationY(&mat2, (GLfloat)(m_Rad));
	//MatrixScaling(&mat3, m_Scale.x, m_Scale.y, m_Scale.z);
	////MatrixScaling(&mat3, m_ScaleRate, m_ScaleRate, m_ScaleRate);
	//MatrixMultiply(&mat1, mat1, mat2);
	//MatrixMultiply(&m_Matrix, mat3, mat1);


	//	DrawMesh(m_Mesh[1]);

	//GLint prm;
	//glGetIntegerv(GL_MAX_TEXTURE_UNITS, &prm);

	//�V�F�[�_�̓K�p
	p_ShadeMng->UseShader(COOK);
	//�`��
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	p_ShadeMng->SetAlpha(COOK,1.0f);		//���߂Ȃ�

	//�������Ă���`��
	
	// �e�N�X�`�����j�b�g���w�肷��
	p_ShadeMng->SetTexUnit(COOK, 0);	//�m�[�}���e�N�X�`��
	DrawMesh(m_Mesh);
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	p_ShadeMng->UnUseShader();

	//�ݒ�����ɖ߂�
	glEnable(GL_ALPHA_TEST);	//���e�X�g������
	glDisable(GL_BLEND);		//
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��(���}�b�v)
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DrawCube(void)
{
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScaled(-1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexID);

	/* �e�N�X�`���� */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
	/* �L���[�u�}�b�s���O��L���ɂ��� */
	glEnable(GL_TEXTURE_CUBE_MAP);
	//�e�N�X�`�����W��������������
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	//�`��
	glPushMatrix();	

	//�v���C���[�A�N�V����
	glTranslatef((GLfloat)m_Pos.x + m_x, (GLfloat)m_Pos.y + m_fSink, (GLfloat)m_Pos.z);	
	glRotatef(((GLfloat)m_Rad * 180 / M_PI), (GLfloat)0, (GLfloat)1.0f , (GLfloat)0);	//Y����]
	glScalef(m_ScaleRate, m_ScaleRate, m_ScaleRate);

	glEnable(GL_DEPTH_TEST);
	//�}�g���b�N�X�̍���
	MATRIX mat1, mat2, mat3;
	m_Pos.y = 0.5f;
	MatrixTranslation(&mat1, m_Pos.x, m_Pos.y, m_Pos.z);
	MatrixRotationY(&mat2, (GLfloat)(m_Rad));
	MatrixScaling(&mat3, m_ScaleRate, m_ScaleRate, m_ScaleRate);
	MatrixMultiply(&mat1, mat1, mat2);
	MatrixMultiply(&m_Matrix, mat3, mat1);


	//	DrawMesh(m_Mesh[1]);

	//GLint prm;
	//glGetIntegerv(GL_MAX_TEXTURE_UNITS, &prm);

	////�V�F�[�_�̓K�p
	p_ShadeMng->UseShader(REFLECT);
	p_ShadeMng->SetCamPos(REFLECT, m_pCamera->ViewPos);
	////�`��
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexID);

	//�������Ă���`��
	if(m_Live)
	{
		// �e�N�X�`�����j�b�g���w�肷��
		//p_ShadeMng->SetTexUnit(PHONG, 0);	//�m�[�}���e�N�X�`��
		DrawMesh(m_Mesh);
	}
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	//p_ShadeMng->UnUseShader();

	//�ݒ�����ɖ߂�
	glEnable(GL_ALPHA_TEST);	//���e�X�g������
	glDisable(GL_BLEND);		//
	//
	//�e�N�X�`�����W�̎��������𖳌��ɂ���
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	/* �e�N�X�`���}�b�s���O�I�� */
	glDisable(GL_TEXTURE_CUBE_MAP);

	/* �e�N�X�`���ϊ��s��̐ݒ� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�L���[�u�}�b�v�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void PLAYER::DrawCubeMap(void)
{
	if(m_pCube)
		m_pCube->MakeCubeMap(m_Pos);
}

//################################################
// End of File
//################################################
