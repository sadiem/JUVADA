//#############################################
//
// <Texture.cpp>
// �e�N�X�`���֘A���W���[��
//						�����Ɠ��@SekiyamaRumi
//
//#############################################
//================================================
//�C���N���[�h
//================================================
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Texture.h"
#include "tga.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++
// BMP�f�[�^�̓ǂݍ���
//-------------------------------------------------
// 
//--in---------------------------------------------
// �t�@�C�����̃|�C���^
//--out--------------------------------------------
// TGAImage
//+++++++++++++++++++++++++++++++++++++++++++++++++
static TGAImage *LoadBMP(const char *pszFName)
{
	TGAImage			*pBmp;
	FILE				*fp;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	unsigned			uSize;
	unsigned char		bTmp;
	unsigned char		*pBGR;

	pBmp = (TGAImage *)malloc(sizeof(TGAImage));
	if (pBmp == NULL) {
		return NULL;	//�������m�ۃG���[
	}
	fp = fopen(pszFName, "rb");
	if (fp == NULL) {
		free(pBmp);
		return NULL;	//�t�@�C����������Ȃ�
	}
	if (fread(&bmfh, sizeof(bmfh), 1, fp) != 1) {
		fclose(fp);
		free(pBmp);
		return NULL;	//�t�@�C�����ǂݍ��߂Ȃ�
	}
	if (bmfh.bfType != 'MB') {
		fclose(fp);
		free(pBmp);
		return NULL;	//�r�b�g�}�b�v�`���łȂ�
	}
	if (fread(&bmih, sizeof(bmih), 1, fp) != 1) {
		fclose(fp);
		free(pBmp);
		return NULL;	//�t�@�C�����ǂݍ��߂Ȃ�
	}
	if (bmih.biBitCount != 24 && bmih.biBitCount != 32) {
		fclose(fp);
		free(pBmp);
		return NULL;	//�Ή��`���łȂ�
	}
	if (bmih.biCompression != BI_RGB) {
		fclose(fp);
		free(pBmp);
		return NULL;	//�Ή��`���łȂ�
	}
	uSize = bmfh.bfSize - bmfh.bfOffBits;
	pBmp->data = (unsigned char *)malloc(uSize);
	if (pBmp->data == NULL) {
		fclose(fp);
		free(pBmp);
		return NULL;	//�������m�ۃG���[
	}
	fseek(fp, bmfh.bfOffBits, SEEK_SET);
	if (fread(pBmp->data, uSize, 1, fp) != 1) {
		fclose(fp);
		free(pBmp->data);
		free(pBmp);
		return NULL;	//�t�@�C�����ǂݍ��߂Ȃ�
	}
	fclose(fp);
	pBmp->alphaDepth = 0;
	pBmp->pixelDepth = bmih.biBitCount;
	pBmp->sizeX = bmih.biWidth;
	pBmp->sizeY = bmih.biHeight;
	pBmp->type = bmih.biBitCount / 8;
	//BGR��RGB�ɕ��ъ���
	for (pBGR = pBmp->data; pBGR < pBmp->data + uSize - 2; pBGR += pBmp->type) {
		bTmp = pBGR[0];
		pBGR[0] = pBGR[2];
		pBGR[2] = bTmp;
	}
	return pBmp;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------
// 
//--in---------------------------------------------
// �t�@�C�����̃|�C���^
//--out--------------------------------------------
// �e�N�X�`��ID �iGLuint�^�j
//+++++++++++++++++++++++++++++++++++++++++++++++++
GLuint LoadTexture(const char *pszFName)
{
	char		szExt[_MAX_EXT];
	GLuint		uTexID;
	bool		bIsTGA;
	TGAImage	*pTextureImage;

	_splitpath(pszFName, NULL, NULL, NULL, szExt);
	bIsTGA = _stricmp(szExt, ".tga") == 0;

	if (bIsTGA)
		pTextureImage = LoadTGA(pszFName);
	else
		pTextureImage = LoadBMP(pszFName);

	if (pTextureImage == NULL) {
//		MessageBox(NULL, _T("�e�N�X�`���ǂݍ��݂Ɏ��s���܂���"),
//			_T("error"), MB_OK | MB_ICONSTOP);
		return 0;
	}

	if (pTextureImage->type != 3 && pTextureImage->type != 4) {
		if (pTextureImage->data)
			free(pTextureImage->data);
		free(pTextureImage);
//		MessageBox(NULL, _T("���̌`���̓T�|�[�g���Ă��܂���"),
//			_T("error"), MB_OK | MB_ICONSTOP);
		return 0;
	}

	glGenTextures(1, &uTexID);
	glBindTexture(GL_TEXTURE_2D, uTexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (pTextureImage->type) {
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, 4, pTextureImage->sizeX, pTextureImage->sizeY,
			0, GL_RGBA, GL_UNSIGNED_BYTE, pTextureImage->data);
		break;
	default:
		glDeleteTextures(1, &uTexID);
		uTexID = 0;
		break;
	}

	if (pTextureImage->data)
		free(pTextureImage->data);
	free(pTextureImage);

	return uTexID;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
// �e�N�X�`���̉��
//-------------------------------------------------
// 
//--in---------------------------------------------
// �t�@�C�����̃|�C���^
//--out--------------------------------------------
// TGAImage
//+++++++++++++++++++++++++++++++++++++++++++++++++
void ReleaseTexture(GLuint uTexID)
{
	if (uTexID == 0)
		return;
	glDeleteTextures(1, &uTexID);	//�e�N�X�`���I�u�W�F�N�g�����
}
