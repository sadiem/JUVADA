//#############################################
//
// <FBX.cpp>
// FBXファイルのロードヘッダー
//					＊授業内　SekiyamaRumi
//
//#############################################

//===========================================
//インクルード
//===========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "FBX.h"

//===========================================
//マクロ定義
//===========================================
#define ERROR1		(-1)	//引数異常
#define ERROR2		(-2)	//ファイルがありません
#define ERROR3		(-3)	//メモリ不足
#define ERROR4		(-4)	//読み込みエラー

//++++++++++++++++++++++++++++++++++++++++++++
//読み込み関数
//++++++++++++++++++++++++++++++++++++++++++++
int LoadFBX(FBX* pFBX, char* pszPath)
{
	//FBXの初期化
	if(pFBX == NULL || pszPath == NULL)
		return ERROR1;
	memset(pFBX, 0, sizeof(FBX));	//領域を埋める(初期化)

	//FBXファイルを開く
	FILE *fp = fopen(pszPath, "rb");	//バイナリ型で読み込みだけ行う
	if(fp == NULL)
		return ERROR2;		//ファイルの読み込みエラー

	//ファイルサイズ取得
	fseek(fp, 0L, SEEK_END);
	long lSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	//読み込みメモリ確保
	char *psz = (char*)malloc(lSize + 1);
	if(psz == NULL)
	{
		fclose(fp);
		return ERROR3;		//メモリ不足
	}

	//全体読み込み
	if(fread(psz, 1, lSize, fp) < lSize)
	{
		free(psz);
		fclose(fp);
		return ERROR4;		//読み込みエラー
	}
	psz[lSize] = '\0';
	//Xファイルを閉じる
	fclose(fp);

	//-------------------------
	//解析開始
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
		case 0:	//頂点座標先頭を探す
			if(strcmp(token, "Vertices") == 0)
			{
				phase = 1;
				type = 0;
				nAlloc = 100;
				pFBX->pVtx = (FBXVECTOR*)malloc(sizeof(FBXVECTOR) * nAlloc);
				break;
			}
			break;
		case 1:	//頂点座標開始
			if(*token != '-' && !isdigit(*token))
			{
				break;
			}
			phase = 2;
		case 2:	//数字が続く間は頂点座標
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
						return ERROR3;	//メモリ不足
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
					return ERROR3;	//メモリー不足
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
//解放関数
//++++++++++++++++++++++++++++++++++++++++++++
void Release(FBX *pFBX)
{
	//中身がない時は何もなく返す
	if(!pFBX) return;

	//中身がある時
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