//################################################
// <Opening.h>
//
//------------------------------------------------
// 2013/01/14 ~
//						SekiyamaRumi
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Opening.h"
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
//�t�F�[�h
#define OP_FADE_POS_X (-10)			//�t�F�[�h�|�������ʒu
#define OP_FADE_POS_Y (-10)
#define OP_FADE_H (20)				//�t�F�[�h�|���c��
#define OP_FADE_W (20)				//�@�@�@�@�@�@�@����
//���S
#define OP_LOGO_POS_X (-3.0f)		//���S�|�������ʒu
#define OP_LOGO_POS_Y (-3.0f)
#define OP_LOGO_H (6)				//���S�|��	�c��
#define OP_LOGO_W (7)				//�@�@�@�@�@s�@�@����
//�^�C�g��
#define OP_TITLE_POS_X (-5)			//�^�C�g���|�������ʒu
#define OP_TITLE_POS_Y (-5)
#define OP_TITLE_H (10)				//�^�C�g���|���c��
#define OP_TITLE_W (10)				//�@�@�@�@�@�@�@����
#define OP_TITLE_SCALE_MAX	(1.5f)	//�^�C�g���̊g�嗦�ő�l
#define OP_ADD_TILE_SCALE	(OP_TITLE_SCALE_MAX * 0.03f)	//�^�C�g���̊g�嗦�̑����l
//BG
#define OP_BG_H (40)				//�t�F�[�h�|���c��
#define OP_BG_W (40)				//�@�@�@�@�@�@�@����
#define OP_BG_POS_X (-OP_BG_H / 2.0f)	//�t�F�[�h�|�������ʒu
#define OP_BG_POS_Y (OP_BG_POS_X)
//PUSH ENTER�p�{�^��
#define OP_PUSHENTER_H (1)				//PushEnter�|���c��
#define OP_PUSHENTER_W (3)				//�@�@�@�@�@�@�@����
#define OP_PUSHENTER_POS_X (-OP_PUSHENTER_W / 2.0f)	//PushEnter�|�������ʒu
#define OP_PUSHENTER_POS_Y (OP_PUSHENTER_POS_X)


//�t�F�[�h����
#define OP_FADE_TIME	(120)		//�t�F�[�h�^�C��

//�҂�����
#define OP_WAIT_TIME    (180)		//�E�F�C�g

//�����O
#define OP_ADD_RING_SPEED (0.2f)		//�����O���Z�X�s�[�h
#define OP_MINUS_RING_SPEED (0.1f)		//�����O���Z�X�s�[�h
#define OP_RING_SCALE	(0.3f)			//�����O�g�k���X�s�[�h
#define OP_RING_JUMP	(0.10f)			//�����O�W�����v
#define OP_RING_SCALE_MAX (10.0f)		//�g�k���}�b�N�X
#define OP_TITLE_OUT	(20.0f)			//��ʊO����
//�^�C�g��
#define OP_TITLE_H_MAX (3.0f)			//�^�C�g���̔�яo�����̍����̍ő�l
#define OP_ADD_H_TITLE (0.05f)			//�^�C�g���̍����̉��Z�l

//��ԑJ��
enum {
	LOGO,			//���S
	TITLE,			//�^�C�g��
	PUSH_ENTER,		//�v�b�V���G���^�[
	OUT_TITLE		//�^�C�g�����|����
};
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
OP::OP(){}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
OP::~OP(){}

//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Init(void)
{
	m_pShadeMng = SHADER_MNG::Instance();
	m_pSE = SOUND::Instance();
	m_TexID = g_TexMng.GetTexture("TEXTURE\\OP\\Op.png", "OP");
	m_TexIDM = g_TexMng.GetTexture("TEXTURE\\PLAYER\\ring.png", "PLAYER");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\OP\\title.png", "PLAYER");
	m_TexIDB = g_TexMng.GetTexture("TEXTURE\\OP\\bg.png", "OP");

	g_MeshMng.GetMesh(&m_MeshR, "MODEL\\PLAYER\\ring.x", "PLAYER");
	g_MeshMng.GetMesh(&m_MeshT, "MODEL\\OP\\title.x", "PLAYER");
	g_MeshMng.GetMesh(&m_MeshD, "MODEL\\OP\\Deco.x","OP"); 
	m_pInput = INPUT_MNG::getInstance();	//�C���X�^���X�̎擾
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Reset(void)
{
	m_nState = LOGO;
	m_nInState = 0;
	m_nRingState = 0;
	m_nCnt = 0;
	m_bFlgPushStart = false;

	//�^�C�g��
	m_Titlpos = VECTOR3(0.0f, 2.0f, 0.0f);
	m_TAng = -20.0f;
	m_TScl = 0.001f;
	//�����O
	m_Ringpos.x = -20.0f;
	m_Ringpos.y =  0.0f;
	m_Ringpos.z =  0.0f;
	m_RAng = 0.0f;
	m_RScl = 1.0f;
	m_RJump = OP_RING_JUMP;	//�����O�W�����v
	m_RbDraw = false;		//�`��t���O

	//���_�Z�b�g
	SetPoli();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::SetPoli(void)
{
	//------------------------
	//���_�̃Z�b�g
	//------------------------
	//�t�F�[�h�p
	m_PFade.ver[0].x = OP_FADE_POS_X;
	m_PFade.ver[0].y = OP_FADE_POS_Y + OP_FADE_H;
	m_PFade.ver[0].z = -1.0f;

	m_PFade.ver[1].x = OP_FADE_POS_X;
	m_PFade.ver[1].y = OP_FADE_POS_Y;
	m_PFade.ver[1].z = -1.0f;

	m_PFade.ver[2].x = OP_FADE_POS_X + OP_FADE_W;
	m_PFade.ver[2].y = OP_FADE_POS_Y ;
	m_PFade.ver[2].z = -1.0f;

	m_PFade.ver[3].x = OP_FADE_POS_X + OP_FADE_W;
	m_PFade.ver[3].y = OP_FADE_POS_Y + OP_FADE_H;
	m_PFade.ver[3].z = -1.0f;

	//���S�p
	m_PLogo.ver[0].x = OP_LOGO_POS_X;
	m_PLogo.ver[0].y = OP_LOGO_POS_Y + OP_LOGO_H;
	m_PLogo.ver[0].z = 0.0f;

	m_PLogo.ver[1].x = OP_LOGO_POS_X;
	m_PLogo.ver[1].y = OP_LOGO_POS_Y;
	m_PLogo.ver[1].z = 0.0f;

	m_PLogo.ver[2].x = OP_LOGO_POS_X + OP_LOGO_W;
	m_PLogo.ver[2].y = OP_LOGO_POS_Y;
	m_PLogo.ver[2].z = 0.0f;

	m_PLogo.ver[3].x = OP_LOGO_POS_X + OP_LOGO_W;
	m_PLogo.ver[3].y = OP_LOGO_POS_Y + OP_LOGO_H;
	m_PLogo.ver[3].z = 0.0f;


	//BG�p
	m_PBg.ver[0].x = OP_BG_POS_X;
	m_PBg.ver[0].y = OP_BG_POS_Y + OP_BG_H;
	m_PBg.ver[0].z = 0.0f;

	m_PBg.ver[1].x = OP_BG_POS_X;
	m_PBg.ver[1].y = OP_BG_POS_Y;
	m_PBg.ver[1].z = 0.0f;

	m_PBg.ver[2].x = OP_BG_POS_X + OP_BG_W;
	m_PBg.ver[2].y = OP_BG_POS_Y;
	m_PBg.ver[2].z = 0.0f;

	m_PBg.ver[3].x = OP_BG_POS_X + OP_BG_W;
	m_PBg.ver[3].y = OP_BG_POS_Y + OP_BG_H;
	m_PBg.ver[3].z = 0.0f;

	//PUSH START�p�{�^��
	m_PPushEnter.ver[0].x = OP_PUSHENTER_POS_X;
	m_PPushEnter.ver[0].y = OP_PUSHENTER_POS_Y + OP_PUSHENTER_H;
	m_PPushEnter.ver[0].z = 0.0f;

	m_PPushEnter.ver[1].x = OP_PUSHENTER_POS_X;
	m_PPushEnter.ver[1].y = OP_PUSHENTER_POS_Y;
	m_PPushEnter.ver[1].z = 0.0f;

	m_PPushEnter.ver[2].x = OP_PUSHENTER_POS_X + OP_PUSHENTER_W;
	m_PPushEnter.ver[2].y = OP_PUSHENTER_POS_Y;
	m_PPushEnter.ver[2].z = 0.0f;

	m_PPushEnter.ver[3].x = OP_PUSHENTER_POS_X + OP_PUSHENTER_W;
	m_PPushEnter.ver[3].y = OP_PUSHENTER_POS_Y + OP_PUSHENTER_H;
	m_PPushEnter.ver[3].z = 0.0f;

	//------------------------
	//�e�N�X�`���̃Z�b�g
	//------------------------
	//�t�F�[�h�p
	m_PFade.tex[0].x = 7.0f / 16.0f;
	m_PFade.tex[0].y = 1.0f - (6.0f / 16.0f);

	m_PFade.tex[1].x = 7.0f / 16.0f;
	m_PFade.tex[1].y = 1.0f - (5.0f / 16.0f);

	m_PFade.tex[2].x = 8.0f / 16.0f;
	m_PFade.tex[2].y = 1.0f - (5.0f / 16.0f);

	m_PFade.tex[3].x = 8.0f / 16.0f;
	m_PFade.tex[3].y = 1.0f - (6.0f / 16.0f);

	//���S�p
	m_PLogo.tex[0].x = 0.0f;
	m_PLogo.tex[0].y = 1.0f - (10.0f / 16.0f);

	m_PLogo.tex[1].x = 0.0f;
	m_PLogo.tex[1].y = 1.0f - (4.0f / 16.0f);

	m_PLogo.tex[2].x = 7.0f / 16.0f;
	m_PLogo.tex[2].y = 1.0f - (4.0f / 16.0f);

	m_PLogo.tex[3].x = 7.0f / 16.0f;
	m_PLogo.tex[3].y = 1.0f - (10.0f / 16.0f);

	//BG�p
	m_PBg.tex[0].x = 0.0f;
	m_PBg.tex[0].y = 1.0f;

	m_PBg.tex[1].x = 0.0f;
	m_PBg.tex[1].y = 0.0f;

	m_PBg.tex[2].x = 1.0f;
	m_PBg.tex[2].y = 0.0f;

	m_PBg.tex[3].x = 1.0f;
	m_PBg.tex[3].y = 1.0f;


	//PUSH START�p�{�^��
	m_PPushEnter.tex[0].x = 0.0f;
	m_PPushEnter.tex[0].y = 1.0f - (12.0f / 16.0f);

	m_PPushEnter.tex[1].x = 0.0f;
	m_PPushEnter.tex[1].y = 1.0f - (10.0f / 16.0f);

	m_PPushEnter.tex[2].x = 6.0f / 16.0f;
	m_PPushEnter.tex[2].y = 1.0f - (10.0f / 16.0f);

	m_PPushEnter.tex[3].x = 6.0f / 16.0f;
	m_PPushEnter.tex[3].y = 1.0f - (12.0f / 16.0f);

	//------------------------
	//�J���[
	//------------------------
	//�t�F�[�h�p
	m_PFade.col.r = 0.0f;
	m_PFade.col.g = 0.0f;
	m_PFade.col.b = 0.0f;
	m_PFade.col.a = 1.0f;	

	//���S�p
	m_PLogo.col.r = 1.0f;
	m_PLogo.col.g = 1.0f;
	m_PLogo.col.b = 1.0f;
	m_PLogo.col.a = 1.0f;

	//BG�p
	m_PBg.col.r = 1.0f;
	m_PBg.col.g = 1.0f;
	m_PBg.col.b = 1.0f;
	m_PBg.col.a = 1.0f;	

	//PUSH START�p�{�^��
	m_PPushEnter.col.r = 1.0f;
	m_PPushEnter.col.g = 1.0f;
	m_PPushEnter.col.b = 1.0f;
	m_PPushEnter.col.a = 1.0f;	

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::Update(void)
{
	static int nCnt = -1;
	m_nCnt ++;	//�t���[���J�E���g
	//nCnt = m_nCnt;

	switch(m_nState)
	{
	case LOGO:	//�i���S�\���ς݁j
		switch(m_nInState)
		{
		case 0:	
			//�E�F�C�g
			if((m_nCnt - nCnt) > (OP_WAIT_TIME * 0.5f)){
				m_nInState = 1;
				nCnt = -1;	//������
			}
			break;
		case 1:		//�t�F�[�h�A�E�g
			if(FadeOut(&m_PFade))
			{
				m_nInState = 2;
				nCnt = m_nCnt;		//���̃E�F�C�g���̎��Ԃ��v�Z
			}
			break;
		case 2:		//�E�F�C�g
			if((m_nCnt - nCnt) > OP_WAIT_TIME){
				m_nInState = 3;
				nCnt = -1;	//������
			}
			break;
		case 3:		//�t�F�[�h�C��
			if(FadeIn(&m_PFade))
			{
				m_nInState = 0;
				m_nState = TITLE;		//�^�C�g���o�͂�
				m_RbDraw = true;		//�`��J�n
			}
			break;
		default: break;
		}
		break;
	case TITLE:
		//---------------------------------------------
		//�@�t�F�[�h�C��
		//�A�����烊���O������Đ^�񒆂Œ�~
		//�B�g��l�܂Ŋg��(�����O��]�A�y���㉺����)
		//�C�^�C�g�����S���^�񒆂���ɂ傫���Əo�Ă���
		//---------------------------------------------
		switch(m_nInState)
		{
		case 0:		//�@�t�F�[�h�C��
			if(FadeOut(&m_PFade))
				m_nInState = 1;
			break;
		case 1:		
		
			
			//�A�����烊���O������Đ^�񒆂Œ�~
			switch(m_nRingState)
			{
			case 0:
				if(m_Ringpos.x < 3.0f)
				{
					m_Ringpos.x += OP_ADD_RING_SPEED;
				}
				else
				{
					m_pSE->PlaySE(BG_TITLE);
					m_nRingState = 1;	//���̏�Ԃ�
				}
				break;
			case 1:
				if(m_Ringpos.x > 0.0f)
				{
					m_Ringpos.x -= OP_MINUS_RING_SPEED;

					m_Ringpos.y += m_RJump;
					if(m_Ringpos.y >= 0.8f)
						m_RJump *= -1;
					if(m_Ringpos.y < 0)
						m_Ringpos.y = 0.0f;

				}else
				{
					m_nRingState = 2;	//���̏�Ԃ�
					m_Ringpos.y = 0.0f;
					m_Ringpos.x = 0.0f;
				}
				break;
			case 2:	
				//�����O�g��
				if(m_RScl < OP_RING_SCALE_MAX)
					m_RScl += OP_RING_SCALE;
				if(m_RScl > OP_RING_SCALE_MAX)
				{
					m_RScl = OP_RING_SCALE_MAX;
					m_nRingState = 4;
				}

				//�^�C�g���g��
				if(m_TScl < OP_TITLE_SCALE_MAX)
					m_TScl += OP_ADD_TILE_SCALE;
				if(m_TScl > OP_TITLE_SCALE_MAX)
					m_TScl = OP_TITLE_SCALE_MAX;
				//�^�C�g����яo��
				if(m_Titlpos.y < OP_TITLE_H_MAX)
					m_Titlpos.y += OP_ADD_H_TITLE;
				if(m_Titlpos.y > OP_TITLE_H_MAX)
				{
					m_Titlpos.y = OP_TITLE_H_MAX;
				}
				break;
			case 3:

				break;
			case 4: //�k��
				if(m_RScl > 1.0f)
					m_RScl -= OP_RING_SCALE;
				if(m_RScl < 1.0f)
				{
					m_RScl = 1.0f;
					m_nRingState = 5;
				}
			case 5:	//��ʊO�֗����
				if(m_Ringpos.x < OP_TITLE_OUT)
					m_Ringpos.x += OP_ADD_RING_SPEED;
				if(m_Ringpos.x > OP_TITLE_OUT)
				{
					m_RbDraw = false;
					m_nInState = 0;
					nCnt = m_nCnt - 1;
					m_nState = PUSH_ENTER;
				}
				break;
			default: break;
			}
		break;
		default:break;
		}
		break;
	case PUSH_ENTER:
		//�v�b�V���G���^�[�@�_��
		int n;
		n = m_nCnt - nCnt;
		switch(n)
		{
		case 1:
			m_PPushEnter.col.a = 0.0f;
			break;
		case 30:
			m_PPushEnter.col.a = 1.0f;
			break;
		case 60:
			nCnt = m_nCnt;
			break;
		default:break;
		}

		//�L�[���͑҂�
		if(m_pInput->GetBtnState(BTN_A) == TRG)
		{
			nCnt = -1;	
			m_nState = OUT_TITLE;
			m_pSE->PlaySE(BUTTON_ON);
		}
		break;
	case OUT_TITLE:
		//�^�C�g���g��
		if(m_TScl < OP_TITLE_SCALE_MAX * 4)
			m_TScl += OP_ADD_TILE_SCALE;
		if(m_TScl > OP_TITLE_SCALE_MAX * 4)
			m_TScl = OP_TITLE_SCALE_MAX * 4;
		//�t�F�[�h�A�E�g
		if(FadeIn(&m_PFade))
		{
			m_TScl = 1.0f;
			return true;
		}
		break;
	default: break;
	}

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �`��
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::Draw(void)
{
	switch(m_nState)
	{
	case LOGO:
		DrawPoli(m_PLogo, 0, VECTOR3(0.0f, 0.0f, 0.0f),VECTOR3(0.0f, 0.0f, 0.0f), m_TexID, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	case TITLE:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	case PUSH_ENTER:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		DrawPoli(m_PPushEnter, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, -2.0f, 3.0f), m_TexID, true);
		break;
	case OUT_TITLE:
		DrawModel();
		DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f),  m_TexIDB, true);
		DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f), m_TexID, true);
		break;
	default: break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �|���S���`��
//--in--------------------------------------------
//POLYGON3D�@�Q��
//��]�p
//��]��
//�ʒu
//�e�N�X�`��ID
//�r���{�[�h�t���O
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::DrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos,  int m_TexID, bool flg)
{
	GLdouble	matView[16];

	//��������
	glDisable(GL_LIGHTING);		//���C�g�I�t
	glEnable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����
	glDepthMask(GL_FALSE);		//�f�v�X�o�b�t�@�ւ̏������݋֎~

	//�J���[�w��
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//�|���S���`��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);	//�e�N�X�`���L����
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	//���W�ϊ�
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);

	if(flg)
	{
		//�r���{�[�h�ϊ�
		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
		glLoadMatrixd(&matView[0]);
	}
	//�|���S���`��
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//�㏈��
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//�u�����h����
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Z�o�b�t�@������
	glDepthMask(GL_TRUE);		//�f�v�X�o�b�t�@�ւ̏������݋���
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


//++++++++++++++++++++++++++++++++++++++++++++++++
// ���f���`��
//--in--------------------------------------------
//���b�V���f�[�^�@(�Q��)
//�ʒu
//��
//��]�p�x
//�g�嗦
//�e�N�X�`��ID
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void OP::DrawModel(void)
{
	//��������
	glEnable(GL_LIGHTING);		//���C�gON
	glDisable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����

	//�����O�̕`��
	if(m_RbDraw)
	{
		m_pShadeMng->UseShader(PHONG);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexIDM);
		glPushMatrix();
		glTranslatef(m_Ringpos.x, m_Ringpos.y, m_Ringpos.z);
		glRotatef((GLfloat)m_RAng, 0.0f, 1.0f, 0.0f);
		glScalef(m_RScl, m_RScl, m_RScl);
		m_pShadeMng->SetTexUnit(PHONG ,0);
		DrawMesh(&m_MeshR);
		glPopMatrix();
		m_pShadeMng->UnUseShader();
	}

	//�^�C�g���̕`��
	m_pShadeMng->UseShader(PHONG);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDT);
	glPushMatrix();
	glTranslatef(m_Titlpos.x, m_Titlpos.y, m_Titlpos.z);
	glRotatef((GLfloat)m_TAng, 1.0f, 0.0f, 0.0f);
	glScalef(m_TScl, m_TScl, m_TScl);
	m_pShadeMng->SetTexUnit(PHONG, 0);
	DrawMesh(&m_MeshT);
	glPopMatrix();
	m_pShadeMng->UnUseShader();


	//�㏈��
	glDisable(GL_LIGHTING);		//���C�g�I�t
	glEnable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �t�F�[�h�C���@�������L�F
//--in--------------------------------------------
//
//--out-------------------------------------------
// �I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::FadeIn(POLYGON3D *pol)
{
	static int nCnt = -1;

	//����
	if(nCnt < 0){
		nCnt = m_nCnt;	//���݂̃t���[���J�E���g����ۑ�
		pol->col.a = 0.0f;
	}

	//���l���グ��
	if((m_nCnt - nCnt) < OP_FADE_TIME)
		pol->col.a += (1.0f / OP_FADE_TIME);
	else{
		pol->col.a = 1.0f;
		nCnt = -1;
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �t�F�[�h�A�E�g�@�L�F������
//--in--------------------------------------------
//
//--out-------------------------------------------
// �I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool OP::FadeOut(POLYGON3D *pol)
{
	static int nCnt = -1;

	//����
	if(nCnt < 0){
		nCnt = m_nCnt;	//���݂̃t���[���J�E���g����ۑ�
		pol->col.a = 1.0f;
	}

	//���l���グ��
	if((m_nCnt - nCnt) < OP_FADE_TIME && pol->col.a > 0.05f)
	{
		pol->col.a -= (1.0f / OP_FADE_TIME);
	}
	else{
		pol->col.a = 0.0f;
		nCnt = -1;
		return true;
	}
	return false;
}

//################################################
// End of File
//################################################
