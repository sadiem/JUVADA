//################################################
// <Result.cpp>
//
//------------------------------------------------
// 2013/01/28 ~
//						SekiyamaRumi
//################################################
//================================================
//インクルードヘッダ
//================================================
#include "Result.h"	
#include "TexMng.h"		//テクスチャマネージャ
//================================================
//定数定義
//================================================
enum {
	RESULT_IN,			//入り
	RESULT_FRAME_IN,	//フレームイン
	RESULT_ITEM_IN,		//アイテムイン
	RESULT_TIME_IN,		//タイムイン
	RESULT_SCORE_IN,	//スコアイン
	RESULT_DEAD_IN,		//死亡数イン
	RESULT_VAL_IN,		//評価イン
	RESULT_WAIT_CLICK,	//ウェイト
	RESULT_FADE_ITEM,	//アイテムはける
	RESULT_END			//リザルト終了
};
//フェードタイム
#define RESULT_FADE_TIME	(120)		//フェードタイム
//BG
#define RESULT_BG_H (40)				//フェード板ポリ縦幅
#define RESULT_BG_W (40)				//　　　　　　　横幅
#define RESULT_BG_POS_X (-RESULT_BG_W / 2.0f)	//フェード板ポリ初期位置
#define RESULT_BG_POS_Y (RESULT_BG_POS_X)
//ステンシル
#define RESULT_STENCIL_H (27.0f)							//ステンシル板ポリ縦幅
#define RESULT_STENCIL_W (27.0f)							//　　　　　　　横幅
#define RESULT_STENCIL_X (-(RESULT_STENCIL_W / 2.0f))	//ステンシル板ポリ初期位置
#define RESULT_STENCIL_Y (RESULT_STENCIL_X)
#define RESULT_STENCIL_MOVE  (VECTOR3(13.5f, -8.5f, 1.0f))	//ステンシル移動値
#define RESULT_STENCIL_ANGLE	((GLfloat)10.0f)	//ステンシル回転角
#define RESULT_STENCIL_MOVE_VEC	(VECTOR3(cosf(RESULT_STENCIL_ANGLE), sinf(RESULT_STENCIL_ANGLE), 0.0f))	//ステンシル移動ベクトル

//評価
#define RESULT_VAL_H (5.0f)							//評価板ポリ縦幅
#define RESULT_VAL_W (5.0f)							//　　　　　　　横幅
#define RESULT_VAL_X (-(RESULT_VAL_W / 2.0f))		//評価板ポリ初期位置
#define RESULT_VAL_Y (RESULT_VAL_X)
#define RESULT_VAL_POS (VECTOR3(0.0f, 0.0f, 10.0f))	//位置
#define RESULT_VAL_POSA (VECTOR3(-4.3f, 1.3f, 5.0f))	//位置
#define RESULT_VAL_ADD_A (0.05f)					//α値加算
#define RESULT_VAL_ADD_Z (0.2f)
//PUSH ENTER用ボタン
#define RESULT_PUSHENTER_H (1)				//PushEnter板ポリ縦幅
#define RESULT_PUSHENTER_W (3)				//　　　　　　　横幅
#define RESULT_PUSHENTER_POS_X (-RESULT_PUSHENTER_W / 2.0f)	//PushEnter板ポリ初期位置
#define RESULT_PUSHENTER_POS_Y (RESULT_PUSHENTER_POS_X)
//デコ　フレーム
#define RESULT_FRAME_STOP	(0)			//左から右へ
#define RESULT_ADD_FRAME_SPEED	(1.0f)	//加算値
//デコ　上フレーム
#define RESULT_FRAME1_H	(2.0f)
#define RESULT_FRAME1_W	(20.0f)
#define RESULT_FRAME1_X (-RESULT_FRAME1_W / 2.0f)	//フェード板ポリ初期位置
#define RESULT_FRAME1_Y (RESULT_FRAME1_X)
#define RESULT_FRAME1_POS_FIR	(VECTOR3(-20.0f, 15.0f, 2.0f))	//初期位置
#define RESULT_FRAME1_POS_SET	(VECTOR3(0.0f, 15.0f, 2.0f))	//移動先位置
//デコ　下フレーム
#define RESULT_FRAME2_H	(2.0f)
#define RESULT_FRAME2_W	(20.0f)
#define RESULT_FRAME2_X (-RESULT_FRAME2_W / 2.0f)	//フェード板ポリ初期位置
#define RESULT_FRAME2_Y (RESULT_FRAME2_X)
#define RESULT_FRAME2_POS_FIR	(VECTOR3(20.0f, 3.2f, 2.0f))	//初期位置
#define RESULT_FRAME2_POS_SET	(VECTOR3(0.0f, 3.2f, 2.0f))		//移動先位置
//出力項目名
#define RESULT_ITEM_NAME_ADD_MOVE_TEX  (0.04f)	//出力項目出現
#define RESULT_ITEM_NAME_W (10.0f)
#define RESULT_ITEM_NAME_H (1.5f)
#define RESULT_ITEM_NAME_X (-RESULT_ITEM_NAME_W / 2.0f)
#define RESULT_ITEM_NAME_Y (0.0f)
#define RESULT_ITEM_NAME_SPACE (1.0f)
#define RESULT_ITEM_NAME_FIR_Y (0.3f)
#define RESULT_ITEM_POS_NAME1 (VECTOR3(4.5f, RESULT_ITEM_NAME_FIR_Y, 0.0f))
#define RESULT_ITEM_POS_NAME2 (VECTOR3(4.5f, -(RESULT_ITEM_NAME_H + RESULT_ITEM_NAME_SPACE) + RESULT_ITEM_NAME_FIR_Y, 0.0f))
#define RESULT_ITEM_POS_NAME3 (VECTOR3(4.5f, -(RESULT_ITEM_NAME_H + RESULT_ITEM_NAME_SPACE) * 2 + RESULT_ITEM_NAME_FIR_Y, 0.0f))
//================================================
//構造体定義
//================================================

//++++++++++++++++++++++++++++++++++++++++++++++++
//初期化
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Init(void)		//初期化
{
	m_pCmr = CAMERA::Instance();
	m_pScr = SCORE::Instance();
	m_pDeadNum = DEAD_NUM::Instance();
	m_pPlayer  = PLAYER::Instance();
	m_pTime    = TIME_MNG::Instance();
	m_Input   = INPUT_MNG::getInstance();
	Reset();
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//リセット
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Reset(void)	//リセット
{
	Load();
	COLOR col = {1.0f, 1.0f, 1.0f, 1.0f};
	m_fade.Reset();
	m_nCnt = 0;
	m_nState = 0;
	//タイムを受け取り
	//m_nTime = 0;
	//m_pTime->Reset();
	m_pTime->SetPos(520, 240, 25, 40);

	m_bScrFlg = false;			//スコア描画フラグ
	m_bTimFlg = false;			//タイム描画フラグ
	m_bDeadFlg = false;			//死亡数描画フラグ
	flg = 0;

	//スコア情報セット
	m_pScr->SetTexID(m_TexIDS);
	m_pScr->SetVer(545, 435, 35, 46);
	m_pScr->SetNum();
	//死亡数情報セット
	m_pDeadNum->SetVer(545, 335, 35, 46);
	m_pDeadNum->SetTexID(m_TexIDS);
	m_pDeadNum->SetNum(m_pPlayer->m_DeadNum);

	//評価値を計算
	m_Val = m_pScr->ColEvolution();

	//カラー指定
	for(int i = 0; i < RESULT_MATERIAL_NUM; i ++)
		PlySetCol(&m_pol[i], col);
	m_pol[RESULT_VAL].col.a = 0.0f;	//透過からスタート

	//座標指定
	PlySetVer(&m_pol[RESULT_BG], RESULT_BG_POS_X, RESULT_BG_POS_Y, RESULT_BG_W, RESULT_BG_H);
	PlySetVer(&m_pol[RESULT_BG_FRAME1], RESULT_FRAME1_X, RESULT_FRAME1_Y, RESULT_FRAME1_W, RESULT_FRAME1_H);
	PlySetVer(&m_pol[RESULT_BG_FRAME2], RESULT_FRAME2_X, RESULT_FRAME2_Y, RESULT_FRAME2_W, RESULT_FRAME2_H);
	PlySetVer(&m_pol[RESULT_BG_STENCIL], RESULT_STENCIL_X, RESULT_STENCIL_Y, RESULT_STENCIL_W, RESULT_STENCIL_W);
	PlySetVer(&m_pol[RESULT_VAL], RESULT_VAL_X, RESULT_VAL_Y, RESULT_VAL_W, RESULT_VAL_W);

	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
		PlySetVer(&m_pol[i], RESULT_ITEM_NAME_X, RESULT_ITEM_NAME_Y, RESULT_ITEM_NAME_W, RESULT_ITEM_NAME_H);
	
	//テクスチャ座標指定
	PlySetTex(&m_pol[RESULT_BG], 8, 16, 8, 16, 16);
	PlySetTex(&m_pol[RESULT_BG_FRAME1], 0, 16, 0, 2, 16);
	PlySetTex(&m_pol[RESULT_BG_FRAME2], 0, 16, 2, 4, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME1], 8, 16, 6, 7, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME2], 8, 16, 5, 6, 16);
	PlySetTex(&m_pol[RESULT_ITEM_NAME3], 8, 16, 4, 5, 16);
	float w;
	w = (float)4 * (m_Val % 4);

	if(m_Val > 3)
		PlySetTex(&m_pol[RESULT_VAL], (float)4 * (m_Val % 4), (float)4 * (m_Val % 4) + 4,  4,  8, 16);
	else
		PlySetTex(&m_pol[RESULT_VAL], (float)4 * (m_Val % 4), (float)4 * (m_Val % 4) + 4,  0,  4, 16);

	//ビルボード用値の初期化
	for(int i = 0; i < RESULT_MATERIAL_NUM; i ++){
		m_bil[i].Angle = 0.0f;
		m_bil[i].axis = VECTOR3(0.0f, 0.0f, 0.0f);
		m_bil[i].pos = VECTOR3(0.0f, 0.0f, 0.0f);
		m_bil[i].ScaleRate = 1.0f;
		m_bil[i].vec = VECTOR3(0.0f, 0.0f, 0.0f);
	}
	//位置の初期設定
	m_bil[RESULT_BG].pos = VECTOR3(0.0f, 0.0f, -10.0f);
	m_bil[RESULT_BG_FRAME1].pos = RESULT_FRAME1_POS_FIR;
	m_bil[RESULT_BG_FRAME2].pos = RESULT_FRAME2_POS_FIR;
	m_bil[RESULT_BG_STENCIL].pos = RESULT_STENCIL_MOVE;
	m_bil[RESULT_ITEM_NAME1].pos = RESULT_ITEM_POS_NAME1;
	m_bil[RESULT_ITEM_NAME2].pos = RESULT_ITEM_POS_NAME2;
	m_bil[RESULT_ITEM_NAME3].pos = RESULT_ITEM_POS_NAME3;	
	m_bil[RESULT_VAL].pos = RESULT_VAL_POS;
	
	//角度初期化
	m_bil[RESULT_BG_STENCIL].Angle = RESULT_STENCIL_ANGLE;
	m_bil[RESULT_BG_STENCIL].axis = VECTOR3(0.0f, 0.0f, 1.0f);
	m_bil[RESULT_BG_STENCIL].ScaleRate = 1.0f;

	//デコレーション初期値セット
	for(int i = 0; i < RESULT_DECO_NUM; i ++){
		m_Ditlpos[i].x = 2.0f * i;			//デコレーション位置
		m_Ditlpos[i].y = 1.0f * i;	//デコレーション位置
		m_Ditlpos[i].z = -5.0f;						//デコレーション位置
		m_DAng[i] = 72.0f * (i + 1);				//デコレーション回転 傾き
		m_DAngM[i] = 0;								//デコレーション回転 自身の回転
		m_DScl[i] = 0.3f + (i + 1) * 0.1f;			//デコレーション拡大
	}

	//ステンシルの移動方向
	m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//読み込み
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Load(void)
{
	//テクスチャ
	m_TexID = g_TexMng.GetTexture("TEXTURE\\RESULT\\result.png", "RESULT");
	m_TexIDD = g_TexMng.GetTexture("TEXTURE\\SELECT\\deko.png", "RESULT");
	m_TexIDS = g_TexMng.GetTexture("TEXTURE\\2D\\number.png", "RESULT");
	m_TexIDV = g_TexMng.GetTexture("TEXTURE\\RESULT\\resultScore.png", "RESULT");
	m_TexIDT = g_TexMng.GetTexture("TEXTURE\\2D\\time.png", "RESULT");
	//モデル
	g_MeshMng.GetMesh(&m_MeshDeco, "MODEL\\OP\\deco.x", "RESULT");
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//解放
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Release(void)
{
	g_TexMng.ReleaseCat("RESULT");
	g_MeshMng.ReleaseCat("RESULT");
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//アイテム移動　
//ゲーム画面から移り変わった時
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//テクスチャ移動終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::ItemMoveAppear(void)
{
	//ボタン
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
	{	
		m_pol[i].tex[0].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[1].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[2].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[3].x -= RESULT_ITEM_NAME_ADD_MOVE_TEX;
	}
	//補正
	if(m_pol[RESULT_ITEM_NAME1].tex[3].x <= 0.5f)
	{	//補正値代入
		for(int k = RESULT_ITEM_NAME1; k < RESULT_ITEM_NAME1 + 3; k ++){
			m_pol[k].tex[0].x = 0.0f;
			m_pol[k].tex[1].x = 0.0f;
			m_pol[k].tex[2].x = 0.5f;
			m_pol[k].tex[3].x = 0.5f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//アイテム移動　
//結果画面からセレクト画面へ移った時
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//テクスチャ移動終了フラグ
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::ItemMoveClose(void)
{
	//ボタン
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i ++)
	{	
		m_pol[i].tex[0].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[1].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[2].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
		m_pol[i].tex[3].x += RESULT_ITEM_NAME_ADD_MOVE_TEX;
	}
	//補正
	if(m_pol[RESULT_ITEM_NAME1].tex[3].x >= 1.0f)
	{	//補正値代入
		for(int k = RESULT_ITEM_NAME1; k < RESULT_ITEM_NAME1 + 3; k ++){
			m_pol[k].tex[0].x = 0.5f;
			m_pol[k].tex[1].x = 0.5f;
			m_pol[k].tex[2].x = 1.0f;
			m_pol[k].tex[3].x = 1.0f;
		}
		return true;
	}
	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//更新
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
bool RESULT_MNG::Update(void)
{
	m_nCnt++;
	m_fade.SetFrame(m_nCnt);
	switch(m_nState)
	{
	case RESULT_IN:			//入り
		if(m_fade.FadeOut(RESULT_FADE_TIME))
			m_nState = RESULT_FRAME_IN;
		break;
	case RESULT_FRAME_IN:	//フレームイン
		if(m_bil[RESULT_BG_FRAME1].pos.x < RESULT_FRAME_STOP)
		{
			m_bil[RESULT_BG_FRAME1].pos.x += RESULT_ADD_FRAME_SPEED;
			m_bil[RESULT_BG_FRAME2].pos.x -= RESULT_ADD_FRAME_SPEED;
		}else
			m_nState = RESULT_ITEM_IN;
		break;
	case RESULT_ITEM_IN:		//アイテムイン
		//画面割れる
		if(m_vSSlide.x < 2.0f){
			m_vSSlide.y -= 0.000001f;
			m_vSSlide.x += 0.1f;
		}else
		{//アイテム名出現	(タイム・死亡回数・スコア)
			if(ItemMoveAppear())
				m_nState = RESULT_TIME_IN;
		}
		break;
	case RESULT_TIME_IN:		//タイムイン
		m_bTimFlg = true;
		m_nState = RESULT_DEAD_IN;
		break;
	case RESULT_DEAD_IN:
		m_bDeadFlg = true;
		m_nState = RESULT_SCORE_IN;
		break;
	case RESULT_SCORE_IN:	//スコアイン
		m_bScrFlg = true;
		Cnt = m_nCnt;			//カウンタセット
		m_nState = RESULT_VAL_IN;
		break;
	case RESULT_VAL_IN:		//評価イン
		
		//回転
		m_bil[RESULT_VAL].axis = VECTOR3(0.0f, 1.0f, 0.0f);
		m_bil[RESULT_VAL].Angle += 10;
		
		//α値1.0まで上げる
		if(m_pol[RESULT_VAL].col.a < 1.0f)
			m_pol[RESULT_VAL].col.a += RESULT_VAL_ADD_A;
		if(m_pol[RESULT_VAL].col.a > 1.0f)
		{
			m_pol[RESULT_VAL].col.a = 1.0f;
		}
		//移動
		if(m_nCnt - Cnt < 60)
			m_bil[RESULT_VAL].pos +=  (RESULT_VAL_POSA - RESULT_VAL_POS) / 120;
		if(m_nCnt - Cnt > 60)
		{
			m_bil[RESULT_VAL].Angle = 0;
			Cnt = 0;
			m_bil[RESULT_VAL].pos = RESULT_VAL_POSA;
			m_nState = RESULT_WAIT_CLICK;
		}
		break;
	case RESULT_WAIT_CLICK:	//ウェイト
		if(m_Input->GetBtnState(BTN_A) == TRG){
			m_nState = RESULT_FADE_ITEM;
			m_bTimFlg = false;
			m_bScrFlg = false;
			m_bDeadFlg = false;
		}
		break;
	case RESULT_FADE_ITEM:	//アイテムはける
		//アイテム名はける	(タイム・死亡回数・スコア)
		if(!flg){
			if(ItemMoveClose())
				flg = true;
			//α値1.0まで上げる
			if(m_pol[RESULT_VAL].col.a > 0.0f)
				m_pol[RESULT_VAL].col.a -= RESULT_VAL_ADD_A * 3;
			if(m_pol[RESULT_VAL].col.a < 0.0f)
				m_pol[RESULT_VAL].col.a = 0.0f;
		}
		else
		{	//画面閉じる
			if(m_vSSlide.x > 0.0f){
				m_vSSlide.y += 0.000001f;
				m_vSSlide.x -= 0.1f;
				//補正
				if(m_vSSlide.x < 0.0f)
					m_vSSlide = VECTOR3(0.0f, 0.0f, 0.0f);
				//フレームをしまう
				if(m_bil[RESULT_BG_FRAME1].pos.x < 4.5f)
				{
					m_bil[RESULT_BG_FRAME1].pos.x -= RESULT_ADD_FRAME_SPEED * 1.0f;
					m_bil[RESULT_BG_FRAME2].pos.x += RESULT_ADD_FRAME_SPEED * 1.0f;
				}
			}
			//フェードアウト
			if(m_fade.FadeIn(RESULT_FADE_TIME))
					m_nState = RESULT_END;
		}

		break;
	case RESULT_END:			//リザルト終了
		return true;
	default:break;
	}

	//デコレーション回転
	for(int i = 0; i < RESULT_DECO_NUM; i++)
		m_DAngM[i] += 1;

	return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//描画
//--in--------------------------------------------
//
//--out-------------------------------------------
//
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::Draw(void)
{	
	PlyDrawPoliBillBoard(m_pol[RESULT_BG], m_bil[RESULT_BG].Angle, m_bil[RESULT_BG].axis, m_bil[RESULT_BG].pos, m_TexID);
	DrawModel();
	DrawStencil();
	for(int i = RESULT_ITEM_NAME1; i < RESULT_ITEM_NAME1 + 3; i++)
		PlyDrawPoliBillBoard(m_pol[i], m_bil[i].Angle, m_bil[i].axis, m_bil[i].pos, m_TexID);
	PlyDrawPoliBillBoard(m_pol[RESULT_VAL], m_bil[RESULT_VAL].Angle, m_bil[RESULT_VAL].axis, m_bil[RESULT_VAL].pos, m_TexIDV);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_FRAME1], m_bil[RESULT_BG_FRAME1].Angle, m_bil[RESULT_BG_FRAME1].axis, m_bil[RESULT_BG_FRAME1].pos, m_TexID);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_FRAME2], m_bil[RESULT_BG_FRAME2].Angle, m_bil[RESULT_BG_FRAME2].axis, m_bil[RESULT_BG_FRAME2].pos, m_TexID);
	m_fade.Draw();
}
void RESULT_MNG::Draw2D(void)
{
	if(m_bScrFlg)
		m_pScr->Draw();
	if(m_bTimFlg)
		m_pTime->Draw(m_TexIDT);
	if(m_bDeadFlg)
		m_pDeadNum->Draw();

}
//++++++++++++++++++++++++++++++++++++++++++++++++
// モデル描画
//--in--------------------------------------------
//なし
//--out-------------------------------------------
//なし
//++++++++++++++++++++++++++++++++++++++++++++++++
void RESULT_MNG::DrawModel(void)
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
	for(int i = 0; i < RESULT_DECO_NUM; i ++)
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
void RESULT_MNG::DrawStencil(void)
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
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_STENCIL], m_bil[RESULT_BG_STENCIL].Angle, m_bil[RESULT_BG_STENCIL].axis, m_bil[RESULT_BG_STENCIL].pos, -1);
	
	//裏面を描く
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	PlyDrawPoliBillBoard(m_pol[RESULT_BG_STENCIL], m_bil[RESULT_BG_STENCIL].Angle, m_bil[RESULT_BG_STENCIL].axis, m_bil[RESULT_BG_STENCIL].pos + m_vSSlide, -1);
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
//################################################
// End of File
//################################################