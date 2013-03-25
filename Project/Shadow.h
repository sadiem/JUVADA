//################################################
// <Shadow.cpp>
// �e��t����
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
//################################################
#ifndef _____SHADOW_H_____
#define _____SHADOW_H_____
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"
#include "Matrix.h"
#include "Common.h"
#include "Mesh.h"		//���b�V���w�b�_
#include "Camera.h"
#include "Object.h"		//�I�u�W�F�N�g
//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================

//================================================
//�\���̒�`
//================================================
//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�N���X��`
//================================================
class SHADOW
{
public: 
	static SHADOW* Instance()
	{
		static SHADOW Inst;
		return &Inst;
	}
private:
	CAMERA *p_Camera;
	SHADOW();
public:
	~SHADOW();
	void CreateShadow(OBJECT *pModel);			//�Ăяo���p


private:
	HRESULT CreateEdge(SHADOWVOLUME *pShadow, MESH *pMesh, float *pLight);	//�G�b�W���X�g����
	void AddEdge(int *pEdge, int *nNumEdge, int nInd1, int nInd2);			//�G�b�W���X�g�ǉ�
	void RenderStencil(void);
	void DrawShadow(SHADOWVOLUME *pShadow);
	void SetLightVec(OBJECT *pObj, VECTOR3 *vec);
	
};
//################################################
// End of File
//################################################
#endif _____SHADOW_H_____

