//################################################
// <Result.cpp>
//
//------------------------------------------------
// 2013/01/28 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Result.h"	
#include "TexMng.h"		//�e�N�X�`���}�l�[�W��
//================================================
//�萔��`
//================================================
enum {
	RESULT_IN,			//����
	RESULT_FRAME_IN,	//�t���[���C��
	RESULT_ITEM_IN,		//�A�C�e���C��
	RESULT_TIME_IN,		//�^�C���C��
	RESULT_SCORE_IN,	//�X�R�A�C��
	RESULT_DEAD_IN,		//���S���C��
	RESULT_VAL_IN,		//�]���C��
	RESULT_WAIT_CLICK,	//�E�F�C�g
	RESULT_FADE_ITEM,	//�A�C�e���͂���
	RESULT_END			//���U���g�I��
};
//�t�F�[�h�^�C��
#define RESULT_FADE_TIME	(120)		//�t�F�[�h�^�C��
//BG
#define RESULT_BG_H (40)				//�t�F�[�h�|���c��
#define RESULT_BG_W (40)				//�@�@�@�@�@�@�@����
#define RESULT_BG_POS_X (-RESULT_BG_W / 2.0f)	//�t�F�[�h�|�������ʒu
#define RESULT_BG_POS_Y (RESULT_BG_POS_X)
//�X�e���V��
#define RESULT_STENCIL_H (27.0f)							//�X�e���V���|���c��
#define RESULT_STENCIL_W (27.0f)							//�@�@�@�@�@�@�@����
#define RESULT_STENCIL_X (-(RESULT_STENCIL_W / 2.0f))	//�X�e���V���|�������ʒu
#define RESULT_STENCIL_Y (RESULT_STENCIL_X)
#define RESULT_STENCIL_MOVE  (VECTOR3(13.5f, -8.5f, 1.0f))	//�X�e���V���ړ��l
#define RESULT_STENCIL_ANGLE	((GLfloat)10.0f)	//�X�e���V����]�p
#define RESULT_STENCIL_MOVE_VEC	(VECTOR3(cosf(RESULT_STENCIL_ANGLE), sinf(RESULT_STENCIL_ANGLE), 0.0f))	//�X�e���V���ړ��x�N�g��

//�]��
#define RESULT_VAL_H (5.0f)							//�]���|���c��
#define RESULT_VAL_W (5.0f)							//�@�@�@�@�@�@�@����
#define RESULT_VAL_X (-(RESULT_VAL_W / 2.0f))		//�]���|�������ʒu
#define RESULT_VAL_Y (RESULT_VAL_X)
#define RESULT_VAL_POS (VECTOR3(0.0f, 0.0f, 10.0f))	//�ʒu
#define RESULT_VAL_POSA (VECTOR3(-4.3f, 1.3f, 5.0f))	//�ʒu
#define RESULT_VAL_ADD_A (0.05f)					//���l���Z
#define RESULT_VAL_ADD_Z (0.2f)
//PUSH ENTER�p�{�^��
#define RESULT_PUSHENTER_H (1)				//PushEnter�|���c��
#define RESULT_PUSHENTER_W (3)				//�@�@�@�@�@�@�@����
#define RESULT_PUSHENTER_POS_X (-RESULT_PUSHENTER_W / 2.0f)	//PushEnter�|�������ʒu
#define RESULT_PUSHENTER_POS_Y (RESULT_PUSHENTER_POS_X)
//�f�R�@�t���[��
#define RESULT_FRAME_STOP	(0)			//������E��
#define RESULT_ADD_FRAME_SPEED	(1.0f)	//���Z�l
//�f�R�@��t���[��
#define RESULT_FRAME1_H	(2.0f)
#define RESULT_FRAME1_W	(20.0f)
#define RESULT_FRAME1_X (-RESULT_FRAME1_W / 2.0f)	//�t�F�[�h�|�������ʒu
#define RESULT_FRAME1_Y (RESULT_FRAME1_X)
#define RESULT_FRAME1_POS_FIR	(VECTOR3(-20.0f, 15.0f, 2.0f))	//�����ʒu
#define RESULT_FRAME1_POS_SET	(VECTOR3(0.0f, 15.0f, 2.0f))	//�ړ���ʒu
//�f�R�@���t���[��
#define RESULT_FRAME2_H	(2.0f)
#define RESULT_FRAME2_W	(20.0f)
#define RESULT_FRAME2_X (-RESULT_FRAME2_W / 2.0f)	//�t�F�[�h�|�������ʒu
#define RESULT_FRAME2_Y (RESULT_FRAME2_X)
#define RESULT_FRAME2_POS_FIR	(VECTOR3(20.0f, 3.2f, 2.0f))	//�����ʒu
#define RESULT_FRAME2_POS_SET	(VECTOR3(0.0f, 3.2f, 2.0f))		//�ړ���ʒu
//�o�͍��ږ�
#define RESULT_ITEM_NAME_ADD_MOVE_TEX  (0.04f)	//�o�͍��ڏo��
#define RESULT_ITEM_NAME_W (10.0f)
#define RESULT_ITEM_NAME_H (1.5f)
#define RESULT_ITEM_NAME_X (-RESULT_ITEM_NAME_W / 2.0f)
#define RESULT_ITEM_NAME_Y (0.0f)
#define RESULT_ITEM_NAME_SPACE (1.0f)
#define RESULT_ITEM_NAME_FIR_Y (0.3f)
#define RESULT_ITEM_POS_NAME1 (VECTOR3(4.5f, RESULT_ITEM_NAME_FIR_Y, 0.0f))
#define RESULT_ITEM_POS_NAME2 (VECTOR3(4.5f, -(RESULT_ITEM_NAME_H + RESULT_ITEM_NAME_SPACE) + RESULT_ITEM_NAME_FIR_Y, 0.0f))
#define RESULT_ITEM_POS_NAME3 (VECTOR3(4.5f, -(RESULT_ITEM_NAME_H + RESULT_ITEM_NAME_SPACE) * 2 + RESULT_ITEM_NAME_FIR_Y, 0.0f))
//================================================
//�\���̒�`
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Init(void)		//������
{
	m_pCmr = CAMERA::Instance();
	m_pScr = SCORE::Instance();
	m_pDeadNum = DEAD_NUM::Instance();
	m_pPlayer  = PLAYER::Instance();
	m_pTime    = TIME_MNG::Instance();
	m_Input   = INPUT_MNG::getInstance();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���Z�b�g
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Reset(void)	//���Z�b�g
{
	Load();
	COLOR col = {1.0f, 1.0f, 1.0f, 1.0f};
	m_fade.Reset();
	m_nCnt = 0;
	m_nState = 0;
	//�^�C�����󂯎��
	//m_nTime = 0;
	//m_pTime->Reset();
	m_pTime->SetPos(520, 240, 25, 40);

	m_bScrFlg = false;			//�X�R�A�`��t���O
	m_bTimFlg = false;			//�^�C���`��t���O
	m_bDeadFlg = false;			//���S���`��t���O
	flg = 0;

	//�X�R�A���Z�b�g
	m_pScr->SetTexID(m_TexIDS);
	m_pScr->SetVer(545, 435, 35, 46);
	m_pScr->SetNum();
	//���S�����Z�b�g
	m_pDeadNum->SetVer(545, 335, 35, 46);
	m_pDeadNum->SetTexID(m_TexIDS);
	m_pDeadNum->SetNum(m_pPlayer->m_DeadNum);

	//�]���l���v�Z
	m_Val = m_pScr->ColEvolution();

	//�J���[�w��
	for(int i = 0; i < RESULT_MATERIAL_NUM; i ++)
		PlySetCol(&m_pol[i], col);
	m_pol[RESULT_VAL].col.a = 0.0f;	//���߂���X�^�[�g

	//���W�w��
	PlySetVer(&m_pol[RESULT_BG], RESULT_BG_POS_X, RESULT_BG_POS_Y, RESULT_BG_W, RESULT_BG_H);
	PlySetVer(&m_pol[RESULT_BG_FRAME1], RESULT_FRAME1_X, RESULT_FRAME1_Y, RESULT_FRAME1_W, RESULT_FRAME1_H);
	PlySetVer(&m_pol[RESULT_BG_FRAME2], RESULT_FRAME2_X, RESULT_FRAME2_Y, RESULT_FRAME2_W, RESULT_FRAME2_H);
	PlySetVer(&m_pol[RESULT_BG_STENCIL], RESULT_STENCIL_X, RESULT_STENCIL_Y, RESULT_STENCIL_W, RESULT_STENCIL_W);
	PlySetVer(&m_pol[RESULT_VAL], RESULT_VAL_X, RESULT_VAL_Y, RESULT_VAL_W, RESULT_VAL_W);

	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
		PlySetVer(&m_pol[i], RESULT_ITEM_NAME_X, RESULT_ITEM_NAME_Y, RESULT_ITEM_NAME_W, RESULT_ITEM_NAME_H);
	
	//�e�N�X�`�����W�w��
	PlySetTex(&m_pol[RESULT_BG], 8, 16, 8, 16, 16);
	PlySetTex(&m_pol[RESULT_BG_FRAME1], 0, 16, 0, 2, 16);
	PlySetTex(&m_pol[RESULT_BG_FRAME2], 0, 16, 2, 4, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME1], 8, 16, 6, 7, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME2], 8, 16, 5, 6, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME3], 8, 16, 4, 5, 16);
	float w;
	w = (float)4 * (m_Val % 4);

	if(m_Val > 3)
		PlySetTex(&m_pol[RESULT_VAL], (float)4 * (m_Val % 4), (float)4 * (m_Val % 4) + 4,  4,  8, 16);
	else
		PlySetTex(&m_pol[RESULT_VAL], (float)4 * (m_Val % 4), (float)4 * (m_Val % 4) + 4,  0,  4, 16);

	//�r���{�[�h�p�l�̏�����
	for(int i = 0; i < RESULT_MATERIAL_NUM; i ++){
		m_bil[i].Angle = 0.0f;
		m_bil[i].axis = VECTOR3(0.0f, 0.0f, 0.0f);
		m_bil[i].pos = VECTOR3(0.0f, 0.0f, 0.0f);
		m_bil[i].ScaleRate = 1.0f;
		m_bil[i].vec = VECTOR3(0.0f, 0.0f, 0.0f);
	}
	//�ʒu�̏����ݒ�
	m_bil[RESULT_BG].pos = VECTOR3(0.0f, 0.0f, -10.0f);
	m_bil[RESULT_BG_FRAME1].pos = RESULT_FRAME1_POS_FIR;
	m_bil[RESULT_BG_FRAME2].pos = RESULT_FRAME2_POS_FIR;
	m_bil[RESULT_BG_STENCIL].pos = RESULT_STENCIL_MOVE;
	m_bil[RESULT_ITEM_NAME1].pos = RESULT_ITEM_POS_NAME1;
	m_bil[RESULT_ITEM_NAME2].pos = RESULT_ITEM_POS_NAME2;
	m_bil[RESULT_ITEM_NAME3].pos = RESULT_ITEM_POS_NAME3;	
	m_bil[RESULT_VAL].pos = RESULT_VAL_POS;
	
	//�p�x������
	m_bil[RESULT_BG_STENCIL].Angle = RESULT_STENCIL_ANGLE;
	m_bil[RESULT_BG_STENCIL].axis = VECTOR3(0.0f, 0.0f, 1.0f);
	m_bil[RESULT_BG_STENCIL].ScaleRate = 1.0f;

	//�f�R���[�V���������l�Z�b�g
	for(int i = 0; i < RESULT_DECO_NUM; i ++){
		m_Ditlpos[i].x = 2.0f * i;			//�f�R���[�V�����ʒu
		m_Ditlpos[i].y = 1.0f * i;	//�f�R���[�V�����ʒu
		m_Ditlpos[i].z = -5.0f;						//�f�R���[�V�����ʒu
		m_DAng[i] = 72.0f * (i + 1);				//�f�R���[�V������] �X��
		m_DAngM[i] = 0;								//�f�R���[�V������] ���g�̉�]
		m_DScl[i] = 0.3f + (i + 1) * 0.1f;			//�f�R���[�V�����g��
	}

	//�X�e���V���̈ړ�����
	m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Load(void)
{
	//�e�N�X�`��
	m_TexID = g_TexMng.GetTexture("TEXTURE\\RESULT\\result.png", "RESULT");
	m_TexIDD = g_TexMng.GetTexture("TEXTURE\\SELECT\\deko.png", "RESULT");
	m_TexIDS = g_TexMng.GetTexture("TEXTURE\\2D\\number.png", "RESULT");
	m_TexIDV = g_TexMng.GetTexture("TEXTURE\\RESULT\\resultScore.png", "RESULT");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\2D\\time.png", "RESULT");
	//���f��
	g_MeshMng.GetMesh(&m_MeshDeco, "MODEL\\OP\\deco.x", "RESULT");
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Release(void)
{
	g_TexMng.ReleaseCat("RESULT");
	g_MeshMng.ReleaseCat("RESULT");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e���ړ��@
//�Q�[����ʂ���ڂ�ς������
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�e�N�X�`���ړ��I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::ItemMoveAppear(void)
{
	//�{�^��
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
	{	
		m_pol[i].tex[0].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[1].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[2].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[3].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
	}
	//�␳
	if(m_pol[RESULT_ITEM_NAME1].tex[3].x <= 0.5f)
	{	//�␳�l���
		for(int k = RESULT_ITEM_NAME1; k < RESULT_ITEM_NAME1 + 3; k ++){
			m_pol[k].tex[0].x = 0.0f;
			m_pol[k].tex[1].x = 0.0f;
			m_pol[k].tex[2].x = 0.5f;
			m_pol[k].tex[3].x = 0.5f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e���ړ��@
//���ʉ�ʂ���Z���N�g��ʂֈڂ�����
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�e�N�X�`���ړ��I���t���O
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::ItemMoveClose(void)
{
	//�{�^��
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
	{	
		m_pol[i].tex[0].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[1].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[2].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[3].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
	}
	//�␳
	if(m_pol[RESULT_ITEM_NAME1].tex[3].x >= 1.0f)
	{	//�␳�l���
		for(int k = RESULT_ITEM_NAME1; k < RESULT_ITEM_NAME1 + 3; k ++){
			m_pol[k].tex[0].x = 0.5f;
			m_pol[k].tex[1].x = 0.5f;
			m_pol[k].tex[2].x = 1.0f;
			m_pol[k].tex[3].x = 1.0f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�X�V
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::Update(void)
{
	m_nCnt++;
	m_fade.SetFrame(m_nCnt);
	switch(m_nState)
	{
	case RESULT_IN:			//����
		if(m_fade.FadeOut(RESULT_FADE_TIME))
			m_nState = RESULT_FRAME_IN;
		break;
	case RESULT_FRAME_IN:	//�t���[���C��
		if(m_bil[RESULT_BG_FRAME1].pos.x < RESULT_FRAME_STOP)
		{
			m_bil[RESULT_BG_FRAME1].pos.x += RESULT_ADD_FRAME_SPEED;
			m_bil[RESULT_BG_FRAME2].pos.x -= RESULT_ADD_FRAME_SPEED;
		}else
			m_nState = RESULT_ITEM_IN;
		break;
	case RESULT_ITEM_IN:		//�A�C�e���C��
		//��ʊ����
		if(m_vSSlide.x < 2.0f){
			m_vSSlide.y -= 0.000001f;
			m_vSSlide.x += 0.1f;
		}else
		{//�A�C�e�����o��	(�^�C���E���S�񐔁E�X�R�A)
			if(ItemMoveAppear())
				m_nState = RESULT_TIME_IN;
		}
		break;
	case RESULT_TIME_IN:		//�^�C���C��
		m_bTimFlg = true;
		m_nState = RESULT_DEAD_IN;
		break;
	case RESULT_DEAD_IN:
		m_bDeadFlg = true;
		m_nState = RESULT_SCORE_IN;
		break;
	case RESULT_SCORE_IN:	//�X�R�A�C��
		m_bScrFlg = true;
		Cnt = m_nCnt;			//�J�E���^�Z�b�g
		m_nState = RESULT_VAL_IN;
		break;
	case RESULT_VAL_IN:		//�]���C��
		
		//��]
		m_bil[RESULT_VAL].axis = VECTOR3(0.0f, 1.0f, 0.0f);
		m_bil[RESULT_VAL].Angle += 10;
		
		//���l1.0�܂ŏグ��
		if(m_pol[RESULT_VAL].col.a < 1.0f)
			m_pol[RESULT_VAL].col.a += RESULT_VAL_ADD_A;
		if(m_pol[RESULT_VAL].col.a > 1.0f)
		{
			m_pol[RESULT_VAL].col.a = 1.0f;
		}
		//�ړ�
		if(m_nCnt - Cnt < 60)
			m_bil[RESULT_VAL].pos +=  (RESULT_VAL_POSA - RESULT_VAL_POS) / 120;
		if(m_nCnt - Cnt > 60)
		{
			m_bil[RESULT_VAL].Angle = 0;
			Cnt = 0;
			m_bil[RESULT_VAL].pos = RESULT_VAL_POSA;
			m_nState = RESULT_WAIT_CLICK;
		}
		break;
	case RESULT_WAIT_CLICK:	//�E�F�C�g
		if(m_Input->GetBtnState(BTN_A) == TRG){
			m_nState = RESULT_FADE_ITEM;
			m_bTimFlg = false;
			m_bScrFlg = false;
			m_bDeadFlg = false;
		}
		break;
	case RESULT_FADE_ITEM:	//�A�C�e���͂���
		//�A�C�e�����͂���	(�^�C���E���S�񐔁E�X�R�A)
		if(!flg){
			if(ItemMoveClose())
				flg = true;
			//���l1.0�܂ŏグ��
			if(m_pol[RESULT_VAL].col.a > 0.0f)
				m_pol[RESULT_VAL].col.a -= RESULT_VAL_ADD_A * 3;
			if(m_pol[RESULT_VAL].col.a < 0.0f)
				m_pol[RESULT_VAL].col.a = 0.0f;
		}
		else
		{	//��ʕ���
			if(m_vSSlide.x > 0.0f){
				m_vSSlide.y += 0.000001f;
				m_vSSlide.x -= 0.1f;
				//�␳
				if(m_vSSlide.x < 0.0f)
					m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
				//�t���[�������܂�
				if(m_bil[RESULT_BG_FRAME1].pos.x < 4.5f)
				{
					m_bil[RESULT_BG_FRAME1].pos.x -= RESULT_ADD_FRAME_SPEED * 1.0f;
					m_bil[RESULT_BG_FRAME2].pos.x += RESULT_ADD_FRAME_SPEED * 1.0f;
				}
			}
			//�t�F�[�h�A�E�g
			if(m_fade.FadeIn(RESULT_FADE_TIME))
					m_nState = RESULT_END;
		}

		break;
	case RESULT_END:			//���U���g�I��
		return true;
	default:break;
	}

	//�f�R���[�V������]
	for(int i = 0; i < RESULT_DECO_NUM; i++)
		m_DAngM[i] += 1;

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Draw(void)
{	
	PlyDrawPoliBillBoard(m_pol[RESULT_BG], m_bil[RESULT_BG].Angle, m_bil[RESULT_BG].axis, m_bil[RESULT_BG].pos, m_TexID);
	DrawModel();
	DrawStencil();
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i++)
		PlyDrawPoliBillBoard(m_pol[i], m_bil[i].Angle, m_bil[i].axis, m_bil[i].pos, m_TexID);
	PlyDrawPoliBillBoard(m_pol[RESULT_VAL], m_bil[RESULT_VAL].Angle, m_bil[RESULT_VAL].axis, m_bil[RESULT_VAL].pos, m_TexIDV);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_FRAME1], m_bil[RESULT_BG_FRAME1].Angle, m_bil[RESULT_BG_FRAME1].axis, m_bil[RESULT_BG_FRAME1].pos, m_TexID);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_FRAME2], m_bil[RESULT_BG_FRAME2].Angle, m_bil[RESULT_BG_FRAME2].axis, m_bil[RESULT_BG_FRAME2].pos, m_TexID);
	m_fade.Draw();
}
void RESULT_MNG::Draw2D(void)
{
	if(m_bScrFlg)
		m_pScr->Draw();
	if(m_bTimFlg)
		m_pTime->Draw(m_TexIDT);
	if(m_bDeadFlg)
		m_pDeadNum->Draw();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ���f���`��
//--in--------------------------------------------
//�Ȃ�
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::DrawModel(void)
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
	for(int i = 0; i < RESULT_DECO_NUM; i ++)
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
void RESULT_MNG::DrawStencil(void)
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
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_STENCIL], m_bil[RESULT_BG_STENCIL].Angle, m_bil[RESULT_BG_STENCIL].axis, m_bil[RESULT_BG_STENCIL].pos, -1);
	
	//���ʂ�`��
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_STENCIL], m_bil[RESULT_BG_STENCIL].Angle, m_bil[RESULT_BG_STENCIL].axis, m_bil[RESULT_BG_STENCIL].pos + m_vSSlide, -1);
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
//################################################
// End of File
//################################################