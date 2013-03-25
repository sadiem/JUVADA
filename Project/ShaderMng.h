//################################################
// <ShaderMng.h>
//
//------------------------------------------------
// 2012/12/11 ~
//						SekiyamaRumi
//################################################
#ifndef _____SHADER_MNG_H_____
#define _____SHADER_MNG_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "Shader.h"			//シェーダ
#include "Matrix.h"

//================================================
//定数定義
//================================================
enum SHADE_TYPE
{
	PHONG,		//フォン
	BUMP,		//バンプ
//	CUBE,		//キューブマップ生成用シェーダ
	POINTSPL,	//ポイントスプライト
	COOK,		//クックトランス
	REFLECT,
	MAX_SHADER,

	//SHADER_NUM = BUMP + 2	//シェーダの数
};

//================================================
//クラス定義
//================================================
class SHADER_MNG
{
public:
	static SHADER_MNG* Instance()
	{
		static SHADER_MNG Inst;
		return &Inst;
	};
private:
	SHADER_MNG();
	~SHADER_MNG();
	CGLSL *pShader[MAX_SHADER];

public:
	void UseShader(int type);		//シェーダータイプとテクスチャユニットを指定
	void SetTexUnit(int type, int unit);
	void SetBumpUnit(int type,int unitBump);
	void SetCubeUnit(int type,int unitEnvi);
	void SetAlpha(int type,float alpha);
	void SetPSize(int type, float size);
	void SetCamPos(int type, VECTOR3 vPos);
	void UnUseShader();
	void Init();
	void setTangent(VECTOR3 v, int type);
	void setColor(VECTOR3 v, float alpha, int type);
	GLint tangent;				//接ベクトル格納用attributeハンドル
};

//################################################
// End of File
//################################################
#endif _____SHADER_MNG_H_____
