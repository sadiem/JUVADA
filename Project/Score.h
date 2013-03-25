//################################################
// <Score.cpp>
//
//------------------------------------------------
// 2012/11/09 ~
//2013/01/31  修正
//						SekiyamaRumi
//################################################
#ifndef _____SCORE_H_____
#define _____SCORE_H_____

//================================================
//インクルードヘッダ
//================================================
#include <windows.h>		//Windows プログラムにはこれを付ける
#include <tchar.h>			//汎用テキスト マッピング

#include "NumView.h"		//数値出力ヘッダ

//================================================
//定数定義
//================================================
//スコアランク表
#define SCORE_SSS	(100)
#define SCORE_SS	(90)
#define SCORE_S		(80)
#define SCORE_A		(50)
#define SCORE_B		(40)
#define SCORE_C		(30)
#define SCORE_D		(0)

enum{
	RANK_D,
	RANK_C,
	RANK_B,
	RANK_A,
	RANK_S,
	RANK_SS,
	RANK_SSS
};
//================================================
//クラス宣言
//================================================
//class SCORE;
class SCORE: public NUM_VIEW
{
private:
	SCORE();						//コンストラクタ
	int m_nScore;			//スコア

public:
	static SCORE *Instance()
	{
		static SCORE Inst;
		return &Inst;
	}

	virtual ~SCORE();		//デストラクタ
	GLuint m_TexID;			//テクスチャID
	
	void Init();			//初期化
	void Load();			//データのロード
	void Update(int Enemy, int Boss);	//更新
	void Draw(void);		//描画
	void Reset(void);		//リセット

	void SetTexID(GLuint TexID);				//テクスチャIDセット
	void SetNum(void);							//数値セット
	void SetVer(int X, int Y, int W, int H);	//テクスチャ情報
	int ColEvolution(void);						//評価判定用
	int GetScore(void){return m_nScore;}
private:
	void Calc(void);					//スコアの計算
	void addEnemyDeathScore(int num);	//スコア加算:敵倒した時
	int EnemyDeath;
	int BossDeath;
	int nCount;
	int nCombo;
	int nMaxCombo;
};

//################################################
// End of File
//################################################
#endif _____SCORE_H_____
