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
#include "enemybullet.h"
#include "game.h"
#include "player.h"

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//位置
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//回転
	m_nLife = 0;				//体力
	m_nMaxLife = 0;				//最大体力
	m_nRemLife = 0;				//残り体力
	m_nCntAttack = 0;			//攻撃タイミング
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_type = ENEMYTYPE_MAX;		//種類
	m_Hp = nullptr;				//HPバー
	m_EnemyBullet = nullptr;	//敵の弾
	m_pExplosion = nullptr;		//爆発
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

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_fWidth = 250.0f;	//幅
		m_fHeight = 350.0f;	//高さ
		m_nLife = 3000;		//体力
		m_nMaxLife = 3000;	//最大体力
		break;

	default:
		m_fWidth = 100.0f;	//幅
		m_fHeight = 100.0f;	//高さ
		m_nLife = 120;		//体力
		m_nMaxLife = 120;	//最大体力
		break;
	}

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

	//-------------------------------
	// カウント
	//-------------------------------
	//テクスチャ
	m_nCntTime++;
	m_nCntTime %= nMaxTexTime;	//リセット

	//攻撃タイミング
	m_nCntAttack++;
	m_nCntAttack %= 30;

	//-------------------------------
	// プレイヤーの位置を保存
	//-------------------------------
	//if (m_nCntAttack == 0 /*&& m_targetPos == D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/)
	if (CInputKeyboard::Trigger(DIK_L))
	{
		m_targetPos = CGame::GetPlayer()->GetPosition();
	}

	//-------------------------------
	// テクスチャ座標の変更
	//-------------------------------
	//if (m_CntTime >= nHalfTexTime)
	//{
	//	CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
	//}
	//else
	//{
	//	CObject2D::SetTexCIE(0.5f, 1.0f);
	//}

	//-------------------------------
	// プレイヤーに向かって回転
	//-------------------------------
	if (m_targetPos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXVECTOR2 vec = m_pos - m_targetPos;

		float fTargetRot = -atan2f(vec.y, vec.x);

		if (m_rot.x != fTargetRot)
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
	}

	//-------------------------------
	// 敵の移動
	//-------------------------------
	switch (m_type)
	{
	case ENEMYTYPE_NORMAL:
		m_move.x = -3.0f;
		break;

	case ENEMYTYPE_CURVE:
		break;

	default:
		break;
	}

	CObject2D::AddMove(m_move);
	m_Hp->SetMove(m_move);

	//--------------------------
	// 敵の攻撃
	//--------------------------
	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		BossAttack();
		break;

	default:
		break;
	}

	//--------------------------
	// 弾の発射
	//--------------------------
	//m_nCntShotTime++;
	//m_nCntShotTime %= nShotTime;	//発射時間をリセット

	//if (m_nCntShotTime == 0)
	//{
	//	m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-8.0f, 0.0f, 0.0f));
	//}

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
// ボスの攻撃
//===========================
void CEnemy::BossAttack()
{
	if (CInputKeyboard::Trigger(DIK_M))
	{
		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR3 pos(300.0f + (i * 200.0f), 0.0f - (i * 50.0f), 0.0f);
			D3DXVECTOR3 move(-5.0f, 9.0f, 0.0f);
			m_EnemyBullet->Create(pos, move);
		}
	}
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