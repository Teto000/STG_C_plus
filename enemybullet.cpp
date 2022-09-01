//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "enemybullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "application.h"
#include "damage.h"
#include "enemy.h"
#include "player.h"
#include "game.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CEnemyBullet::fBulletSpeed_Homing = 1.01f;	//弾の速度(ホーミング)

//===========================
// コンストラクタ
//===========================
CEnemyBullet::CEnemyBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目標
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転
	m_nEnemyAttack = 0;			//敵の攻撃力
	m_nLife = 0;				//寿命
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_type = ENEMYBULLETTYPE_NORMAL;
}

//===========================
// デストラクタ
//===========================
CEnemyBullet::~CEnemyBullet()
{

}

//===========================
// 初期化
//===========================
HRESULT CEnemyBullet::Init(D3DXVECTOR3 pos)
{
	//----------------------------
	// メンバ変数の初期化
	//----------------------------
	m_pos = pos;
	m_fWidth = 50.0f;
	m_fHeight = 50.0f;
	m_nLife = 300;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);			//サイズの設定
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CEnemyBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CEnemyBullet::Update()
{
	CObject2D::Update();

	m_nLife--;

	//----------------------
	// ホーミング弾なら
	//----------------------
	switch (m_type)
	{
	case ENEMYBULLETTYPE_HORMING:
		m_Tirget = CObject2D::GetTargetPos();	//敵の位置の取得

		if (m_Tirget.x == 0.0f, m_Tirget.y == 0.0f)
		{//ターゲットが消えたら
			//横に向かって飛ぶ
			m_Tirget = D3DXVECTOR3(1280.0f, m_pos.y, 0.0f);
		}

		if (m_nLife >= 260)
		{
			//敵に向かってホーミング
			m_move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
			m_pos = CObject2D::AddMove(m_move);
		}
		else
		{
			m_pos = CObject2D::AddMove(m_move);
		}
		break;

	default:
		//移動量の加算
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//画面外に出たら
	if (CObject2D::OutScreen(m_pos))
	{
		Uninit();
		return;
	}

	if (CGame::GetPlayer()->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
	{//プレイヤーが無敵状態じゃないなら
		//当たった処理
		CollisionEnemyBullet();
	}
}

//===========================
// 描画
//===========================
void CEnemyBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move
									, int nAttack, CEnemyBullet::ENEMYBULLETTYPE type)
{
	CEnemyBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CEnemyBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
		pBullet->m_move = move;				//移動量の代入
		pBullet->m_nEnemyAttack = nAttack;	//攻撃力の代入
		pBullet->m_type = type;				//種類

		//初期化
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//===========================
// 当たった処理
//===========================
void CEnemyBullet::CollisionEnemyBullet()
{
	CObject* pHitObject = CObject2D::GetCollision(OBJTYPE_PLAYER);

	if (pHitObject != nullptr)
	{//プレイヤーと当たった

		//pObjectをCPlayer型にダウンキャスト
		CPlayer* pPlayer = (CPlayer*)pHitObject;

		pPlayer->SubLife(m_nEnemyAttack);	//敵の体力の減少

		//弾の消滅
		Uninit();
		return;
	}
}

//=======================
// ホーミング弾
//=======================
D3DXVECTOR3 CEnemyBullet::Homing(float& posX, float& posY, float& moveX, float& moveY)
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