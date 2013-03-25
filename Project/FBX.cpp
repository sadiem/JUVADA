//#############################################
//
// <FBX.cpp>
// FBX�t�@�C���̃��[�h�w�b�_�[
//					�����Ɠ��@SekiyamaRumi
//
//#############################################

//===========================================
//�C���N���[�h
//===========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "FBX.h"

//===========================================
//�}�N����`
//===========================================
#define ERROR1		(-1)	//�����ُ�
#define ERROR2		(-2)	//�t�@�C��������܂���
#define ERROR3		(-3)	//�������s��
#define ERROR4		(-4)	//�ǂݍ��݃G���[

//++++++++++++++++++++++++++++++++++++++++++++
//�ǂݍ��݊֐�
//++++++++++++++++++++++++++++++++++++++++++++
int LoadFBX(FBX* pFBX, char* pszPath)
{
	//FBX�̏�����
	if(pFBX == NULL || pszPath == NULL)
		return ERROR1;
	memset(pFBX, 0, sizeof(FBX));	//�̈�𖄂߂�(������)

	//FBX�t�@�C�����J��
	FILE *fp = fopen(pszPath, "rb");	//�o�C�i���^�œǂݍ��݂����s��
	if(fp == NULL)
		return ERROR2;		//�t�@�C���̓ǂݍ��݃G���[

	//�t�@�C���T�C�Y�擾
	fseek(fp, 0L, SEEK_END);
	long lSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	//�ǂݍ��݃������m��
	char *psz = (char*)malloc(lSize + 1);
	if(psz == NULL)
	{
		fclose(fp);
		return ERROR3;		//�������s��
	}

	//�S�̓ǂݍ���
	if(fread(psz, 1, lSize, fp) < lSize)
	{
		free(psz);
		fclose(fp);
		return ERROR4;		//�ǂݍ��݃G���[
	}
	psz[lSize] = '\0';
	//X�t�@�C�������
	fclose(fp);

	//-------------------------
	//��͊J�n
	//-------------------------
	int phase = 0;
	int type;
	int nAlloc;
	const char szSep[] = " ,:\t\r\n";
	char *token = strtok(psz, szSep);
	
	while(token)
	{
		switch(phase)
		{
		case 0:	//���_���W�擪��T��
			if(strcmp(token, "Vertices") == 0)
			{
				phase = 1;
				type = 0;
				nAlloc = 100;
				pFBX->pVtx = (FBXVECTOR*)malloc(sizeof(FBXVECTOR) * nAlloc);
				break;
			}
			break;
		case 1:	//���_���W�J�n
			if(*token != '-' && !isdigit(*token))
			{
				break;
			}
			phase = 2;
		case 2:	//�����������Ԃ͒��_���W
			if(*token != '-' && !isdigit(*token))
			{
				phase = 3;
				goto INDEXSEARCH;
			}
			switch(type)
			{
			case 0:
				if(pFBX->nVtx >= nAlloc)
				{
					nAlloc += 100;
					FBXVECTOR *pNew = (FBXVECTOR*)realloc(pFBX->pVtx, sizeof(FBXVECTOR) * nAlloc);
					if(pNew)
						pFBX->pVtx = pNew;
					else
						return ERROR3;	//�������s��
				}
				pFBX-> pVtx[pFBX->nVtx].v.x = atof(token);
				type = 1;
				break;
			case 1:
				pFBX->pVtx[pFBX->nVtx].v.y = atof(token);
				type = 2;
				break;
			case 2:
				pFBX->pVtx[pFBX->nVtx].v.z = atof(token);
				type = 0;
				pFBX->nVtx++;
				break;
			}
			break;
		case 3:
INDEXSEARCH:
			if(strcmp(token, "PolygonVertexIndex") == 0)
			{
				phase = 4;
				nAlloc = 100;
				pFBX -> pIdx = (int *)malloc(sizeof(int)*nAlloc);
				break;
			}
			break;
		case 4:
			if(*token != '-' && !isdigit(*token))
			{
				break;
			}
			phase = 5;
		case 5:
			if(*token != '-' && !isdigit(*token))
			{
				phase = 6;
				break;
			}
			if(pFBX->nIdx >= nAlloc)
			{
				nAlloc += 100;
				int *pNew = (int *)realloc(pFBX->pIdx, sizeof(int)*nAlloc);
				if(pNew)
					pFBX->pIdx = pNew;
				else
					return ERROR3;	//�������[�s��
			}
			pFBX->pIdx[pFBX->nIdx] = atoi(token);
			pFBX->nIdx++;
			break;
		default: break;
		}
		token = strtok(NULL, szSep);
	}
	return 0;
}
//++++++++++++++++++++++++++++++++++++++++++++
//����֐�
//++++++++++++++++++++++++++++++++++++++++++++
void Release(FBX *pFBX)
{
	//���g���Ȃ����͉����Ȃ��Ԃ�
	if(!pFBX) return;

	//���g�����鎞
	if(pFBX->pVtx)
	{
		free(pFBX->pVtx);
		pFBX->pVtx = NULL;
	}
	pFBX->nVtx = 0;
	if(pFBX->pIdx)
	{
		free(pFBX->pIdx);
		pFBX->pIdx = NULL;
	}
	pFBX->nIdx = 0;
}