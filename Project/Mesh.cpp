//######################################################
//���b�V���̓ǂݍ���
//------------------------------------------------------
//���^�Z�R�C�A�̃f�[�^����f�[�^�𔲂�����
//######################################################

//======================================================
//�C���N���[�h
//======================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Mesh.h"
#include "Matrix.h"
#include "ShaderMng.h"

//======================================================
//�萔��`
//======================================================
#define DATA_ERROR		(-1)	//�����G���[
#define FILE_ERROR		(-2)	//�t�@�C���G���[
#define MEMOLI_ERROR	(-3)	//�������G���[
#define LOAD_ERROR		(-4)	//�ǂݍ��݃G���[
#define MEMOLI_ERROR2	(-5)	//�������G���[
#define MEMOLI_ERROR3	(-6)	//�������G���[

//+++++++++++++++++++++++++++++++++++++++++++++++++
// X�t�@�C���̓ǂݍ���
//-------------------------------------------------
// ���^�Z�R�C���̃f�[�^�̂ݗL��
//--in---------------------------------------------
// ���b�V���|�C���^
// �t�@�C�����̃|�C���^
//--out--------------------------------------------
// ���b�V��ID
//+++++++++++++++++++++++++++++++++++++++++++++++++
int LoadMesh(MESH* pMesh, char* pszPath)		//�ǂݍ���
{
	//���b�V���̏�����
	if(pMesh == NULL || pszPath == NULL)
	{
		return DATA_ERROR;	//�������������ݒ肳��Ă܂���
	}
	memset(pMesh, 0, sizeof(MESH));		//���������̏�����

	//�t�@�C���̓W�J
	FILE* fp;
	fopen_s(&fp, pszPath, "rb");

	if(fp == NULL)
	{
		return FILE_ERROR;	//�t�@�C��������܂���
	}
	//�t�@�C���T�C�Y�擾
	fseek(fp, 0L, SEEK_END);
	long lSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	//�ǂݍ��݃������m��
	char *psz = (char*)malloc(lSize + 1);
	if(psz == NULL)
	{
		fclose(fp);
		return MEMOLI_ERROR;
	}
	//�S�̓ǂݍ���
	if(long(fread(psz, 1, lSize, fp)) < lSize)
	{
		free(psz);
		fclose(fp);
		return LOAD_ERROR;	//�ǂݍ��݃G���[
	}
	psz[lSize] = '\0';
	fclose(fp);
	//�t�@�C�������
	fclose(fp);
	//printf("%s", psz);


	//��͊J�n
	int nIndex = 0;
	int nMtrlIndex = 0;
	int nType  = 0;
	int nColorType = 0;
	int phase = 0;
	int num = 0;
	const char szSep[]	= " ,;\t\r\n";
	char* token = strtok(psz, szSep);
	while (token)
	{
		switch(phase)
		{
		case 0:
			if(strcmp(token, "template") == 0)
			{
				phase = 1;
				break;
			}
			//���_�f�[�^�y�іʂ̔����o��
			if(strcmp(token, "Mesh") == 0)
			{
				phase = 2;
				nIndex = 0;
				break;
			}
			//�}�e���A�����X�g
			if(strcmp(token, "MeshMaterialList") == 0)
			{
				phase = 12;
				nIndex = 0;
				nType = 0;
				break;
			}
			//�}�e���A�����̔��o
			if(strcmp(token, "Material") == 0)
			{
				phase = 14;
				nIndex = 0;
				nType = 0;
				num = 0;
				break;
			}
			//�@���̔����o��
			if(strcmp(token, "MeshNormals") == 0)
			{
				phase = 6;
				nIndex = 0;
				nType = 0;
				break;
			}
			//�e�N�X�`�����W
			if(strcmp(token, "MeshTextureCoords") == 0)
			{
				phase = 8;
				nIndex = 0;
				nType = 0;
				break;
			}
			//���_�J���\�̔����o��
			if(strcmp(token, "MeshVertexColors") == 0)
			{
				phase = 10;
				nIndex = 0;
				nType = 0;
				break;
			}
			break;
		case 1:
			if(strcmp(token, "}") == 0)
			{
				phase = 0;
				break;
			}
			break;
		case 2:
			if(isdigit(*token))
			{
				//���_��
				pMesh->nVtx = atoi(token);
				//���_���W�z��m��
				pMesh->pVtx = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);
				pMesh->pTang = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);		//�ڃx�N�g��
				pMesh->pBinormal = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);	//�]�@��
				if(pMesh->pVtx == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//�������s��
				}
				phase = 3;
			}
			break;
		case 3:		//���_���W�̓ǂݍ���
			switch(nType)
			{
			case 0:	//X���W
				pMesh->pVtx[nIndex].x = (float)atof(token);
				nType = 1;
				break;
			case 1:	//Y���W
				pMesh->pVtx[nIndex].y = (float)atof(token);
				nType = 2;
				break;
			case 2:	//Z���W
				pMesh->pVtx[nIndex].z = (float)atof(token);
				nIndex ++;
				if(nIndex < pMesh->nVtx)
				{
					nType = 0;
				}
				else
				{
					phase = 4;
				}
				break;
			}
			break;
		case 4:		//�ʐ��̓ǂݍ���
			if(isdigit(*token))
			{
				//�ʐ�
				pMesh->nFace = atoi(token);
				//�ʔz��m��
				pMesh->pFace = (FACE*)malloc(sizeof(FACE)* pMesh->nFace);
				if(pMesh->pFace == NULL)
				{
					free(psz);
					return MEMOLI_ERROR3;	//�������s��
				}
				phase = 5;
				nIndex = 0;
				nType = -1;
			}
			break;
		case 5:		//�ʍ\���i���_�C���f�b�N�X�̏��j
			switch(nType)
			{
			case -1:		//���_��
				pMesh->pFace[nIndex].usNum = (unsigned short)atoi(token);
				++ nType;
				break;
			default: 
				pMesh->pFace[nIndex].usIdx[nType] = (unsigned short)atoi(token);
				++ nType;
				if(nType >= pMesh->pFace[nIndex].usNum)
				{
					++ nIndex;
					if(nIndex < pMesh->nFace)
					{
						nType = -1;
					}
					else
					{
						phase = 0;
					}
				}
				break;
			}
			break;
		case 6:		//�@���f�[�^�̈�m��
			if(isdigit(*token))
			{
				//�@���̐����m��
				pMesh->nNormal = atoi(token);
				//�@���̗̈���m��
				pMesh->pNormal = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nNormal);
				phase = 7;
			}
			break;
		case 7:		//�@���f�[�^�̓ǂݍ���
			switch(nType)
			{
			case 0:	//X
				pMesh->pNormal[nIndex].x = (float)atof(token);
				nType = 1;
				break;
			case 1:	//Y
				pMesh->pNormal[nIndex].y = (float)atof(token);
				nType = 2;
				break;
			case 2:	//Z
				pMesh->pNormal[nIndex].z = (float)atof(token);
				nType = 3;
				nIndex ++;
				if(nIndex < pMesh->nNormal)
				{
					nType = 0;
				}
				else
				{
					phase = 20;
					nType = 0;
				}
				break;
			}
			break;
		case 20:		//�@���̃C���f�b�N�X���ǂݍ���
			if(isdigit(*token))
			{
				//�@���̐����m��
				pMesh->nNormalIndex = atoi(token);
				//�@���̗̈���m��
				pMesh->pNormalIndex = (FACE*)malloc(sizeof(FACE)* pMesh->nNormalIndex);
				if(pMesh->pNormalIndex == NULL)
				{
					free(psz);
					return MEMOLI_ERROR3;	//�������s��
				}
				phase = 21;
				nIndex = 0;
				nType = -1;
			}
			break;
		case 21:	//�@���̃C���f�b�N�X�ǂݍ���
			switch(nType)
			{
			case -1:		//���_��
				pMesh->pNormalIndex[nIndex].usNum = (unsigned short)atoi(token);
				++ nType;
				break;
			default: 
				pMesh->pNormalIndex[nIndex].usIdx[nType] = (unsigned short)atoi(token);
				++ nType;
				if(nType >= pMesh->pNormalIndex[nIndex].usNum)
				{
					++ nIndex;
					if(nIndex < pMesh->nNormalIndex)
					{
						nType = -1;
					}
					else
					{
						phase = 0;
					}
				}
				break;
			}

			break;

		case 8:	//�e�N�X�`����
			if(isdigit(*token))
			{
				//�@���̐����m��
				pMesh->nTexCoord = atoi(token);
				//�@���̗̈���m��
				pMesh->pTex = (VECTOR2D*)malloc(sizeof(VECTOR2D)* pMesh->nTexCoord);
				phase = 9;
			}
			break;
		case 9:	//�e�N�X�`�����W
			switch(nType)
			{
			case 0:	//X
				pMesh->pTex[nIndex].x = (float)atof(token);
				nType = 1;
				break;
			case 1:	//Y
				pMesh->pTex[nIndex].y = (float)atof(token);
				nIndex ++;
				if(nIndex < pMesh->nTexCoord)
				{
					nType = 0;
				}
				else
				{
					phase = 0;
				}
				break;
			}
			break;
		case 10:			//���_�J���\�̗̈�m��
			if(isdigit(*token))
			{
				//���_�J���\�͒��_��������

				//���_�J���[�z��m��
				pMesh->pColor = (COLOR *)malloc(sizeof(COLOR) *pMesh->nVtx);
				if(pMesh->pColor == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//�������s��
				}
				phase = 11;
			}
			break;
		case 11:			//���_�J���\�̓ǂݍ���
			switch(nType)
			{
			case 0:	//RED
				pMesh->pColor[nIndex].r = (float)atof(token);
				nType = 1;
				break;
			case 1:	//GREEN
				pMesh->pColor[nIndex].g = (float)atof(token);
				nType = 2;
				break;
			case 2:	//BLUE
				pMesh->pColor[nIndex].b = (float)atof(token);
				nType = 3;
			case 3:	//ALPHA
				pMesh->pColor[nIndex].a = (float)atof(token);
				nIndex ++;
				if(nIndex < pMesh->nVtx)
				{
					nType = 0;
				}
				else
				{
					phase = 999;	//�����I��
				}
				break;
			}
			break;
		case 12:		//�}�e���A�����̔��o
			if(isdigit(*token))
			{
				pMesh->nMaterialNum = atoi(token);	//�}�e���A�����擾
				pMesh->pMaterial = (MATERIAL *)malloc(sizeof(MATERIAL) * pMesh->nFace);
				if(pMesh->pMaterial == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//�������s��
				}
				phase = 18;	//�}�e���A���̃C���f�b�N�X���擾��
			}
			break;
		case 18:		//�C���f�b�N�X��
			if(isdigit(*token))
			{
				phase = 13;		//�C���f�b�N�X���͕K�v�Ȃ�
			}
			break;
		case 13:
			if(isdigit(*token))
			{
				pMesh->pFace[nIndex].nMaterialNo = atoi(token);
				if(nIndex >= pMesh->nFace - 1)
				{
					phase = 0;
				}else{
					nIndex ++;	//����
				}
			}
			break;
		case 14:	//�f�B�t��[�Y
			if(isdigit(*token))
			{
				pMesh->pMaterial[nMtrlIndex].Diffuse.v[num] = (float)atof(token);
				num ++;
				if(num >= 4){
					phase = 15;
					num = 0;
				}
			}
			break;	
		case 15:	//�X�y�L�����[�̍���
			if(isdigit(*token))
			{
				pMesh->pMaterial[nMtrlIndex].SpecPower = (float)atof(token);
				phase = 16;
			}
			break;
		case 16:	//�X�y�L�����[
			if(isdigit(*token))
			{
				pMesh->pMaterial[nMtrlIndex].Specular.v[num] = (float)atof(token);
				num ++;
				if(num >= 3){
					phase = 17;
					num = 0;
				}
			}
			break;
		case 17:	//�G�~�b�V����
			if(isdigit(*token))
			{
				pMesh->pMaterial[nMtrlIndex].Emissive.v[num] = (float)atof(token);
				num ++;
				if(num >= 3){
					phase = 0;
					num = 0;
					nMtrlIndex ++;
				}
			}
			break;
		default: break;
		}
		token = strtok(NULL, szSep);
	}
	//���t�@�C���C���[�W�̉��
	free(psz);

	//�Z���^�[���W��T��
	pMesh->vMin	= pMesh->pVtx[0];
	pMesh->vMax	= pMesh->vMin;
	VECTOR3 *pTmp = pMesh->pVtx;

	//--------------------------------
	//�o�E���f�B���O�X�t�B�A�쐬�p
	//--------------------------------
	for(int nLoop = 0; nLoop < pMesh->nVtx; nLoop ++ , pTmp ++)
	{
		//�ő�̐��l�ƍŏ��̐��l�����
		if(pMesh->vMax.x < pTmp->x)
			pMesh->vMax.x = pTmp->x;
		if(pMesh->vMax.y < pTmp->y)
			pMesh->vMax.y = pTmp->y;
		if(pMesh->vMax.z < pTmp->z)
			pMesh->vMax.z = pTmp->z;

		if(pMesh->vMin.x > pTmp->x)
			pMesh->vMin.x = pTmp->x;
		if(pMesh->vMin.y > pTmp->y)
			pMesh->vMin.y = pTmp->y;
		if(pMesh->vMin.z > pTmp->z)
			pMesh->vMin.z = pTmp->z;
	}
	pMesh->vCenter.x = (pMesh->vMax.x + pMesh->vMin.x) / 2.0f;	//�Z���^�[���W
	pMesh->vCenter.y = (pMesh->vMax.y + pMesh->vMin.y) / 2.0f;	//�Z���^�[���W
	pMesh->vCenter.z = (pMesh->vMax.z + pMesh->vMin.z) / 2.0f;	//�Z���^�[���W

	//���a�̔����o��
	float fLength = 0.0f;
	fLength = VecLength(pMesh->vMax - pMesh->vMin);	//���������߂�
	pMesh->fRadius = fLength / 2.0f;		//���a

	//--------------------------------
	//�ڃx�N�g�������߂�
	//--------------------------------
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)	//�ʂ̐������܂킷
	{
		//���[�J����Ԃł̍��W
		VECTOR3 p0 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[0]];
		VECTOR3 p1 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[1]];
		VECTOR3 p2 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[2]];

		//�e���_��UV
		VECTOR2D uv0 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[0]];
		VECTOR2D uv1 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[1]];
		VECTOR2D uv2 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[2]];

		//�|���S���`�揃��5��������3�������W�ɕϊ�����
		VECTOR3 CP0[3]={
			VECTOR3(p0.x, uv0.x, uv0.y),
			VECTOR3(p0.y, uv0.x, uv0.y),
			VECTOR3(p0.z, uv0.x, uv0.y)
		};
		VECTOR3 CP1[3]={
			VECTOR3(p1.x, uv1.x, uv1.y),
			VECTOR3(p1.y, uv1.x, uv1.y),
			VECTOR3(p1.z, uv1.x, uv1.y)
		};
		VECTOR3 CP2[3]={
			VECTOR3(p2.x, uv2.x, uv2.y),
			VECTOR3(p2.y, uv2.x, uv2.y),
			VECTOR3(p2.z, uv2.x, uv2.y)
		};

		VECTOR3 U, V;
		for(int nLoop2 = 0; nLoop2 < 3; nLoop2 ++)
		{
			VECTOR3 tmpV1 = CP1[nLoop2] - CP0[nLoop2];
			VECTOR3 tmpV2 = CP2[nLoop2] - CP1[nLoop2];
			VECTOR3 tmp;
			Vec3Cross(&tmp, tmpV1, tmpV2);

			if(tmp.x == 0.0f)
			{
				memset(pMesh->pTang[pMesh->pFace[nLoop].usIdx[nLoop2]].v, 0, sizeof(VECTOR3));
				memset(pMesh->pBinormal[pMesh->pFace[nLoop].usIdx[nLoop2]].v, 0, sizeof(VECTOR3));
				return -1;
			}
			U.v[nLoop2] = - tmp.y / tmp.x;
			V.v[nLoop2] = - tmp.z / tmp.x;
		}
		//���K��
		Vec3Normalize(&U, U);
		Vec3Normalize(&V, V);

		//���
		for(int nLoop3 = 0; nLoop3 < 3; nLoop3 ++)
		{
			pMesh->pTang[pMesh->pFace[nLoop].usIdx[nLoop3]] = V;
			pMesh->pBinormal[pMesh->pFace[nLoop].usIdx[nLoop3]] = U;
		}
	}


	return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���b�V���̕`��
//-------------------------------------------------
// 
//--in---------------------------------------------
// ���b�V���|�C���^
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh)					//���
{
	//�e�N�X�`���I��
	glAlphaFunc(GL_GEQUAL, 0.02f);

	//���f���`��
	//�ʂ̐��������[�v
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{
		//�}�e���A���ݒ�
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//�|���S��
		glBegin(GL_POLYGON);
		//�ʂ̒��_�����[�v
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//�e�N�X�`��
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y);
			//�@��
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//���_���W
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���b�V���̕`��
//-------------------------------------------------
// 
//--in---------------------------------------------
// ���b�V���|�C���^
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh, GLuint tangent)					//���
{
	SHADER_MNG *pShaderMng = SHADER_MNG::Instance();
	//�e�N�X�`���I��
	glAlphaFunc(GL_GEQUAL, 0.5);

	//���f���`��
	//�ʂ̐��������[�v
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{

		//�}�e���A���ݒ�
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//�|���S��
		glBegin(GL_POLYGON);
		//�ʂ̒��_�����[�v
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//�e�N�X�`��
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y);
			//�@��
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//�ڃx�N�g����ݒ�
			pShaderMng->setTangent( pMesh->pTang[pMesh->pFace[nLoop].usIdx[nLoop2]], BUMP);
			//���_���W
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���b�V���̕`��i�e�N�X�`���A�j���[�V�����j
//-------------------------------------------------
// 
//--in---------------------------------------------
// ���b�V���|�C���^
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh, float offset)					//���
{
	//SHADER_MNG *pShaderMng = SHADER_MNG::Instance();
	//�e�N�X�`���I��
	//glAlphaFunc(GL_GEQUAL, 0.5);

	//���f���`��
	//�ʂ̐��������[�v
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{

		//�}�e���A���ݒ�
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//�|���S��
		glBegin(GL_POLYGON);
		//�C���f�b�N�X�����[�v
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//�e�N�X�`��
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y + offset);
			//�@��
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//���_���W
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// ���b�V���̉��
//-------------------------------------------------
// 
//--in---------------------------------------------
// ���b�V���|�C���^
//--out--------------------------------------------
// �Ȃ�
//+++++++++++++++++++++++++++++++++++++++++++++++++
void ReleaseMesh(MESH* pMesh)					//���
{
	if(pMesh)
	{
		//���_�̉��
		if(pMesh->pVtx)
		{
			free(pMesh->pVtx);
			free(pMesh->pVtxC);
			//delete[] pMesh->pVtx;
			pMesh->pVtx = NULL;
			pMesh->pVtxC = NULL;
		}
		pMesh->nVtx = 0;

		//�ʂ̉��
		if(pMesh->pFace)
		{
			free(pMesh->pFace);
			//delete[] pMesh->pFace;
			pMesh->pFace = NULL;
		}
		//
		pMesh->nFace = 0;
		//���_�J���[�̉��
		if(pMesh->pColor)
		{
			free(pMesh->pColor);
			pMesh->pColor = NULL;
		}
		//�@���̉��
		if(pMesh->pNormal)
		{
			free(pMesh->pNormal);
			pMesh->pNormal = NULL;
		}
		pMesh->nNormal = 0;
		//�@���C���f�b�N�X�̉��
		if(pMesh->pNormalIndex)
		{
			free(pMesh->pNormalIndex);
			pMesh->pNormalIndex = NULL;
		}
		pMesh->nNormalIndex = 0;
		//�e�N�X�`�����_���W�̉��
		if(pMesh->pTex)
		{
			free(pMesh->pTex);
			pMesh->pTex = NULL;
		}
		pMesh->nTexCoord = 0;
		//�}�e���A���̉��
		if(pMesh->pMaterial)
		{
			free(pMesh->pMaterial);
			pMesh->pMaterial = NULL;
		}
		pMesh->nMaterialNum = 0;	
		//�ڃx�N�g���̉��
		if(pMesh->pTang)
		{
			free(pMesh->pTang);
			pMesh->pTang = NULL;
		}
		//�]�@���̉��
		if(pMesh->pBinormal)
		{
			free(pMesh->pBinormal);
			pMesh->pBinormal = NULL;
		}
		pMesh->vMin = 0.0f;
		pMesh->vMax = 0.0f;
		pMesh->fRadius = 0.0f;
	}

}

void SetMorph(MESH* m_Tmp, MESH &Mesh)
{
	memcpy(m_Tmp, &Mesh, sizeof(MESH));
	m_Tmp->pVtx = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh.nVtx);	//���_�̂ݗ̈��V�����m��
}
void CpyVertex(MESH* m_Tmp, MESH &Mesh)
{
	VECTOR3 *pT = m_Tmp->pVtx;
	VECTOR3 *pM = Mesh.pVtx;

	//���_����������
	for(int i = 0; i < Mesh.nVtx; i++)
	{
		*pT = *pM;

		pT++;
		pM++;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//���b�V���f�[�^���󂯎�荇���ς݃��b�V�����
//--in--------------------------------------------
// �󂯎��p���b�V��
// ���b�V��A
// ���b�V��B
// ���݃t���[��
// ���[�t�B���O�J�n����
// A����B�֕ω����郂�[�t�B���O����
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
bool Morphing(MESH* m_Tmp, MESH &MeshA, MESH &MeshB, int nFrameNow, int nMorphingStartTime, int nMorphingTime)
{
	float rate;	//����������
	VECTOR3   ver;
	VECTOR3 *pA = MeshA.pVtx;
	VECTOR3 *pB = MeshB.pVtx;
	VECTOR3 *pT = m_Tmp->pVtx;


	//���_����������珈���ł��Ȃ�
	if(MeshA.nVtx != MeshB.nVtx)
		return false;

	//���_����������
	for(int i = 0; i < MeshA.nVtx; i++)
	{
		rate = (float)(nFrameNow - nMorphingStartTime) / (float)(nMorphingTime - nMorphingStartTime) ;	
		ver = *pA + ((*pB - *pA) * rate);
		*pT = ver;

		pT++;
		pA++;
		pB++;
	}

	return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���b�V���̒��_�f�[�^�̂݉������
//--in--------------------------------------------
// ������郁�b�V��
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void ReleaseVertex(MESH *Mesh)					//���_�f�[�^�̂݉��
{
	if(Mesh->pVtx)
	{
		free(Mesh->pVtx);
		Mesh->pVtx = NULL;
	}
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//DIFFUSE�F�̓_�ł�����
// �����ƌ��̃f�[�^�͎����Ă�������
//--in--------------------------------------------
// ���������郁�b�V��
// �F1�@�u�������O
// �F2	�u��������
// ���݃t���[��
// ���b�ԂŐF��ς��邩
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void SetDiffuse(MESH *Mesh, COLOR col)
{
	MATERIAL *tmp = Mesh->pMaterial;
	for(int i = 0; i < Mesh->nMaterialNum; i ++)
	{
		tmp->Diffuse.x = col.r;
		tmp->Diffuse.y = col.g;
		tmp->Diffuse.z = col.b;

		tmp++;	
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//DIFFUSE�F�̓_�ł�����
// �����ƌ��̃f�[�^�͎����Ă�������
//--in--------------------------------------------
// ���������郁�b�V��
// �F1�@�u�������O
// �F2	�u��������
// ���݃t���[��
// ���b�ԂŐF��ς��邩
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void FlashDiffuse(MESH *Mesh, COLOR col1, COLOR col2, int nMaxTime, int nTimeNow)
{
	MATERIAL *tmp = Mesh->pMaterial;
	float   rate;

	for(int i = 0; i < Mesh->nMaterialNum; i ++)
	{
		rate = (float)nTimeNow / nMaxTime;	//
		tmp->Diffuse.x = col1.r + (col2.r - col1.r) * rate;
		tmp->Diffuse.y = col1.g + (col2.g - col1.g) * rate;
		tmp->Diffuse.z = col1.b + (col2.b - col1.b) * rate;

		tmp++;	
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���b�V���̔���
//--in--------------------------------------------
// ���������郁�b�V�� (�ۊǂ��Ă�������)
//--out-------------------------------------------
// �Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void MeshBomb(MESH *Mesh, MESH *SrcMesh)
{
	Mesh->nVtx = SrcMesh->nFace * 3;		//���_���͖ʐ��~�R
	Mesh->pVtx = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh->nVtx);	//���_�̂ݗ̈��V�����m��
	Mesh->pNormal = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh->nVtx);
	Mesh->pTex = (VECTOR2D*)malloc(sizeof (VECTOR2D) * Mesh->nVtx);
	Mesh->nFace = SrcMesh->nFace;

	int k = 0;
	for(int i = 0; i < SrcMesh->nFace; i++)//�ʐ����[�v
	{
		for(int j = 0; j < 3; j++)//�C���f�b�N�X���[�v
		{
			Mesh->pVtx[k] = SrcMesh->pVtx[SrcMesh->pFace[i].usIdx[j]];
			//Mesh->pNormal[k] = SrcMesh->pNormal[SrcMesh->pNormalIndex[i].usIdx[j]];
			Mesh->pTex[k] = SrcMesh->pTex[SrcMesh->pFace[i].usIdx[j]];
			k++;
		}
		//�@���̌v�Z
		VECTOR3 v1, v2, result;
		v1 = Mesh->pVtx[k - 2] - Mesh->pVtx[k - 3];
		v2 = Mesh->pVtx[k - 1] - Mesh->pVtx[k - 3];
		Vec3Cross(&result, v1, v2);
		Vec3Normalize(&result, result);
		Mesh->pNormal[k - 1] = result;
		Mesh->pNormal[k - 2] = result;
		Mesh->pNormal[k - 3] = result;
		
	}
}
//�����`��
void DrawBomb(MESH *mesh)
{
	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̔z���L���ɂ��� */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̏ꏊ���w�肷�� */
	glVertexPointer(3, GL_FLOAT, 0, mesh->pVtx );
	glNormalPointer(GL_FLOAT, 0, mesh->pNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mesh->pTex);

	/* ���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷�� */
	//glEnable(GL_TRIANGLES);
	glDrawArrays(GL_TRIANGLES, 0, mesh->nVtx);
	//glDisable(GL_TRIANGLES);


	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̔z��𖳌��ɂ��� */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

