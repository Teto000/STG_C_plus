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
#include "application.h"

//------------------------
// 静的メンバ変数宣言
//------------------------

//===========================
// コンストラクタ
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_HP, 0, sizeof(m_HP));	//構造体のクリア
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
	m_HP.pos = pos;

	CObject2D::Init(m_HP.pos);

	CObject2D::SetSize(80.0f, 100.0f);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_HP.pos = CObject2D::GetPosition();

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

		//=============================
		// プレイヤーの処理
		//=============================
		if (type == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = CApplication::GetPlayer();

			//プレイヤーの残り体力を取得
			int PlayerLife = pPlayer->GetRemLife();

			//頂点座標の設定
			CObject2D::SetVtxCIE_SP(m_HP.pos, m_HP.fWidth,
				m_HP.fWidth / 2 + (m_HP.fLength * PlayerLife), m_HP.fHeight, m_HP.fHeight);

			//--------------------
			// HPが0になったら
			//--------------------
			if (m_HP.fLength * PlayerLife <= 0)
			{
				Uninit();
				CObject2D::Release();
			}
		}
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
CHp *CHp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE type)
{
	CHp *pHP = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pHP = new CHp;	//生成

	//構造体に値を代入
	pHP->m_HP.pos = pos;
	pHP->m_HP.move = move;
	pHP->m_HP.fWidth = fWidth;
	pHP->m_HP.fHeight = fHeight;
	pHP->m_HP.type = type;

	if (pHP != nullptr)
	{//NULLチェック
		//初期化
		pHP->Init(pHP->m_HP.pos);
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}