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
#include "score.h"
#include "effect.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CBullet::fBulletSpeed = 5.0f;	//弾の速度

int CBullet::s_nShotTime;		//弾の発射時間を数える
int CBullet::s_nChageTime;		//弾のチャージ時間

//===========================
// コンストラクタ
//===========================
CBullet::CBullet() : CObject2D()
{
	memset(&m_Bullet, 0, sizeof(m_Bullet));	//構造体のクリア
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
	//メンバ変数の初期化
	m_Bullet.move = D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f);
	m_Bullet.nLife = 100;
	m_Bullet.fWidth = 50.0f;
	m_Bullet.fHeight = 50.0f;

	CObject2D::Init(pos);

	if (m_Bullet.type == BULLETSTATE_NORMAL)
	{
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//サイズの設定
	}
	else if (m_Bullet.type == BULLETSTATE_CHARGE)
	{
		CObject2D::SetSize(80.0f, 80.0f);
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

	//エフェクトの生成
	CEffect::Create(m_Bullet.pos);

	//移動量の加算
	m_Bullet.pos = CObject2D::AddMove(m_Bullet.move);

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
	if (m_Bullet.pos.x >= 1280.0f)
	{
		CObject2D::Release();
	}

	//------------------------
	// 敵との当たり判定
	//------------------------
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GETObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		//オブジェクトの種類の取得
		CObject::EObjType type = pObject->GetObjType();

		//------------------
		// 弾の情報を取得
		//------------------
		D3DXVECTOR3 BulletPos = CObject2D::GetPosition();	//位置
		float BulletWidth = CObject2D::GetWidth();			//幅
		float BulletHeight = CObject2D::GetHeight();		//高さ

		if (type == OBJTYPE_ENEMY)
		{//オブジェクトの種類が敵なら
			//------------------
			// 敵の情報を取得
			//------------------
			D3DXVECTOR3 EnemyPos = pObject->GetPosition();	//位置
			float EnemyWidth = pObject->GetWidth();			//幅
			float EnemyHeight = pObject->GetHeight();		//高さ

			float fLeft = EnemyPos.x - (EnemyWidth / 2);	//敵の左側
			float fRight = EnemyPos.x + (EnemyWidth / 2);	//敵の右側
			float fTop = EnemyPos.y - (EnemyHeight / 2);	//敵の上側
			float fBottom = EnemyPos.y + (EnemyHeight / 2);	//敵の下側

			//------------------
			// 当たり判定
			//------------------
			if (BulletPos.x + BulletWidth / 2 >= fLeft && BulletPos.x - BulletWidth / 2 <= fRight
				&& BulletPos.y - BulletHeight / 2 <= fBottom && BulletPos.y + BulletHeight / 2 >= fTop)
			{
				CExplosion::Create(m_Bullet.pos);//爆発の生成
				CScore::AddScore(50);

				//弾の消滅
				Uninit();
				CObject2D::Release();
			}
		}
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

	s_nShotTime++;
	s_nShotTime %= nShotTime;	//発射時間をリセット

	//---------------------------
	// 通常弾
	//---------------------------
	if (!CInputKeyboard::Press(DIK_1) && s_nShotTime == 0)
	{//SPACEキーが押されている間 かつ 弾の発射時間が0なら
		//プレイヤーの向きに弾を発射する
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_NORMAL);
	}

	//---------------------------
	// チャージショット
	//---------------------------
	if (CInputKeyboard::Press(DIK_1))
	{//1キーが押されている間
		s_nChageTime++;		//チャージ時間を加算

		if (s_nChageTime >= 40)
		{//チャージ時間が10以上なら
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//プレイヤーの色を変更
		}
	}

	if (CInputKeyboard::Release(DIK_1) && s_nChageTime >= 40)
	{//1キーを離したとき かつ チャージ状態なら
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_CHARGE);

		s_nChageTime = 0;	//チャージ時間をリセット
		s_nShotTime = 0;	//通常弾のの発射時間リセット
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//プレイヤーの色を変更
	}
	else if (CInputKeyboard::Release(DIK_1) && s_nChageTime < 40)
	{
		s_nChageTime = 0;	//チャージ時間をリセット
	}
}