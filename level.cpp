//===================================
//
// レベルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "level.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"

//===========================
// コンストラクタ
//===========================
CLevel::CLevel() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CLevel::~CLevel()
{

}

//===========================
// 初期化
//===========================
HRESULT CLevel::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fWidth = 100.0f;
	m_fHeight = 100.0f;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_RING);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CLevel::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CLevel::Update()
{
	CObject2D::Update();
}

//===========================
// 描画
//===========================
void CLevel::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CLevel *CLevel::Create()
{
	CLevel *pLevel = nullptr;

	//----------------------------------
	// レベルの生成と初期化
	//----------------------------------
	pLevel = new CLevel;	//生成

	if (pLevel != nullptr)
	{//NULLチェック
		//初期化
		pLevel->Init(D3DXVECTOR3(120.0f, 100.0f, 0.0f));
		pLevel->SetObjType(OBJTYPE_LEVEL);
	}

	return pLevel;
}