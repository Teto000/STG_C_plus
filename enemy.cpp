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

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	memset(&m_Enemy, 0, sizeof(Enemy));	//構造体のクリア
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
	m_Enemy.pos = pos;			//位置
	m_Enemy.fWidth = 100.0f;	//幅
	m_Enemy.fHeight = 100.0f;	//高さ
	m_Enemy.nLife = 120;		//体力
	m_Enemy.nMaxLife = 120;		//最大体力
	m_Enemy.nRemLife = 100;		//残り体力

	CObject2D::Init(m_Enemy.pos);

	CObject2D::SetSize(m_Enemy.fWidth, m_Enemy.fHeight);	//サイズの設定

	CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//テクスチャの設定

	//--------------------------
	// HPの表示
	//--------------------------
	//CHp::Create(D3DXVECTOR3(m_Enemy.pos.x, m_Enemy.pos.y - (m_Enemy.fHeight / 2 + 20.0f), m_Enemy.pos.z)
	//			, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Enemy.fWidth, 10.0f, CHp::HPTYPE_ENEMY);

	//--------------------------
	// バリアの生成
	//--------------------------
	//CBarrier::Create(m_Enemy.pos, m_Enemy.move, m_Enemy.fWidth, m_Enemy.fHeight);

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

	//--------------------------
	// 体力の減少
	//--------------------------
	if (CInputKeyboard::Press(DIK_LEFT))
	{
		SubLife(1);
	}

	//--------------------------
	// 終了条件を満たしたら
	//--------------------------
	if (!IsUsed())
	{
		//消去処理
		Destroy();
	}
	else
	{
		//残り体力を計算
		m_Enemy.nRemLife = m_Enemy.nLife * 100 / m_Enemy.nMaxLife;
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// 敵の生成と初期化
	//----------------------------------
	pEnemy = new CEnemy;	//生成

	if (pEnemy != nullptr)
	{//NULLチェック
		//初期化
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//===========================
// 終了条件処理
//===========================
bool CEnemy::IsUsed()
{
	if (m_Enemy.nLife <= 0)
	{
		return false;
	}

	return true;
}

//===========================
// 消去処理
//===========================
void CEnemy::Destroy()
{
	CLevel::AddExp(10);		//経験値の取得

	//敵の消滅
	Uninit();
	CObject2D::Release();
}

//===========================
// 体力の減少
//===========================
void CEnemy::SubLife(int nLife)
{
	m_Enemy.nLife -= nLife;
}

//===========================
// 体力の取得
//===========================
int CEnemy::GetLife()
{
	return m_Enemy.nLife;
}

//===========================
// 残り体力の取得
//===========================
int CEnemy::GetRemLife()
{
	return m_Enemy.nRemLife;
}