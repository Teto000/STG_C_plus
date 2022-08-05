//===================================
//
// バリアの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "barrier.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//===========================
// コンストラクタ
//===========================
CBarrier::CBarrier() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CBarrier::~CBarrier()
{

}

//===========================
// 初期化
//===========================
HRESULT CBarrier::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;	//位置

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));	//色の設定

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CBarrier::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CBarrier::Update()
{
	CObject2D::Update();

	if (CObject2D::GetCollision(OBJTYPE_BULLET))
	{
		Uninit();
		return;
	}
}

//===========================
// 描画
//===========================
void CBarrier::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	CBarrier *pBarrier = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------zz
	pBarrier = new CBarrier;	//生成

	if (pBarrier != nullptr)
	{//NULLチェック
		//構造体に代入
		pBarrier->m_move = move;				//移動量
		pBarrier->m_fWidth = fWidth + 50.0f;	//幅
		pBarrier->m_fHeight = fHeight + 50.0f;	//高さ

		//初期化
		pBarrier->Init(pos);
		pBarrier->SetObjType(OBJTYPE_BARRIER);
	}

	return pBarrier;
}