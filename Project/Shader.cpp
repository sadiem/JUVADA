//################################################
// <Shader.h>
//
//------------------------------------------------
// 2012/11/20 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Shader.h"			//シェーダヘッダ

//================================================
//定数定義
//================================================

static GLuint verShader;		//頂点情報
static GLuint fragShader;		//フラグ
static GLuint pragma;			//プラグマ
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================


//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL()
{
	shaderProg		= 0;
	vertexShader	= 0;		//バーテックスシェーダ
	fragmentShader	= 0;		//フラグメントシェーダ
	
	/*Init(VTX_FILE,FRG_FILE);*/
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//頂点シェーダファイル名、フラグメントシェーダファイル名
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL(const char* vtx_file, const char* frg_file)
{
	shaderProg		= 0;
	vertexShader	= 0;		//バーテックスシェーダ
	fragmentShader	= 0;		//フラグメントシェーダ
	Init(vtx_file,frg_file);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
//--in--------------------------------------------
//頂点シェーダファイル名、
//フラグメントシェーダファイル名
//ジオメトリシェーダ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL(const char* vtx_file, const char* frg_file, const char* geo_file)
{
	shaderProg		= 0;
	vertexShader	= 0;		//バーテックスシェーダ
	fragmentShader	= 0;		//フラグメントシェーダ
	Init(vtx_file,frg_file,geo_file);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//デストラクタ
//--in--------------------------------------------
//頂点シェーダファイル名、
//フラグメントシェーダファイル名
//ジオメトリシェーダ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::~CGLSL()
{
  glDeleteProgram(shaderProg);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//シェーダのロード
//--in--------------------------------------------
//　シェーダID
//　シェーダファイル名
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CGLSL::ReadShaderSource(GLuint shader, const char* filename)
{
	FILE *fp;
	const GLchar *src;
	GLsizei	length;
	int ret;

	//ファイルのオープン
	fp = fopen(filename, "rb");
	if(fp == NULL)
		return E_FAIL;

	//ファイルサイズ取得
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);

	//メモリ確保
	src = (GLchar *)malloc(length);
	if(src == NULL)
		return E_FAIL;

	//読み込み
	fseek(fp, 0L, SEEK_SET);
	ret = (fread((void *)src, 1, length, fp) != (size_t)length);
	fclose(fp);

	//シェーダーオブジェクトへ読み込み
	glShaderSource( shader, 1, &src, &length);

	free((void *)src);


	return S_OK;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//頂点シェーダファイル名、
//フラグメントシェーダファイル名
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::Init(const char* vtx_file, const char* frg_file)
{


	//シェーダオブジェクトの作成
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	//プログラムの作成
	shaderProg = glCreateProgram();

	//読み込みとコンパイル
	if(ReadShaderSource(vertexShader, vtx_file) == S_OK)
	{
		glCompileShader(vertexShader);		//コンパイル
		glAttachShader(shaderProg, vertexShader);	//プログラムに登録
	}
	else
	{
		//エラー処理
	}

	if(ReadShaderSource(fragmentShader, frg_file) == S_OK)
	{
		glCompileShader(fragmentShader);		//コンパイル
		glAttachShader(shaderProg, fragmentShader);	//プログラムに登録
	}
	else
	{
		//エラー処理
	}


	glLinkProgram(shaderProg);
	int linked = 0;
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &linked);
	tangent = glGetAttribLocation(shaderProg, "tangent");
	color = glGetAttribLocation(shaderProg, "color");

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//頂点シェーダファイル名、
//フラグメントシェーダファイル名
//ジオメトリシェーダ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::Init(const char* vtx_file, const char* frg_file, const char* geo_file)
{


	//シェーダオブジェクトの作成
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	geometoryShader = glCreateShader(GL_GEOMETRY_SHADER);


	//プログラムの作成
	shaderProg = glCreateProgram();

	//読み込みとコンパイル
	if(ReadShaderSource(vertexShader, vtx_file) == S_OK)
	{
		glCompileShader(vertexShader);		//コンパイル
		glAttachShader(shaderProg, vertexShader);	//プログラムに登録
	}
	else
	{
		//エラー処理
	}

	if(ReadShaderSource(fragmentShader, frg_file) == S_OK)
	{
		glCompileShader(fragmentShader);		//コンパイル
		glAttachShader(shaderProg, fragmentShader);	//プログラムに登録
	}
	else
	{
		//エラー処理
	}	
	if(ReadShaderSource(geometoryShader, frg_file) == S_OK)
	{
		glCompileShader(geometoryShader);		//コンパイル
		glAttachShader(shaderProg, geometoryShader);	//プログラムに登録
	}
	else
	{
		//エラー処理
	}
	glProgramParameteriEXT(shaderProg,GL_GEOMETRY_INPUT_TYPE_EXT,GL_POLYGON);
	glProgramParameteriEXT(shaderProg,GL_GEOMETRY_OUTPUT_TYPE_EXT,GL_POLYGON);

	int temp;
	glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT,&temp);
	glProgramParameteriEXT(shaderProg,GL_GEOMETRY_VERTICES_OUT_EXT,temp);

	glLinkProgram(shaderProg);

	tangent = glGetAttribLocation(shaderProg, "tangent");

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//シェーダ有効化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::UseShader()
{
	glUseProgram(shaderProg);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//テクスチャ指定
//--in--------------------------------------------
//テクスチャID
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetTextureUnit(int UnitID)
{
	//GLint tex = glGetUniformLocation(shaderProg, "texture");
	GLint tex = glGetUniformLocation(shaderProg, "Tex");
	glUniform1i(tex, UnitID);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//ノーマルマップ指定
//--in--------------------------------------------
//テクスチャID
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetNormalMapUnit(int unitID)
{
	//GLint bump = glGetUniformLocation(shaderProg, "normalmap");
	GLint bump = glGetUniformLocation(shaderProg, "TexBump");
	glUniform1i(bump, unitID);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//キューブマップ指定
//--in--------------------------------------------
//テクスチャID
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetCubeMapUnit(int unitID)
{
	GLint envi = glGetUniformLocation(shaderProg, "envi");
	glUniform1i(envi, unitID);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//アルファ指定
//--in--------------------------------------------
//アルファ値
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetAlpha(float alpha)
{
	
	GLint nAlpha = glGetUniformLocation(shaderProg, "Alpha");
	glUniform1f(nAlpha, alpha);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//ポイントスプライトのサイズ
//--in--------------------------------------------
//サイズ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetPointSize(float size)
{
	GLint nSize = glGetUniformLocation(shaderProg, "size");
	glUniform1f(nSize, size);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//カメラ座標
//--in--------------------------------------------
//サイズ
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetCamPos(VECTOR3 vPos)
{
	GLint pos = glGetUniformLocation(shaderProg, "WorldCameraPosition");
	float fPos[4] = {vPos.x, vPos.y, vPos.z, 1.0f};
	glUniform4fv(pos, 1, fPos);
}
//################################################
// End of File
//################################################