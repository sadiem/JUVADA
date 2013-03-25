//######################################################
//メッシュの読み込み
//------------------------------------------------------
//メタセコイアのデータからデータを抜きだす
//######################################################

//======================================================
//インクルード
//======================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Mesh.h"
#include "Matrix.h"
#include "ShaderMng.h"

//======================================================
//定数定義
//======================================================
#define DATA_ERROR		(-1)	//引数エラー
#define FILE_ERROR		(-2)	//ファイルエラー
#define MEMOLI_ERROR	(-3)	//メモリエラー
#define LOAD_ERROR		(-4)	//読み込みエラー
#define MEMOLI_ERROR2	(-5)	//メモリエラー
#define MEMOLI_ERROR3	(-6)	//メモリエラー

//+++++++++++++++++++++++++++++++++++++++++++++++++
// Xファイルの読み込み
//-------------------------------------------------
// メタセコイヤのデータのみ有効
//--in---------------------------------------------
// メッシュポインタ
// ファイル名のポインタ
//--out--------------------------------------------
// メッシュID
//+++++++++++++++++++++++++++++++++++++++++++++++++
int LoadMesh(MESH* pMesh, char* pszPath)		//読み込み
{
	//メッシュの初期化
	if(pMesh == NULL || pszPath == NULL)
	{
		return DATA_ERROR;	//引数が正しく設定されてません
	}
	memset(pMesh, 0, sizeof(MESH));		//メモリ内の初期化

	//ファイルの展開
	FILE* fp;
	fopen_s(&fp, pszPath, "rb");

	if(fp == NULL)
	{
		return FILE_ERROR;	//ファイルがありません
	}
	//ファイルサイズ取得
	fseek(fp, 0L, SEEK_END);
	long lSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	//読み込みメモリ確保
	char *psz = (char*)malloc(lSize + 1);
	if(psz == NULL)
	{
		fclose(fp);
		return MEMOLI_ERROR;
	}
	//全体読み込み
	if(long(fread(psz, 1, lSize, fp)) < lSize)
	{
		free(psz);
		fclose(fp);
		return LOAD_ERROR;	//読み込みエラー
	}
	psz[lSize] = '\0';
	fclose(fp);
	//ファイルを閉じる
	fclose(fp);
	//printf("%s", psz);


	//解析開始
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
			//頂点データ及び面の抜き出し
			if(strcmp(token, "Mesh") == 0)
			{
				phase = 2;
				nIndex = 0;
				break;
			}
			//マテリアルリスト
			if(strcmp(token, "MeshMaterialList") == 0)
			{
				phase = 12;
				nIndex = 0;
				nType = 0;
				break;
			}
			//マテリアル情報の抜出
			if(strcmp(token, "Material") == 0)
			{
				phase = 14;
				nIndex = 0;
				nType = 0;
				num = 0;
				break;
			}
			//法線の抜き出し
			if(strcmp(token, "MeshNormals") == 0)
			{
				phase = 6;
				nIndex = 0;
				nType = 0;
				break;
			}
			//テクスチャ座標
			if(strcmp(token, "MeshTextureCoords") == 0)
			{
				phase = 8;
				nIndex = 0;
				nType = 0;
				break;
			}
			//頂点カラ―の抜き出し
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
				//頂点数
				pMesh->nVtx = atoi(token);
				//頂点座標配列確保
				pMesh->pVtx = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);
				pMesh->pTang = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);		//接ベクトル
				pMesh->pBinormal = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nVtx);	//従法線
				if(pMesh->pVtx == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//メモリ不足
				}
				phase = 3;
			}
			break;
		case 3:		//頂点座標の読み込み
			switch(nType)
			{
			case 0:	//X座標
				pMesh->pVtx[nIndex].x = (float)atof(token);
				nType = 1;
				break;
			case 1:	//Y座標
				pMesh->pVtx[nIndex].y = (float)atof(token);
				nType = 2;
				break;
			case 2:	//Z座標
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
		case 4:		//面数の読み込み
			if(isdigit(*token))
			{
				//面数
				pMesh->nFace = atoi(token);
				//面配列確保
				pMesh->pFace = (FACE*)malloc(sizeof(FACE)* pMesh->nFace);
				if(pMesh->pFace == NULL)
				{
					free(psz);
					return MEMOLI_ERROR3;	//メモリ不足
				}
				phase = 5;
				nIndex = 0;
				nType = -1;
			}
			break;
		case 5:		//面構造（頂点インデックスの情報）
			switch(nType)
			{
			case -1:		//頂点数
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
		case 6:		//法線データ領域確保
			if(isdigit(*token))
			{
				//法線の数を確保
				pMesh->nNormal = atoi(token);
				//法線の領域を確保
				pMesh->pNormal = (VECTOR3*)malloc(sizeof(VECTOR3)* pMesh->nNormal);
				phase = 7;
			}
			break;
		case 7:		//法線データの読み込み
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
		case 20:		//法線のインデックス数読み込み
			if(isdigit(*token))
			{
				//法線の数を確保
				pMesh->nNormalIndex = atoi(token);
				//法線の領域を確保
				pMesh->pNormalIndex = (FACE*)malloc(sizeof(FACE)* pMesh->nNormalIndex);
				if(pMesh->pNormalIndex == NULL)
				{
					free(psz);
					return MEMOLI_ERROR3;	//メモリ不足
				}
				phase = 21;
				nIndex = 0;
				nType = -1;
			}
			break;
		case 21:	//法線のインデックス読み込み
			switch(nType)
			{
			case -1:		//頂点数
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

		case 8:	//テクスチャ数
			if(isdigit(*token))
			{
				//法線の数を確保
				pMesh->nTexCoord = atoi(token);
				//法線の領域を確保
				pMesh->pTex = (VECTOR2D*)malloc(sizeof(VECTOR2D)* pMesh->nTexCoord);
				phase = 9;
			}
			break;
		case 9:	//テクスチャ座標
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
		case 10:			//頂点カラ―の領域確保
			if(isdigit(*token))
			{
				//頂点カラ―は頂点数分存在

				//頂点カラー配列確保
				pMesh->pColor = (COLOR *)malloc(sizeof(COLOR) *pMesh->nVtx);
				if(pMesh->pColor == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//メモリ不足
				}
				phase = 11;
			}
			break;
		case 11:			//頂点カラ―の読み込み
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
					phase = 999;	//処理終了
				}
				break;
			}
			break;
		case 12:		//マテリアル情報の抜出
			if(isdigit(*token))
			{
				pMesh->nMaterialNum = atoi(token);	//マテリアル数取得
				pMesh->pMaterial = (MATERIAL *)malloc(sizeof(MATERIAL) * pMesh->nFace);
				if(pMesh->pMaterial == NULL)
				{
					free(psz);
					return MEMOLI_ERROR2;	//メモリ不足
				}
				phase = 18;	//マテリアルのインデックス数取得へ
			}
			break;
		case 18:		//インデックス数
			if(isdigit(*token))
			{
				phase = 13;		//インデックス数は必要なし
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
					nIndex ++;	//次へ
				}
			}
			break;
		case 14:	//ディフｭーズ
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
		case 15:	//スペキュラーの高さ
			if(isdigit(*token))
			{
				pMesh->pMaterial[nMtrlIndex].SpecPower = (float)atof(token);
				phase = 16;
			}
			break;
		case 16:	//スペキュラー
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
		case 17:	//エミッション
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
	//ｘファイルイメージの解放
	free(psz);

	//センター座標を探す
	pMesh->vMin	= pMesh->pVtx[0];
	pMesh->vMax	= pMesh->vMin;
	VECTOR3 *pTmp = pMesh->pVtx;

	//--------------------------------
	//バウンディングスフィア作成用
	//--------------------------------
	for(int nLoop = 0; nLoop < pMesh->nVtx; nLoop ++ , pTmp ++)
	{
		//最大の数値と最小の数値を取る
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
	pMesh->vCenter.x = (pMesh->vMax.x + pMesh->vMin.x) / 2.0f;	//センター座標
	pMesh->vCenter.y = (pMesh->vMax.y + pMesh->vMin.y) / 2.0f;	//センター座標
	pMesh->vCenter.z = (pMesh->vMax.z + pMesh->vMin.z) / 2.0f;	//センター座標

	//半径の抜き出し
	float fLength = 0.0f;
	fLength = VecLength(pMesh->vMax - pMesh->vMin);	//長さを求める
	pMesh->fRadius = fLength / 2.0f;		//半径

	//--------------------------------
	//接ベクトルを求める
	//--------------------------------
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)	//面の数だけまわす
	{
		//ローカル空間での座標
		VECTOR3 p0 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[0]];
		VECTOR3 p1 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[1]];
		VECTOR3 p2 = pMesh->pVtx[pMesh->pFace[nLoop].usIdx[2]];

		//各頂点のUV
		VECTOR2D uv0 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[0]];
		VECTOR2D uv1 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[1]];
		VECTOR2D uv2 = pMesh->pTex[pMesh->pFace[nLoop].usIdx[2]];

		//ポリゴン描画純に5次元から3次元座標に変換する
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
		//正規化
		Vec3Normalize(&U, U);
		Vec3Normalize(&V, V);

		//代入
		for(int nLoop3 = 0; nLoop3 < 3; nLoop3 ++)
		{
			pMesh->pTang[pMesh->pFace[nLoop].usIdx[nLoop3]] = V;
			pMesh->pBinormal[pMesh->pFace[nLoop].usIdx[nLoop3]] = U;
		}
	}


	return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// メッシュの描画
//-------------------------------------------------
// 
//--in---------------------------------------------
// メッシュポインタ
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh)					//解放
{
	//テクスチャオン
	glAlphaFunc(GL_GEQUAL, 0.02f);

	//モデル描画
	//面の数だけループ
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{
		//マテリアル設定
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//ポリゴン
		glBegin(GL_POLYGON);
		//面の頂点分ループ
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//テクスチャ
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y);
			//法線
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//頂点座標
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// メッシュの描画
//-------------------------------------------------
// 
//--in---------------------------------------------
// メッシュポインタ
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh, GLuint tangent)					//解放
{
	SHADER_MNG *pShaderMng = SHADER_MNG::Instance();
	//テクスチャオン
	glAlphaFunc(GL_GEQUAL, 0.5);

	//モデル描画
	//面の数だけループ
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{

		//マテリアル設定
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//ポリゴン
		glBegin(GL_POLYGON);
		//面の頂点分ループ
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//テクスチャ
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y);
			//法線
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//接ベクトルを設定
			pShaderMng->setTangent( pMesh->pTang[pMesh->pFace[nLoop].usIdx[nLoop2]], BUMP);
			//頂点座標
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// メッシュの描画（テクスチャアニメーション）
//-------------------------------------------------
// 
//--in---------------------------------------------
// メッシュポインタ
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void DrawMesh(MESH* pMesh, float offset)					//解放
{
	//SHADER_MNG *pShaderMng = SHADER_MNG::Instance();
	//テクスチャオン
	//glAlphaFunc(GL_GEQUAL, 0.5);

	//モデル描画
	//面の数だけループ
	for(int nLoop = 0; nLoop < pMesh->nFace; nLoop ++)
	{

		//マテリアル設定
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].SpecPower);
		GLfloat fD[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.z, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Diffuse.w};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fD);
		GLfloat fS[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Specular.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fS);
		GLfloat fA[] = {pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.x, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.y, pMesh->pMaterial[pMesh->pFace[nLoop].nMaterialNo].Emissive.z, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fA);

		//ポリゴン
		glBegin(GL_POLYGON);
		//インデックス分ループ
		for(int nLoop2 = 0; nLoop2 < pMesh->pFace[nLoop].usNum; nLoop2 ++)
		{
			//テクスチャ
			glTexCoord2f(pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pTex[pMesh->pFace[nLoop].usIdx[nLoop2]].y + offset);
			//法線
			glNormal3f(pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].x, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].y, pMesh->pNormal[pMesh->pNormalIndex[nLoop].usIdx[nLoop2]].z);
			//頂点座標
			glVertex3f(pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].x, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].y, pMesh->pVtx[pMesh->pFace[nLoop].usIdx[nLoop2]].z);
		}
		glEnd();
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++
// メッシュの解放
//-------------------------------------------------
// 
//--in---------------------------------------------
// メッシュポインタ
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void ReleaseMesh(MESH* pMesh)					//解放
{
	if(pMesh)
	{
		//頂点の解放
		if(pMesh->pVtx)
		{
			free(pMesh->pVtx);
			free(pMesh->pVtxC);
			//delete[] pMesh->pVtx;
			pMesh->pVtx = NULL;
			pMesh->pVtxC = NULL;
		}
		pMesh->nVtx = 0;

		//面の解放
		if(pMesh->pFace)
		{
			free(pMesh->pFace);
			//delete[] pMesh->pFace;
			pMesh->pFace = NULL;
		}
		//
		pMesh->nFace = 0;
		//頂点カラーの解放
		if(pMesh->pColor)
		{
			free(pMesh->pColor);
			pMesh->pColor = NULL;
		}
		//法線の解放
		if(pMesh->pNormal)
		{
			free(pMesh->pNormal);
			pMesh->pNormal = NULL;
		}
		pMesh->nNormal = 0;
		//法線インデックスの解放
		if(pMesh->pNormalIndex)
		{
			free(pMesh->pNormalIndex);
			pMesh->pNormalIndex = NULL;
		}
		pMesh->nNormalIndex = 0;
		//テクスチャ頂点座標の解放
		if(pMesh->pTex)
		{
			free(pMesh->pTex);
			pMesh->pTex = NULL;
		}
		pMesh->nTexCoord = 0;
		//マテリアルの解放
		if(pMesh->pMaterial)
		{
			free(pMesh->pMaterial);
			pMesh->pMaterial = NULL;
		}
		pMesh->nMaterialNum = 0;	
		//接ベクトルの解放
		if(pMesh->pTang)
		{
			free(pMesh->pTang);
			pMesh->pTang = NULL;
		}
		//従法線の解放
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
	m_Tmp->pVtx = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh.nVtx);	//頂点のみ領域を新しく確保
}
void CpyVertex(MESH* m_Tmp, MESH &Mesh)
{
	VECTOR3 *pT = m_Tmp->pVtx;
	VECTOR3 *pM = Mesh.pVtx;

	//頂点数分だけ回す
	for(int i = 0; i < Mesh.nVtx; i++)
	{
		*pT = *pM;

		pT++;
		pM++;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//メッシュデータを受け取り合成済みメッシュ作る
//--in--------------------------------------------
// 受け取り用メッシュ
// メッシュA
// メッシュB
// 現在フレーム
// モーフィング開始時間
// AからBへ変化するモーフィング時間
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
bool Morphing(MESH* m_Tmp, MESH &MeshA, MESH &MeshB, int nFrameNow, int nMorphingStartTime, int nMorphingTime)
{
	float rate;	//動かす割合
	VECTOR3   ver;
	VECTOR3 *pA = MeshA.pVtx;
	VECTOR3 *pB = MeshB.pVtx;
	VECTOR3 *pT = m_Tmp->pVtx;


	//頂点数が違ったら処理できない
	if(MeshA.nVtx != MeshB.nVtx)
		return false;

	//頂点数分だけ回す
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
//メッシュの頂点データのみ解放する
//--in--------------------------------------------
// 解放するメッシュ
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void ReleaseVertex(MESH *Mesh)					//頂点データのみ解放
{
	if(Mesh->pVtx)
	{
		free(Mesh->pVtx);
		Mesh->pVtx = NULL;
	}
}


//++++++++++++++++++++++++++++++++++++++++++++++++
//DIFFUSE色の点滅をする
// ちゃんと元のデータは持っておくこと
//--in--------------------------------------------
// 書き換えるメッシュ
// 色1　置き換え前
// 色2	置き換え後
// 現在フレーム
// 何秒間で色を変えるか
//--out-------------------------------------------
// なし
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
//DIFFUSE色の点滅をする
// ちゃんと元のデータは持っておくこと
//--in--------------------------------------------
// 書き換えるメッシュ
// 色1　置き換え前
// 色2	置き換え後
// 現在フレーム
// 何秒間で色を変えるか
//--out-------------------------------------------
// なし
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
//メッシュの爆発
//--in--------------------------------------------
// 書き換えるメッシュ (保管しておくこと)
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void MeshBomb(MESH *Mesh, MESH *SrcMesh)
{
	Mesh->nVtx = SrcMesh->nFace * 3;		//頂点数は面数×３
	Mesh->pVtx = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh->nVtx);	//頂点のみ領域を新しく確保
	Mesh->pNormal = (VECTOR3*)malloc(sizeof (VECTOR3) * Mesh->nVtx);
	Mesh->pTex = (VECTOR2D*)malloc(sizeof (VECTOR2D) * Mesh->nVtx);
	Mesh->nFace = SrcMesh->nFace;

	int k = 0;
	for(int i = 0; i < SrcMesh->nFace; i++)//面数ループ
	{
		for(int j = 0; j < 3; j++)//インデックスループ
		{
			Mesh->pVtx[k] = SrcMesh->pVtx[SrcMesh->pFace[i].usIdx[j]];
			//Mesh->pNormal[k] = SrcMesh->pNormal[SrcMesh->pNormalIndex[i].usIdx[j]];
			Mesh->pTex[k] = SrcMesh->pTex[SrcMesh->pFace[i].usIdx[j]];
			k++;
		}
		//法線の計算
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
//爆発描画
void DrawBomb(MESH *mesh)
{
	/* 頂点データ，法線データ，テクスチャ座標の配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/* 頂点データ，法線データ，テクスチャ座標の場所を指定する */
	glVertexPointer(3, GL_FLOAT, 0, mesh->pVtx );
	glNormalPointer(GL_FLOAT, 0, mesh->pNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mesh->pTex);

	/* 頂点のインデックスの場所を指定して図形を描画する */
	//glEnable(GL_TRIANGLES);
	glDrawArrays(GL_TRIANGLES, 0, mesh->nVtx);
	//glDisable(GL_TRIANGLES);


	/* 頂点データ，法線データ，テクスチャ座標の配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

