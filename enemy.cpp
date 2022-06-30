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
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "bullet.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CEnemy::m_CntTime = 0;

//------------------------
// マクロ定義
//------------------------
#define ENEMY_SPEED	(5.0f)	//プレイヤーの速度

//===========================
// コンストラクタ
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(100.0f, 100.0f);	//サイズの設定

	CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//テクスチャの設定

	m_pos = CObject2D::GetPosition();

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
CEnemy *CEnemy::Create()
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pEnemy = new CEnemy;	//生成

	if (pEnemy != nullptr)
	{//NULLチェック
		//初期化
		pEnemy->Init(D3DXVECTOR3(800.0f, SCREEN_HEIGHT / 2, 0.0f));
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}