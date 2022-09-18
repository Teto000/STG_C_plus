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

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CEnemy::fBulletSpeed_Homing = 1.01f;	//弾の速度(ホーミング)

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目標位置
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_rot = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//回転
	m_nLife = 0;				//体力
	m_nMaxLife = 0;				//最大体力
	m_nRemLife = 0;				//残り体力
	m_nAttack = 0;				//攻撃力
	m_nCntHorming = 0;			//ホーミング時間のカウント
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_fTargetRot = 0.0f;		//プレイヤーまでの角度
	m_fChangeAngle = 0.0f;		//変動する移動量
	m_bChangeAttack = false;	//攻撃変化
	m_type = ENEMYTYPE_MAX;		//種類
	m_pHp = nullptr;			//HPバー
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
	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	//初期値の設定
	m_pos = pos;		//位置
	m_nRemLife = 100;	//残り体力
	m_nAttack = 5;		//攻撃力
	SetLife(100);		//体力
	m_fWidth = 80.0f;	//幅
	m_fHeight = 80.0f;	//高さ

	CObject2D::Init(m_pos);

	//-------------------------------
	// 敵の種類ごとの情報を設定
	//-------------------------------
	switch (m_type)
	{
	//通常の敵
	case ENEMYTYPE_NORMAL:
		m_move.x = -3.0f;	//移動量
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BLUE);	//テクスチャの設定
		break;

	//ホーミングする敵
	case ENEMYTYPE_HORMING:
		SetLife(300);		//体力
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_RED);	//テクスチャの設定
		break;

	//ボス敵
	case ENEMYTYPE_BOSS:
		m_fWidth = 200.0f;	//幅
		m_fHeight = 200.0f;	//高さ
		SetLife(3000);		//体力
		CObject2D::SetTexCIE(0.0f, 0.5f);
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BIRD);	//テクスチャの設定
		break;

	default:
		break;
	}

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	//--------------------------
	// HPの表示
	//--------------------------
	{
		//HPの位置を設定
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_pHp = CHp::Create(hpPos, m_fWidth, 10.0f);//HPの生成
		m_pHp->SetLife(m_nLife, m_nRemLife);		//HPに体力を設定
		m_pHp->SetMove(m_move);						//HPに移動量を設定
	}

	//--------------------------
	// バリアの生成
	//--------------------------
	/*{
		int nData = rand() % 9;

		if (m_type != ENEMYTYPE_BOSS && nData == 1)
		{//ボス以外の敵 かつ ランダムな値が1の時
			//バリアの生成
			m_pBarrier->Create(m_pos, m_move, m_fWidth, m_fHeight, CBarrier::BARRIERTYPE_ENEMY);
		}
	}*/

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

	//--------------------------
	// テクスチャアニメーション
	//--------------------------
	Animation();

	//--------------------------
	// 移動処理
	//--------------------------
	Move();

	//--------------------------
	// 攻撃処理
	//--------------------------
	CntAttack();

	//--------------------------
	// 消える処理
	//--------------------------
	if (Destroy())
	{
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
		//メンバ変数に代入
		pEnemy->m_type = type;

		//初期化
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//============================
// テクスチャアニメーション
//============================
void CEnemy::Animation()
{
	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		//テクスチャ切り替え時間の加算
		m_nCntTime++;
		m_nCntTime %= nMaxTexTime;	//リセット

		if (m_nCntTime >= nHalfTexTime)
		{
			//テクスチャ座標の設定
			CObject2D::SetTexCIE(0.0f, 0.5f);
		}
		else
		{
			CObject2D::SetTexCIE(0.5f, 1.0f);
		}
		break;

	default:
		break;
	}
}

//=======================
// 移動処理
//=======================
void CEnemy::Move()
{
	switch (m_type)
	{
	/* ↓ 通常の敵 ↓ */
	case ENEMYTYPE_NORMAL:
		//上下移動
		m_fChangeAngle += 0.01f;	//角度の加算
		m_move.y = sinf(D3DX_PI * m_fChangeAngle);	//上下の移動量を計算
		break;

	/* ↓ ホーミングする敵 ↓ */
	case ENEMYTYPE_HORMING:
		m_nCntHorming++;	//ホーミング時間のカウント

		if (m_nCntHorming <= 200)
		{//カウントが200以下なら
			//プレイヤーの位置を取得
			m_Tirget = CGame::GetPlayer()->GetPosition();

			//ホーミングの移動量を取得
			m_move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
		}
		break;

	case ENEMYTYPE_BOSS:
		//上下移動
		m_fChangeAngle += 0.01f;	//角度の加算
		m_move.y = sinf(D3DX_PI * m_fChangeAngle) * 2.0f;	//上下の移動量を計算
		break;

	default:
		break;
	}

	m_pos = CObject2D::AddMove(m_move);	//敵の移動
	m_pHp->SetMove(m_move);				//HPバーの移動量の設定
}

//=======================
// 攻撃までの時間を数える
//=======================
void CEnemy::CntAttack()
{
	//カウントの加算
	m_nCntShotTime++;
	m_nCntShotTime %= nShotTime;

	//----------------------------
	// カウントが0になったら
	//----------------------------
	if (m_nCntShotTime == 0)
	{
		//攻撃処理
		Attack();
	}
}

//=======================
// 攻撃処理
//=======================
void CEnemy::Attack()
{
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
	// 攻撃
	//-------------------------------
	switch (m_type)
	{
	/* ↓ 通常の敵 ↓ */
	case ENEMYTYPE_NORMAL:
		m_pEnemyBullet->Create(m_pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nAttack);
		break;

	/* ↓ ボス敵 ↓ */
	case ENEMYTYPE_BOSS:
		BossAttack(vec);
		break;

	default:
		break;
	}
}

//=======================
// ボス敵の攻撃
//=======================
void CEnemy::BossAttack(D3DXVECTOR2 vec)
{
	int nRandAttack = rand() % 3;

	switch (nRandAttack)
	{
	case 0:
		/* ↓ 攻撃1 ↓ */
		for (int i = 0; i < 3; i++)
		{
			D3DXVECTOR3 move(-vec.x * 4.0f, -vec.y * (i + 1), 0.0f);
			m_pEnemyBullet->Create(m_pos, move, m_nAttack);
		}
		break;

	case 1:
		/* ↓ 攻撃2 ↓ */
		for (int i = 0; i < 3; i++)
		{
			D3DXVECTOR3 pos(m_pos.x, 50.0f + 200.0f * (i + 1), m_pos.z);
			m_pEnemyBullet->Create(pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nAttack);
		}
		break;
	case 2:
		/* ↓ 攻撃3 ↓ */

		break;

	default:
		break;
	}
}

//=======================
// 消える処理
//=======================
bool CEnemy::Destroy()
{
	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);				//経験値の取得
		CScore::AddScore(10);			//スコアの加算
		m_pExplosion->Create(m_pos);	//爆発の生成

		return true;
	}

	//--------------------------
	// 画面外に出た
	//--------------------------
	if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
	{
		return true;
	}

	//--------------------------
	// 自爆
	//--------------------------
	if (CObject2D::GetCollision(OBJTYPE_PLAYER) && m_type == ENEMYTYPE_HORMING)
	{//プレイヤーと当たった && ホーミングする敵なら
		CLevel::AddExp(10);					//経験値の取得
		m_pExplosion->Create(m_pos);		//爆発の生成
		CGame::GetPlayer()->AddLife(-30);	//プレイヤーの体力を減らす
		return true;
	}

	return false;
}

//=======================
// ホーミング
//=======================
D3DXVECTOR3 CEnemy::Homing(float& posX, float& posY, float& moveX, float& moveY)
{
	//弾の元の速度
	float vx0 = moveX, vy0 = moveY;

	//自機方向の速度ベクトル(vx1,vy1)を求める
	float vx1, vy1;

	//目標までの距離dを求める
	float d = sqrtf((m_Tirget.x - posX) * (m_Tirget.x - posX)
		+ (m_Tirget.y - posY) * (m_Tirget.y - posY));

	if (d)
	{
		vx1 = (m_Tirget.x - posX) / d * fBulletSpeed_Homing;
		vy1 = (m_Tirget.y - posY) / d * fBulletSpeed_Homing;
	}
	else
	{
		vx1 = 0;
		vy1 = fBulletSpeed_Homing;
	}

	//右回り旋回角度上限の速度ベクトル(vx2,vy2)を求める
	float rad = (D3DX_PI / 180) * 5.0f; //旋回角度上限
	float vx2 = cosf(rad) * vx0 - sinf(rad) * vy0;
	float vy2 = sinf(rad) * vx0 + cosf(rad) * vy0;

	//自機方向と旋回角度上限のどちらに曲がるかを決める
	if (vx0 * vx1 + vy0 * vy1 >= vx0 * vx2 + vy0 * vy2)
	{//自機方向が旋回可能範囲内の場合
	 //自機方向に曲がる
		moveX = vx1;
		moveY = vy1;
	}
	else
	{
		//自機方向が旋回可能範囲外の場合
		//左回り旋回角度上限の速度ベクトル(vx3,vy3)を求める
		float vx3 = cosf(rad) * vx0 + sinf(rad) * vy0;
		float vy3 = -sinf(rad) * vx0 + cosf(rad) * vy0;

		//弾から自機への相対位置ベクトル(px,py)を求める
		float px = m_Tirget.x - posX, py = m_Tirget.y - posY;

		//右回りか左回りかを決める
		if (px * vx2 + py * vy2 >= px * vx3 + py * vy3)
		{//右回りの場合
			moveX = vx2;
			moveY = vy2;
		}
		else
		{//左回りの場合
			moveX = vx3;
			moveY = vy3;
		}
	}

	moveX *= fBulletSpeed_Homing;
	moveY *= fBulletSpeed_Homing;

	return D3DXVECTOR3(moveX, moveY, 0.0f);
}

//===========================
// 移動量の取得
//===========================
D3DXVECTOR3 CEnemy::GetMove()
{
	return m_move;
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