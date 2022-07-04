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
#include <memory.h>
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
	memset(&m_Explosion, 0, sizeof(m_Explosion));	//構造体のクリア
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
	//------------------
	// 構造体の初期化
	//------------------
	m_Explosion.nLife = 100;
	m_Explosion.pos = pos;
	m_Explosion.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Explosion.fWidth = 80.0f;
	m_Explosion.fHeight = 80.0f;

	CObject2D::Init(m_Explosion.pos);

	CObject2D::SetSize(m_Explosion.fWidth, m_Explosion.fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_RING);	//テクスチャの設定

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

	//--------------------
	// 拡大
	//--------------------
	m_Explosion.fWidth += 3;
	m_Explosion.fHeight += 3;

	CObject2D::SetPosition(m_Explosion.pos);	//位置の設定
	CObject2D::SetSize(m_Explosion.fWidth, m_Explosion.fHeight);	//サイズの設定
	CObject2D::SetVtxCIE(m_Explosion.pos, m_Explosion.fWidth, m_Explosion.fHeight);	//頂点座標の設定

	//--------------------
	// 徐々に透過
	//--------------------
	m_Explosion.col.a -= 0.05f;
	SetColor(m_Explosion.col);
	
	//--------------------
	// 寿命
	//--------------------
	//寿命の減少
	m_Explosion.nLife--;

	//寿命が尽きた
	if (m_Explosion.nLife <= 0)
	{
		CObject2D::Uninit();
		CObject2D::Release();	//解放
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