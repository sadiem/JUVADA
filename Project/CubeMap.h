//################################################
//<CubeMap.cpp>
// ���I�L���[�u�}�b�s���O
//------------------------------------------------
//2012/01/22 ~
//						Akihito Tanaka
//################################################
#ifndef _____CUBEMAP_H______
#define _____CUBEMAP_H______

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "Main.h"
#include "Player.h"
#include "Camera.h"
#include "EnemyMng.h"
#include "Field.h"
#include "Graphic.h"
#include "Matrix.h"
//================================================
//�萔��`
//================================================
#define TEXWIDTH  (512)				//�e�N�X�`���̕�
#define TEXHEIGHT (TEXWIDTH)		//�e�N�X�`���̍���(���Ɠ���)

class PLAYER;
class ENEMYMNG;
//================================================
//�N���X��`
//================================================
class CUBEMAP
{
private:
	GLuint		uTexID;		//�e�N�X�`��ID
	unsigned char* buffer;
	GLuint		uFB;	//�t���[���o�b�t�@
	GLuint		uRB;	//�����_�[�o�b�t�@
	PLAYER		*pPlayer;
	CAMERA		*pCamera;
	ENEMYMNG	*pEnemyMng;
	FIELD		*pField;
	VECTOR3		m_Center;		//���S�ʒu
	
	MATRIX		matCube;
	
	GLuint	viewport[ 4 ];
	void RenderToTex(GLenum target, double vx, double vy, double vz, 
									double ux, double uy, double uz);
	void SaveFramebufferStatus( void );
	void RestoreFramebufferStatus( void );

public:
	CUBEMAP();			// �R���X�g���N�^
	~CUBEMAP();			// �f�X�g���N�^
	// �e�N�X�`���̃|�C���^�𓾂�
	GLuint GetTexture(char *name, char *cat);
	void Release(GLuint uTexID);
	void SetID(int ID);
	GLuint InitCubeMap();
	void MakeCubeMap(VECTOR3 v);
//	void CalcMarix(VECTOR3 vPos, MATRIX m);
};

#endif  _____CUBEMAP_H______