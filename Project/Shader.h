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
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "Matrix.h"
#include <math.h>

//================================================
//���C�u������`
//================================================

//================================================
//�萔��`
//================================================

//================================================
//�N���X��`
//================================================
class CGLSL{
public:
	CGLSL();
	CGLSL(const char* vtx_file, const char* frg_file);
	CGLSL(const char* vtx_file, const char* frg_file, const char* geo_file);
	~CGLSL();
	void UseShader();		//�V�F�[�_�̓K�p
	//void UnUseShader();		//�Œ�@�\�ɖ߂�
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
	GLuint vertexShader;		//�o�[�e�b�N�X�V�F�[�_
	GLuint fragmentShader;		//�t���O�����g�V�F�[�_
	GLuint geometoryShader;		//�W�I���g���V�F�[�_
	GLint tangent;				//�ڃx�N�g���i�[�pattribute�n���h��	
	GLint color;				//�A���t�@�̃n���h��
};
//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================


//################################################
// End of File
//################################################
#endif _____SHADER_H_____
