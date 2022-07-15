//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
#include "bullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"
#include "player.h"
#include "explosion.h"
#include "number.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "barrier.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CBullet::fBulletSpeed = 10.0f;	//弾の速度
float CBullet::fBulletSpeed_Homing = 1.05f;	//弾の速度(ホーミング)

int CBullet::m_nShotTime;		//弾の発射時間を数える
int CBullet::m_nChageTime;		//弾のチャージ時間

//===========================
// コンストラクタ
//===========================
CBullet::CBullet() : CObject2D()
{
	memset(&m_Bullet, 0, sizeof(m_Bullet));	//構造体のクリア
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================
// デストラクタ
//===========================
CBullet::~CBullet()
{

}

//===========================
// 初期化
//===========================
HRESULT CBullet::Init(D3DXVECTOR3 pos)
{
	//----------------------------
	// メンバ変数の初期化
	//----------------------------
	m_Bullet.pos = pos;
	m_Bullet.fWidth = 50.0f;
	m_Bullet.fHeight = 50.0f;

	CObject2D::Init(m_Bullet.pos);

	//----------------------------
	// 種類別の情報の設定
	//----------------------------
	if (m_Bullet.type == BULLETSTATE_NORMAL)
	{
		m_Bullet.nLife = 100;
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//サイズの設定
	}
	else if (m_Bullet.type == BULLETSTATE_CHARGE)
	{
		m_Bullet.nLife = 100;
		CObject2D::SetSize(m_Bullet.fWidth * 1.5f, m_Bullet.fHeight * 1.5f);
	}
	else if (m_Bullet.type == BULLETSTATE_HORMING)
	{
		m_Bullet.nLife = 200;
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//サイズの設定
	}

	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CBullet::Update()
{
	CObject2D::Update();

	if (m_Bullet.type == BULLETSTATE_HORMING)
	{//ホーミング弾なら
		m_Tirget = CObject2D::GetTargetPos();	//敵の位置の取得
		D3DXVECTOR3 move = Homing(m_Bullet.pos.x, m_Bullet.pos.y, m_Bullet.move.x, m_Bullet.move.y);
		m_Bullet.pos = CObject2D::AddMove(move);
	}
	else
	{
		//移動量の加算
		m_Bullet.pos = CObject2D::AddMove(m_Bullet.move);
	}

	//エフェクトの生成
	CEffect::Create(m_Bullet.pos);

	//寿命の減少
	m_Bullet.nLife--;

	//寿命が尽きた
	if (m_Bullet.nLife <= 0.0f)
	{
		CExplosion::Create(m_Bullet.pos);//爆発の生成
		Uninit();
		CObject2D::Release();	//弾の開放
	}
	//画面端の処理
	else if (m_Bullet.pos.x >= SCREEN_WIDTH)
	{
		Uninit();
		CObject2D::Release();
	}

	//------------------------
	// 当たり判定
	//------------------------
	if (CObject2D::GetCollision(OBJTYPE_ENEMY))
	{//敵と当たった
		CExplosion::Create(m_Bullet.pos);	//爆発の生成

		CScore::AddScore(1);

		//ダメージの表示
		CNumber::Create(m_Bullet.pos, 20.0f, 30.0f, 20.0f, 2, 87);

		//弾の消滅
		Uninit();
		CObject2D::Release();
	}
	else if (CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//バリアと当たった
		//弾の消滅
		Uninit();
		CObject2D::Release();
	}
}

//===========================
// 描画
//===========================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
		//初期化
		pBullet->m_Bullet.move = move;		//移動量の代入
		pBullet->m_Bullet.type = type;		//種類の代入
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//=======================
// 弾の発射
//=======================
void CBullet::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	rot.x = rot.x - D3DX_PI / 2;	//右を前に変更

	m_nShotTime++;
	m_nShotTime %= nShotTime;	//発射時間をリセット

	//---------------------------
	// 通常弾
	//---------------------------
	if (!CInputKeyboard::Press(DIK_1) && m_nShotTime == 0)
	{//SPACEキーが押されている間 かつ 弾の発射時間が0なら
		//プレイヤーの向きに弾を発射する
		//Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_NORMAL);
		Create(pos, D3DXVECTOR3(0.0f,0.0f,0.0f), BULLETSTATE_HORMING);
	}

	//---------------------------
	// チャージショット
	//---------------------------
	if (CInputKeyboard::Press(DIK_1))
	{//1キーが押されている間
		m_nChageTime++;		//チャージ時間を加算

		if (m_nChageTime >= 40)
		{//チャージ時間が10以上なら
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//プレイヤーの色を変更
		}
	}

	if (CInputKeyboard::Release(DIK_1) && m_nChageTime >= 40)
	{//1キーを離したとき かつ チャージ状態なら
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_CHARGE);

		m_nChageTime = 0;	//チャージ時間をリセット
		m_nShotTime = 0;	//通常弾のの発射時間リセット
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//プレイヤーの色を変更
	}
	else if (CInputKeyboard::Release(DIK_1) && m_nChageTime < 40)
	{
		m_nChageTime = 0;	//チャージ時間をリセット
	}
}

//=======================
// ホーミング弾
//=======================
D3DXVECTOR3 CBullet::Homing(float& posX, float& posY, float& moveX, float& moveY)
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