//################################################
// <Particle.h>
//		パーティクルクラス
//------------------------------------------------
// 2013/1/15
//						Akihito Tanaka
//################################################
#ifndef _____PARTICLE_H_____
#define _____PARTICLE_H_____
//================================================
//インクルードヘッダ
//================================================
#include "Include.h"		//インクルードヘッダ
#include "Matrix.h"			//ベクトル用

//================================================
//定数定義
//================================================
//================================================
//クラス定義
//================================================
class PARTICLE
{
public:
	PARTICLE(){	m_Alpha = 0.0f;
				m_Scale = 0.0f;
				m_Live = false;
				m_Time = 0;
				m_Type = 0;
	};
	~PARTICLE(){};
	void UpDate(void);
	void Load(void);
	void Draw(void);
	void Init(void);
	VECTOR3 m_Pos;			//表示位置
	VECTOR3 m_Move;			//移動方向
	float	m_Alpha;		//アルファ値
	float	m_Scale;
	bool	m_Live;
	int		m_Time;
	int		m_Type;
};
#endif _____PARTICLE_H_____