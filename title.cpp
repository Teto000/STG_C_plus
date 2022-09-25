//===================================
//
// タイトルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"
#include "sound.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg *CTitle::m_pBG[MaxBg] = {};	//背景

//===========================
// コンストラクタ
//===========================
CTitle::CTitle()
{

}

//===========================
// デストラクタ
//===========================
CTitle::~CTitle()
{

}

//===========================
// 初期化
//===========================
HRESULT CTitle::Init()
{
	//背景の生成
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_TITLE);

	m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f)
					, CBg::BGTYPE_TITLE_LOGO);

	m_pBG[2]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f)
					, CBg::BGTYPE_TITLE_ENTER);

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CTitle::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_TITLE);
}

//===========================
// 更新
//===========================
void CTitle::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SEの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// 背景の取得
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG[0];
}