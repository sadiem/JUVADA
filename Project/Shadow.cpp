//################################################
// <Shadow.cpp>
//
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Shadow.h"
#include "Graphic.h"

#define SHADOW_LENGTH (1000)
int g_nCntFace = 0;
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SHADOW::SHADOW()
{
	p_Camera = CAMERA::Instance();
	//p_Player = PLAYER::Instance();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SHADOW::~SHADOW()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�V���h�E����
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::CreateShadow(OBJECT *pModel)
{
	VECTOR3 vec;	//�e�`�掞�̍�Ɨp�x�N�g��

	//�V���h�E�p���b�V���̐���
	SetLightVec(pModel, &vec);
	HRESULT nEra = CreateEdge(&pModel->m_Shadow, pModel->m_Mesh, &vec.v[0]);

	//������
	glLoadIdentity();
	gluLookAt(p_Camera->ViewPos.x, p_Camera->ViewPos.y, p_Camera->ViewPos.z, p_Camera->ViewCent.x, p_Camera->ViewCent.y, p_Camera->ViewCent.z, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE, GL_FALSE,GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
//	glDisable(GL_FOG);

	//�\�ʂ����`��
	glStencilFunc(GL_ALWAYS, 0, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);			//���v��聁�\
	glPushMatrix();
	glTranslatef((GLfloat)pModel->m_Pos.x, (GLfloat)pModel->m_Pos.y, (GLfloat)pModel->m_Pos.z);	
	glRotatef(((GLfloat)pModel->m_Rad * 180 / M_PI), (GLfloat)0.0f, (GLfloat)1.0f , (GLfloat)0.0f);	//Y����]
	glScalef(pModel->m_ScaleRate, pModel->m_ScaleRate, pModel->m_ScaleRate);
	DrawShadow(&pModel->m_Shadow);
	//���ʂ�`��
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glFrontFace(GL_CCW);		//�����v�܂�聁��
	DrawShadow(&pModel->m_Shadow);
	glPopMatrix();

	//�ݒ��߂�
	glFrontFace(GL_CCW);
	glColorMask(1, 1, 1, 1);
	glDepthMask(1);

	//-----------------------------------------------
	//�e��t����
	//-----------------------------------------------
	glStencilFunc(GL_NOTEQUAL, 0, ~0);
	glEnable(GL_BLEND);										//����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		//���ߏ����ݒ�
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);						//�F
	glDisable(GL_DEPTH_TEST);								//�f�v�X�e�X�g������
	glDisable(GL_CULL_FACE);								//���ʂ͕`���Ȃ�

	//�e�̃X�e���V��������`��
	glPushMatrix();
	glTranslatef((GLfloat)pModel->m_Pos.x, (GLfloat)pModel->m_Pos.y, (GLfloat)pModel->m_Pos.z);	
	glRotatef(((GLfloat)p_Camera->rotR * 180 / M_PI), (GLfloat)0.0f, (GLfloat)1.0f , (GLfloat)0.0f);	
	glRotatef(((GLfloat)p_Camera->rotZ * 180 / M_PI), (GLfloat)1.0f, (GLfloat)0.0f , (GLfloat)0.0f);
	glBegin(GL_QUADS);
	glVertex3f(100.0f, 100.0f, -20.0f); 
	glVertex3f(100.0f, -100.0f, -20.0f); 
	glVertex3f(-100.0f, -100.0f, -20.0f); 
	glVertex3f(-100.0f,  100.0f, -20.0f); 
	glEnd();
	glPopMatrix();

	//�����ݒ�����ɖ߂�
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
	//glEnable(GL_FOG);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�V���h�E�{�����[���̂��߂̃|���S������
//--in--------------------------------------------
// ���b�V���f�[�^
// �ϊ��}�g���b�N�X�f�[�^
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT SHADOW::CreateEdge(SHADOWVOLUME *pShadow, MESH *pMesh, float *pLight)
{
	//���C�g���x�N�g���\�L�ɒ���
	VECTOR3 Light;
	Light.v[0] = *(pLight + 0);
	Light.v[1] = *(pLight + 1);
	Light.v[2] = *(pLight + 2);

	//���[�N�p�G�b�W���X�g�̍쐬�c�C���f�b�N�X�ԍ��i�[
	int *pEdge = new int[pMesh->nFace * 6];		//1�|���S��6���_

	if(pEdge == NULL)
		return S_FALSE;

	int nNumEdge = 0;	//�G�b�W��
	int i = 0;
	//�����������Ă���ʂ�����
	for(i = 0; i < pMesh->nFace; i++)	//�ʂ̐�������
	{
		//�ʂ̃C���f�b�N�X�ԍ��ێ�
		int faseIdx[3];
		faseIdx[0] = pMesh->pFace[i].usIdx[0];
		faseIdx[1] = pMesh->pFace[i].usIdx[1];
		faseIdx[2] = pMesh->pFace[i].usIdx[2];

		//���_���擾
		VECTOR3 vec0 = pMesh->pVtx[pMesh->pFace[i].usIdx[0]];
		VECTOR3 vec1 = pMesh->pVtx[pMesh->pFace[i].usIdx[1]];
		VECTOR3 vec2 = pMesh->pVtx[pMesh->pFace[i].usIdx[2]];

		//------------------------------------
		//�����������Ă���ʂ�����
		//------------------------------------
		//�ʂ��\������҂𐶐�
		VECTOR3 cross1 = vec2 - vec0;
		VECTOR3 cross2 = vec1 - vec0;

		//2�̕ӂ̊O�ς���ʂ̖@�����쐬
		VECTOR3 normal;
		Vec3Cross(&normal, cross1, cross2);

		float n;
		n = Vec3Dot(Light, normal);
		//�ʂ̖@���ƃ��C�g�x�N�g���̓��ς�-�̏ꍇ�ӂ�ǉ�
		if(Vec3Dot(Light, normal) <= 0)
		{
			g_nCntFace ++;
			//�ӂ�ǉ�
			AddEdge(pEdge, &nNumEdge, faseIdx[0], faseIdx[1]);
			AddEdge(pEdge, &nNumEdge, faseIdx[1], faseIdx[2]);
			AddEdge(pEdge, &nNumEdge, faseIdx[2], faseIdx[0]);
		}
	}

	//�V���h�E�{�����[���̑��ʂ̒ǉ�
	pShadow->nEdgeNum = 0;
	for(i = 0; i < nNumEdge; i ++)	//�G�b�W�̐�������
	{
		VECTOR3 v1, v2;
		VECTOR3 v3, v4;
		//���_�o�^
		v1 = pMesh->pVtx[pEdge[i * 2 + 0]];
		v2 = pMesh->pVtx[pEdge[i * 2 + 1]];
		v3 = v1 - Light * SHADOW_LENGTH;
		v4 = v2 - Light * SHADOW_LENGTH;

		//��`�ǉ� -- �g���C�A���O�����X�g
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v1;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v2;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v3;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v1;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v3;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v4;
	}
	//���[�N�p�G�b�W���X�g�̉��
	if(pEdge)
		delete pEdge;
	pEdge = NULL;

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//�G�b�W���X�g�̒ǉ�
//--in--------------------------------------------
// �G�b�W���X�g(�C���f�b�N�X���X�g)
// ���̖ʐ�(���������܂�)
// �o�^�\��C���f�b�N�X�P
// �o�^�\��C���f�b�N�X�Q
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::AddEdge(int *pEdge, int *nNumEdge, int nInd1, int nInd2)
{
	static int nCnt = 0;
	//���݂̓o�^�G�b�W�̕�������
	for(int i = 0; i < *nNumEdge; i ++)
	{
		int L1 = i * 2 + 0;
		int L2 = i * 2 + 1;
		//�G�b�W����
		if(((pEdge[i * 2 + 0] == nInd1) && (pEdge[i * 2 + 1] == nInd2)) || ((pEdge[i * 2 + 0] == nInd2) && (pEdge[i * 2 + 1] == nInd1)))
		{
			nCnt ++;
			//�ۑ��G�b�W���l�߂�
			for(int k = i; k < *nNumEdge - 1; k++)
			{
				int nT1 = k * 2 + 0;
				int nT2 = k * 2 + 1;

				int nT3 =  (k + 1) * 2 + 0;
				int nT4 = (k + 1) * 2 + 1;

				pEdge[k * 2 + 0] = pEdge[(k + 1) * 2 + 0];
				pEdge[k * 2 + 1] = pEdge[(k + 1) * 2 + 1];

				pEdge[(k + 1) * 2 + 0] = -1;
				pEdge[(k + 1) * 2 + 1] = -1;

			}
			--*nNumEdge;
			return;
		}
	}
	int n1 = *nNumEdge * 2 + 0;
	int n2 = *nNumEdge * 2 + 1;
	pEdge[*nNumEdge * 2 + 0] = nInd1;
	pEdge[*nNumEdge * 2 + 1] = nInd2;
	
	++*nNumEdge;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// �e�`�掞�̂��߂̃��C�g�x�N�g���̌v�Z
//--in---------------------------------------------
// �I�u�W�F�N�g�|�C���^
// ���C�g�x�N�g��
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::SetLightVec(OBJECT *pObj, VECTOR3 *vec)
{
	//�e�̂��߂̃}�g���b�N�X����
	VECTOR3 vectmp;
	MATRIX tmpMat;
	VECTOR3 mul;
	float *pLight;
	pLight = GetLight();
	MATRIX _m;

	vectmp.v[0] = *(pLight + 0);
	vectmp.v[1] = *(pLight + 1);
	vectmp.v[2] = *(pLight + 2);
	MatrixInv(&tmpMat, pObj->m_Matrix);
	MatrixMultiply(&_m, tmpMat, pObj->m_Matrix);
	Vec3TransformCoord(vec, tmpMat, vectmp);
	*vec = vectmp;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// �e�����̃|���S���̕`��
//--in---------------------------------------------
// �V���h�[�{�����[���\���̎󂯎��
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::DrawShadow(SHADOWVOLUME *pShadow)
{
	for(int i = 0; i < pShadow->nEdgeNum;)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glVertex3fv(pShadow->vecEdge[i++].v);
		glEnd();
	}
}
//################################################
// End of File
//################################################
