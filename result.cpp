//===================================
//
// リザルトの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "result.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg *CResult::m_pBG = nullptr;	//背景

//===========================
// コンストラクタ
//===========================
CResult::CResult()
{

}

//===========================
// デストラクタ
//===========================
CResult::~CResult()
{

}

//===========================
// 初期化
//===========================
HRESULT CResult::Init()
{
	//背景の生成
	m_pBG->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		, CBg::BGTYPE_NORMAL);

	return S_OK;
}

//===========================
// 終了
//===========================
void CResult::Uninit()
{

}

//===========================
// 更新
//===========================
void CResult::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_TITLE);
	}
}

//===========================
// 背景の取得
//===========================
CBg *CResult::GetBG()
{
	return m_pBG;
}