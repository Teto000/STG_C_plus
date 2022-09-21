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
#include "sound.h"
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

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGame::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_GAME);
}

//===========================
// 更新
//===========================
void CGame::Update()
{
	//敵の出現
	AppearEnemy();

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
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_RESULT);
	}
}

//===========================
// 敵の出現
//===========================
void CGame::AppearEnemy()
{
	m_nTime++;

	if (m_nTime == nOneSecond * 1)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 4)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 5)
	{
		SetEnemy(1300.0f, 600.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 7)
	{
		SetEnemy(1300.0f, 450.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 10)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 300.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 13)
	{
		SetEnemy(1300.0f, 200.0f, HORMING);
	}
	else if (m_nTime == nOneSecond * 18)
	{
		SetEnemy(1300.0f, 300.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 23)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 28)
	{
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 31)
	{
		SetEnemy(1300.0f, 500.0f, BIG);
		SetEnemy(1300.0f, 250.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 36)
	{
		SetEnemy(1300.0f, 250.0f, HPITEM);
	}
	else if (m_nTime == nOneSecond * 41)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 43)
	{
		SetEnemy(1300.0f, 250.0f, HORMING);
	}
	else if (m_nTime == nOneSecond * 44)
	{
		SetEnemy(1300.0f, 250.0f, MPITEM);
	}
	else if (m_nTime == nOneSecond * 48)
	{
		SetEnemy(1300.0f, 400.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 50)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 600.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 52)
	{
		SetEnemy(1300.0f, 300.0f, HORMING);
		SetEnemy(1300.0f, 500.0f, HORMING);
	}

	else if (m_nTime == nOneSecond * 55)
	{
		m_nTime = 0;
		CEnemy::AddLevel();
	}
}

//===========================
// 敵の生成
//===========================
void CGame::SetEnemy(float X, float Y, EnemyType type)
{
	switch (type)
	{
	case NORMAL:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_NORMAL);
		break;

	case HORMING:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_HORMING);
		break;

	case HPITEM:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_HPITEM);
		break;

	case MPITEM:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_MPITEM);
		break;

	case BIG:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_BIG);
		break;

	default:
		break;
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