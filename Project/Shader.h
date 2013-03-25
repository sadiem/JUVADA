//################################################
// <Shader.h>
//
//------------------------------------------------
// 2013/1/11
//						Akihtio Tanaka
//################################################
#ifndef _____SHADER_H_____
#define _____SHADER_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "Matrix.h"
#include <math.h>

//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================

//================================================
//クラス定義
//================================================
class CGLSL{
public:
	CGLSL();
	CGLSL(const char* vtx_file, const char* frg_file);
	CGLSL(const char* vtx_file, const char* frg_file, const char* geo_file);
	~CGLSL();
	void UseShader();		//シェーダの適用
	//void UnUseShader();		//固定機能に戻す
	void Init(const char* vtx_file, const char* frg_file);
	void Init(const char* vtx_file, const char* frg_file, const char* geo_file);
	void SetTextureUnit(int unitID);
	void SetNormalMapUnit(int unitID);
	void SetCubeMapUnit(int unitID);
	void SetCamPos(VECTOR3 vPos);
	void SetAlpha(float alpha);
	void SetPointSize(float size);
	GLint GetTangent(){ return tangent; }
	GLint GetColor(){ return color; }

private:
	HRESULT ReadShaderSource(GLuint shader, const char* filename);
	GLuint shaderProg;
	GLuint vertexShader;		//バーテックスシェーダ
	GLuint fragmentShader;		//フラグメントシェーダ
	GLuint geometoryShader;		//ジオメトリシェーダ
	GLint tangent;				//接ベクトル格納用attributeハンドル	
	GLint color;				//アルファのハンドル
};
//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================


//################################################
// End of File
//################################################
#endif _____SHADER_H_____
