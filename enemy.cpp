//===================================
//
// エネミーの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <time.h>
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "object2D.h"
#include "input_keybord.h"
#include "bullet.h"
#include "texture.h"
#include "hp.h"
#include "barrier.h"
#include "explosion.h"
#include "level.h"
#include "score.h"
#include "enemybullet.h"
#include "game.h"
#include "player.h"
#include "hpfream.h"
#include "item.h"

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_rot = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//回転
	m_nLife = 0;				//体力
	m_nMaxLife = 0;				//最大体力
	m_nRemLife = 0;				//残り体力
	m_nAttack = 0;				//攻撃力
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_fTargetRot = 0.0f;		//プレイヤーまでの角度
	m_fChangeMove = 0.0f;		//変動する移動量
	m_type = ENEMYTYPE_MAX;		//種類
	m_pHp = nullptr;				//HPバー
	m_pEnemyBullet = nullptr;	//敵の弾
	m_pExplosion = nullptr;		//爆発
	m_pBarrier = nullptr;		//バリア
	m_pHpFream = nullptr;		//HPフレーム
	m_pItem = nullptr;			//アイテム
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
	m_nRemLife = 100;	//残り体力
	m_nAttack = 5;		//攻撃力

	CObject2D::Init(m_pos);

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BLUE);	//テクスチャの設定

	//-------------------------------
	// 敵の種類ごとの情報を設定
	//-------------------------------
	/*switch (m_type)
	{
	case 0:
		break;

	default:*/
		m_move.x = -3.0f;	//移動量
		m_fWidth = 80.0f;	//幅
		m_fHeight = 80.0f;	//高さ
		SetLife(100);		//体力
	//	break;
	//}

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	//--------------------------
	// HPの表示
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_pHp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_pHp->SetLife(m_nLife, m_nRemLife);
		m_pHp->SetMove(m_move);
	}

	//--------------------------
	// バリアの生成
	//--------------------------
	{
		int nData = rand() % 9;

		if (m_type != ENEMYTYPE_BOSS && nData == 1)
		{//ボス以外の敵 かつ ランダムな値が1の時
			//バリアの生成
			m_pBarrier->Create(m_pos, m_move, m_fWidth, m_fHeight, CBarrier::BARRIERTYPE_ENEMY);
		}
	}

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

	//-------------------------------
	// 敵の移動
	//-------------------------------
	//上下移動
	m_fChangeMove += 0.01f;
	m_move.y = sinf(D3DX_PI * m_fChangeMove);

	m_pos = CObject2D::AddMove(m_move);

	m_pHp->SetMove(m_move);

	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);				//経験値の取得
		CScore::AddScore(10);			//スコアの加算
		m_pExplosion->Create(m_pos);	//爆発の生成

		//敵の消滅
		Uninit();
		return;
	}

	//--------------------------
	// 画面外に出た
	//--------------------------
	if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
	{
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
		//メンバ変数に代入
		pEnemy->m_type = type;

		//初期化
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//===========================
// 体力の設定
//===========================
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
	m_nMaxLife = nLife;
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
	m_pHp->SetLife(m_nLife, m_nRemLife);
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

//===========================
// 攻撃力の設定
//===========================
int CEnemy::GetAttack()
{
	return m_nAttack;
}