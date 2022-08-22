//===================================
//
// アプリケーションの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "texture.h"
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "bg.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CRenderer *CApplication::m_pRenderer = nullptr;	//レンダラー
CInput	  *CApplication::m_pInput = nullptr;	//インプット
CTexture  *CApplication::m_pTexture = nullptr;	//テクスチャ
CSound	  *CApplication::m_pSound = nullptr;	//サウンド
CPlayer	  *CApplication::m_pPlayer = nullptr;	//プレイヤー
CEnemy	  *CApplication::m_pEnemy = nullptr;	//敵
CScore	  *CApplication::m_pScore = nullptr;	//スコア
CBg		  *CApplication::m_pBG = nullptr;		//背景

//===========================
// コンストラクタ
//===========================
CApplication::CApplication()
{
	m_EnemyCnt = 0;
}

//===========================
// デストラクタ
//===========================
CApplication::~CApplication()
{

}

//===========================
// 初期化
//===========================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	//--------------------------
	// インスタンスの生成
	//--------------------------
	m_pRenderer = new CRenderer;	//レンダリング
	m_pInput = new CInput;			//インプット
	m_pTexture = new CTexture;		//テクスチャ
	m_pSound = new CSound;			//サウンド

	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	//レンダリングの初期化
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//インプットの初期化
	m_pInput->Init(hInstance, hWnd);

	//サウンドの初期化
	//m_pSound->Init(hWnd);

	//背景の生成
	m_pBG = CBg::Create();

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	//スコアの生成
	m_pScore = CScore::Create();

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL);

	return S_OK;
}

//===========================
// 終了
//===========================
void CApplication::Uninit()
{
	//テクスチャの終了
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//レンダリングの終了
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//インプットの終了
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//オブジェクトの全解放
	CObject::ReleaseAll();

	//サウンドの終了
	/*if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}*/

}

//===========================
// 更新
//===========================
void CApplication::Update()
{
	//インプットの更新
	m_pInput->Update();	//最初にやる

	//レンダリングの更新
	m_pRenderer->Update();

	//m_EnemyCnt++;
	//m_EnemyCnt %= 80;

	//if (m_EnemyCnt == 0)
	//{
	//	int nRand = rand() % 520 + 200;

	//	//敵の生成
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, (float)nRand, 0.0f),
	//								CEnemy::ENEMYTYPE_NORMAL);
	//}
}

//===========================
// 描画
//===========================
void CApplication::Draw()
{
	//レンダリングの描画
	m_pRenderer->Draw();
}

//===========================
// レンダリングの取得
//===========================
CRenderer *CApplication::GetRenderer()
{
	return m_pRenderer;
}

//===========================
// インプットの取得
//===========================
CInput *CApplication::GetInput()
{
	return m_pInput;
}

//===========================
// テクスチャの取得
//===========================
CTexture *CApplication::GetTexture()
{
	return m_pTexture;
}

//===========================
// サウンドの取得
//===========================
CSound *CApplication::GetSound()
{
	return m_pSound;
}

//===========================
// プレイヤーの取得
//===========================
CPlayer *CApplication::GetPlayer()
{
	return m_pPlayer;
}

//===========================
// スコアの取得
//===========================
CScore *CApplication::GetScore()
{
	return m_pScore;
}