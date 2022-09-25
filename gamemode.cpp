//===================================
//
// ゲームモードの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "gamemode.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CGameMode::CGameMode() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CGameMode::~CGameMode()
{

}

//===========================
// 初期化
//===========================
HRESULT CGameMode::Init(D3DXVECTOR3 pos)
{
	//------------------
	// 構造体の初期化
	//------------------
	m_pos = pos;
	m_fWidth = 300.0f;
	m_fHeight = 50.0f;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CGameMode::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CGameMode::Update()
{
	CObject2D::Update();
}

//===========================
// 描画
//===========================
void CGameMode::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CGameMode *CGameMode::Create(D3DXVECTOR3 pos)
{
	CGameMode *pGameMode = nullptr;

	//----------------------------------
	// エクスプロージョンの生成と初期化
	//----------------------------------
	pGameMode = new CGameMode;	//生成

	if (pGameMode != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
		//初期化
		pGameMode->Init(pos);
		pGameMode->SetObjType(OBJTYPE_EXPLOSION);
	}

	return pGameMode;
}