//===================================
//
// タイトルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <time.h>
#include "title.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg *CTitle::m_pBG = nullptr;	//背景

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
	m_pBG->Create();

	return S_OK;
}

//===========================
// 終了
//===========================
void CTitle::Uninit()
{

}

//===========================
// 更新
//===========================
void CTitle::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// 背景の取得
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG;
}