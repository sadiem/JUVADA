//################################################
// <Shader.h>
//
//------------------------------------------------
// 2012/11/20 ~
//						SekiyamaRumi
//################################################
//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Shader.h"			//�V�F�[�_�w�b�_

//================================================
//�萔��`
//================================================

static GLuint verShader;		//���_���
static GLuint fragShader;		//�t���O
static GLuint pragma;			//�v���O�}
//================================================
//�\���̒�`
//================================================

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//�v���g�^�C�v�錾
//================================================


//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL()
{
	shaderProg		= 0;
	vertexShader	= 0;		//�o�[�e�b�N�X�V�F�[�_
	fragmentShader	= 0;		//�t���O�����g�V�F�[�_
	
	/*Init(VTX_FILE,FRG_FILE);*/
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//���_�V�F�[�_�t�@�C�����A�t���O�����g�V�F�[�_�t�@�C����
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL(const char* vtx_file, const char* frg_file)
{
	shaderProg		= 0;
	vertexShader	= 0;		//�o�[�e�b�N�X�V�F�[�_
	fragmentShader	= 0;		//�t���O�����g�V�F�[�_
	Init(vtx_file,frg_file);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
//--in--------------------------------------------
//���_�V�F�[�_�t�@�C�����A
//�t���O�����g�V�F�[�_�t�@�C����
//�W�I���g���V�F�[�_
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::CGLSL(const char* vtx_file, const char* frg_file, const char* geo_file)
{
	shaderProg		= 0;
	vertexShader	= 0;		//�o�[�e�b�N�X�V�F�[�_
	fragmentShader	= 0;		//�t���O�����g�V�F�[�_
	Init(vtx_file,frg_file,geo_file);

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�f�X�g���N�^
//--in--------------------------------------------
//���_�V�F�[�_�t�@�C�����A
//�t���O�����g�V�F�[�_�t�@�C����
//�W�I���g���V�F�[�_
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
CGLSL::~CGLSL()
{
  glDeleteProgram(shaderProg);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�V�F�[�_�̃��[�h
//--in--------------------------------------------
//�@�V�F�[�_ID
//�@�V�F�[�_�t�@�C����
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CGLSL::ReadShaderSource(GLuint shader, const char* filename)
{
	FILE *fp;
	const GLchar *src;
	GLsizei	length;
	int ret;

	//�t�@�C���̃I�[�v��
	fp = fopen(filename, "rb");
	if(fp == NULL)
		return E_FAIL;

	//�t�@�C���T�C�Y�擾
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);

	//�������m��
	src = (GLchar *)malloc(length);
	if(src == NULL)
		return E_FAIL;

	//�ǂݍ���
	fseek(fp, 0L, SEEK_SET);
	ret = (fread((void *)src, 1, length, fp) != (size_t)length);
	fclose(fp);

	//�V�F�[�_�[�I�u�W�F�N�g�֓ǂݍ���
	glShaderSource( shader, 1, &src, &length);

	free((void *)src);


	return S_OK;

}

//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//���_�V�F�[�_�t�@�C�����A
//�t���O�����g�V�F�[�_�t�@�C����
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::Init(const char* vtx_file, const char* frg_file)
{


	//�V�F�[�_�I�u�W�F�N�g�̍쐬
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	//�v���O�����̍쐬
	shaderProg = glCreateProgram();

	//�ǂݍ��݂ƃR���p�C��
	if(ReadShaderSource(vertexShader, vtx_file) == S_OK)
	{
		glCompileShader(vertexShader);		//�R���p�C��
		glAttachShader(shaderProg, vertexShader);	//�v���O�����ɓo�^
	}
	else
	{
		//�G���[����
	}

	if(ReadShaderSource(fragmentShader, frg_file) == S_OK)
	{
		glCompileShader(fragmentShader);		//�R���p�C��
		glAttachShader(shaderProg, fragmentShader);	//�v���O�����ɓo�^
	}
	else
	{
		//�G���[����
	}


	glLinkProgram(shaderProg);
	int linked = 0;
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &linked);
	tangent = glGetAttribLocation(shaderProg, "tangent");
	color = glGetAttribLocation(shaderProg, "color");

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//������
//--in--------------------------------------------
//���_�V�F�[�_�t�@�C�����A
//�t���O�����g�V�F�[�_�t�@�C����
//�W�I���g���V�F�[�_
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::Init(const char* vtx_file, const char* frg_file, const char* geo_file)
{


	//�V�F�[�_�I�u�W�F�N�g�̍쐬
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	geometoryShader = glCreateShader(GL_GEOMETRY_SHADER);


	//�v���O�����̍쐬
	shaderProg = glCreateProgram();

	//�ǂݍ��݂ƃR���p�C��
	if(ReadShaderSource(vertexShader, vtx_file) == S_OK)
	{
		glCompileShader(vertexShader);		//�R���p�C��
		glAttachShader(shaderProg, vertexShader);	//�v���O�����ɓo�^
	}
	else
	{
		//�G���[����
	}

	if(ReadShaderSource(fragmentShader, frg_file) == S_OK)
	{
		glCompileShader(fragmentShader);		//�R���p�C��
		glAttachShader(shaderProg, fragmentShader);	//�v���O�����ɓo�^
	}
	else
	{
		//�G���[����
	}	
	if(ReadShaderSource(geometoryShader, frg_file) == S_OK)
	{
		glCompileShader(geometoryShader);		//�R���p�C��
		glAttachShader(shaderProg, geometoryShader);	//�v���O�����ɓo�^
	}
	else
	{
		//�G���[����
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
//�V�F�[�_�L����
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
//�e�N�X�`���w��
//--in--------------------------------------------
//�e�N�X�`��ID
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
//�m�[�}���}�b�v�w��
//--in--------------------------------------------
//�e�N�X�`��ID
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
//�L���[�u�}�b�v�w��
//--in--------------------------------------------
//�e�N�X�`��ID
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetCubeMapUnit(int unitID)
{
	GLint envi = glGetUniformLocation(shaderProg, "envi");
	glUniform1i(envi, unitID);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�A���t�@�w��
//--in--------------------------------------------
//�A���t�@�l
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetAlpha(float alpha)
{
	
	GLint nAlpha = glGetUniformLocation(shaderProg, "Alpha");
	glUniform1f(nAlpha, alpha);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�|�C���g�X�v���C�g�̃T�C�Y
//--in--------------------------------------------
//�T�C�Y
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void CGLSL::SetPointSize(float size)
{
	GLint nSize = glGetUniformLocation(shaderProg, "size");
	glUniform1f(nSize, size);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�J�������W
//--in--------------------------------------------
//�T�C�Y
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