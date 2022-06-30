//===================================
//
// 爆発の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "explosion.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//------------------------
// マクロ定義
//------------------------
#define TEX_DIVISION	(8)	//テクスチャの分割数

//------------------------
//静的メンバ変数
//------------------------


//===========================
// コンストラクタ
//===========================
CExplosion::CExplosion() : CObject2D()
{
	m_nCnterAnim = 0;
	m_nPatternAnim = 0;
}

//===========================
// デストラクタ
//===========================
CExplosion::~CExplosion()
{

}

//===========================
// 初期化
//===========================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);

	CObject2D::SetSize(80.0f, 80.0f);	//サイズの設定

	CObject2D::SetTexCIE(0.0f, 1.0f / TEX_DIVISION);	//テクスチャ座標の設定

	CObject2D::SetTexture(CTexture::TEXTURE_EXPLOSION);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CExplosion::Update()
{
	CObject2D::Update();

	float fPart = (1.0f / TEX_DIVISION);

	m_nCnterAnim++;

	if ((m_nCnterAnim % TEX_DIVISION) == 0)
	{
		m_nPatternAnim++;

		CObject2D::SetTexCIE((fPart *m_nPatternAnim), (fPart * (m_nPatternAnim + 1)));

		if (m_nPatternAnim >= TEX_DIVISION)
		{//パターンが最大数に達したら
			m_nCnterAnim = 0;
			m_nPatternAnim = 0;
			CObject2D::Uninit();
			CObject2D::Release();	//解放
		}
	}
}

//===========================
// 描画
//===========================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = nullptr;

	//----------------------------------
	// エクスプロージョンの生成と初期化
	//----------------------------------
	pExplosion = new CExplosion;	//生成

	if (pExplosion != nullptr)
	{//NULLチェック
		//初期化
		pExplosion->Init(pos);
		pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	}

	return pExplosion;
}