//################################################
// <Select.cpp>
// セレクトメニューを作成
//------------------------------------------------
// 2013/01/18 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Select.h"
#include "TexMng.h"
#include "Random.h"

//================================================
//ライブラリ定義
//================================================

//================================================
//定数定義
//================================================
//フェード
#define SELECT_FADE_POS_X (-10)			//フェード板ポリ初期位置
#define SELECT_FADE_POS_Y (-10)
#define SELECT_FADE_H (20)				//フェード板ポリ縦幅
#define SELECT_FADE_W (20)				//　　　　　　　横幅
//フェード時間
#define SELECT_FADE_TIME	(120)		//フェードタイム
//BG
#define SELECT_BG_H (50)				//フェード板ポリ縦幅
#define SELECT_BG_W (50)				//　　　　　　　横幅
#define SELECT_BG_POS_X (-(SELECT_BG_H / 2.0f))				//フェード板ポリ初期位置
#define SELECT_BG_POS_Y (SELECT_BG_POS_X)
//ステンシル
#define SELECT_STENCIL_H (27.0f)							//ステンシル板ポリ縦幅
#define SELECT_STENCIL_W (27.0f)							//　　　　　　　横幅
#define SELECT_STENCIL_POS_X (-(SELECT_STENCIL_H / 2.0f))	//ステンシル板ポリ初期位置
#define SELECT_STENCIL_POS_Y (SELECT_STENCIL_POS_X)
#define SELECT_STENCIL_MOVE  (VECTOR3(11.5f, -5.5f, 0.0f))	//ステンシル移動値
#define SELECT_STENCIL_ANGLE	((GLfloat)20.0f)	//ステンシル回転角
#define SELECT_STENCIL_MOVE_VEC	(VECTOR3(cosf(SELECT_STENCIL_ANGLE), sinf(SELECT_STENCIL_ANGLE), 0.0f))	//ステンシル移動ベクトル
//終了選択BG
#define SELECT_END_BG_H (4)				//終了選択板ポリ縦幅
#define SELECT_END_BG_W (8)				//　　　　　　　横幅
#define SELECT_END_BG_POS_X (-(SELECT_END_BG_W / 2.0f))			//終了選択板ポリ初期位置
#define SELECT_END_BG_POS_Y (-(SELECT_END_BG_H / 2.0f))
#define SELECT_END_BG_ADD_SCALE	(0.08f)							//終了選択拡大率
//終了選択ボタン
#define SELECT_BUTTOM_END_H (1.0f)								//終了選択ボタン板ポリ縦幅
#define SELECT_BUTTOM_END_W (2.0f)								//　　　　　　　横幅
#define SELECT_BUTTOM_END_POS_X (-(SELECT_BUTTOM_END_W / 2.0f))	//終了選択ボタン板ポリ初期位置
#define SELECT_BUTTOM_END_POS_Y (-(SELECT_BUTTOM_END_H / 2.0f))
#define SELECT_BUTTOM_END_FIRST_SCALE	(0.01f)					//終了選択ボタンの初期拡大値
//ボタン
#define SELECT_BUTTOM_H (1.5f)							//ボタン板ポリ縦幅
#define SELECT_BUTTOM_W (6.0f)							//　　　　　　　横幅
#define SELECT_BUTTOM_POS_X (-(SELECT_BUTTOM_H / 2.0f))	//ボタン板ポリ初期位置
#define SELECT_BUTTOM_POS_Y (SELECT_BUTTOM_POS_X - 0.5f)
#define SELECT_BUTTOM_SPACE_Y	(-SELECT_BUTTOM_H * 0.8f)		//ボタン間隔
#define SELECT_BUTTOM_SPACE_X	(0.5f)							//ボタン間隔
#define SELECT_BUTTOM_POP		(1.0f)					//ボタンの飛び出し
#define SELECT_BUTTOM_ADD_POP	(0.1f)					//ボタンの飛び出しの増加量
#define SELECT_BUTTOM_MINUS_POP	(0.1f)					//ボタンの飛び出しの減算量
#define SELECT_BUTTOM_FIRST_POS_X	(-4.5f)				//ボタン初期位置
#define SELECT_BUTTOM_FIRST_POS_Y	(0.0f)				//ボタン初期位置
#define SELECT_BUTTOM_ADD_MOVE_TEX	(0.02f)				//ボタンテクスチャ移動

//タイトル
#define SELECT_TITLE_SCALE_MAX			(3.0f)						//拡大率最大値
#define SELECT_TITLE_FIRST_POS			(VECTOR3(0.0f, 4.5f, 14.0f))
#define SELECT_TITLE_POS				(VECTOR3(2.5f, 3.0f, 6.0f))	//目標地点
#define SELECT_TITLE_COMPLETION_TIME	(120.0f)					//移動保管時間
enum {
	SLCT_APPEAR,		//セレクト画面への入り
	SLCT_CRACK,			//画面割れる
	SLCT_MENU,			//メニュー欄での選択
	SLCT_SELECT_ITEM,	//選んだ項目別の処理
	SLCT_END_SELECT,	//終了選択
	SLCT_END,			//エンド
	SLCT_WINDOW_CLOSE	//ウィンドウを閉じる

};
enum{
	SL_KEY_START,	//ゲームスタート
	SL_KEY_HOWTO,	//プレイ方法
	SL_KEY_CONFFIG,	//キーコンフィグ
	SL_KEY_END,		//END

	SL_KEY_MAX,		//キーの総数
};
//================================================
//構造体定義
//================================================

//================================================
//グローバル変数
//================================================

//================================================
//プロトタイプ宣言
//================================================
SELECT::SELECT(){}
SELECT::~SELECT(){}
//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Init(void)
{
	m_pShadeMng = SHADER_MNG::Instance();
	m_pInput = INPUT_MNG::getInstance();
	m_TexID = g_TexMng.GetTexture("TEXTURE\\SELECT\\select.png", "SELECT");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\SELECT\\title.png", "SELECT");
	m_TexIDD = g_TexMng.GetTexture("TEXTURE\\SELECT\\deko.png", "SELECT");
	m_TexIDF = g_TexMng.GetTexture("TEXTURE\\SELECT\\fade.png", "SELECT");
	m_TexIDE = g_TexMng.GetTexture("TEXTURE\\SELECT\\endselect.png", "SELECT");

	g_MeshMng.GetMesh(&m_MeshT, "MODEL\\OP\\title.x", "SELECT");
	g_MeshMng.GetMesh(&m_MeshDeco, "MODEL\\OP\\deco.x", "SELECT");
	m_pCmr = CAMERA::Instance();	//インスタンスの取得
	m_pSE = SOUND::Instance();
	m_pSE->PlayBG(BG_SELECT);
	Reset();
}

void SELECT::Release(void)
{
	g_TexMng.ReleaseCat("SELECT");
	g_MeshMng.ReleaseCat("SELECT");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
// なし
//--out-------------------------------------------
// なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Reset(void)
{
	static int nKeyEnd = 0;

	m_nState = SLCT_APPEAR;
	m_nInState = 0;
	m_nCnt = 0;
	m_nSelect = SL_KEY_START;
	bflg = false;
	bflgKey1 = false;
	bflgKey2 = false;
	nCnt = 0;


	//タイトル
	m_Titlpos = SELECT_TITLE_FIRST_POS;
	m_TAngY = -10.0f;
	m_TAngZ = -5.0f;
	m_TScl = SELECT_TITLE_SCALE_MAX;

	//終了選択画面
	m_EScl = SELECT_BUTTOM_END_FIRST_SCALE;

	//頂点セット
	SetPoli();

	//ボタン初期位置
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++){
		m_vBtmpos[i].x = i * SELECT_BUTTOM_SPACE_X + SELECT_BUTTOM_FIRST_POS_X;
		m_vBtmpos[i].y = i * SELECT_BUTTOM_SPACE_Y + SELECT_BUTTOM_FIRST_POS_Y;
		m_vBtmpos[i].z = 5.0f;
		//コピー
		m_vBtmposCopy[i].x = i * SELECT_BUTTOM_SPACE_X + SELECT_BUTTOM_FIRST_POS_X;
		m_vBtmposCopy[i].y = i * SELECT_BUTTOM_SPACE_Y + SELECT_BUTTOM_FIRST_POS_Y;
		m_vBtmposCopy[i].z = 5.0f;

		//画像変換
		m_bButtunChange[i] = false;
	}

	//デコレーション初期値セット
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++){
		m_Ditlpos[i].x = 2.0f * i;			//デコレーション位置
		m_Ditlpos[i].y = 1.0f * i;	//デコレーション位置
		m_Ditlpos[i].z = 1.0f;						//デコレーション位置
		m_DAng[i] = 72.0f * (i + 1);				//デコレーション回転 傾き
		m_DAngM[i] = 0;								//デコレーション回転 自身の回転
		m_DScl[i] = 0.3f + (i + 1) * 0.1f;			//デコレーション拡大
	}

	//ステンシルの移動方向
	m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::SetPoli(void)
{
	//------------------------
	//頂点のセット
	//------------------------
	//フェード用
	m_PFade.ver[0].x = SELECT_FADE_POS_X;
	m_PFade.ver[0].y = SELECT_FADE_POS_Y + SELECT_FADE_H;
	m_PFade.ver[0].z = 5.0f;

	m_PFade.ver[1].x = SELECT_FADE_POS_X;
	m_PFade.ver[1].y = SELECT_FADE_POS_Y;
	m_PFade.ver[1].z = 5.0f;

	m_PFade.ver[2].x = SELECT_FADE_POS_X + SELECT_FADE_W;
	m_PFade.ver[2].y = SELECT_FADE_POS_Y ;
	m_PFade.ver[2].z = 5.0f;

	m_PFade.ver[3].x = SELECT_FADE_POS_X + SELECT_FADE_W;
	m_PFade.ver[3].y = SELECT_FADE_POS_Y + SELECT_FADE_H;
	m_PFade.ver[3].z = 5.0f;

	//BG用
	m_PBg.ver[0].x = SELECT_BG_POS_X;
	m_PBg.ver[0].y = SELECT_BG_POS_Y + SELECT_BG_H;
	m_PBg.ver[0].z = -10.0f;

	m_PBg.ver[1].x = SELECT_BG_POS_X;
	m_PBg.ver[1].y = SELECT_BG_POS_Y;
	m_PBg.ver[1].z = -10.0f;

	m_PBg.ver[2].x = SELECT_BG_POS_X + SELECT_BG_W;
	m_PBg.ver[2].y = SELECT_BG_POS_Y;
	m_PBg.ver[2].z = -10.0f;

	m_PBg.ver[3].x = SELECT_BG_POS_X + SELECT_BG_W;
	m_PBg.ver[3].y = SELECT_BG_POS_Y + SELECT_BG_H;
	m_PBg.ver[3].z = -10.0f;

	//ステンシル用
	m_PStencil.ver[0].x = SELECT_STENCIL_POS_X;
	m_PStencil.ver[0].y = SELECT_STENCIL_POS_Y + SELECT_STENCIL_H;
	m_PStencil.ver[0].z = 5.0f;

	m_PStencil.ver[1].x = SELECT_STENCIL_POS_X;
	m_PStencil.ver[1].y = SELECT_STENCIL_POS_Y;
	m_PStencil.ver[1].z = 5.0f;

	m_PStencil.ver[2].x = SELECT_STENCIL_POS_X + SELECT_STENCIL_W;
	m_PStencil.ver[2].y = SELECT_STENCIL_POS_Y;
	m_PStencil.ver[2].z = 5.0f;

	m_PStencil.ver[3].x = SELECT_STENCIL_POS_X + SELECT_STENCIL_W;
	m_PStencil.ver[3].y = SELECT_STENCIL_POS_Y + SELECT_STENCIL_H;
	m_PStencil.ver[3].z = 5.0f;

	//終了選択画面BG用
	m_PEndselect.ver[0].x = SELECT_END_BG_POS_X;
	m_PEndselect.ver[0].y = SELECT_END_BG_POS_Y + SELECT_END_BG_H;
	m_PEndselect.ver[0].z = 7.0f;

	m_PEndselect.ver[1].x = SELECT_END_BG_POS_X;
	m_PEndselect.ver[1].y = SELECT_END_BG_POS_Y;
	m_PEndselect.ver[1].z = 7.0f;

	m_PEndselect.ver[2].x = SELECT_END_BG_POS_X + SELECT_END_BG_W;
	m_PEndselect.ver[2].y = SELECT_END_BG_POS_Y;
	m_PEndselect.ver[2].z = 7.0f;

	m_PEndselect.ver[3].x = SELECT_END_BG_POS_X + SELECT_END_BG_W;
	m_PEndselect.ver[3].y = SELECT_END_BG_POS_Y + SELECT_END_BG_H;
	m_PEndselect.ver[3].z = 7.0f;


	//ボタン
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].ver[0].x = SELECT_BUTTOM_POS_X;
		m_PButtom[i].ver[0].y = SELECT_BUTTOM_POS_Y + SELECT_BUTTOM_H;
		m_PButtom[i].ver[0].z = -1.0f;

		m_PButtom[i].ver[1].x = SELECT_BUTTOM_POS_X;
		m_PButtom[i].ver[1].y = SELECT_BUTTOM_POS_Y;
		m_PButtom[i].ver[1].z = -1.0f;

		m_PButtom[i].ver[2].x = SELECT_BUTTOM_POS_X + SELECT_BUTTOM_W;
		m_PButtom[i].ver[2].y = SELECT_BUTTOM_POS_Y ;
		m_PButtom[i].ver[2].z = -1.0f;

		m_PButtom[i].ver[3].x = SELECT_BUTTOM_POS_X + SELECT_BUTTOM_W;
		m_PButtom[i].ver[3].y = SELECT_BUTTOM_POS_Y + SELECT_BUTTOM_H;
		m_PButtom[i].ver[3].z = -1.0f;
	}
	//終了選択ボタン
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].ver[0].x = SELECT_BUTTOM_END_POS_X;
		m_PButtumEnd[i].ver[0].y = SELECT_BUTTOM_END_POS_Y + SELECT_BUTTOM_END_H;
		m_PButtumEnd[i].ver[0].z = 7.1f;

		m_PButtumEnd[i].ver[1].x = SELECT_BUTTOM_END_POS_X;
		m_PButtumEnd[i].ver[1].y = SELECT_BUTTOM_END_POS_Y;
		m_PButtumEnd[i].ver[1].z = 7.1f;

		m_PButtumEnd[i].ver[2].x = SELECT_BUTTOM_END_POS_X + SELECT_BUTTOM_END_W;
		m_PButtumEnd[i].ver[2].y = SELECT_BUTTOM_END_POS_Y ;
		m_PButtumEnd[i].ver[2].z = 7.1f;

		m_PButtumEnd[i].ver[3].x = SELECT_BUTTOM_END_POS_X + SELECT_BUTTOM_END_W;
		m_PButtumEnd[i].ver[3].y = SELECT_BUTTOM_END_POS_Y + SELECT_BUTTOM_END_H;
		m_PButtumEnd[i].ver[3].z = 7.1f;
	}

	//------------------------
	//テクスチャのセット
	//------------------------
	//フェード用
	m_PFade.tex[0].x = 0.0f;
	m_PFade.tex[0].y = 1.0f;

	m_PFade.tex[1].x = 0.0f;
	m_PFade.tex[1].y = 0.0f;

	m_PFade.tex[2].x = 1.0f;
	m_PFade.tex[2].y = 0.0f;

	m_PFade.tex[3].x = 1.0f;
	m_PFade.tex[3].y = 1.0f;

	//BG用
	m_PBg.tex[0].x = 0.5f;
	m_PBg.tex[0].y = 1.0f - (16.0f / 16.0f);

	m_PBg.tex[1].x = 0.5f;
	m_PBg.tex[1].y = 1.0f - (8.0f / 16.0f);

	m_PBg.tex[2].x = 1.0f;
	m_PBg.tex[2].y = 1.0f - (8.0f / 16.0f);

	m_PBg.tex[3].x = 1.0f;
	m_PBg.tex[3].y = 1.0f - (16.0f / 16.0f);

	//ステンシル用
	m_PStencil.tex[0].x = 0.0f;
	m_PStencil.tex[0].y = 1.0f;

	m_PStencil.tex[1].x = 0.0f;
	m_PStencil.tex[1].y = 0.0f;

	m_PStencil.tex[2].x = 1.0f;
	m_PStencil.tex[2].y = 0.0f;

	m_PStencil.tex[3].x = 1.0f;
	m_PStencil.tex[3].y = 1.0f;

	//ボタン
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].tex[0].x = 0.5f;
		m_PButtom[i].tex[0].y = 1.0f - ((i * 2.0f + 2.0f) / 16.0f);

		m_PButtom[i].tex[1].x = 0.5f;
		m_PButtom[i].tex[1].y = 1.0f - (i * 2.0f / 16.0f);

		m_PButtom[i].tex[2].x = 1.0f;
		m_PButtom[i].tex[2].y = 1.0f - (i * 2.0f / 16.0f);

		m_PButtom[i].tex[3].x = 1.0f;
		m_PButtom[i].tex[3].y = 1.0f- ((i * 2.0f + 2.0f) / 16.0f);	

		m_CopyTexButtom[i][0].x = m_PButtom[i].tex[0].x;
		m_CopyTexButtom[i][0].y = m_PButtom[i].tex[0].y;
		m_CopyTexButtom[i][1].x = m_PButtom[i].tex[1].x;
		m_CopyTexButtom[i][1].y = m_PButtom[i].tex[1].y;
		m_CopyTexButtom[i][2].x = m_PButtom[i].tex[2].x;
		m_CopyTexButtom[i][2].y = m_PButtom[i].tex[2].y;
		m_CopyTexButtom[i][3].x = m_PButtom[i].tex[3].x;
		m_CopyTexButtom[i][3].y = m_PButtom[i].tex[3].y;
	}

	//終了選択BG用
	m_PEndselect.tex[0].x = 0.0f;
	m_PEndselect.tex[0].y = 1.0f - (16.0f / 16.0f);
							
	m_PEndselect.tex[1].x = 0.0f;
	m_PEndselect.tex[1].y = 1.0f - (8.0f / 16.0f);
							
	m_PEndselect.tex[2].x = 1.0f;
	m_PEndselect.tex[2].y = 1.0f - (8.0f / 16.0f);
							
	m_PEndselect.tex[3].x = 1.0f;
	m_PEndselect.tex[3].y = 1.0f - (16.0f / 16.0f);

	//終了選択ボタン
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].tex[0].x = 0.0f;
		m_PButtumEnd[i].tex[0].y = 1.0f - ((i * 2.0f + 6.0f) / 16.0f);

		m_PButtumEnd[i].tex[1].x = 0.0f;
		m_PButtumEnd[i].tex[1].y = 1.0f - ((i * 2.0f + 4.0f) / 16.0f);

		m_PButtumEnd[i].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[i].tex[2].y = 1.0f - ((i * 2.0f + 4.0f) / 16.0f);

		m_PButtumEnd[i].tex[3].x = 4.0f / 16.0f;
		m_PButtumEnd[i].tex[3].y = 1.0f - ((i * 2.0f + 6.0f) / 16.0f);	
	}
	//------------------------
	//カラー
	//------------------------
	//フェード用
	m_PFade.col.r = 1.0f;
	m_PFade.col.g = 0.0f;
	m_PFade.col.b = 0.0f;
	m_PFade.col.a = 1.0f;	

	//BG用
	m_PBg.col.r = 1.0f;
	m_PBg.col.g = 1.0f;
	m_PBg.col.b = 1.0f;
	m_PBg.col.a = 1.0f;	
	
	//ステンシル用
	m_PStencil.col.r = 1.0f;
	m_PStencil.col.g = 1.0f;
	m_PStencil.col.b = 1.0f;
	m_PStencil.col.a = 1.0f;	
	
	//ボタン用
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{
		m_PButtom[i].col.r = 1.0f;
		m_PButtom[i].col.g = 1.0f;
		m_PButtom[i].col.b = 1.0f;
		m_PButtom[i].col.a = 1.0f;	
	}

	//終了選択用BG
	m_PEndselect.col.r = 1.0f;
	m_PEndselect.col.g = 1.0f;
	m_PEndselect.col.b = 1.0f;
	m_PEndselect.col.a = 1.0f;	

	//終了選択用ボタン//ボタン用
	for(int i = 0; i < 2; i ++)
	{
		m_PButtumEnd[i].col.r = 1.0f;
		m_PButtumEnd[i].col.g = 1.0f;
		m_PButtumEnd[i].col.b = 1.0f;
		m_PButtumEnd[i].col.a = 1.0f;	
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++
//ボタンテクスチャの移動　出現
//セレクトに移った時
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//テクスチャ移動終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::TexMoveAppear(void)
{
	//ボタン
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{	
		m_PButtom[i].tex[0].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[1].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[2].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[3].x -= SELECT_BUTTOM_ADD_MOVE_TEX;
	}
	//補正
	if(m_PButtom[0].tex[3].x < 0.5f)
	{	//補正値代入
		for(int k = 0; k < SLECT_BUTTOM_NUM; k ++){
			m_PButtom[k].tex[0].x = 0.0f;
			m_PButtom[k].tex[1].x = 0.0;
			m_PButtom[k].tex[2].x = 0.5f;
			m_PButtom[k].tex[3].x = 0.5f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//ボタンテクスチャの移動　仕舞う
//セレクト画面から退避する場面に移った時
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//テクスチャ移動終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::TexMovePutaway(void)
{
	//ボタン
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
	{	
		m_PButtom[i].tex[0].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[1].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[2].x += SELECT_BUTTOM_ADD_MOVE_TEX;
		m_PButtom[i].tex[3].x += SELECT_BUTTOM_ADD_MOVE_TEX;
	}
	//補正
	if(m_PButtom[0].tex[3].x < 1.0f)
	{	//補正値代入
		for(int k = 0; k < SLECT_BUTTOM_NUM; k ++){
			m_PButtom[k].tex[0].x = 0.5f;
			m_PButtom[k].tex[1].x = 0.5f;
			m_PButtom[k].tex[2].x = 1.0f;
			m_PButtom[k].tex[3].x = 1.0f;
		}
		return true;
	}
	return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//ボタンテクスチャの移動　仕舞う
//セレクト画面から退避する場面に移った時
//--in--------------------------------------------
//右か左に移動　右=>1 左=>-1
//--out-------------------------------------------
//テクスチャ移動終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::TexMovePutawayEnd(int nMove)
{
	switch(nMove)
	{
	case 0:
		//YES
		m_PButtumEnd[0].tex[0].x = 0.0f;
		m_PButtumEnd[0].tex[1].x = 0.0f;
		m_PButtumEnd[0].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[3].x = 4.0f / 16.0f;

		m_PButtumEnd[1].tex[0].x = 0.0f;
		m_PButtumEnd[1].tex[1].x = 0.0f;
		m_PButtumEnd[1].tex[2].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[3].x = 4.0f / 16.0f;
		break;
	case 1:
		//NO
		m_PButtumEnd[0].tex[0].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[1].x = 4.0f / 16.0f;
		m_PButtumEnd[0].tex[2].x = 8.0f / 16.0f;
		m_PButtumEnd[0].tex[3].x = 8.0f / 16.0f;

		m_PButtumEnd[1].tex[0].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[1].x = 4.0f / 16.0f;
		m_PButtumEnd[1].tex[2].x = 8.0f / 16.0f;
		m_PButtumEnd[1].tex[3].x = 8.0f / 16.0f;

		break;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//選択中ボタンのテクスチャ変更
//--in--------------------------------------------
//ボタン番号
//ボタンが選択されたかどうかのフラグ	1 , -1
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::TexChange(int nID, int flg)
{
	if(flg){
	m_PButtom[nID].tex[0].y = m_CopyTexButtom[nID][0].y - 0.5f;
	m_PButtom[nID].tex[1].y = m_CopyTexButtom[nID][1].y - 0.5f;
	m_PButtom[nID].tex[2].y = m_CopyTexButtom[nID][2].y - 0.5f;
	m_PButtom[nID].tex[3].y = m_CopyTexButtom[nID][3].y - 0.5f;
	}else{
	m_PButtom[nID].tex[0].y = m_CopyTexButtom[nID][0].y;
	m_PButtom[nID].tex[1].y = m_CopyTexButtom[nID][1].y;
	m_PButtom[nID].tex[2].y = m_CopyTexButtom[nID][2].y;
	m_PButtom[nID].tex[3].y = m_CopyTexButtom[nID][3].y;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::Update(void)
{
	m_nCnt ++;	//フレームカウント

	switch(m_nState)
	{
	case SLCT_APPEAR:
		if(!bflg){
		if(FadeOut(&m_PFade))
			bflg = 1;
		}
		//タイトル出現
		if(((m_nCnt - nCnt) < SELECT_TITLE_COMPLETION_TIME)){
			float f = (m_nCnt - nCnt) / SELECT_TITLE_COMPLETION_TIME;
			VECTOR3 v;
			v = SELECT_TITLE_FIRST_POS - SELECT_TITLE_POS;
			m_Titlpos = SELECT_TITLE_FIRST_POS - (SELECT_TITLE_FIRST_POS - SELECT_TITLE_POS) * float((m_nCnt - nCnt) / SELECT_TITLE_COMPLETION_TIME);
			m_TScl -= 0.1f;
			if(m_TScl < 0.6f)
				m_TScl = 0.6f;
		}
		else if(((m_nCnt - nCnt) > SELECT_TITLE_COMPLETION_TIME))
		{
			m_nState = SLCT_CRACK;
			bflg = 0;
			nCnt =  0;
		}
		break;
		//画面が割れる	あとで
	case SLCT_CRACK:	
		//画面割れる
		if(m_vSSlide.x < 3.0f){
			m_vSSlide.y -= 0.000001f;
			m_vSSlide.x += 0.1f;
		}else
		{//ボタン出現
			if(TexMoveAppear())
				m_nState = SLCT_MENU;
		}
		break;
	case SLCT_MENU:
		//メニューを選ぶ
		if(m_pInput->GetBtnState(BTN_UP) == TRG)
			m_nSelect --;	
		if(m_pInput->GetBtnState(BTN_DOWN) == TRG)
			m_nSelect ++;
		if(m_nSelect > SL_KEY_MAX - 1)	//補正
			m_nSelect = (SL_KEY_MAX - 1);
		if(m_nSelect < 0)
			m_nSelect = 0;

		//キーの動き(見た目)
		switch(m_nSelect)
		{
		case SL_KEY_START:		//ゲームスタート
			m_vBtmpos[0].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[0].x > m_vBtmposCopy[0].x + SELECT_BUTTOM_POP){
				m_vBtmpos[0].x = m_vBtmposCopy[0].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[0]){
					TexChange(0, 1);
					m_bButtunChange[0] = true;
				}
			}
			break;
		case SL_KEY_HOWTO:		//プレイ方法
			m_vBtmpos[1].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[1].x > m_vBtmposCopy[1].x + SELECT_BUTTOM_POP){
				m_vBtmpos[1].x = m_vBtmposCopy[1].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[1]){
					TexChange(1, 1);
					m_bButtunChange[1] = true;
				}
			}
			break;
		case SL_KEY_CONFFIG:	//キーコンフィグ
			m_vBtmpos[2].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[2].x > m_vBtmposCopy[2].x + SELECT_BUTTOM_POP){
				m_vBtmpos[2].x = m_vBtmposCopy[2].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[2]){
					TexChange(2, 1);
					m_bButtunChange[2] = true;
				}
			}
			break;
		case SL_KEY_END:		//キーEND
			m_vBtmpos[3].x += SELECT_BUTTOM_ADD_POP;
			if(m_vBtmpos[3].x > m_vBtmposCopy[3].x + SELECT_BUTTOM_POP){
				m_vBtmpos[3].x = m_vBtmposCopy[3].x + SELECT_BUTTOM_POP;
				if(!m_bButtunChange[3]){
					TexChange(3, 1);
					m_bButtunChange[3] = true;
				}
			}
			break;
		default: break;
		}
		for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
		{	//位置を元に戻す
			if(m_nSelect == i)
				continue;
			if(m_vBtmpos[i].x > m_vBtmposCopy[i].x)
				m_vBtmpos[i].x -= SELECT_BUTTOM_MINUS_POP;
			if(m_vBtmpos[i].x < m_vBtmposCopy[i].x)
				m_vBtmpos[i].x = m_vBtmposCopy[i].x;
			if(m_bButtunChange[i])
				m_bButtunChange[i] = false;
			else
				TexChange(i, 0);
		}

		//決定キー
		if(m_pInput->GetBtnState(BTN_A) == TRG)
		{
			m_nState = SLCT_SELECT_ITEM;
		}
		
		//m_nState = SLCT_END;
		break;
	case SLCT_SELECT_ITEM:
		//選んだものによる動き
		switch(m_nSelect)
		{
		case SL_KEY_START:		//ゲームスタート
			//ボタンテクスチャを元の位置へ
			for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
				TexChange(i, 0);
			bflg = false;
			m_nState = SLCT_END;
			break;
		case SL_KEY_HOWTO:		//プレイ方法
			break;
		case SL_KEY_CONFFIG:	//キーコンフィグ
			break;
		case SL_KEY_END:		//キーEND
			m_nState = SLCT_END_SELECT;
			break;
		default: break;
		}
		break;
		

		//メニューに戻る
		if(m_pInput->GetBtnState(BTN_B) == TRG )	//…ESC
			m_nState = SLCT_MENU;

	case SLCT_END_SELECT:	//終了処理の有無
		
		switch(m_nInState)
		{
		case 0:
			//選択画面拡大
			if(m_EScl < 1.0f){
				m_EScl += SELECT_END_BG_ADD_SCALE;
			}
			if(m_EScl > 1.0f){
				m_EScl = 1.0f;	
				m_nInState = 1;
				bflg = false;
			}
		case 1:	//キー情報入力
			//ボタン選択
			if(m_pInput->GetBtnState(BTN_LEFT) == TRG )
			{
				m_nKeyEnd = 0;
				TexMovePutawayEnd(0);
			}

			if(m_pInput->GetBtnState(BTN_RIGHT) == TRG)
			{
				m_nKeyEnd = 1;
				TexMovePutawayEnd(1);
			}
			//決定キーで確定
			if(m_pInput->GetBtnState(BTN_A) == TRG)
			{
				switch(m_nKeyEnd)
				{
				case 0:
					//ゲームを続ける
					break;
				case 1:
					m_nState = SLCT_WINDOW_CLOSE;
					m_nKeyEnd = 0;
					break;
				default: break;
				}
				m_nInState = 2;
				m_nKeyEnd = 0;
				bflg = false;
			}
			break;
		case 2:
			//選択画面縮小
			if(m_EScl > SELECT_BUTTOM_END_FIRST_SCALE){
				m_EScl -= SELECT_END_BG_ADD_SCALE;
			}
			if(m_EScl < SELECT_BUTTOM_END_FIRST_SCALE){
				m_EScl = SELECT_BUTTOM_END_FIRST_SCALE;	
				m_nInState = 0;
				m_nState = SLCT_MENU;
			}
			break;
		}
		break;
	case SLCT_END:
		//ボタンをしまう
		if(!bflg){
			if(TexMovePutaway())
				bflg = true;
		}
		else
		{
			//タイトルを右へ退避
			m_Titlpos.x += 0.1f;
			//ステンシルを戻す
			if((m_vSSlide.x > 0.0f) || !FadeIn(&m_PFade)){
				m_vSSlide.y += 0.000002f;
				m_vSSlide.x -= 0.2f;
				//補正
				if(m_vSSlide.x < 0.0f)
					m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
			}else
			{
				m_pSE->StopBG(BG_SELECT);
				return true;		//次のシーンへ
			}
		}
		break;
	case SLCT_WINDOW_CLOSE:
		return true;
		break;
	default: break;
	}

	for(int i = 0; i < SLECT_DECO_NUM; i++)
		m_DAngM[i] += 1;
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// 描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::Draw(void)
{
	DrawPoli(m_PBg, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, -10.0f), 1,  m_TexID, true);
	DrawModel();
	DrawStencil();
	for(int i = 0; i < SLECT_BUTTOM_NUM; i ++)
		DrawPoli(m_PButtom[i], 0, VECTOR3(0.0f, 0.0f, 0.0f), m_vBtmpos[i], 1, m_TexID, true);
	DrawTitle();
	
	switch(m_nState)
	{
	case SLCT_APPEAR:
	case SLCT_CRACK:	
	case SLCT_MENU:	
		break;
	case SLCT_END_SELECT:		
		DrawPoli(m_PEndselect, 0, VECTOR3(1.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 0.0f), m_EScl, m_TexIDE, true);
		DrawPoli(m_PButtumEnd[0], 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(-(SELECT_BUTTOM_END_W + 0.3f) / 2.0f, -0.5f, 0.0f), m_EScl,  m_TexIDE, true);
		DrawPoli(m_PButtumEnd[1], 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3((SELECT_BUTTOM_END_W + 0.3f) / 2.0f, -0.5f, 0.0f), m_EScl,  m_TexIDE, true);
		break;
	case SLCT_END:
		break;
	default: break;
	}
	DrawPoli(m_PFade, 0, VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 10.0f),1,  m_TexIDF, true);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン描画
//--in--------------------------------------------
//POLYGON3D　参照
//回転角
//回転軸
//位置
//拡大率
//テクスチャID
//ビルボードフラグ
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawPoli(POLYGON3D &pol,  float ang, VECTOR3 axis, VECTOR3 pos, float scl,  int m_TexID, bool flg)
{
	GLdouble	matView[16];

	//初期処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
	glDepthMask(GL_FALSE);		//デプスバッファへの書き込み禁止

	//カラー指定
	glColor4f(pol.col.r, pol.col.g, pol.col.b, pol.col.a);
	//ポリゴン描画
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(m_TexID > 0)
	{
		glEnable(GL_TEXTURE_2D);	//テクスチャ有効化
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}
	//座標変換
	glPushMatrix();

	if(flg)
	{
		//ビルボード変換
		glGetDoublev(GL_MODELVIEW_MATRIX, (double *)&matView[0]);
		matView[0] = matView[5] = matView[10] = 1.0f;
		matView[1] = matView[2] = matView[4] = matView[6] = matView[8] = matView[9] = 0.0f;
		glLoadMatrixd(&matView[0]);
	}
	//ポリゴン描画
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef((GLfloat)ang, axis.x, axis.y, axis.z);
	glScalef((GLfloat)scl, (GLfloat)scl, (GLfloat)scl);
	glBegin(GL_POLYGON);
	for(int i = 0; i < 4; i ++)
	{
		glTexCoord2f(pol.tex[i].x, pol.tex[i].y);
		glVertex3f(pol.ver[i].x, pol.ver[i].y, pol.ver[i].z);
	}
	glEnd();
	glPopMatrix();

	//後処理
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);				//ブレンド無効
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);	//Zバッファ無効化
	glDepthMask(GL_TRUE);		//デプスバッファへの書き込み許可
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


//++++++++++++++++++++++++++++++++++++++++++++++++
// ポリゴン描画
//--in--------------------------------------------
//POLYGON3D　参照
//回転角
//回転軸
//位置
//テクスチャID
//ビルボードフラグ
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawStencil(void)
{
	//初期化
	glLoadIdentity();
	gluLookAt(m_pCmr->ViewPos.x, m_pCmr->ViewPos.y, m_pCmr->ViewPos.z, m_pCmr->ViewCent.x, m_pCmr->ViewCent.y, m_pCmr->ViewCent.z, 0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE, GL_FALSE,GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);

	//表面だけ描く
	glStencilFunc(GL_ALWAYS, 0, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glEnable(GL_CULL_FACE);
	DrawPoli(m_PStencil, SELECT_STENCIL_ANGLE, VECTOR3(0.0f, 0.0f, 1.0f), SELECT_STENCIL_MOVE, 1, -1, true);

	//裏面を描く
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	DrawPoli(m_PStencil, SELECT_STENCIL_ANGLE, VECTOR3(0.0f, 0.0f, 1.0f), SELECT_STENCIL_MOVE + m_vSSlide, 1, -1, true);

	//設定を戻す
	glFrontFace(GL_CCW);
	glColorMask(1, 1, 1, 1);
	glDepthMask(1);

	//-----------------------------------------------
	//影を付ける
	//-----------------------------------------------
	glStencilFunc(GL_NOTEQUAL, 0, ~0);
	glDisable(GL_LIGHTING);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);						//色
	glDisable(GL_DEPTH_TEST);								//デプステスト無効化
	glDisable(GL_CULL_FACE);								//裏面は描かない

	//影のステンシル部分を描画
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(100.0f, 100.0f, 15.0f); 
	glVertex3f(100.0f, -100.0f, 15.0f); 
	glVertex3f(-100.0f, -100.0f, 15.0f); 
	glVertex3f(-100.0f,  100.0f, 15.0f); 
	glEnd();
	glPopMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);						//色
	//処理設定を元に戻す
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// モデル描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawModel(void)
{
	//初期処理
	glEnable(GL_LIGHTING);		//ライトON
	glDisable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化

	//デコレーション描画
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);	//加算合成
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDD);
	for(int i = 0; i < SLECT_DECO_NUM; i ++)
	{
	glPushMatrix();
	glTranslatef(m_Ditlpos[i].x, m_Ditlpos[i].y, m_Ditlpos[i].z);
	glRotatef((GLfloat) m_DAng[i], 0.0f, 0.0f, 1.0f);
	glRotatef((GLfloat) m_DAngM[i], 0.0f, 1.0f, 0.0f);
	glScalef(m_DScl[i], m_DScl[i], m_DScl[i]);
	DrawMesh(&m_MeshDeco);
	glPopMatrix();
	}
	glDisable(GL_BLEND);

	//後処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
}

//++++++++++++++++++++++++++++++++++++++++++++++++
// タイトル描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void SELECT::DrawTitle(void)
{
	//初期処理
	glEnable(GL_LIGHTING);		//ライトON
	glDisable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化

	//タイトルの描画
	m_pShadeMng->UseShader(PHONG);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexIDT);
	glPushMatrix();
	glTranslatef(m_Titlpos.x, m_Titlpos.y, m_Titlpos.z);
	glRotatef((GLfloat)m_TAngZ, 1.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)m_TAngY, 0.0f, 1.0f, 0.0f);
	glScalef(m_TScl, m_TScl, m_TScl);
	m_pShadeMng->SetTexUnit(PHONG, 0);
	DrawMesh(&m_MeshT);
	glPopMatrix();
	m_pShadeMng->UnUseShader();

	//後処理
	glDisable(GL_LIGHTING);		//ライトオフ
	glEnable(GL_ALPHA_TEST);	//αテストON
	glEnable(GL_DEPTH_TEST);	//Zバッファ有効化
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// フェードイン　透明→有色
//--in--------------------------------------------
//
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::FadeIn(POLYGON3D *pol)
{
	static int nCnt = -1;

	//初回時
	if(nCnt < 0){
		nCnt = m_nCnt;	//現在のフレームカウント数を保存
		pol->col.a = 0.0f;
	}

	//α値を上げる
	if((m_nCnt - nCnt) < SELECT_FADE_TIME)
		pol->col.a += (1.0f / SELECT_FADE_TIME);
	else{
		pol->col.a = 1.0f;
		nCnt = -1;
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
// フェードアウト　有色→透明
//--in--------------------------------------------
//
//--out-------------------------------------------
// 終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool SELECT::FadeOut(POLYGON3D *pol)
{
	static int nCnt = -1;

	//初回時
	if(nCnt < 0){
		nCnt = m_nCnt;	//現在のフレームカウント数を保存
		pol->col.a = 1.0f;
	}

	//α値を上げる
	if((m_nCnt - nCnt) < SELECT_FADE_TIME && pol->col.a > 0.05f)
	{
		pol->col.a -= (1.0f / SELECT_FADE_TIME);
	}
	else{
		pol->col.a = 0.0f;
		nCnt = -1;
		return true;
	}
	return false;
}

//デバック用
int SELECT::GetSelect(void)
{
	return m_nSelect;
}
//################################################
// End of File
//################################################
