//################################################
// <PostEffectMng.h>
//
//------------------------------------------------
// 2013/1/30
//						Akihito Tanaka
//################################################
#ifndef _____POST_EFFECT_MNG_H_____
#define _____POST_EFFECT_MNG_H_____

//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "FBO.h"


//================================================
//定数定義
//================================================
//================================================
//クラス定義
//================================================

class POST_EFFECT_MNG{
	
public:
	static POST_EFFECT_MNG* Instance()
	{
		static POST_EFFECT_MNG Inst;
		return &Inst;
	};
private:
	POST_EFFECT_MNG();

	//画面の描画対象
	FBO RenderBuffer;
public:
	void Init();
	void StartRenderMain();			//フレームバッファに書き出し開始
	void EndRenderMain();			//フレームバッファに書き出し終了
	void Draw();					//画面に書き出し

};
#endif _____POST_EFFECT_MNG_H_____