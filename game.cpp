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
#include "skill.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;		//プレイヤー
CEnemy	  *CGame::m_pEnemy = nullptr;		//敵
CScore	  *CGame::m_pScore = nullptr;		//スコア
CBg		  *CGame::m_pBG = nullptr;			//背景
CSkill	  *CGame::m_pSkill[nMaxSkill] = {};	//スキル

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{
	m_EnemyCnt = 0;
	m_nTime = 0;
	m_nSkillTime[nMaxSkill] = {};
	m_bSkill[nMaxSkill] = {};
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

	//メンバ変数の初期化
	for (int i = 0; i < 2; i++)
	{
		m_bSkill[i] = false;
		m_nSkillTime[i] = 0;
	}

	//背景の生成
	m_pBG = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CBg::BGTYPE_GAME);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	//スコアの生成
	m_pScore = CScore::Create();

	m_pSkill[0] = CSkill::Create(CSkill::SKILLTYPE_HEAL);
	m_pSkill[1] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);

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
	//敵の出現
	SetEnemy();

	//------------------------
	// スキルの色変更
	//------------------------
	if (CInputKeyboard::Trigger(DIK_1) && !m_bSkill[0])
	{
		m_pSkill[0]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[0] = true;
	}
	else if (CInputKeyboard::Trigger(DIK_2) && !m_bSkill[1])
	{
		m_pSkill[1]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[1] = true;
	}

	//-------------------------
	// スキル時間のカウント
	//-------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (m_bSkill[i])
		{
			m_nSkillTime[i]++;
		}

		if (m_nSkillTime[i] >= 600)
		{
			//スキルの色を戻す
			m_bSkill[i] = false;
			m_pSkill[i]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nSkillTime[i] = 0;
		}
	}

	//画面遷移
	/*if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_RESULT);
	}*/
}

//===========================
// 敵の出現
//===========================
void CGame::SetEnemy()
{
	m_nTime++;

	if (m_nTime % (nOneSecond * 5) == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 360.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL);
	}

	if (m_nTime % (nOneSecond * 12) == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 360.0f, 0.0f), CEnemy::ENEMYTYPE_HORMING);
	}

	if (m_nTime % (nOneSecond * 20) == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 200.0f, 0.0f), CEnemy::ENEMYTYPE_HPITEM);
	}

	if (m_nTime % (nOneSecond * 20) == 0)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, 500.0f, 0.0f), CEnemy::ENEMYTYPE_MPITEM);
	}

	if (m_nTime == (nOneSecond * 60))
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), CEnemy::ENEMYTYPE_BOSS);
	}
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