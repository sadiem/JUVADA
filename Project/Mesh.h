//######################################################
//メッシュの読み込み
//------------------------------------------------------
//メタセコイアのデータからデータを抜きだす
//######################################################

#ifndef _____MESH_H______
#define _____MESH_H______

#include "Main.h"
#include "Matrix.h"
#include "Common.h"

struct MATERIAL{
	int nNo;						//マテリアル番号
	VECTOR4		Diffuse;			//ディフューズ
	float		SpecPower;			//スペキュラーの強さ
	VECTOR3		Specular;			//スペキュラー
	VECTOR3     Emissive;			//エミッション
};
//======================================================
//構造体定義
//======================================================

//メッシュ構造体
struct MESH{
	int			nVtx;				//頂点の数
	VECTOR3		*pVtx;				//頂点座標
	VECTOR3		*pVtxC;				//頂点座標
	int			nFace;				//面数
	FACE		*pFace;				//面構成
	COLOR		*pColor;			//頂点カラ―
	int			nNormal;			//法線の数	
	VECTOR3		*pNormal;			//法線
	int			nNormalIndex;		//法線インデックス数
	FACE		*pNormalIndex;		//法線インデックス
	int			nTexCoord;			//テクスチャ座標数
	VECTOR2D	*pTex;				//テクスチャ
	//マテリアル情報
	int         nMaterialNum;		//マテリアル数
	MATERIAL	*pMaterial;			//マテリアル情報ポインタ

	VECTOR3		vMin;				//最小値
	VECTOR3		vMax;				//最大値
	float		fRadius;			//半径
	VECTOR3		vVel;				//爆発時の速度

	VECTOR3		vCenter;			//メッシュデータの中心

	VECTOR3     *pTang;				//接ベクトル
	VECTOR3		*pBinormal;			//従法線
};
//======================================================
//プロトタイプ宣言
//======================================================
int LoadMesh(MESH* pMesh, char* pszPath);		//読み込み
void ReleaseMesh(MESH* pMesh);					//解放
void DrawMesh(MESH* pMesh);						//描画
void DrawMesh(MESH* pMesh, GLuint tangent);		//接ベクトル設定の描画	
void DrawMesh(MESH* pMesh, float offset);		//テクスチャアニメーション	
void CreateBoxSphireInfo(MESH* pMesh);
void SetMorph(MESH* m_Tmp, MESH &Mesh);			//モーフィングセット
void CpyVertex(MESH* m_Tmp, MESH &Mesh);		//コピー
bool Morphing(MESH* m_Tmp, MESH &MeshA, MESH &MeshB, int nFrameNow, int nMorphingStartTime, int nMorphingTime);	//モーフィング
void ReleaseVertex(MESH *Mesh);					//頂点データのみ解放
void SetDiffuse(MESH *Mesh, COLOR col);			//ディフューズ色のセット
void FlashDiffuse(MESH *Mesh, COLOR col1, COLOR col2, int nMaxTime, int nTimeNow);	//カラーアニメーション
void MeshBomb(MESH *Mesh, MESH *srcMesh);
void DrawBomb(MESH *mesh);
#endif _____MESH_H______
