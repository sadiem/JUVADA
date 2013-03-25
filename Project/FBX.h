//#############################################
//
// <FBX.h>
// FBXファイルのロードヘッダー
//					＊授業内　SekiyamaRumi
//
//#############################################

#ifndef _____FBX_H______
#define _____FBX_H______

union FBXVECTOR
{
	struct{
		double x, y, z;
	}v;
	double p[3];
};

typedef struct{
	int			nVtx;
	FBXVECTOR	*pVtx;
	int			nIdx;
	int			*pIdx;
}FBX;

int LoadFBX(FBX* pFBX, char* pszPath);
void Release(FBX *pFBX);


#endif _____FBX_H______
