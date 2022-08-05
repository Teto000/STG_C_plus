//===================================
//
// HPの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nLife = 0;			//体力受け取り用
	m_nRemLife = 0;			//残り体力受け取り用
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_fLength = 0.0f;		//HPバーの長さ
	m_type = HPTYPE_MAX;	//種類
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
	m_pos = pos;
	m_fLength = (m_fWidth / 100);

	CObject2D::Init(m_pos);
	CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//頂点座標の設定
	CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
		-m_fWidth / 2 + (m_fLength * 100), -m_fHeight / 2, m_fHeight / 2);

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

	//-------------------
	// 移動
	//-------------------
	CObject2D::AddMove(m_move);

	//-------------------
	// HPの減少
	//-------------------
	switch (m_type)
	{
	//=============================
	// プレイヤーの処理
	//=============================
	case HPTYPE_PLAYER:

		//プレイヤーの体力を取得
		m_nLife = pPlayer->GetLife();

		//プレイヤーの残り体力を取得
		m_nRemLife = pPlayer->GetRemLife();
		break;

	default:
		break;
	}

	//HP減少時の処理
	SubHP();
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
	pHP->m_pos = pos;
	pHP->m_move = move;
	pHP->m_fWidth = fWidth;
	pHP->m_fHeight = fHeight;
	pHP->m_type = type;

	if (pHP != nullptr)
	{//NULLチェック
		//初期化
		pHP->Init(pHP->m_pos);
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}

//===========================
// HPの設定
//===========================
void CHp::SetLife(int nLife, int nRemLife)
{
	m_nLife = nLife;
	m_nRemLife = nRemLife;
}

//===========================
// HP減少時の処理
//===========================
void CHp::SubHP()
{
	//-------------------------
	// 頂点座標の設定
	//-------------------------
	if (m_nRemLife >= 1)
	{//残り体力(%)があるなら
		//その体力分の座標を設定
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + (m_fLength * m_nRemLife), -m_fHeight / 2, m_fHeight / 2);
	}
	else if (m_nRemLife == 0 && m_nLife > 0)
	{//残り体力が0% かつ 体力が0じゃないなら
		//1%分のゲージを維持
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + m_fLength, -m_fHeight / 2, m_fHeight / 2);
	}

	//-------------------------
	// HPごとの処理
	//-------------------------
	if (m_nRemLife <= 0 && m_nLife <= 0)
	{//HPが0になった かつ 体力がなかったら
		//HPバーの消去
		Uninit();
		return;
	}
	else if (m_nRemLife <= 20)
	{//HPが20%以下になったら
		//赤色にする
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_nRemLife <= 50)
	{//HPが50%以下になったら
		//黄色にする
		CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		//緑色にする
		CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}