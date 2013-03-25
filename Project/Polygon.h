//################################################
//<Polygon.h>
// �|���S���̏o��
//------------------------------------------------
//2012/07/12 ~
//						SekiyamaRumi
//################################################
#ifndef ______POLYGON_H_____
#define ______POLYGON_H_____

//================================================
//�C���N���[�h
//================================================
#include <windows.h>		//Windows
#include <tchar.h>			//�ėp�e�L�X�g �}�b�s���O

#include "Include.h"		//�C���N���[�h
#include "Common.h"			//����

//================================================
//�\����
//================================================

//================================================
//�N���X��`
//================================================
void PlySetCol(POLYGON3D *pol, COLOR col);		//�J���[�ݒ�
void PlySetTex(POLYGON3D *pol);					//�e�N�X�`���P�����P�|���S���@���W���Z�b�g
void PlySetTex(POLYGON3D *pol, float x, float y, float width, float height, float DivisionNum);		//�e�N�X�`���P���� ���R���W���Z�b�g
void PlySetVer(POLYGON3D *pol, float x, float y, float width, float height);				//���_�̃Z�b�g
void PlySetScl(POLYGON3D *pol, float scl);	//�g�k

void PlyDrawPoliBillBoard(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID);	//�r���{�[�h�`��
void PlyDrawPoli(POLYGON3D &pol, float ang, VECTOR3 axis,  VECTOR3 pos, int m_TexID);			//�|���S���`��

#endif ______POLYGON_H_____
