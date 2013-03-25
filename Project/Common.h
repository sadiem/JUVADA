//################################################
// <Main.cpp>
// 
//------------------------------------------------
//
//						SekiyamaRumi
//################################################
#ifndef _____COMMON_H_____
#define _____COMMON_H_____

//================================================
//�C���N���[�h�w�b�_
//================================================
#include <windows.h>			//���C���w�b�_
#include "Matrix.h"

#include <GL/glew.h>		//OpenGL �֘A�̃w�b�_
#include <GL/wglew.h>		//OpenGL �֘A�̃w�b�_

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
//================================================
//�萔��`
//================================================
#define SCREEN_WIDTH		(800)		//�X�N���[���̕�
#define SCREEN_HEIGHT		(600)		//�X�N���[���̍���

#define FOVY				45.0f							//����p
#define NEAR_CLIP			1.0f							//�j�A�N���b�v���s������
#define FAR_CLIP			10000.0f						//�t�@�[�N���b�v���s������

#define M_PI				(3.141592f)			//�o�h
#define M_PI_H				(M_PI / 2.0f)		//90�x
#define RAD					(float)(M_PI/180.0)	//���W�A���ϊ��p�萔

//�f�o�b�O�p
#define DEBUG_ON			(1)		//�f�o�b�O���Ɏ��s
#define DEBUG_OFF			(0)		//�f�o�b�O���ɖ����s

#define FIELD_WIDTH         (110)	//�t�B�[���h��

//================================================
//�\���̒�`
//================================================

//���_�t�H�[�}�b�g��` 2D
struct FVERTEX{
	// GL_T2F_V3F
	GLfloat		tu, tv;			// �e�N�X�`�����W
	GLfloat		x, y, z;		// ���_���W
};

//�x�N�g���^�@�Q
struct VECTOR2D{
	float x, y;
};


//���_�J���\
struct COLOR{
	float r, g, b, a;
};
//��
struct FACE{
	int				nMaterialNo;	//�}�e���A���i���o�[
	unsigned short	usNum;		//���_��
	unsigned short	usIdx[3];	//���_�C���f�b�N�X
};

//�e
struct SHADOWVOLUME{
	VECTOR3 vecEdge[32768];		//���_	�\���ȗʂ̒��_���m�ۂ��Ă���
	int		nEdgeNum;			//�G�b�W��
};

//�r���{�[�h�p
struct BILLBOARD
{
	VECTOR3	m_Pos;			//�ʒu
	VECTOR3 m_vec;			//�ړ������x�N�g��
	bool	m_Live;			//����
	int		m_Time;			//��������
	float   m_Alpha;		//�_�̃��l
	float   m_Angle;		//�p�x
	float   m_Speed;		//���x
	float	m_ScaleRate;	//�g�嗦
	float   m_Scale;		//�g��
	float	m_SpeedY;		//�����̑��x
};
//�QD�r���{�[�h�p
struct BILLBOARD2D
{
	VECTOR3	pos;		//�ʒu
	VECTOR3 axis;		//��]��
	VECTOR3 vec;		//�ړ������x�N�g��
	float   Angle;		//�p�x
	float	ScaleRate;	//�g�嗦
};
//�|��
struct POLYGON3D
{
	VECTOR3  ver[4];		//���_
	VECTOR2D tex[4];		//�e�N�X�`��
	COLOR  col;				//�F���
};
//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================
void SetExecTime(DWORD time);		//���s���ԃZ�b�g


//################################################
// End of File
//################################################
#endif _____COMMON_H_____