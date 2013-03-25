//######################################################
//���b�V���̓ǂݍ���
//------------------------------------------------------
//���^�Z�R�C�A�̃f�[�^����f�[�^�𔲂�����
//######################################################

#ifndef _____MESH_H______
#define _____MESH_H______

#include "Main.h"
#include "Matrix.h"
#include "Common.h"

struct MATERIAL{
	int nNo;						//�}�e���A���ԍ�
	VECTOR4		Diffuse;			//�f�B�t���[�Y
	float		SpecPower;			//�X�y�L�����[�̋���
	VECTOR3		Specular;			//�X�y�L�����[
	VECTOR3     Emissive;			//�G�~�b�V����
};
//======================================================
//�\���̒�`
//======================================================

//���b�V���\����
struct MESH{
	int			nVtx;				//���_�̐�
	VECTOR3		*pVtx;				//���_���W
	VECTOR3		*pVtxC;				//���_���W
	int			nFace;				//�ʐ�
	FACE		*pFace;				//�ʍ\��
	COLOR		*pColor;			//���_�J���\
	int			nNormal;			//�@���̐�	
	VECTOR3		*pNormal;			//�@��
	int			nNormalIndex;		//�@���C���f�b�N�X��
	FACE		*pNormalIndex;		//�@���C���f�b�N�X
	int			nTexCoord;			//�e�N�X�`�����W��
	VECTOR2D	*pTex;				//�e�N�X�`��
	//�}�e���A�����
	int         nMaterialNum;		//�}�e���A����
	MATERIAL	*pMaterial;			//�}�e���A�����|�C���^

	VECTOR3		vMin;				//�ŏ��l
	VECTOR3		vMax;				//�ő�l
	float		fRadius;			//���a
	VECTOR3		vVel;				//�������̑��x

	VECTOR3		vCenter;			//���b�V���f�[�^�̒��S

	VECTOR3     *pTang;				//�ڃx�N�g��
	VECTOR3		*pBinormal;			//�]�@��
};
//======================================================
//�v���g�^�C�v�錾
//======================================================
int LoadMesh(MESH* pMesh, char* pszPath);		//�ǂݍ���
void ReleaseMesh(MESH* pMesh);					//���
void DrawMesh(MESH* pMesh);						//�`��
void DrawMesh(MESH* pMesh, GLuint tangent);		//�ڃx�N�g���ݒ�̕`��	
void DrawMesh(MESH* pMesh, float offset);		//�e�N�X�`���A�j���[�V����	
void CreateBoxSphireInfo(MESH* pMesh);
void SetMorph(MESH* m_Tmp, MESH &Mesh);			//���[�t�B���O�Z�b�g
void CpyVertex(MESH* m_Tmp, MESH &Mesh);		//�R�s�[
bool Morphing(MESH* m_Tmp, MESH &MeshA, MESH &MeshB, int nFrameNow, int nMorphingStartTime, int nMorphingTime);	//���[�t�B���O
void ReleaseVertex(MESH *Mesh);					//���_�f�[�^�̂݉��
void SetDiffuse(MESH *Mesh, COLOR col);			//�f�B�t���[�Y�F�̃Z�b�g
void FlashDiffuse(MESH *Mesh, COLOR col1, COLOR col2, int nMaxTime, int nTimeNow);	//�J���[�A�j���[�V����
void MeshBomb(MESH *Mesh, MESH *srcMesh);
void DrawBomb(MESH *mesh);
#endif _____MESH_H______
