//===================================
//
// エフェクトの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
#include "effect.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"

//===========================
// コンストラクタ
//===========================
CEffect::CEffect() : CObject2D()
{
	memset(&m_Effect, 0, sizeof(Effect));	//構造体のクリア
}

//===========================
// デストラクタ
//===========================
CEffect::~CEffect()
{

}

//===========================
// 初期化
//===========================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_Effect.pos = pos;			//位置
	m_Effect.nLife = 100;		//寿命
	m_Effect.fRadius = 50.0f;	//半径
	m_Effect.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//色

	CObject2D::Init(m_Effect.pos);

	CObject2D::SetSize(m_Effect.fRadius, m_Effect.fRadius);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_EFFECT);		//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CEffect::Update()
{
	CObject2D::Update();

	//徐々に小さくする
	m_Effect.fRadius -= 1.5f;

	//徐々に透明にする
	m_Effect.col.a -= 0.05f;

	if (m_Effect.fRadius <= 0.0f || m_Effect.col.a <= 0.0f)
	{//小さくなって消えた or 完全に透明なら
		//エフェクトの消去
		Uninit();
		CObject2D::Release();
	}
	else
	{
		//サイズの設定
		SetSize(m_Effect.fRadius, m_Effect.fRadius);

		//色の設定
		CObject2D::SetColor(m_Effect.col);
	}
}

//===========================
// 描画
//===========================
void CEffect::Draw()
{
	//αブレンディングを加算合成に設定
	CObject2D::SetAddALPHA();

	CObject2D::Draw();

	//αブレンディングを元に戻す
	CObject2D::ResAddALPHA();
}

//===========================
// 生成
//===========================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect *pEffect = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pEffect = new CEffect;	//生成

	if (pEffect != nullptr)
	{//NULLチェック
	 //初期化
		pEffect->Init(pos);
		pEffect->SetObjType(OBJTYPE_EFFECT);
	}

	return pEffect;
}