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

//===========================
// コンストラクタ
//===========================
CEnemyBullet::CEnemyBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転
	m_nLife = 0;				//寿命
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
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
	m_nLife = 50;
	m_fWidth = 50.0f;
	m_fHeight = 50.0f;

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

	//移動量の加算
	m_pos = CObject2D::AddMove(m_move);

	//寿命の減少
	//m_nLife--;

	////寿命が尽きた
	//if (m_nLife <= 0.0f)
	//{
	//	Uninit();
	//	return;
	//}
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
CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CEnemyBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CEnemyBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
	 //初期化
		pBullet->m_move = move;		//移動量の代入
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}