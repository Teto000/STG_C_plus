//===================================
//
// バレットの処理
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

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CBullet::fBulletSpeed = 5.0f;	//弾の速度

//===========================
// コンストラクタ
//===========================
CBullet::CBullet() : CObject2D()
{
	memset(&m_aBullet, 0, sizeof(m_aBullet));	//構造体のクリア
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
	m_aBullet.move = D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f);
	m_aBullet.nLife = 100;

	CObject2D::Init(pos);

	CObject2D::SetSize(50.0f, 50.0f);	//サイズの設定

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
	//移動量の加算
	CObject2D::AddMove(m_aBullet.move);

	CObject2D::Update();

	D3DXVECTOR3 pos = CObject2D::GetPosition();

	//寿命の減少
	m_aBullet.nLife--;

	//寿命が尽きた
	if (m_aBullet.nLife <= 0.0f)
	{
		CObject2D::Release();	//弾の開放
		//CExplosion::Create(pos);//爆発の生成
	}

	//画面端の処理
	if (pos.x >= 1280.0f)
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
CBullet *CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
		//初期化
		pBullet->Init(pos);
		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}