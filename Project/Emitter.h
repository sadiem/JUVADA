//################################################
// <Emitter.h>
//
//------------------------------------------------
// 2012/01/15 ~
//						Akihito Tanaka
//################################################
#ifndef _____EMITTER_H_____
#define _____EMITTER_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "include.h"
#include "Common.h"
#include "Particle.h"
#include "Object.h"
#include "ShaderMng.h"
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================
#define MAX_PARTICLE (500)
#define SPLASH_GEN_NUM (100)
#define SPIN_GEN_NUM (3)
#define BOMB_GEN_NUM (10)

//�G�~�b�^��������
#define EM_SPIN_TIME	(200)
#define EM_SPLSH_TIME	(60)
#define EM_BOMB_TIME	(100)
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
class EMITTER
{
public:
	EMITTER();
	~EMITTER();
private:
	GLuint		m_TexID;									//�e�N�X�`��ID
	PARTICLE	m_Particle[MAX_PARTICLE];					//�p�[�e�B�N��
	PARTICLE	*SearchBlankParticle(void);					//�󂫂̌���
	void		DeleteParticle(PARTICLE *particle);			//����
	void		CreatePrticle(void);						//�����ʒu�̃Z�b�g
	int			m_ParticleCount;							//�p�[�e�B�N���̐�
	int			m_LifeTime;									//�G�~�b�^�[�̐�������
	VECTOR3		m_Pos;										//�G�~�b�^�[�̍��W
	int			m_Type;										//�p�[�e�B�N���^�C�v
	OBJECT		*m_obj;										//�Ǐ]����I�u�W�F�N�g
	float		m_PointSize;								//�|�C���g�X�v���C�g�̃T�C�Y
	VECTOR3		m_Color;									//�p�[�e�B�N���̐F

	SHADER_MNG	*m_pShaderMng;								//�V�F�[�_�}�l�[�W��	

public:
	bool		m_Enable;									//�G�~�b�^���L�����̃t���O
	void		Init(void);	//������
	void		UpDate(void);	//�X�V
	void		Draw(void);	//�`��
	void		DrawShader(void);
	void		Create(int type, GLuint texID, OBJECT *obj);
};

//################################################
// End of File
//################################################
#endif _____EMITTER_H_____
