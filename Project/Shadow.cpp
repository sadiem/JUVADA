//################################################
// <Shadow.cpp>
//
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Shadow.h"
#include "Graphic.h"

#define SHADOW_LENGTH (1000)
int g_nCntFace = 0;
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
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
//デストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
SHADOW::~SHADOW()
{

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//シャドウ生成
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::CreateShadow(OBJECT *pModel)
{
	VECTOR3 vec;	//影描画時の作業用ベクトル

	//シャドウ用メッシュの生成
	SetLightVec(pModel, &vec);
	HRESULT nEra = CreateEdge(&pModel->m_Shadow, pModel->m_Mesh, &vec.v[0]);

	//初期化
	glLoadIdentity();
	gluLookAt(p_Camera->ViewPos.x, p_Camera->ViewPos.y, p_Camera->ViewPos.z, p_Camera->ViewCent.x, p_Camera->ViewCent.y, p_Camera->ViewCent.z, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE, GL_FALSE,GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
//	glDisable(GL_FOG);

	//表面だけ描く
	glStencilFunc(GL_ALWAYS, 0, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);			//時計回り＝表
	glPushMatrix();
	glTranslatef((GLfloat)pModel->m_Pos.x, (GLfloat)pModel->m_Pos.y, (GLfloat)pModel->m_Pos.z);	
	glRotatef(((GLfloat)pModel->m_Rad * 180 / M_PI), (GLfloat)0.0f, (GLfloat)1.0f , (GLfloat)0.0f);	//Y軸回転
	glScalef(pModel->m_ScaleRate, pModel->m_ScaleRate, pModel->m_ScaleRate);
	DrawShadow(&pModel->m_Shadow);
	//裏面を描く
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glFrontFace(GL_CCW);		//半時計まわり＝裏
	DrawShadow(&pModel->m_Shadow);
	glPopMatrix();

	//設定を戻す
	glFrontFace(GL_CCW);
	glColorMask(1, 1, 1, 1);
	glDepthMask(1);

	//-----------------------------------------------
	//影を付ける
	//-----------------------------------------------
	glStencilFunc(GL_NOTEQUAL, 0, ~0);
	glEnable(GL_BLEND);										//透過
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		//透過処理設定
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);						//色
	glDisable(GL_DEPTH_TEST);								//デプステスト無効化
	glDisable(GL_CULL_FACE);								//裏面は描かない

	//影のステンシル部分を描画
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

	//処理設定を元に戻す
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
	//glEnable(GL_FOG);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//シャドウボリュームのためのポリゴン生成
//--in--------------------------------------------
// メッシュデータ
// 変換マトリックスデータ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT SHADOW::CreateEdge(SHADOWVOLUME *pShadow, MESH *pMesh, float *pLight)
{
	//ライトをベクトル表記に直す
	VECTOR3 Light;
	Light.v[0] = *(pLight + 0);
	Light.v[1] = *(pLight + 1);
	Light.v[2] = *(pLight + 2);

	//ワーク用エッジリストの作成…インデックス番号格納
	int *pEdge = new int[pMesh->nFace * 6];		//1ポリゴン6頂点

	if(pEdge == NULL)
		return S_FALSE;

	int nNumEdge = 0;	//エッジ数
	int i = 0;
	//光源を向いている面を検索
	for(i = 0; i < pMesh->nFace; i++)	//面の数だけ回す
	{
		//面のインデックス番号保持
		int faseIdx[3];
		faseIdx[0] = pMesh->pFace[i].usIdx[0];
		faseIdx[1] = pMesh->pFace[i].usIdx[1];
		faseIdx[2] = pMesh->pFace[i].usIdx[2];

		//頂点を取得
		VECTOR3 vec0 = pMesh->pVtx[pMesh->pFace[i].usIdx[0]];
		VECTOR3 vec1 = pMesh->pVtx[pMesh->pFace[i].usIdx[1]];
		VECTOR3 vec2 = pMesh->pVtx[pMesh->pFace[i].usIdx[2]];

		//------------------------------------
		//光源を向いている面を検索
		//------------------------------------
		//面を構成する編を生成
		VECTOR3 cross1 = vec2 - vec0;
		VECTOR3 cross2 = vec1 - vec0;

		//2つの辺の外積から面の法線を作成
		VECTOR3 normal;
		Vec3Cross(&normal, cross1, cross2);

		float n;
		n = Vec3Dot(Light, normal);
		//面の法線とライトベクトルの内積が-の場合辺を追加
		if(Vec3Dot(Light, normal) <= 0)
		{
			g_nCntFace ++;
			//辺を追加
			AddEdge(pEdge, &nNumEdge, faseIdx[0], faseIdx[1]);
			AddEdge(pEdge, &nNumEdge, faseIdx[1], faseIdx[2]);
			AddEdge(pEdge, &nNumEdge, faseIdx[2], faseIdx[0]);
		}
	}

	//シャドウボリュームの側面の追加
	pShadow->nEdgeNum = 0;
	for(i = 0; i < nNumEdge; i ++)	//エッジの数だけ回す
	{
		VECTOR3 v1, v2;
		VECTOR3 v3, v4;
		//頂点登録
		v1 = pMesh->pVtx[pEdge[i * 2 + 0]];
		v2 = pMesh->pVtx[pEdge[i * 2 + 1]];
		v3 = v1 - Light * SHADOW_LENGTH;
		v4 = v2 - Light * SHADOW_LENGTH;

		//矩形追加 -- トライアングルリスト
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v1;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v2;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v3;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v1;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v3;
		pShadow->vecEdge[pShadow->nEdgeNum ++] = v4;
	}
	//ワーク用エッジリストの解放
	if(pEdge)
		delete pEdge;
	pEdge = NULL;

	return S_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//エッジリストの追加
//--in--------------------------------------------
// エッジリスト(インデックスリスト)
// 今の面数(書き換えます)
// 登録予定インデックス１
// 登録予定インデックス２
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::AddEdge(int *pEdge, int *nNumEdge, int nInd1, int nInd2)
{
	static int nCnt = 0;
	//現在の登録エッジの分だけ回す
	for(int i = 0; i < *nNumEdge; i ++)
	{
		int L1 = i * 2 + 0;
		int L2 = i * 2 + 1;
		//エッジ共通
		if(((pEdge[i * 2 + 0] == nInd1) && (pEdge[i * 2 + 1] == nInd2)) || ((pEdge[i * 2 + 0] == nInd2) && (pEdge[i * 2 + 1] == nInd1)))
		{
			nCnt ++;
			//保存エッジを詰める
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
// 影描画時のためのライトベクトルの計算
//--in---------------------------------------------
// オブジェクトポインタ
// ライトベクトル
//--out--------------------------------------------
// なし
//+++++++++++++++++++++++++++++++++++++++++++++++++
void SHADOW::SetLightVec(OBJECT *pObj, VECTOR3 *vec)
{
	//影のためのマトリックス生成
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
// 影部分のポリゴンの描画
//--in---------------------------------------------
// シャドーボリューム構造体受け取り
//--out--------------------------------------------
// なし
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
