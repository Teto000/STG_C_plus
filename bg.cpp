//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "bg.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CBg::CBg() : CObject()
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//===========================
// デストラクタ
//===========================
CBg::~CBg()
{

}

//===========================
// 初期化
//===========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fWidth = SCREEN_WIDTH;
	m_fHeight = SCREEN_HEIGHT;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);

		m_pObject2D->SetSize(m_fWidth, m_fHeight);

		m_pObject2D->SetTexture(CTexture::TEXTURE_BG);	//テクスチャの設定
	}

	return S_OK;
}

//===========================
// 終了
//===========================
void CBg::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
	}
}

//===========================
// 更新
//===========================
void CBg::Update()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Update();
	}
}

//===========================
// 描画
//===========================
void CBg::Draw()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Draw();
	}
}

//===========================
// 生成
//===========================
CBg *CBg::Create()
{
	CBg *pBG = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBG = new CBg;	//生成
	pBG->m_pObject2D = new CObject2D;

	if (pBG != nullptr)
	{//NULLチェック
	 //初期化
		pBG->Init(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
		pBG->SetObjType(OBJTYPE_BG);
	}

	return pBG;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CBg::GetPosition()
{
	return m_pos;
}

//===========================
// 幅の取得
//===========================
float CBg::GetWidth()
{
	return m_fWidth;
}

//===========================
// 高さの取得
//===========================
float CBg::GetHeight()
{
	return m_fHeight;
}