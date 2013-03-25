//################################################
// <Select.h>
// �Z���N�g���j���[���쐬
//------------------------------------------------
// 2013/01/18 ~
//						SekiyamaRumi
//################################################
#ifndef _____SELECT_H_____
#define _____SELECT_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"	//�C���N���[�h�w�b�_
#include "MeshMng.h"	//���b�V���}�l�[�W��
#include "Common.h"		//����
#include "ShaderMng.h"		//�V�F�[�_�}�l�[�W��
#include "Camera.h"			//�J�����}�l�[�W��
#include "Input.h"
#include "Sound.h"
//================================================
//�萔��`
//================================================
#define SLECT_BUTTOM_NUM	(4)		//�{�^����
#define SLECT_DECO_NUM		(5)		//�f�R���[�V����
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class SELECT
{
public:
	SELECT();
	~SELECT();

	void Init(void);		//������
	void Reset(void);		//���Z�b�g
	void Release(void);		//�����[�X
	bool Update(void);		//�X�V
	void Draw(void);		//�`��
	int GetSelect(void);//�L�[�Z���N�g
private:
	POLYGON3D	m_PFade;	//�t�F�[�h�p�|���S��
	POLYGON3D	m_PBg;		//BG�p�|���S��
	POLYGON3D	m_PButtom[SLECT_BUTTOM_NUM];	//�{�^���p�|���S��
	POLYGON3D	m_PStencil;	//�X�e���V���p�|���S��
	POLYGON3D	m_PEndselect;		//�I���I�����
	POLYGON3D	m_PButtumEnd[2];	//�I����ʃ{�^��

	VECTOR2D	m_CopyTexButtom[SLECT_BUTTOM_NUM][4];	//�{�^���e�N�X�`�����W�̃R�s�[

	CAMERA		*m_pCmr;		//�J�����}�l�[�W��
	SHADER_MNG  *m_pShadeMng;	//�V�F�[�_�}�l�[�W��
	INPUT_MNG	*m_pInput;
	SOUND		*m_pSE;

	int			m_nState;	//��ԑJ��
	int			m_nInState;	//��ԑJ��(���) 
	int			m_nCnt;		//�t���[���J�E���^
	int			m_nSelect;	//��ʑI��
	int			m_nKeyEnd;	//�I����ʓ��L�[


	bool bflg;
	bool bflgKey1;
	bool bflgKey2;
	int nCnt;

	bool		m_bButtunChange[4];	//�{�^���摜�ϊ��t���O

	MESH m_MeshT;			//���b�V���^�C�g��
	MESH m_MeshDeco;		//�f�R���[�V����

	GLuint  m_TexID;		//�e�N�X�`��ID	�|��
	GLuint  m_TexIDM;		//�e�N�X�`��ID	���f��
	GLuint  m_TexIDD;		//�e�N�X�`��ID	���f�� �f�R���[�V����
	GLuint  m_TexIDT;		//�e�N�X�`��ID	�^�C�g��
	GLuint	m_TexIDF;		//�e�N�X�`��ID	�t�F�[�h
	GLuint	m_TexIDE;		//�e�N�X�`��ID	�G���h�Z���N�g
	
	VECTOR3 m_Titlpos;		//�^�C�g���ʒu
	float   m_TAngZ;		//�^�C�g����]
	float   m_TAngY;		//�^�C�g����]
	float   m_TScl;			//�^�C�g���g��
	float   m_EScl;			//�I���I����ʊg�嗦
	
	//�f�R���[�V����
	VECTOR3 m_Ditlpos[SLECT_DECO_NUM];		//�^�C�g���ʒu
	float   m_DAng[SLECT_DECO_NUM];			//�^�C�g����] �X��
	float   m_DAngM[SLECT_DECO_NUM];		//�^�C�g����] ���g�̉�]
	float   m_DScl[SLECT_DECO_NUM];			//�^�C�g���g��
	
	//�X�e���V��
	VECTOR3 m_vSSlide;							//�X���C�h

	VECTOR3	m_vBtmpos[SLECT_BUTTOM_NUM];		//�{�^���ʒu
	VECTOR3 m_vBtmposCopy[SLECT_BUTTOM_NUM];	//�R�s�[

	bool FadeIn(POLYGON3D *pol);				//�t�F�[�hin
	bool FadeOut(POLYGON3D *pol);				//�t�F�[�hout
	void DrawModel();							//���f���`��
	void DrawTitle();							//���f���`�恨�^�C�g��
	void DrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, float scl, int m_TexID, bool flg);	//�|���S���`��
	void SetPoli(void);							//���_�Z�b�g
	void DrawStencil(void);						//�X�e���V���`��
	bool TexMoveAppear(void);					//�{�^���e�N�X�`���̈ړ�
	bool TexMovePutaway(void);					//�{�^�������܂�	
	void TexChange(int nID, int flg);			//�I�𒆃{�^���̃e�N�X�`���ύX
	void TexMovePutawayEnd(int nMove);				//�I���I���{�^���̃e�N�X�`���؂�ւ�
};
//################################################
// End of File
//################################################
#endif _____SELECT_H_____
