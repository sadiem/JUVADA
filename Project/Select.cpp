//################################################
// <Select.cpp>
// �Z���N�g���j���[���쐬
//------------------------------------------------
// 2013/01/18 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Select.h"
#include "TexMng.h"
#include "Random.h"

//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
//�t�F�[�h
#define SELECT_FADE_POS_X (-10)			//�t�F�[�h�|�������ʒu
#define SELECT_FADE_POS_Y (-10)
#define SELECT_FADE_H (20)				//�t�F�[�h�|���c��
#define SELECT_FADE_W (20)				//�@�@�@�@�@�@�@����
//�t�F�[�h����
#define SELECT_FADE_TIME	(120)		//�t�F�[�h�^�C��
//BG
#define SELECT_BG_H (50)				//�t�F�[�h�|���c��
#define SELECT_BG_W (50)				//�@�@�@�@�@�@�@����
#define SELECT_BG_POS_X (-(SELECT_BG_H / 2.0f))				//�t�F�[�h�|�������ʒu
#define SELECT_BG_POS_Y (SELECT_BG_POS_X)
//�X�e���V��
#define SELECT_STENCIL_H (27.0f)							//�X�e���V���|���c��
#define SELECT_STENCIL_W (27.0f)							//�@�@�@�@�@�@�@����
#define SELECT_STENCIL_POS_X (-(SELECT_STENCIL_H / 2.0f))	//�X�e���V���|�������ʒu
#define SELECT_STENCIL_POS_Y (SELECT_STENCIL_POS_X)
#define SELECT_STENCIL_MOVE  (VECTOR3(11.5f, -5.5f, 0.0f))	//�X�e���V���ړ��l
#define SELECT_STENCIL_ANGLE	((GLfloat)20.0f)	//�X�e���V����]�p
#define SELECT_STENCIL_MOVE_VEC	(VECTOR3(cosf(SELECT_STENCIL_ANGLE), sinf(SELECT_STENCIL_ANGLE), 0.0f))	//�X�e���V���ړ��x�N�g��
//�I���I��BG
#define SELECT_END_BG_H (4)				//�I���I��|���c��
#define SELECT_END_BG_W (8)				//�@�@�@�@�@�@�@����
#define SELECT_END_BG_POS_X (-(SELECT_END_BG_W / 2.0f))			//�I���I��|�������ʒu
#define SELECT_END_BG_POS_Y (-(SELECT_END_BG_H / 2.0f))
#define SELECT_END_BG_ADD_SCALE	(0.08f)							//�I���I���g�嗦
//�I���I���{�^��
#define SELECT_BUTTOM_END_H (1.0f)								//�I���I���{�^���|���c��
#define SELECT_BUTTOM_END_W (2.0f)								//�@�@�@�@�@�@�@����
#define SELECT_BUTTOM_END_POS_X (-(SELECT_BUTTOM_END_W / 2.0f))	//�I���I���{�^���|�������ʒu
#define SELECT_BUTTOM_END_POS_Y (-(SELECT_BUTTOM_END_H / 2.0f))
#define SELECT_BUTTOM_END_FIRST_SCALE	(0.01f)					//�I���I���{�^���̏����g��l
//�{�^��
#define SELECT_BUTTOM_H (1.5f)							//�{�^���|���c��
#define SELECT_BUTTOM_W (6.0f)							//�@�@�@�@�@�@�@����
#define SELECT_BUTTOM_POS_X (-(SELECT_BUTTOM_H / 2.0f))	//�{�^���|�������ʒu
#define SELECT_BUTTOM_POS_Y (SELECT_BUTTOM_POS_X - 0.5f)
#define SELECT_BUTTOM_SPACE_Y	(-SELECT_BUTTOM_H * 0.8f)		//�{�^���Ԋu
#define SELECT_BUTTOM_SPACE_X	(0.5f)							//�{�^���Ԋu
#define SELECT_BUTTOM_POP		(1.0f)					//�{�^���̔�яo��
#define SELECT_BUTTOM_ADD_POP	(0.1f)					//�{�^���̔�яo���̑�����
#define SELECT_BUTTOM_MINUS_POP	(0.1f)					//�{�^���̔�яo���̌��Z��
#define SELECT_BUTTOM_FIRST_POS_X	(-4.5f)				//�{�^�������ʒu
#define SELECT_BUTTOM_FIRST_POS_Y	(0.0f)				//�{�^�������ʒu
#define SELECT_BUTTOM_ADD_MOVE_TEX	(0.02f)				//�{�^���e�N�X�`���ړ�

//�^�C�g��
#define SELECT_TITLE_SCALE_MAX			(3.0f)						//�g�嗦�ő�l
#define SELECT_TITLE_FIRST_POS			(VECTOR3(0.0f, 4.5f, 14.0f))
#define SELECT_TITLE_POS				(VECTOR3(2.5f, 3.0f, 6.0f))	//�ڕW�n�_
#define SELECT_TITLE_COMPLETION_TIME	(120.0f)					//�ړ��ۊǎ���
enum {
	SLCT_APPEAR,		//�Z���N�g��ʂւ̓���
	SLCT_CRACK,			//��ʊ����
	SLCT_MENU,			//���j���[���ł̑I��
	SLCT_SELECT_ITEM,	//�I�񂾍��ڕʂ̏���
	SLCT_END_SELECT,	//�I���I��
	SLCT_END,			//�G���h
	SLCT_WINDOW_CLOSE	//�E�B���h�E�����

};
enum{
	SL_KEY_START,	//�Q�[���X�^�[�g
	SL_KEY_HOWTO,	//�v���C���@
	SL_KEY_CONFFIG,	//�L�[�R���t�B�O
	SL_KEY_END,		//END

	SL_KEY_MAX,		//�L�[�̑���
};
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
SELECT::SELECT(){}
SELECT::~SELECT(){}
//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Init(void)
{
	m_pShadeMng = SHADER_MNG::Instance();
	m_pInput = INPUT_MNG::getInstance();
	m_TexID = g_TexMng.GetTexture("TEXTURE\\SELECT\\select.png", "SELECT");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\SELECT\\title.png", "SELECT");
	m_TexIDD = g_TexMng.GetTexture("TEXTURE\\SELECT\\deko.png", "SELECT");
	m_TexIDF = g_TexMng.GetTexture("TEXTURE\\SELECT\\fade.png", "SELECT");
	m_TexIDE = g_TexMng.GetTexture("TEXTURE\\SELECT\\endselect.png", "SELECT");

	g_MeshMng.GetMesh(&m_MeshT, "MODEL\\OP\\title.x", "SELECT");
	g_MeshMng.GetMesh(&m_MeshDeco, "MODEL\\OP\\deco.x", "SELECT");
	m_pCmr = CAMERA::Instance();	//�C���X�^���X�̎擾
	m_pSE = SOUND::Instance();
	m_pSE->PlayBG(BG_SELECT);
	Reset();
}

void SELECT::Release(void)
{
	g_TexMng.ReleaseCat("SELECT");
	g_MeshMng.ReleaseCat("SELECT");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
// �Ȃ�
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Reset(void)
{
	static int nKeyEnd = 0;

	m_nState = SLCT_APPEAR;
	m_nInState = 0;
	m_nCnt = 0;
	m_nSelect = SL_KEY_START;
	bflg = false;
	bflgKey1 = false;
	bflgKey2 = false;
	nCnt = 0;


	//�^�C�g��
	m_Titlpos = SELECT_TITLE_FIRST_POS;
	m_TAngY = -10.0f;
	m_TAngZ = -5.0f;
	m_TScl = SELECT_TITLE_SCALE_MAX;

	//�I���I�����
	m_EScl = SELECT_BUTTOM_END_FIRST_SCALE;

	//���_�Z�b�g
	SetPoli();

	//�{�^�������ʒu
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++){
		m_vBtmpos[i].x = i * SELECT_BUTTOM_SPACE_X + SELECT_BUTTOM_FIRST_POS_X;
		m_vBtmpos[i].y = i * SELECT_BUTTOM_SPACE_Y + SELECT_BUTTOM_FIRST_POS_Y;
		m_vBtmpos[i].z = 5.0f;
		//�R�s�[
		m_vBtmposCopy[i].x = i * SELECT_BUTTOM_SPACE_X + SELECT_BUTTOM_FIRST_POS_X;
		m_vBtmposCopy[i].y = i * SELECT_BUTTOM_SPACE_Y + SELECT_BUTTOM_FIRST_POS_Y;
		m_vBtmposCopy[i].z = 5.0f;

		//�摜�ϊ�
		m_bButtunChange[i] = false;
	}

	//�f�R���[�V���������l�Z�b�g
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++){
		m_Ditlpos[i].x = 2.0f * i;			//�f�R���[�V�����ʒu
		m_Ditlpos[i].y = 1.0f * i;	//�f�R���[�V�����ʒu
		m_Ditlpos[i].z = 1.0f;						//�f�R���[�V�����ʒu
		m_DAng[i] = 72.0f * (i + 1);				//�f�R���[�V������] �X��
		m_DAngM[i] = 0;								//�f�R���[�V������] ���g�̉�]
		m_DScl[i] = 0.3f + (i + 1) * 0.1f;			//�f�R���[�V�����g��
	}

	//�X�e���V���̈ړ�����
	m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::SetPoli(void)
{
	//------------------------
	//���_�̃Z�b�g
	//------------------------
	//�t�F�[�h�p
	m_PFade.ver[0].x = SELECT_FADE_POS_X;
	m_PFade.ver[0].y = SELECT_FADE_POS_Y + SELECT_FADE_H;
	m_PFade.ver[0].z = 5.0f;

	m_PFade.ver[1].x = SELECT_FADE_POS_X;
	m_PFade.ver[1].y = SELECT_FADE_POS_Y;
	m_PFade.ver[1].z = 5.0f;

	m_PFade.ver[2].x = SELECT_FADE_POS_X + SELECT_FADE_W;
	m_PFade.ver[2].y = SELECT_FADE_POS_Y ;
	m_PFade.ver[2].z = 5.0f;

	m_PFade.ver[3].x = SELECT_FADE_POS_X + SELECT_FADE_W;
	m_PFade.ver[3].y = SELECT_FADE_POS_Y + SELECT_FADE_H;
	m_PFade.ver[3].z = 5.0f;

	//BG�p
	m_PBg.ver[0].x = SELECT_BG_POS_X;
	m_PBg.ver[0].y = SELECT_BG_POS_Y + SELECT_BG_H;
	m_PBg.ver[0].z = -10.0f;

	m_PBg.ver[1].x = SELECT_BG_POS_X;
	m_PBg.ver[1].y = SELECT_BG_POS_Y;
	m_PBg.ver[1].z = -10.0f;

	m_PBg.ver[2].x = SELECT_BG_POS_X + SELECT_BG_W;
	m_PBg.ver[2].y = SELECT_BG_POS_Y;
	m_PBg.ver[2].z = -10.0f;

	m_PBg.ver[3].x = SELECT_BG_POS_X + SELECT_BG_W;
	m_PBg.ver[3].y = SELECT_BG_POS_Y + SELECT_BG_H;
	m_PBg.ver[3].z = -10.0f;

	//�X�e���V���p
	m_PStencil.ver[0].x = SELECT_STENCIL_POS_X;
	m_PStencil.ver[0].y = SELECT_STENCIL_POS_Y + SELECT_STENCIL_H;
	m_PStencil.ver[0].z = 5.0f;

	m_PStencil.ver[1].x = SELECT_STENCIL_POS_X;
	m_PStencil.ver[1].y = SELECT_STENCIL_POS_Y;
	m_PStencil.ver[1].z = 5.0f;

	m_PStencil.ver[2].x = SELECT_STENCIL_POS_X + SELECT_STENCIL_W;
	m_PStencil.ver[2].y = SELECT_STENCIL_POS_Y;
	m_PStencil.ver[2].z = 5.0f;

	m_PStencil.ver[3].x = SELECT_STENCIL_POS_X + SELECT_STENCIL_W;
	m_PStencil.ver[3].y = SELECT_STENCIL_POS_Y + SELECT_STENCIL_H;
	m_PStencil.ver[3].z = 5.0f;

	//�I���I�����BG�p
	m_PEndselect.ver[0].x = SELECT_END_BG_POS_X;
	m_PEndselect.ver[0].y = SELECT_END_BG_POS_Y + SELECT_END_BG_H;
	m_PEndselect.ver[0].z = 7.0f;

	m_PEndselect.ver[1].x = SELECT_END_BG_POS_X;
	m_PEndselect.ver[1].y = SELECT_END_BG_POS_Y;
	m_PEndselect.ver[1].z = 7.0f;

	m_PEndselect.ver[2].x = SELECT_END_BG_POS_X + SELECT_END_BG_W;
	m_PEndselect.ver[2].y = SELECT_END_BG_POS_Y;
	m_PEndselect.ver[2].z = 7.0f;

	m_PEndselect.ver[3].x = SELECT_END_BG_POS_X + SELECT_END_BG_W;
	m_PEndselect.ver[3].y = SELECT_END_BG_POS_Y + SELECT_END_BG_H;
	m_PEndselect.ver[3].z = 7.0f;


	//�{�^��
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].ver[0].x = SELECT_BUTTOM_POS_X;
		m_PButtom[i].ver[0].y = SELECT_BUTTOM_POS_Y + SELECT_BUTTOM_H;
		m_PButtom[i].ver[0].z = -1.0f;

		m_PButtom[i].ver[1].x = SELECT_BUTTOM_POS_X;
		m_PButtom[i].ver[1].y = SELECT_BUTTOM_POS_Y;
		m_PButtom[i].ver[1].z = -1.0f;

		m_PButtom[i].ver[2].x = SELECT_BUTTOM_POS_X + SELECT_BUTTOM_W;
		m_PButtom[i].ver[2].y = SELECT_BUTTOM_POS_Y ;
		m_PButtom[i].ver[2].z = -1.0f;

		m_PButtom[i].ver[3].x = SELECT_BUTTOM_POS_X + SELECT_BUTTOM_W;
		m_PButtom[i].ver[3].y = SELECT_BUTTOM_POS_Y + SELECT_BUTTOM_H;
		m_PButtom[i].ver[3].z = -1.0f;
	}
	//�I���I���{�^��
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].ver[0].x = SELECT_BUTTOM_END_POS_X;
		m_PButtumEnd[i].ver[0].y = SELECT_BUTTOM_END_POS_Y + SELECT_BUTTOM_END_H;
		m_PButtumEnd[i].ver[0].z = 7.1f;

		m_PButtumEnd[i].ver[1].x = SELECT_BUTTOM_END_POS_X;
		m_PButtumEnd[i].ver[1].y = SELECT_BUTTOM_END_POS_Y;
		m_PButtumEnd[i].ver[1].z = 7.1f;

		m_PButtumEnd[i].ver[2].x = SELECT_BUTTOM_END_POS_X + SELECT_BUTTOM_END_W;
		m_PButtumEnd[i].ver[2].y = SELECT_BUTTOM_END_POS_Y ;
		m_PButtumEnd[i].ver[2].z = 7.1f;

		m_PButtumEnd[i].ver[3].x = SELECT_BUTTOM_END_POS_X + SELECT_BUTTOM_END_W;
		m_PButtumEnd[i].ver[3].y = SELECT_BUTTOM_END_POS_Y + SELECT_BUTTOM_END_H;
		m_PButtumEnd[i].ver[3].z = 7.1f;
	}

	//------------------------
	//�e�N�X�`���̃Z�b�g
	//------------------------
	//�t�F�[�h�p
	m_PFade.tex[0].x = 0.0f;
	m_PFade.tex[0].y = 1.0f;

	m_PFade.tex[1].x = 0.0f;
	m_PFade.tex[1].y = 0.0f;

	m_PFade.tex[2].x = 1.0f;
	m_PFade.tex[2].y = 0.0f;

	m_PFade.tex[3].x = 1.0f;
	m_PFade.tex[3].y = 1.0f;

	//BG�p
	m_PBg.tex[0].x = 0.5f;
	m_PBg.tex[0].y = 1.0f - (16.0f / 16.0f);

	m_PBg.tex[1].x = 0.5f;
	m_PBg.tex[1].y = 1.0f - (8.0f / 16.0f);

	m_PBg.tex[2].x = 1.0f;
	m_PBg.tex[2].y = 1.0f - (8.0f / 16.0f);

	m_PBg.tex[3].x = 1.0f;
	m_PBg.tex[3].y = 1.0f - (16.0f / 16.0f);

	//�X�e���V���p
	m_PStencil.tex[0].x = 0.0f;
	m_PStencil.tex[0].y = 1.0f;

	m_PStencil.tex[1].x = 0.0f;
	m_PStencil.tex[1].y = 0.0f;

	m_PStencil.tex[2].x = 1.0f;
	m_PStencil.tex[2].y = 0.0f;

	m_PStencil.tex[3].x = 1.0f;
	m_PStencil.tex[3].y = 1.0f;

	//�{�^��
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].tex[0].x = 0.5f;
		m_PButtom[i].tex[0].y = 1.0f - ((i * 2.0f + 2.0f) / 16.0f);

		m_PButtom[i].tex[1].x = 0.5f;
		m_PButtom[i].tex[1].y = 1.0f - (i * 2.0f / 16.0f);

		m_PButtom[i].tex[2].x = 1.0f;
		m_PButtom[i].tex[2].y = 1.0f - (i * 2.0f / 16.0f);

		m_PButtom[i].tex[3].x = 1.0f;
		m_PButtom[i].tex[3].y = 1.0f- ((i * 2.0f + 2.0f) / 16.0f);	

		m_CopyTexButtom[i][0].x = m_PButtom[i].tex[0].x;
		m_CopyTexButtom[i][0].y = m_PButtom[i].tex[0].y;
		m_CopyTexButtom[i][1].x = m_PButtom[i].tex[1].x;
		m_CopyTexButtom[i][1].y = m_PButtom[i].tex[1].y;
		m_CopyTexButtom[i][2].x = m_PButtom[i].tex[2].x;
		m_CopyTexButtom[i][2].y = m_PButtom[i].tex[2].y;
		m_CopyTexButtom[i][3].x = m_PButtom[i].tex[3].x;
		m_CopyTexButtom[i][3].y = m_PButtom[i].tex[3].y;
	}

	//�I���I��BG�p
	m_PEndselect.tex[0].x = 0.0f;
	m_PEndselect.tex[0].y = 1.0f - (16.0f / 16.0f);
							
	m_PEndselect.tex[1].x = 0.0f;
	m_PEndselect.tex[1].y = 1.0f - (8.0f / 16.0f);
							
	m_PEndselect.tex[2].x = 1.0f;
	m_PEndselect.tex[2].y = 1.0f - (8.0f / 16.0f);
							
	m_PEndselect.tex[3].x = 1.0f;
	m_PEndselect.tex[3].y = 1.0f - (16.0f / 16.0f);

	//�I���I���{�^��
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].tex[0].x = 0.0f;
		m_PButtumEnd[i].tex[0].y = 1.0f - ((i * 2.0f + 6.0f) / 16.0f);

		m_PButtumEnd[i].tex[1].x = 0.0f;
		m_PButtumEnd[i].tex[1].y = 1.0f - ((i * 2.0f + 4.0f) / 16.0f);

		m_PButtumEnd[i].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[i].tex[2].y = 1.0f - ((i * 2.0f + 4.0f) / 16.0f);

		m_PButtumEnd[i].tex[3].x = 4.0f / 16.0f;
		m_PButtumEnd[i].tex[3].y = 1.0f - ((i * 2.0f + 6.0f) / 16.0f);	
	}
	//------------------------
	//�J���[
	//------------------------
	//�t�F�[�h�p
	m_PFade.col.r = 1.0f;
	m_PFade.col.g = 0.0f;
	m_PFade.col.b = 0.0f;
	m_PFade.col.a = 1.0f;	

	//BG�p
	m_PBg.col.r = 1.0f;
	m_PBg.col.g = 1.0f;
	m_PBg.col.b = 1.0f;
	m_PBg.col.a = 1.0f;	
	
	//�X�e���V���p
	m_PStencil.col.r = 1.0f;
	m_PStencil.col.g = 1.0f;
	m_PStencil.col.b = 1.0f;
	m_PStencil.col.a = 1.0f;	
	
	//�{�^���p
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].col.r = 1.0f;
		m_PButtom[i].col.g = 1.0f;
		m_PButtom[i].col.b = 1.0f;
		m_PButtom[i].col.a = 1.0f;	
	}

	//�I���I��pBG
	m_PEndselect.col.r = 1.0f;
	m_PEndselect.col.g = 1.0f;
	m_PEndselect.col.b = 1.0f;
	m_PEndselect.col.a = 1.0f;	

	//�I���I��p�{�^��//�{�^���p
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].col.r = 1.0f;
		m_PButtumEnd[i].col.g = 1.0f;
		m_PButtumEnd[i].col.b = 1.0f;
		m_PButtumEnd[i].col.a = 1.0f;	
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�{�^���e�N�X�`���̈ړ��@�o��
//�Z���N�g�Ɉڂ�����
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�e�N�X�`���ړ��I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::TexMoveAppear(void)
{
	//�{�^��
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{	
		m_PButtom[i].tex[0].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[1].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[2].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[3].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
	}
	//�␳
	if(m_PButtom[0].tex[3].x < 0.5f)
	{	//�␳�l���
		for(int k = 0; k < SLECT_BUTTOM_NUM; k ++){
			m_PButtom[k].tex[0].x = 0.0f;
			m_PButtom[k].tex[1].x = 0.0;
			m_PButtom[k].tex[2].x = 0.5f;
			m_PButtom[k].tex[3].x = 0.5f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�{�^���e�N�X�`���̈ړ��@�d����
//�Z���N�g��ʂ���ޔ������ʂɈڂ�����
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�e�N�X�`���ړ��I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::TexMovePutaway(void)
{
	//�{�^��
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{	
		m_PButtom[i].tex[0].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[1].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[2].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[3].x += SELECT_BUTTOM_ADD_MOVE_TEX;
	}
	//�␳
	if(m_PButtom[0].tex[3].x < 1.0f)
	{	//�␳�l���
		for(int k = 0; k < SLECT_BUTTOM_NUM; k ++){
			m_PButtom[k].tex[0].x = 0.5f;
			m_PButtom[k].tex[1].x = 0.5f;
			m_PButtom[k].tex[2].x = 1.0f;
			m_PButtom[k].tex[3].x = 1.0f;
		}
		return true;
	}
	return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�{�^���e�N�X�`���̈ړ��@�d����
//�Z���N�g��ʂ���ޔ������ʂɈڂ�����
//--in--------------------------------------------
//�E�����Ɉړ��@�E=>1 ��=>-1
//--out-------------------------------------------
//�e�N�X�`���ړ��I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::TexMovePutawayEnd(int nMove)
{
	switch(nMove)
	{
	case 0:
		//YES
		m_PButtumEnd[0].tex[0].x = 0.0f;
		m_PButtumEnd[0].tex[1].x = 0.0f;
		m_PButtumEnd[0].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[3].x = 4.0f / 16.0f;

		m_PButtumEnd[1].tex[0].x = 0.0f;
		m_PButtumEnd[1].tex[1].x = 0.0f;
		m_PButtumEnd[1].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[3].x = 4.0f / 16.0f;
		break;
	case 1:
		//NO
		m_PButtumEnd[0].tex[0].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[1].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[2].x = 8.0f / 16.0f;
		m_PButtumEnd[0].tex[3].x = 8.0f / 16.0f;

		m_PButtumEnd[1].tex[0].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[1].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[2].x = 8.0f / 16.0f;
		m_PButtumEnd[1].tex[3].x = 8.0f / 16.0f;

		break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�I�𒆃{�^���̃e�N�X�`���ύX
//--in--------------------------------------------
//�{�^���ԍ�
//�{�^�����I�����ꂽ���ǂ����̃t���O	1 , -1
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::TexChange(int nID, int flg)
{
	if(flg){
	m_PButtom[nID].tex[0].y = m_CopyTexButtom[nID][0].y - 0.5f;
	m_PButtom[nID].tex[1].y = m_CopyTexButtom[nID][1].y - 0.5f;
	m_PButtom[nID].tex[2].y = m_CopyTexButtom[nID][2].y - 0.5f;
	m_PButtom[nID].tex[3].y = m_CopyTexButtom[nID][3].y - 0.5f;
	}else{
	m_PButtom[nID].tex[0].y = m_CopyTexButtom[nID][0].y;
	m_PButtom[nID].tex[1].y = m_CopyTexButtom[nID][1].y;
	m_PButtom[nID].tex[2].y = m_CopyTexButtom[nID][2].y;
	m_PButtom[nID].tex[3].y = m_CopyTexButtom[nID][3].y;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::Update(void)
{
	m_nCnt ++;	//�t���[���J�E���g

	switch(m_nState)
	{
	case SLCT_APPEAR:
		if(!bflg){
		if(FadeOut(&m_PFade))
			bflg = 1;
		}
		//�^�C�g���o��
		if(((m_nCnt - nCnt) < SELECT_TITLE_COMPLETION_TIME)){
			float f = (m_nCnt - nCnt) / SELECT_TITLE_COMPLETION_TIME;
			VECTOR3 v;
			v = SELECT_TITLE_FIRST_POS - SELECT_TITLE_POS;
			m_Titlpos = SELECT_TITLE_FIRST_POS - (SELECT_TITLE_FIRST_POS - SELECT_TITLE_POS) * float((m_nCnt - nCnt) / SELECT_TITLE_COMPLETION_TIME);
			m_TScl -= 0.1f;
			if(m_TScl < 0.6f)
				m_TScl = 0.6f;
		}
		else if(((m_nCnt - nCnt) > SELECT_TITLE_COMPLETION_TIME))
		{
			m_nState = SLCT_CRACK;
			bflg = 0;
			nCnt =  0;
		}
		break;
		//��ʂ������	���Ƃ�
	case SLCT_CRACK:	
		//��ʊ����
		if(m_vSSlide.x < 3.0f){
			m_vSSlide.y -= 0.000001f;
			m_vSSlide.x += 0.1f;
		}else
		{//�{�^���o��
			if(TexMoveAppear())
				m_nState = SLCT_MENU;
		}
		break;
	case SLCT_MENU:
		//���j���[��I��
		if(m_pInput->GetBtnState(BTN_UP) == TRG)
			m_nSelect --;	
		if(m_pInput->GetBtnState(BTN_DOWN) == TRG)
			m_nSelect ++;
		if(m_nSelect > SL_KEY_MAX - 1)	//�␳
			m_nSelect = (SL_KEY_MAX - 1);
		if(m_nSelect < 0)
			m_nSelect = 0;

		//�L�[�̓���(������)
		switch(m_nSelect)
		{
		case SL_KEY_START:		//�Q�[���X�^�[�g
			m_vBtmpos[0].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[0].x > m_vBtmposCopy[0].x + SELECT_BUTTOM_POP){
				m_vBtmpos[0].x = m_vBtmposCopy[0].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[0]){
					TexChange(0, 1);
					m_bButtunChange[0] = true;
				}
			}
			break;
		case SL_KEY_HOWTO:		//�v���C���@
			m_vBtmpos[1].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[1].x > m_vBtmposCopy[1].x + SELECT_BUTTOM_POP){
				m_vBtmpos[1].x = m_vBtmposCopy[1].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[1]){
					TexChange(1, 1);
					m_bButtunChange[1] = true;
				}
			}
			break;
		case SL_KEY_CONFFIG:	//�L�[�R���t�B�O
			m_vBtmpos[2].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[2].x > m_vBtmposCopy[2].x + SELECT_BUTTOM_POP){
				m_vBtmpos[2].x = m_vBtmposCopy[2].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[2]){
					TexChange(2, 1);
					m_bButtunChange[2] = true;
				}
			}
			break;
		case SL_KEY_END:		//�L�[END
			m_vBtmpos[3].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[3].x > m_vBtmposCopy[3].x + SELECT_BUTTOM_POP){
				m_vBtmpos[3].x = m_vBtmposCopy[3].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[3]){
					TexChange(3, 1);
					m_bButtunChange[3] = true;
				}
			}
			break;
		default: break;
		}
		for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
		{	//�ʒu�����ɖ߂�
			if(m_nSelect == i)
				continue;
			if(m_vBtmpos[i].x > m_vBtmposCopy[i].x)
				m_vBtmpos[i].x -= SELECT_BUTTOM_MINUS_POP;
			if(m_vBtmpos[i].x < m_vBtmposCopy[i].x)
				m_vBtmpos[i].x = m_vBtmposCopy[i].x;
			if(m_bButtunChange[i])
				m_bButtunChange[i] = false;
			else
				TexChange(i, 0);
		}

		//����L�[
		if(m_pInput->GetBtnState(BTN_A) == TRG)
		{
			m_nState = SLCT_SELECT_ITEM;
		}
		
		//m_nState = SLCT_END;
		break;
	case SLCT_SELECT_ITEM:
		//�I�񂾂��̂ɂ�铮��
		switch(m_nSelect)
		{
		case SL_KEY_START:		//�Q�[���X�^�[�g
			//�{�^���e�N�X�`�������̈ʒu��
			for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
				TexChange(i, 0);
			bflg = false;
			m_nState = SLCT_END;
			break;
		case SL_KEY_HOWTO:		//�v���C���@
			break;
		case SL_KEY_CONFFIG:	//�L�[�R���t�B�O
			break;
		case SL_KEY_END:		//�L�[END
			m_nState = SLCT_END_SELECT;
			break;
		default: break;
		}
		break;
		

		//���j���[�ɖ߂�
		if(m_pInput->GetBtnState(BTN_B) == TRG )	//�cESC
			m_nState = SLCT_MENU;

	case SLCT_END_SELECT:	//�I�������̗L��
		
		switch(m_nInState)
		{
		case 0:
			//�I����ʊg��
			if(m_EScl < 1.0f){
				m_EScl += SELECT_END_BG_ADD_SCALE;
			}
			if(m_EScl > 1.0f){
				m_EScl = 1.0f;	
				m_nInState = 1;
				bflg = false;
			}
		case 1:	//�L�[������
			//�{�^���I��
			if(m_pInput->GetBtnState(BTN_LEFT) == TRG )
			{
				m_nKeyEnd = 0;
				TexMovePutawayEnd(0);
			}

			if(m_pInput->GetBtnState(BTN_RIGHT) == TRG)
			{
				m_nKeyEnd = 1;
				TexMovePutawayEnd(1);
			}
			//����L�[�Ŋm��
			if(m_pInput->GetBtnState(BTN_A) == TRG)
			{
				switch(m_nKeyEnd)
				{
				case 0:
					//�Q�[���𑱂���
					break;
				case 1:
					m_nState = SLCT_WINDOW_CLOSE;
					m_nKeyEnd = 0;
					break;
				default: break;
				}
				m_nInState = 2;
				m_nKeyEnd = 0;
				bflg = false;
			}
			break;
		case 2:
			//�I����ʏk��
			if(m_EScl > SELECT_BUTTOM_END_FIRST_SCALE){
				m_EScl -= SELECT_END_BG_ADD_SCALE;
			}
			if(m_EScl < SELECT_BUTTOM_END_FIRST_SCALE){
				m_EScl = SELECT_BUTTOM_END_FIRST_SCALE;	
				m_nInState = 0;
				m_nState = SLCT_MENU;
			}
			break;
		}
		break;
	case SLCT_END:
		//�{�^�������܂�
		if(!bflg){
			if(TexMovePutaway())
				bflg = true;
		}
		else
		{
			//�^�C�g�����E�֑ޔ�
			m_Titlpos.x += 0.1f;
			//�X�e���V����߂�
			if((m_vSSlide.x > 0.0f) || !FadeIn(&m_PFade)){
				m_vSSlide.y += 0.000002f;
				m_vSSlide.x -= 0.2f;
				//�␳
				if(m_vSSlide.x < 0.0f)
					m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
			}else
			{
				m_pSE->StopBG(BG_SELECT);
				return true;		//���̃V�[����
			}
		}
		break;
	case SLCT_WINDOW_CLOSE:
		return true;
		break;
	default: break;
	}

	for(int i = 0; i < SLECT_DECO_NUM; i++)
		m_DAngM[i] += 1;
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �`��
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Draw(void)
{
	DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f), 1,  m_TexID, true);
	DrawModel();
	DrawStencil();
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
		DrawPoli(m_PButtom[i], 0, VECTOR3(0.0f, 0.0f, 0.0f), m_vBtmpos[i], 1, m_TexID, true);
	DrawTitle();
	
	switch(m_nState)
	{
	case SLCT_APPEAR:
	case SLCT_CRACK:	
	case SLCT_MENU:	
		break;
	case SLCT_END_SELECT:		
		DrawPoli(m_PEndselect, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 0.0f), m_EScl, m_TexIDE, true);
		DrawPoli(m_PButtumEnd[0], 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(-(SELECT_BUTTOM_END_W + 0.3f) / 2.0f, -0.5f, 0.0f), m_EScl,  m_TexIDE, true);
		DrawPoli(m_PButtumEnd[1], 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3((SELECT_BUTTOM_END_W + 0.3f) / 2.0f, -0.5f, 0.0f), m_EScl,  m_TexIDE, true);
		break;
	case SLCT_END:
		break;
	default: break;
	}
	DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f),1,  m_TexIDF, true);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// �|���S���`��
//--in--------------------------------------------
//POLYGON3D�@�Q��
//��]�p
//��]��
//�ʒu
//�g�嗦
//�e�N�X�`��ID
//�r���{�[�h�t���O
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos, float scl,  int m_TexID, bool flg)
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
	if(m_TexID > 0)
	{
		glEnable(GL_TEXTURE_2D);	//�e�N�X�`���L����
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}
	//���W�ϊ�
	glPushMatrix();

	if(flg)
	{
		//�r���{�[�h�ϊ�
		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
		glLoadMatrixd(&matView[0]);
	}
	//�|���S���`��
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);
	glScalef((GLfloat)scl, (GLfloat)scl, (GLfloat)scl);
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
void SELECT::DrawStencil(void)
{
	//������
	glLoadIdentity();
	gluLookAt(m_pCmr->ViewPos.x, m_pCmr->ViewPos.y, m_pCmr->ViewPos.z, m_pCmr->ViewCent.x, m_pCmr->ViewCent.y, m_pCmr->ViewCent.z, 0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE, GL_FALSE,GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);

	//�\�ʂ����`��
	glStencilFunc(GL_ALWAYS, 0, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glEnable(GL_CULL_FACE);
	DrawPoli(m_PStencil, SELECT_STENCIL_ANGLE, VECTOR3(0.0f, 0.0f, 1.0f), SELECT_STENCIL_MOVE, 1, -1, true);

	//���ʂ�`��
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	DrawPoli(m_PStencil, SELECT_STENCIL_ANGLE, VECTOR3(0.0f, 0.0f, 1.0f), SELECT_STENCIL_MOVE + m_vSSlide, 1, -1, true);

	//�ݒ��߂�
	glFrontFace(GL_CCW);
	glColorMask(1, 1, 1, 1);
	glDepthMask(1);

	//-----------------------------------------------
	//�e��t����
	//-----------------------------------------------
	glStencilFunc(GL_NOTEQUAL, 0, ~0);
	glDisable(GL_LIGHTING);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);						//�F
	glDisable(GL_DEPTH_TEST);								//�f�v�X�e�X�g������
	glDisable(GL_CULL_FACE);								//���ʂ͕`���Ȃ�

	//�e�̃X�e���V��������`��
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(100.0f, 100.0f, 15.0f); 
	glVertex3f(100.0f, -100.0f, 15.0f); 
	glVertex3f(-100.0f, -100.0f, 15.0f); 
	glVertex3f(-100.0f,  100.0f, 15.0f); 
	glEnd();
	glPopMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);						//�F
	//�����ݒ�����ɖ߂�
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ���f���`��
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawModel(void)
{
	//��������
	glEnable(GL_LIGHTING);		//���C�gON
	glDisable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����

	//�f�R���[�V�����`��
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);	//���Z����
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDD);
	for(int i = 0; i < SLECT_DECO_NUM; i ++)
	{
	glPushMatrix();
	glTranslatef(m_Ditlpos[i].x, m_Ditlpos[i].y, m_Ditlpos[i].z);
	glRotatef((GLfloat) m_DAng[i], 0.0f, 0.0f, 1.0f);
	glRotatef((GLfloat) m_DAngM[i], 0.0f, 1.0f, 0.0f);
	glScalef(m_DScl[i], m_DScl[i], m_DScl[i]);
	DrawMesh(&m_MeshDeco);
	glPopMatrix();
	}
	glDisable(GL_BLEND);

	//�㏈��
	glDisable(GL_LIGHTING);		//���C�g�I�t
	glEnable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����
}

//++++++++++++++++++++++++++++++++++++++++++++++++
// �^�C�g���`��
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawTitle(void)
{
	//��������
	glEnable(GL_LIGHTING);		//���C�gON
	glDisable(GL_ALPHA_TEST);	//���e�X�gON
	glEnable(GL_DEPTH_TEST);	//Z�o�b�t�@�L����

	//�^�C�g���̕`��
	m_pShadeMng->UseShader(PHONG);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDT);
	glPushMatrix();
	glTranslatef(m_Titlpos.x, m_Titlpos.y, m_Titlpos.z);
	glRotatef((GLfloat)m_TAngZ, 1.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)m_TAngY, 0.0f, 1.0f, 0.0f);
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
bool SELECT::FadeIn(POLYGON3D *pol)
{
	static int nCnt = -1;

	//����
	if(nCnt < 0){
		nCnt = m_nCnt;	//���݂̃t���[���J�E���g����ۑ�
		pol->col.a = 0.0f;
	}

	//���l���グ��
	if((m_nCnt - nCnt) < SELECT_FADE_TIME)
		pol->col.a += (1.0f / SELECT_FADE_TIME);
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
bool SELECT::FadeOut(POLYGON3D *pol)
{
	static int nCnt = -1;

	//����
	if(nCnt < 0){
		nCnt = m_nCnt;	//���݂̃t���[���J�E���g����ۑ�
		pol->col.a = 1.0f;
	}

	//���l���グ��
	if((m_nCnt - nCnt) < SELECT_FADE_TIME && pol->col.a > 0.05f)
	{
		pol->col.a -= (1.0f / SELECT_FADE_TIME);
	}
	else{
		pol->col.a = 0.0f;
		nCnt = -1;
		return true;
	}
	return false;
}

//�f�o�b�N�p
int SELECT::GetSelect(void)
{
	return m_nSelect;
}
//################################################
// End of File
//################################################
