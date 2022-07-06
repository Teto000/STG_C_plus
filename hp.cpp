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
#include "object2D.h"
#include "player.h"
#include "enemy.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_HP, 0, sizeof(HP));	//構造体のクリア
	m_nPlayerLife = 0;
	m_nEnemyLife = 0;
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
	m_HP.fLength = (m_HP.fWidth / 100);

	CObject2D::Init(m_HP.pos);

	//頂点座標の設定
	CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
		-m_HP.fWidth / 2 + (m_HP.fLength * 100), -m_HP.fHeight / 2, m_HP.fHeight / 2);

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//テクスチャの設定

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
	// クラスの取得
	//-------------------
	CPlayer *pPlayer = CApplication::GetPlayer();	//プレイヤー
	CEnemy *pEnemy = CApplication::GetEnemy();		//敵

	//-------------------
	// HPの減少
	//-------------------
	switch (m_HP.type)
	{
		//=============================
		// プレイヤーの処理
		//=============================
	case HPTYPE_PLAYER:

		//プレイヤーの残り体力を取得
		m_nPlayerLife = pPlayer->GetRemLife();

		//頂点座標の設定
		CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
			-m_HP.fWidth / 2 + (m_HP.fLength * m_nPlayerLife), -m_HP.fHeight / 2, m_HP.fHeight / 2);

		//--------------------
		// HPが0になったら
		//--------------------
		if (m_HP.fLength * m_nPlayerLife <= 0)
		{
			Uninit();
			CObject2D::Release();
		}
		break;

		//=============================
		// 敵の処理
		//=============================
	case HPTYPE_ENEMY:

		//敵の残り体力を取得
		m_nEnemyLife = pEnemy->GetRemLife();

		//頂点座標の設定
		CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
			-m_HP.fWidth / 2 + (m_HP.fLength * m_nEnemyLife), -m_HP.fHeight / 2, m_HP.fHeight / 2);

		//--------------------
		// HPが0になったら
		//--------------------
		if (m_HP.fLength * m_nEnemyLife <= 0)
		{
			Uninit();
			CObject2D::Release();
		}
		break;

	default:
		break;
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