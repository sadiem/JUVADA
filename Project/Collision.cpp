//################################################
// <Collision.h>
//
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
// 2013/1/9		:�{�X�����蔻��ǉ�
//						Akihito Tanaka
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Collision.h"
#include "Matrix.h"
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
COLLISION::COLLISION()
{
	m_pPlayer = PLAYER::Instance();
	m_pEnemy  = ENEMYMNG::Instance();
	m_pEffect = EFFECT_MNG::Instance();
	m_flgAtk = false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
COLLISION::~COLLISION()
{

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�Փ˔���
// �G��Ă���
//--in--------------------------------------------
// 1�C�ڂ̈ʒu
// 2�C�ڂ̈ʒu
// 1�C�ڂ̕�
// 2�C�ڂ̕�
//--out-------------------------------------------
// ����
//++++++++++++++++++++++++++++++++++++++++++++++++
bool COLLISION::CollsionSphere(VECTOR3 pos, VECTOR3 pos2, float w, float w2)	//�Փ˔���
{
	//�o�E���f�B���O�X�t�B�A
	VECTOR3 tmp;
	tmp.x = pos.x - pos2.x;
	tmp.y = pos.y - pos2.y;
	tmp.z = pos.z - pos2.z;

	if(VecLength(tmp) < (w + w2))
	{
		return true;	//�Փ�
	}
	return false;		//���Փ�
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::Update()
{
	CollisionEnemyAndPlayer();
	CollisionBossAndPlayer();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�G�ƃv���C���[�̏Փ˔���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::CollisionEnemyAndPlayer(void)
{
	//----------------------------------
	//	�m�[�}���ȓG�Ƃ̃A�^������
	//----------------------------------
	for(int nLoop = 0; nLoop < ENEMY_NOMAL_NUM; nLoop ++)
	{
		//����ł��玟�̓G������
		if(!m_pEnemy->m_pEnemy[nLoop]->m_Live)
			continue;

		//�v���C���[�ƓG�̏Փ˔���
		if((VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) < m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + m_pPlayer->m_Width * 0.5f)	//�O���̉�
			&&
			(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) > m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + ((m_pPlayer->m_Width * 0.5f) * 0.8f)))	//�����̉�
		{
			m_pEffect->Set(E_PARTICLE_LINE, m_pEnemy->m_pEnemy[nLoop]);	//�G�t�F�N�g�Z�b�g
			m_pEnemy->m_pEnemy[nLoop]->m_ColPlayer = true;
			
			//�v���C���[���G����_���[�W���󂯂�
			if(m_pEnemy->m_pEnemy[nLoop]->m_AtkHitPlayer)
			{
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemy[nLoop]->m_Attack);	//�v���C���[�փ_���[�W
				m_pEnemy->m_pEnemy[nLoop]->m_AtkHitPlayer = false;
			}
		}
		else
			m_pEnemy->m_pEnemy[nLoop]->m_ColPlayer = false;	//�Փ˂��Ă��Ȃ���Ԃ�
		if(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemy[nLoop]->m_Pos) < m_pEnemy->m_pEnemy[nLoop]->m_Width * 0.5f + ((m_pPlayer->m_Width * 0.5f) * 0.8f))
		{
			//�v���C���[��
			if(!m_pPlayer->m_InEnemyFlg)
				m_pPlayer->m_InEnemyFlg = true;		//�G�����ɂ���
			//�G��
			if(m_pPlayer->m_State == P_ENEMY_IN_COLLECT)
				m_pEnemy->m_pEnemy[nLoop]->m_ColRingIn = true;	//�U�����󂯂�
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�G�ƃv���C���[�̏Փ˔���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void COLLISION::CollisionBossAndPlayer(void)
{
	//����ł��珈�����Ȃ�
	if(!m_pEnemy->m_pEnemyBoss->m_Live)
			return;

		
	//�G��WAIT�̂Ƃ��A�^�b�N�t���O��܂�
	if(m_pEnemy->m_pEnemyBoss->m_State == WAIT)
		m_flgAtk = false;

	
//if(m_pEnemy->m_pEnemyBoss->m_State == SPIN_ATTACK)
//{	
//	float a;
//	a = 1.0f;
//}
	//�v���C���[�ƓG�̏Փ˔���
	if(CollsionSphere(m_pPlayer->m_Pos, m_pEnemy->m_pEnemyBoss->m_Pos, m_pPlayer->m_Width * 0.5f, m_pEnemy->m_pEnemyBoss->m_Width))
	{
		if(!m_pPlayer->m_InEnemyFlg)
				m_pPlayer->m_InEnemyFlg = true;

		//�W�����v�A�^�b�N��
		if(m_pEnemy->m_pEnemyBoss->m_JumpFlg)	//�W�����v���n��
		{
			if(!m_flgAtk)
			{
				m_flgAtk = true;		//�U��
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemyBoss->m_Attack);	//�v���C���[�փ_���[�W
			}
		}
		//�X�s���A�^�b�N��
		if(m_pEnemy->m_pEnemyBoss->m_State == SPIN_ATTACK)
		{	
			if(!m_flgAtk)
			{
				m_flgAtk = true;	//�U��
				m_pPlayer->LifeCount(m_pEnemy->m_pEnemyBoss->m_Attack);	//�v���C���[�փ_���[�W
			}
		}

		if(!m_pPlayer->m_InEnemyFlg)
			m_pPlayer->m_InEnemyFlg = true;
	}


	//�v���C���[�ƓG�̃����O���Փ˔���
	if(m_pEnemy->m_pEnemyBoss->m_State == WAIT)
	{
		if(m_pPlayer->m_State == P_ENEMY_IN_COLLECT)	//�U����
		{
			float f0, f1;
			f0 = VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemyBoss->m_Pos);
			f1 = (m_pPlayer->m_Width + m_pEnemy->m_pEnemyBoss->m_Width);
			if(VecLength(m_pPlayer->m_Pos - m_pEnemy->m_pEnemyBoss->m_Pos) < (m_pPlayer->m_Width + m_pEnemy->m_pEnemyBoss->m_Width))
			{
				m_pEnemy->m_pEnemyBoss->m_ColRingIn = true;	//�v���C���[����̍U��
			}
		}
	}
}

//################################################
// End of File
//################################################