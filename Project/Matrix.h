//################################################
//<Matrix.h>
// 変換マトリックス作成
//------------------------------------------------
//座標変換
//2012/06/15 ~
//						SekiyamaRumi
//################################################
#ifndef ______MATRIX_H_____
#define ______MATRIX_H_____

#include <GL/glew.h>		//OpenGL 関連のヘッダ
#include <GL/wglew.h>		//OpenGL 関連のヘッダ
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#include <math.h>		//

//====================================================
// プロトタイプ宣言
//====================================================
class MATRIX;
class VECTOR3;
void MatrixIdentity(MATRIX *m);														//マトリックスの初期化
void MatrixTranslation(MATRIX *m, float fX, float fY, float fZ);					//平行移動
void MatrixScaling(MATRIX *m, float fSx, float fSy, float fSz);						//拡大縮小
void MatrixRotationX(MATRIX *m, float fPitch);										//X軸回転
void MatrixRotationY(MATRIX *m, float fYaw);										//Y軸回転
void MatrixRotationZ(MATRIX *m, float fRoll);										//Z軸回転
void MatrixRotationYawPitchRoll(MATRIX *m, float fYaw, float fPitch, float fRoll);	//行列の合成処理
void MatrixRotationAxis(MATRIX *m, VECTOR3 v, float fAngle);						//任意軸回転の処理
void MatrixMultiply(MATRIX *m, MATRIX mL, MATRIX mR);								//掛け算
void MatrixInv(MATRIX *mat, MATRIX m);												//逆行列
void MatrixTransposition(MATRIX *mat, MATRIX &m);									//転置行列

void Vec3Identity(VECTOR3 *vec);													//初期化
void Vec3TransformCoord(VECTOR3 *v, MATRIX m, VECTOR3 vS);							//移動成分含みの回転処理
void Vec3TransformNormal(VECTOR3 v, MATRIX m, VECTOR3 vR);							//回転成分のみの回転処理
void Vec3Cross(VECTOR3 *v, VECTOR3 vL, VECTOR3 vR);									//外積
float Vec3Dot(VECTOR3 vL, VECTOR3 vR);												//内積
void Vec3Normalize(VECTOR3* v, VECTOR3& vR);										//単位行列
float Vec3Length(VECTOR3 vR, VECTOR3 vL);											//２つのベクドルの大きさ
float VectoVec(VECTOR3 vec1, VECTOR3 vec2);											//ベクトル１と２から回転角を返す
float VecLength(VECTOR3 vec);														//ベクトルの大きさ								
void VecScale(VECTOR3 *vec, float fScale);											//ベクトルにスカラ値をかける
void VecScaleM(VECTOR3 *vec, float fScale);											//ベクトルを割る
void VecRot(VECTOR3 *vec, float fRadius);										//単位ベクトル取得角度から。
void multiplication(GLfloat* src1,GLfloat* src2,GLfloat* dst);

class MATRIX
{
public:
	union{
		float m[4][4];
		struct{
			float _11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;
		};
	};
	MATRIX(){MatrixIdentity(this);};
	~MATRIX(){};
};
class VECTOR4	//主に色で使用
{
public:
	union{
		float v[4];
		struct{
			float x, y, z, w;
		};
	};
	VECTOR4(float dx = 0.0f, float dy = 0.0f, float dz = 0.0f, float dw = 0.0f)
	{
		x = dx;
		y = dy;
		z = dz;
		w = dw;
	};
	~VECTOR4();
};

class VECTOR3
{
public:
	union{
		float v[3];
		struct{
			float x,y,z;
		};
	};

	VECTOR3(float dx = 0.0f, float dy = 0.0f, float dz = 0.0f)
	{
		x = dx;
		y = dy;
		z = dz;
	};
	~VECTOR3(){};

	//足し算
	VECTOR3 operator+(const VECTOR3 &vec)
	{
		VECTOR3 temp;
		temp.x = x + vec.x;
		temp.y = y + vec.y;
		temp.z = z + vec.z;
		return temp;
	};
	VECTOR3 operator+=(const VECTOR3 &vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	};
	//引き算
	VECTOR3 operator-(const VECTOR3 &vec)
	{
		VECTOR3 temp;
		temp.x = x - vec.x;
		temp.y = y - vec.y;
		temp.z = z - vec.z;
		return temp;
	};
	VECTOR3 operator-=(const VECTOR3 &vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	};
	//かけ算
	VECTOR3 operator*(const float &fval)
	{
		VECTOR3 temp;
		temp.x = x * fval;
		temp.y = y * fval;
		temp.z = z * fval;
		return temp;
	};
	VECTOR3 operator*=(const float &fval)
	{
		x *= fval;
		y *= fval;
		z *= fval;
		return *this;
	};
	//わり算
	VECTOR3 operator/(const float &fval)
	{
		VECTOR3 temp;
		temp.x = x / fval;
		temp.y = y / fval;
		temp.z = z / fval;
		return temp;
	};
	VECTOR3 operator/=(const float &fval)
	{
		x /= fval;
		y /= fval;
		z /= fval;
		return *this;
	};
	//代入演算子
	VECTOR3 operator=(const VECTOR3 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	};
	//比較演算子
	int operator==(const VECTOR3 &vec)
	{
		return (x == vec.x && y == vec.y && z == vec.y);
	};
	//比較演算子
	int operator!=(const VECTOR3 &vec)
	{
		return (!(x == vec.x && y == vec.y && z == vec.z));
	};
	
};

//################################################
// End of File
//################################################
#endif ______MATRIX_H_____
