//################################################
//<CubeMap.cpp>
// 動的キューブマッピング
//------------------------------------------------
//2012/01/22 ~
//						Akihito Tanaka
//################################################
#ifndef _____CUBEMAP_H______
#define _____CUBEMAP_H______

//================================================
//インクルードヘッダ
//================================================
#include "Main.h"
#include "Player.h"
#include "Camera.h"
#include "EnemyMng.h"
#include "Field.h"
#include "Graphic.h"
#include "Matrix.h"
//================================================
//定数定義
//================================================
#define TEXWIDTH  (512)				//テクスチャの幅
#define TEXHEIGHT (TEXWIDTH)		//テクスチャの高さ(幅と同じ)

class PLAYER;
class ENEMYMNG;
//================================================
//クラス定義
//================================================
class CUBEMAP
{
private:
	GLuint		uTexID;		//テクスチャID
	unsigned char* buffer;
	GLuint		uFB;	//フレームバッファ
	GLuint		uRB;	//レンダーバッファ
	PLAYER		*pPlayer;
	CAMERA		*pCamera;
	ENEMYMNG	*pEnemyMng;
	FIELD		*pField;
	VECTOR3		m_Center;		//中心位置
	
	MATRIX		matCube;
	
	GLuint	viewport[ 4 ];
	void RenderToTex(GLenum target, double vx, double vy, double vz, 
									double ux, double uy, double uz);
	void SaveFramebufferStatus( void );
	void RestoreFramebufferStatus( void );

public:
	CUBEMAP();			// コンストラクタ
	~CUBEMAP();			// デストラクタ
	// テクスチャのポインタを得る
	GLuint GetTexture(char *name, char *cat);
	void Release(GLuint uTexID);
	void SetID(int ID);
	GLuint InitCubeMap();
	void MakeCubeMap(VECTOR3 v);
//	void CalcMarix(VECTOR3 vPos, MATRIX m);
};

#endif  _____CUBEMAP_H______