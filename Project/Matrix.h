//################################################
//<Matrix.h>
// �ϊ��}�g���b�N�X�쐬
//------------------------------------------------
//���W�ϊ�
//2012/06/15 ~
//						SekiyamaRumi
//################################################
#ifndef ______MATRIX_H_____
#define ______MATRIX_H_____

#include <GL/glew.h>		//OpenGL �֘A�̃w�b�_
#include <GL/wglew.h>		//OpenGL �֘A�̃w�b�_
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#include <math.h>		//

//====================================================
// �v���g�^�C�v�錾
//====================================================
class MATRIX;
class VECTOR3;
void MatrixIdentity(MATRIX *m);														//�}�g���b�N�X�̏�����
void MatrixTranslation(MATRIX *m, float fX, float fY, float fZ);					//���s�ړ�
void MatrixScaling(MATRIX *m, float fSx, float fSy, float fSz);						//�g��k��
void MatrixRotationX(MATRIX *m, float fPitch);										//X����]
void MatrixRotationY(MATRIX *m, float fYaw);										//Y����]
void MatrixRotationZ(MATRIX *m, float fRoll);										//Z����]
void MatrixRotationYawPitchRoll(MATRIX *m, float fYaw, float fPitch, float fRoll);	//�s��̍�������
void MatrixRotationAxis(MATRIX *m, VECTOR3 v, float fAngle);						//�C�ӎ���]�̏���
void MatrixMultiply(MATRIX *m, MATRIX mL, MATRIX mR);								//�|���Z
void MatrixInv(MATRIX *mat, MATRIX m);												//�t�s��
void MatrixTransposition(MATRIX *mat, MATRIX &m);									//�]�u�s��

void Vec3Identity(VECTOR3 *vec);													//������
void Vec3TransformCoord(VECTOR3 *v, MATRIX m, VECTOR3 vS);							//�ړ������܂݂̉�]����
void Vec3TransformNormal(VECTOR3 v, MATRIX m, VECTOR3 vR);							//��]�����݂̂̉�]����
void Vec3Cross(VECTOR3 *v, VECTOR3 vL, VECTOR3 vR);									//�O��
float Vec3Dot(VECTOR3 vL, VECTOR3 vR);												//����
void Vec3Normalize(VECTOR3* v, VECTOR3& vR);										//�P�ʍs��
float Vec3Length(VECTOR3 vR, VECTOR3 vL);											//�Q�̃x�N�h���̑傫��
float VectoVec(VECTOR3 vec1, VECTOR3 vec2);											//�x�N�g���P�ƂQ�����]�p��Ԃ�
float VecLength(VECTOR3 vec);														//�x�N�g���̑傫��								
void VecScale(VECTOR3 *vec, float fScale);											//�x�N�g���ɃX�J���l��������
void VecScaleM(VECTOR3 *vec, float fScale);											//�x�N�g��������
void VecRot(VECTOR3 *vec, float fRadius);										//�P�ʃx�N�g���擾�p�x����B
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
class VECTOR4	//��ɐF�Ŏg�p
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

	//�����Z
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
	//�����Z
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
	//�����Z
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
	//���Z
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
	//������Z�q
	VECTOR3 operator=(const VECTOR3 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	};
	//��r���Z�q
	int operator==(const VECTOR3 &vec)
	{
		return (x == vec.x && y == vec.y && z == vec.y);
	};
	//��r���Z�q
	int operator!=(const VECTOR3 &vec)
	{
		return (!(x == vec.x && y == vec.y && z == vec.z));
	};
	
};

//################################################
// End of File
//################################################
#endif ______MATRIX_H_____
