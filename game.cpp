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
void CGame::Uninit()
{
	//オブジェクトの全解放
	CObject::ReleaseAll();
}

//===========================
// 更新
//===========================
void CGame::Update()
{
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