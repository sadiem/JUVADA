//################################################
// <Particle.h>
//		�p�[�e�B�N���N���X
//------------------------------------------------
// 2013/1/15
//						Akihito Tanaka
//################################################
#ifndef _____PARTICLE_H_____
#define _____PARTICLE_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "Matrix.h"			//�x�N�g���p

//================================================
//�萔��`
//================================================
//================================================
//�N���X��`
//================================================
class PARTICLE
{
public:
	PARTICLE(){	m_Alpha = 0.0f;
				m_Scale = 0.0f;
				m_Live = false;
				m_Time = 0;
				m_Type = 0;
	};
	~PARTICLE(){};
	void UpDate(void);
	void Load(void);
	void Draw(void);
	void Init(void);
	VECTOR3 m_Pos;			//�\���ʒu
	VECTOR3 m_Move;			//�ړ�����
	float	m_Alpha;		//�A���t�@�l
	float	m_Scale;
	bool	m_Live;
	int		m_Time;
	int		m_Type;
};
#endif _____PARTICLE_H_____