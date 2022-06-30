//===================================
//
// HPの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
#include "hp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "player.h"

//------------------------
// 静的メンバ変数宣言
//------------------------

//===========================
// コンストラクタ
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_aHP, 0, sizeof(m_aHP));	//構造体のクリア
}

//===========================
// デストラクタ
//===========================
CHp::~CHp()
{

}

//===========================
// 初期化
//===========================
HRESULT CHp::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_aHP.pos = pos;

	CObject2D::Init(m_aHP.pos);

	CObject2D::SetSize(80.0f, 100.0f);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_aHP.pos = CObject2D::GetPosition();

	return S_OK;
}

//===========================
// 終了
//===========================
void CHp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CHp::Update()
{
	CObject2D::Update();

	//-------------------
	// HPの減少
	//-------------------
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GETObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		//オブジェクトの種類の取得
		CObject::EObjType type = pObject->GetObjType();

		////=============================
		//// プレイヤーの処理
		////=============================
		//if (type == OBJTYPE_PLAYER)
		//{
		//	//プレイヤーの残り体力を取得
		//	int PlayerLife = GetRemLife();

		//	//--------------------
		//	// HPが0になったら
		//	//--------------------
		//	if (m_aHP.fLength * pPlayer->nRemLife <= 0)
		//	{
		//		Uninit();
		//		CObject2D::Release();
		//	}

		//	//---------------------------
		//	// 頂点座標の移動
		//	//---------------------------
		//	pVtx[0].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2, -hp->fHeight / 2, 0.0f);
		//	pVtx[1].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2 + (hp->fLength * pPlayer->nRemLife), -hp->fHeight / 2, 0.0f);
		//	pVtx[2].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2, hp->fHeight / 2, 0.0f);
		//	pVtx[3].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2 + (hp->fLength * pPlayer->nRemLife), hp->fHeight / 2, 0.0f);
		//}
	}
}

//===========================
// 描画
//===========================
void CHp::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CHp *CHp::Create()
{
	CHp *pHP = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pHP = new CHp;	//生成

	if (pHP != nullptr)
	{//NULLチェック
	 //初期化
		pHP->Init(D3DXVECTOR3(400.0f, SCREEN_HEIGHT / 2, 0.0f));
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}