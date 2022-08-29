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

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);
		m_fWidth = SCREEN_WIDTH / 2;
		m_fHeight = SCREEN_HEIGHT - 150.0f;
		m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

		switch (m_type)
		{
		case BGTYPE_NORMAL:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG);	//テクスチャの設定
			m_fWidth = SCREEN_WIDTH;
			m_fHeight = SCREEN_HEIGHT;
			m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		case BGTYPE_FIELD_PLAYER:
			m_pObject2D->SetTexture(CTexture::TEXTURE_FIELD_PLAYER);
			break;

		case BGTYPE_FIELD_ENEMY:
			m_pObject2D->SetTexture(CTexture::TEXTURE_FIELD_ENEMY);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
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
		m_pObject2D = nullptr;
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

		if (m_type == BGTYPE_FIELD_PLAYER && m_pObject2D->GetCollision(OBJTYPE_ENEMY))
		{
			m_fWidth--;
			m_pos.x -= 0.5f;

			if (m_type == BGTYPE_FIELD_ENEMY)
			{
				m_fWidth++;
				m_pos.x -= 0.5f;
			}
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
		m_pObject2D->SetPosition(m_pos);
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
CBg *CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBG = nullptr;

	//----------------------------------
	// 背景の生成と初期化
	//----------------------------------
	pBG = new CBg;	//生成
	pBG->m_pObject2D = new CObject2D;

	if (pBG != nullptr)
	{//NULLチェック
		pBG->m_type = type;

		//初期化
		pBG->Init(pos);
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