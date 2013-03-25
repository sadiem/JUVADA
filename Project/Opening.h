//################################################
// <Opening.h>
// �I�[�v�j���O�Ǘ��}�l�[�W��
//------------------------------------------------
// 2013/01/14 ~
//						SekiyamaRumi
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "Common.h"			//���ʃw�b�_
#include "Input.h"			//�L�[�w�b�_
#include "MeshMng.h"		//���b�V���}�l�[�W��
#include "ShaderMng.h"		//�V�F�[�_�}�l�[�W��
#include "Sound.h"

//================================================
//�N���X��`
//================================================
class OP
{
public:
	OP();
	~OP();

	void Init(void);		//������
	void Reset(void);		//���Z�b�g
	bool Update(void);		//�X�V
	void Draw(void);		//�`��

private:
	SHADER_MNG *m_pShadeMng;	//�V�F�[�_�}�l�[�W��
	INPUT_MNG  *m_pInput;			//�L�[�|�C���^
	SOUND	   *m_pSE;
	MESH m_MeshR;			//���b�V�������O
	MESH m_MeshT;			//���b�V���^�C�g��
	MESH m_MeshD;			//���b�V���f�R���[�V����

	bool m_bFlgPushStart;	//�X�^�[�g�{�^���҂�
	int m_nState;			//���
	int m_nInState;			//���(switch����)
	int m_nRingState;		//�����O���
	int m_nCnt;				//�J�E���^

	POLYGON3D m_PFade;		//�t�F�[�h�p�|���S��
	POLYGON3D m_PLogo;		//���S�p�|���S��
	POLYGON3D m_PBg;		//BG�p�|���S��
	POLYGON3D m_PPushEnter;	//PUSHENTER�p�|���S��

	bool	m_RbDraw;		//�`��t���O
	VECTOR3 m_Ringpos;		//�����O�ʒu
	float	m_RAng;			//�����O��]
	float   m_RScl;			//�����O�g�嗦
	float   m_RJump;		//�W�����v
	VECTOR3 m_Titlpos;		//�^�C�g���ʒu
	float   m_TAng;			//�^�C�g����]
	float   m_TScl;			//�^�C�g���g��
	float   m_DAng;			//�f�R���[�V�����̉�]

	GLuint  m_TexID;		//�e�N�X�`��ID	�|��
	GLuint  m_TexIDM;		//�e�N�X�`��ID	���f��
	GLuint  m_TexIDT;		//�e�N�X�`��ID�@�^�C�g��
	GLuint  m_TexIDB;		//�e�N�X�`��ID�@BG

	bool FadeIn(POLYGON3D *pol);				//�t�F�[�hin
	bool FadeOut(POLYGON3D *pol);				//�t�F�[�hout
	void DrawModel();	//���f���`��
	void DrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID, bool flg);	//�|���S���`��
	void SetPoli(void);		//���_�Z�b�g
};

//################################################
// End of File
//################################################
