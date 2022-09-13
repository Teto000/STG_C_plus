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
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//位置
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
	m_type = ENEMYTYPE_MAX;		//種類
	m_Hp = nullptr;				//HPバー
	m_EnemyBullet = nullptr;	//敵の弾
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
	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	//位置の設定
	m_pos = pos;		//位置
	m_nRemLife = 100;	//残り体力
	m_nAttack = 5;

	CObject2D::Init(m_pos);
	CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BIRD);	//テクスチャの設定

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_fWidth = 250.0f;	//幅
		m_fHeight = 350.0f;	//高さ
		SetLife(3000);
		break;

	case ENEMYTYPE_BIG:
		m_move.x = -2.0f;	//移動量
		m_fWidth = 100.0f;	//幅
		m_fHeight = 100.0f;	//高さ
		SetLife(500);
		CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_DEVIL);
		break;

	case ENEMYTYPE_HORMING:
		m_move.x = -2.0f;	//移動量
		m_fWidth = 100.0f;	//幅
		m_fHeight = 100.0f;	//高さ
		SetLife(500);
		break;

	default:
		m_move.x = -4.0f;	//移動量
		m_fWidth = 80.0f;	//幅
		m_fHeight = 80.0f;	//高さ
		SetLife(100);
		CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
		break;
	}

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	//--------------------------
	// HPの表示
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_Hp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_Hp->SetLife(m_nLife, m_nRemLife);
		m_Hp->SetMove(m_move);

		//フレームの生成
		//m_pHpFream = CHpFream::Create(hpPos, m_fWidth, 15.0f);
		//m_pHpFream->SetMove(m_move);
	}

	//--------------------------
	// バリアの生成
	//--------------------------
	{
		int nData = rand() % 5;

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
	// プレイヤーの位置を保存
	//-------------------------------
	if (CGame::GetPlayer()->GetLife() > 0)
	{//プレイヤーが生きているなら
		m_targetPos = CGame::GetPlayer()->GetPosition();
	}

	//プレイヤーまでの角度
	D3DXVECTOR2 vec = m_pos - m_targetPos;
	D3DXVec2Normalize(&vec, &vec);

	//-------------------------------
	// テクスチャ座標の変更
	//-------------------------------
	if (m_type == ENEMYTYPE_NORMAL || m_type == ENEMYTYPE_BIG)
	{
		//テクスチャ
		m_nCntTime++;
		m_nCntTime %= nMaxTexTime;	//リセット

		if (m_nCntTime >= nHalfTexTime)
		{
			CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
		}
		else
		{
			CObject2D::SetTexCIE(0.5f, 1.0f);
		}
	}

	//-------------------------------
	// プレイヤーに向かって回転
	//-------------------------------
	/*if (m_targetPos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXVECTOR2 vec = m_pos - m_targetPos;

		m_fTargetRot = -atan2f(vec.y, vec.x);

		if (m_rot.x != m_fTargetRot)
		{
			m_rot.x += 0.1f;
		}

		//角度の正規化
		if (m_rot.x >= D3DX_PI)
		{
			m_rot.x -= D3DX_PI;
		}
		else if (m_rot.x <= -D3DX_PI)
		{
			m_rot.x += D3DX_PI;
		}

		CObject2D::SetVtxCIE_Rot(m_pos, m_rot, m_fWidth, m_fHeight);
	}*/

	//-------------------------------
	// 敵の移動
	//-------------------------------
	m_pos = CObject2D::AddMove(m_move);

	//--------------------------
	// 敵の攻撃
	//--------------------------
	EnemyAttackCount(vec);

	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);				//経験値の取得
		CScore::AddScore(10);			//スコアの加算
		m_pExplosion->Create(m_pos);	//爆発の生成

		//-----------------------
		// アイテムの生成
		//-----------------------
		//m_pItem = CItem::Create(m_pos,CItem::ITEMTYPE_HPHEAL);

		//敵の消滅
		Uninit();

		//-----------------------
		// 倒れたのがボスなら
		//-----------------------
		if (m_type == ENEMYTYPE_BOSS)
		{
			//リザルト画面に移行
			CApplication::SetMode(CApplication::MODE_RESULT);
		}
		return;
	}
	//--------------------------
	// 画面外に出た
	//--------------------------
	else if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
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
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===============================
// 敵の攻撃タイミングを数える
//===============================
void CEnemy::EnemyAttackCount(D3DXVECTOR2 vec)
{
	m_nCntShotTime++;

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_nCntShotTime %= nShotTime * 2;
		break;

	case ENEMYTYPE_BIG:
		m_nCntShotTime %= nShotTime * 2;
		break;

	case ENEMYTYPE_HORMING:
		m_nCntShotTime %= nShotTime;
		break;

	default:
		m_nCntShotTime %= nShotTime;
		break;
	}

	//----------------------------
	// カウントが0になったら
	//----------------------------
	if (m_nCntShotTime == 0)
	{
		EnemyAttack(vec);
	}
}

//===========================
// 敵の攻撃処理
//===========================
void CEnemy::EnemyAttack(D3DXVECTOR2 vec)
{
	switch (m_type)
	{
		//----------------------
		// ボスの攻撃
		//----------------------
	case ENEMYTYPE_BOSS:
		BossAttack();
		break;

	case ENEMYTYPE_BIG:
		for (int i = 0; i < 5; i++)
		{
			m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-vec.x * 4.0f, -vec.y * (i + 1), 0.0f)
				, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_NORMAL);
		}
		break;

	case ENEMYTYPE_HORMING:
		m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f)
			, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_HORMING);
		break;

	default:
		m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f)
			, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_NORMAL);
		break;
	}
}

//===========================
// ボスの攻撃
//===========================
void CEnemy::BossAttack()
{
	
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