//===================================
//
// エネミーの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Barrier, 0, sizeof(Barrier));	//構造体のクリア
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
	m_Barrier.pos = pos;			//位置
	m_Barrier.nLife = 120;		//体力
	m_Barrier.fWidth = 100.0f;	//幅
	m_Barrier.fHeight = 100.0f;	//高さ

	CObject2D::Init(m_Barrier.pos);

	CObject2D::SetSize(m_Barrier.fWidth, m_Barrier.fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//テクスチャの設定

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
	CBarrier *pEnemy = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------zz
	pEnemy = new CBarrier;	//生成

	if (pEnemy != nullptr)
	{//NULLチェック
	 //初期化
		pEnemy->Init(D3DXVECTOR3(800.0f, SCREEN_HEIGHT / 2, 0.0f));
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}