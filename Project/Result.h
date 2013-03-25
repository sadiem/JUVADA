//################################################
// <Result.h>
//
//------------------------------------------------
//2013/01/31 
//						SekiyamaRumi
//################################################
#ifndef ______RESULT_H______
#define ______RESULT_H______

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//�C���N���[�h
#include "Common.h"		//����
#include "Polygon.h"	//�|���S���`��
#include "Fade.h"		//�t�F�[�h�`��
#include "Score.h"		//�X�R�A�w�b�_
#include "MeshMng.h"	//���b�V���}�l�[�W��
#include "Camera.h"		//�J����
#include "Score.h"		//�X�R�A
#include "DeadNum.h"	//���S��
#include "Player.h"
#include "Time.h"		//����
#include "Input.h"

//================================================
//�萔��`
//================================================
enum {
	RESULT_BG,			//�w�i
	RESULT_BG_FRAME1,	//�f�R���[�V����
	RESULT_BG_FRAME2,	//�f�R���[�V����
	RESULT_BG_STENCIL,	//�X�e���V��
	RESULT_ITEM_NAME1,	//�o�̓f�[�^���� �^�C��
	RESULT_ITEM_NAME2,	//�o�̓f�[�^���� ���S��
	RESULT_ITEM_NAME3,	//�o�̓f�[�^���� �X�R�A
	RESULT_VAL,			//�]��
	RESULT_MATERIAL_NUM	//�f�ސ�
};
#define RESULT_DECO_NUM		(5)		//�f�R���[�V����
//================================================
//�v���g�^�C�v�錾
//================================================
class RESULT_MNG
{
public:
	static RESULT_MNG *Instance()
	{
		static RESULT_MNG Inst;
		return &Inst;
	}

private:
	RESULT_MNG(){}
	CAMERA *m_pCmr;
	SCORE  *m_pScr;	
	DEAD_NUM *m_pDeadNum;
	PLAYER *m_pPlayer;
	TIME_MNG *m_pTime;
	INPUT_MNG	*m_Input;
	
	POLYGON3D   m_stencil;					//�X�e���V��
	POLYGON3D   m_pol[RESULT_MATERIAL_NUM];	//�|���S��
	BILLBOARD2D	m_bil[RESULT_MATERIAL_NUM];	//�r���{�[�h2D�p�\����
	GLuint		m_TexID;					//�e�N�X�`��ID
	GLuint		m_TexIDD;					//�e�N�X�`��ID�@�f�R
	GLuint		m_TexIDS;					//�e�N�X�`��ID�@�X�R�A
	GLuint		m_TexIDV;					//�e�N�X�`��ID�@�]��
	GLuint		m_TexIDT;					//�e�N�X�`��ID�@�^�C��
	int			m_nState;					//���
	int			m_nCnt;						//�t���[���J�E���^
	int			m_nTime;					//���Ԏ󂯎��
	int			m_nEvaluation;				//�]���󂯎�
	int			m_nScr;						//�X�R�A�󂯎�
	bool		m_bScrFlg;					//�X�R�A�`��t���O
	bool		m_bTimFlg;					//�^�C���`��t���O
	bool        m_bDeadFlg;					//���S���`��t���O
	FADE		m_fade;						//�t�F�[�h
	MESH		m_MeshDeco;					//�w�i�Ŏg�p���郂�f��
	
	//�J�E���^�ƃt���O
	int			Cnt;
	bool		flg;

	int			m_Val;						//�]��
	//�f�R���[�V����
	VECTOR3 m_Ditlpos[RESULT_DECO_NUM];		//�f�R�ʒu
	float   m_DAng[RESULT_DECO_NUM];		//�f�R��] �X��
	float   m_DAngM[RESULT_DECO_NUM];		//�f�R��] ���g�̉�]
	float   m_DScl[RESULT_DECO_NUM];		//�f�R�g��

	//�X�e���V��
	VECTOR3 m_vSSlide;						//�X���C�h

	void Load(void);			//�ǂݍ���
	void DrawModel(void);		//���f���`��
	void DrawStencil(void);		//�X�e���V���`��
	bool ItemMoveAppear(void);	//�o�͍��ږ��o��
	bool ItemMoveClose(void);	//�o�͍��ږ����܂�
public:
	virtual ~RESULT_MNG(){}
	void Init(void);	//������
	void Reset(void);	//���Z�b�g
	void Release(void);	//���
	bool Update(void);	//�X�V
	void Draw(void);	//�`��
	void Draw2D(void);	//�`��2D 
};


//################################################
// End of File
//################################################
#endif ______RESULT_H______
