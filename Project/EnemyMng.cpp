//################################################
// <EnemyMng.h>
//
//------------------------------------------------
// 2012/12/03 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "EnemyMng.h"

//================================================
//�萔��`
//================================================
#define COL_RATE_MAX (1.0f)		//�Փ˔���͈̔�
#define COL_RATE_1   (0.8f)		//�Փ˔���͈̔�
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

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
ENEMYMNG::ENEMYMNG()
{	
	//�U�R�G
	for(int i = 0; i < ENEMY_NOMAL_NUM; i++)
	{
		m_pEnemy[i] = NULL;
		m_pEnemy[i] = new ENEMY_NORMAL;
	}
	//�{�X

		m_pEnemyBoss = NULL;
		m_pEnemyBoss = new ENEMY_BOSS;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
ENEMYMNG::~ENEMYMNG()
{
	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
	{
		//�f�[�^������Ώ���
		if(m_pEnemy[i])
		{
			delete m_pEnemy[i];				//�f�[�^���폜
			m_pEnemy[i] = NULL;
		}
	}
	//�{�X�G

		//�f�[�^������Ώ���
		if(m_pEnemyBoss)
		{
			delete m_pEnemyBoss;				//�f�[�^���폜
			m_pEnemyBoss = NULL;
		}

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�쐬
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Init(PLAYER *pPlayer)
{
	//�v���C���[�̃|�C���^��Ⴄ
	m_pPlayer = pPlayer;		//�A�^������p

	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Init();
	//�{�X�G
		m_pEnemyBoss->Init();

	m_pEffectMng = EFFECT_MNG::Instance();
	m_pScore = SCORE::Instance();
	m_pSE = SOUND::Instance();

	Load();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�쐬
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Reset(void)
{
	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Reset();
	//�{�X�G
	m_pEnemyBoss->Reset();

	//�J�E���g
	m_DeadCnt = 0;
	m_BossCnt = 0;

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Load(void)
{
	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Load();
	//�{�X�G

		m_pEnemyBoss->Load();
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�쐬
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Create(void)
{
	static int nCount = 0;

	nCount ++;

	if(nCount < 60)
		return;
	nCount = 0;

	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
	{
		if(m_pEnemy[i]->m_Live)
			continue;
		m_pEnemy[i]->Create();	//�쐬
		break;
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�폜
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG:: Deleate(void)
{
	//�U�R�G
	for(int i=0; i < ENEMY_NOMAL_NUM; i++)
		m_pEnemy[i]->Deleate();
	//�{�X�G
	m_pEnemyBoss->Deleate();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void ENEMYMNG::Update(void)
{
	bool bDead = false;

	//�G�̐���
	if(m_BossCnt == 0)	//�{�X���|����Ă��Ȃ���ΓG�𐶐�
		Create();

	//�U�R�G
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		if(!m_pEnemy[i]->m_Live)
			continue;
		bDead = m_pEnemy[i]->Update(m_pPlayer->m_Pos, m_pPlayer->m_Width, m_pPlayer->m_Attack);

		//���S���J�E���g
		if(bDead)
		{
			m_pEffectMng->Set(E_PARTICLE_SPLASH, m_pEnemy[i]);
			 m_DeadCnt ++; 
		
			//m_pScore->addEnemyDeathScore(m_DeadCnt);//�X�R�A���Z
			bDead = false;
		}

	}
	//�t���O������
	bDead = false;

	if(m_DeadCnt > m_pEnemyBoss->m_AppearBoss)
	{
		m_pEnemyBoss->SetLive(true);
	}
	//�{�X�G

		if(!m_pEnemyBoss->m_Live)
			return;
		bDead = m_pEnemyBoss->Update(m_pPlayer->m_Pos, m_pPlayer->m_Width, m_pPlayer->m_Attack);

		if(m_pEnemyBoss->m_Life <= 0)
		{
			//���ׂĂ̓G���_���[�W���[�V������
			for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
			{
				if(!m_pEnemy[i]->m_Live)
					continue;
				//�����U�����[�V�������̏ꍇ
				m_pEnemy[i]->m_ColRingIn = true;
			}

		//���S���J�E���g
		if(bDead)
		{
			m_BossCnt ++;
			bDead = false;
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
void ENEMYMNG::Draw(void)
{
	//�U�R�G
	for(int i = 0; i < ENEMY_NOMAL_NUM; i ++)
	{
		if(!m_pEnemy[i]->m_Live)
			continue;
		m_pEnemy[i]->Draw();
	}
	//�{�X�G

		if(!m_pEnemyBoss->m_Live)
			return;
		m_pEnemyBoss->Draw();

}
//################################################
// End of File
//################################################
