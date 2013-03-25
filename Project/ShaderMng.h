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
//�C���N���[�h�w�b�_
//================================================
#include "Include.h"		//�C���N���[�h�w�b�_
#include "Shader.h"			//�V�F�[�_
#include "Matrix.h"

//================================================
//�萔��`
//================================================
enum SHADE_TYPE
{
	PHONG,		//�t�H��
	BUMP,		//�o���v
//	CUBE,		//�L���[�u�}�b�v�����p�V�F�[�_
	POINTSPL,	//�|�C���g�X�v���C�g
	COOK,		//�N�b�N�g�����X
	REFLECT,
	MAX_SHADER,

	//SHADER_NUM = BUMP + 2	//�V�F�[�_�̐�
};

//================================================
//�N���X��`
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
	void UseShader(int type);		//�V�F�[�_�[�^�C�v�ƃe�N�X�`�����j�b�g���w��
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
	GLint tangent;				//�ڃx�N�g���i�[�pattribute�n���h��
};

//################################################
// End of File
//################################################
#endif _____SHADER_MNG_H_____
