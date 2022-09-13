//===================================
//
// ゲームの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <time.h>
#include "game.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "bg.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;	//プレイヤー
CEnemy	  *CGame::m_pEnemy = nullptr;	//敵
CScore	  *CGame::m_pScore = nullptr;	//スコア
CBg		  *CGame::m_pBG = nullptr;		//背景

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{
	m_EnemyCnt = 0;
	m_nTime = 0;
}

//===========================
// デストラクタ
//===========================
CGame::~CGame()
{

}

//===========================
// 初期化
//===========================
HRESULT CGame::Init()
{
	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	//背景の生成
	m_pBG = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CBg::BGTYPE_GAME);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	//スコアの生成
	m_pScore = CScore::Create();

	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), CEnemy::ENEMYTYPE_BOSS);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGame::Uninit()
{

}

//===========================
// 更新
//===========================
void CGame::Update()
{
	m_nTime++;

	if (m_nTime % (nOneSecond * 5) == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 360.0f, 0.0f), CEnemy::ENEMYTYPE_HORMING);
	}

	//画面遷移
	/*if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_RESULT);
	}*/
}

//===========================
// プレイヤーの取得
//===========================
CPlayer *CGame::GetPlayer()
{
	return m_pPlayer;
}

//===========================
// スコアの取得
//===========================
CScore *CGame::GetScore()
{
	return m_pScore;
}

//===========================
// 背景の取得
//===========================
CBg *CGame::GetBG()
{
	return m_pBG;
}