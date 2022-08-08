//===================================
//
// エネミーの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "bullet.h"
#include "texture.h"
#include "hp.h"
#include "barrier.h"
#include "explosion.h"
#include "level.h"
#include "score.h"

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_nLife = 0;			//体力
	m_nMaxLife = 0;			//最大体力
	m_nRemLife = 0;			//残り体力
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_type = ENEMYTYPE_MAX;	//種類
	m_Hp = nullptr;
}

//===========================
// デストラクタ
//===========================
CEnemy::~CEnemy()
{

}

//===========================
// 初期化
//===========================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;		//位置
	m_fWidth = 100.0f;	//幅
	m_fHeight = 100.0f;	//高さ
	m_nLife = 120;		//体力
	m_nMaxLife = 120;	//最大体力
	m_nRemLife = 100;	//残り体力

	m_move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//テクスチャの設定

	//--------------------------
	// HPの表示
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_Hp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_Hp->SetLife(m_nLife, m_nRemLife);
		m_Hp->SetMove(m_move);
	}

	//--------------------------
	// バリアの生成
	//--------------------------
	//CBarrier::Create(m_pos, m_move, m_fWidth, m_fHeight);

	return S_OK;
}

//===========================
// 終了
//===========================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CEnemy::Update()
{
	CObject2D::Update();

	//テクスチャカウント
	m_CntTime++;
	m_CntTime %= nMaxTexTime;	//リセット

	//-------------------------------
	// テクスチャ座標の変更
	//-------------------------------
	if (m_CntTime >= nHalfTexTime)
	{
		CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
	}
	else
	{
		CObject2D::SetTexCIE(0.5f, 1.0f);
	}

	//-------------------------------
	// 敵の移動
	//-------------------------------
	switch (m_type)
	{
	case ENEMYTYPE_NORMAL:
		CObject2D::AddMove(m_move);
		break;

	case ENEMYTYPE_CURVE:
		m_move.x = sinf(m_move.x);
		CObject2D::AddMove(m_move);
		break;

	default:
		break;
	}

	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);		//経験値の取得
		CScore::AddScore(10);	//スコアの加算

		//敵の消滅
		Uninit();
		return;
	}
}

//===========================
// 描画
//===========================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// 敵の生成と初期化
	//----------------------------------
	pEnemy = new CEnemy;	//生成

	if (pEnemy != nullptr)
	{//NULLチェック
		//構造体に代入
		pEnemy->m_type = type;

		//初期化
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//===========================
// 体力の減少
//===========================
void CEnemy::SubLife(int nLife)
{
	m_nLife -= nLife;

	//残り体力を計算
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP減少時の処理
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// 体力の取得
//===========================
int CEnemy::GetLife()
{
	return m_nLife;
}

//===========================
// 残り体力の取得
//===========================
int CEnemy::GetRemLife()
{
	return m_nRemLife;
}