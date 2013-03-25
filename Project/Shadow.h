//################################################
// <Shadow.cpp>
// 影を付ける
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
//################################################
#ifndef _____SHADOW_H_____
#define _____SHADOW_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Include.h"
#include "Matrix.h"
#include "Common.h"
#include "Mesh.h"		//メッシュヘッダ
#include "Camera.h"
#include "Object.h"		//オブジェクト
//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================

//================================================
//構造体定義
//================================================
//================================================
//グローバル変数
//================================================

//================================================
//クラス定義
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
	void CreateShadow(OBJECT *pModel);			//呼び出し用


private:
	HRESULT CreateEdge(SHADOWVOLUME *pShadow, MESH *pMesh, float *pLight);	//エッジリスト生成
	void AddEdge(int *pEdge, int *nNumEdge, int nInd1, int nInd2);			//エッジリスト追加
	void RenderStencil(void);
	void DrawShadow(SHADOWVOLUME *pShadow);
	void SetLightVec(OBJECT *pObj, VECTOR3 *vec);
	
};
//################################################
// End of File
//################################################
#endif _____SHADOW_H_____

