//===================================
//
// �Q�[���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
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
#include "timer.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;		//�v���C���[
CEnemy	  *CGame::m_pEnemy = nullptr;		//�G
CScore	  *CGame::m_pScore = nullptr;		//�X�R�A
CBg		  *CGame::m_pBG[nMaxBg] = {};		//�w�i
CSkill	  *CGame::m_pSkill[nMaxSkill] = {};	//�X�L��
CTimer	  *CGame::m_pTimer;					//�^�C�}�[
CGame::MODE CGame::m_mode = MODE_MAX;		//���[�h

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{
	m_EnemyCnt = 0;
	m_nTime = 0;
	m_nSkillTime[nMaxSkill] = {};
	m_bSkill[nMaxSkill] = {};
}

//===========================
// �f�X�g���N�^
//===========================
CGame::~CGame()
{

}

//===========================
// ������
//===========================
HRESULT CGame::Init()
{
	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	//�����o�ϐ��̏�����
	for (int i = 0; i < nMaxSkill; i++)
	{
		m_bSkill[i] = false;
		m_nSkillTime[i] = 0;
	}

	//�w�i�̐���
	{
		D3DXVECTOR3 bgPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		D3DXVECTOR3 timePos(950.0f, 70.0f, 0.0f);
		D3DXVECTOR3 scorePos(1170.0f, 70.0f, 0.0f);

		m_pBG[0] = CBg::Create(bgPos, CBg::BGTYPE_GAME);
		m_pBG[1] = CBg::Create(timePos, CBg::BGTYPE_GAME_TIME);
		m_pBG[2] = CBg::Create(scorePos, CBg::BGTYPE_GAME_SCORE);
	}

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	//�X�R�A�̐���
	m_pScore = CScore::Create(CScore::MODE_GAME);

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(CTimer::MODE_GAME);

	m_pSkill[0] = CSkill::Create(CSkill::SKILLTYPE_HEAL);
	m_pSkill[1] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);
	m_pSkill[2] = CSkill::Create(CSkill::SKILLTYPE_ATTACKUP);
	m_pSkill[3] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP);

	//�T�E���h�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{
	//�T�E���h�̒�~
	CSound::StopSound(CSound::SOUND_LABEL_GAME);
}

//===========================
// �X�V
//===========================
void CGame::Update()
{
	//�G�̏o��
	AppearEnemy();

	//------------------------
	// �X�L���̐F�ύX
	//------------------------
	if (CInputKeyboard::Trigger(DIK_U) && !m_bSkill[0])
	{
		m_pSkill[0]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[0] = true;
	}
	else if (CInputKeyboard::Trigger(DIK_I) && !m_bSkill[1])
	{
		m_pSkill[1]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[1] = true;
	}
	else if (CInputKeyboard::Trigger(DIK_O) && !m_bSkill[2])
	{
		m_pSkill[2]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[2] = true;
	}
	else if (CInputKeyboard::Trigger(DIK_P) && !m_bSkill[3])
	{
		m_pSkill[3]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bSkill[3] = true;
	}

	//-------------------------
	// �X�L�����Ԃ̃J�E���g
	//-------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (m_bSkill[i])
		{
			m_nSkillTime[i]++;
		}

		if (m_nSkillTime[i] >= 600)
		{
			//�X�L���̐F��߂�
			m_bSkill[i] = false;
			m_pSkill[i]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nSkillTime[i] = 0;
		}
	}

	//-------------------------
	// ���ԂŏI�����鏈��
	//-------------------------
	if (m_mode == MODE_TIME)
	{//�^�C���A�^�b�N���[�h�Ȃ�
		int nTime = m_pTimer->GetTime();

		if (nTime >= 180)
		{//1�����o�߂�����
			//���U���g��ʂֈړ�
			CApplication::SetMode(CApplication::MODE_RESULT);
		}
	}
}

//===========================
// �G�̏o��
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
// �G�̐���
//===========================
void CGame::SetEnemy(float X, float Y, EnemyName type)
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
// ���[�h�ݒ�
//===========================
void CGame::SetMode(CApplication::GAMEMODE mode)
{
	switch (mode)
	{
	case CApplication::GAMEMODE_TIME:
		m_mode = CGame::MODE_TIME;
		break;

	case CApplication::GAMEMODE_SCORE:
		m_mode = CGame::MODE_SCORE;
		break;

	case CApplication::GAMEMODE_MAX:
		break;

	default:
		break;
	}
}

//===========================
// ���[�h�̐ݒ�
//===========================
void CGame::SetMode(CGame::MODE mode)
{
	m_mode = mode;
}

//===========================
// �v���C���[�̎擾
//===========================
CPlayer *CGame::GetPlayer()
{
	return m_pPlayer;
}

//===========================
// �X�R�A�̎擾
//===========================
CScore *CGame::GetScore()
{
	return m_pScore;
}

//===========================
// �w�i�̎擾
//===========================
CBg *CGame::GetBG()
{
	return m_pBG[0];
}

//===========================
// �^�C�}�[�̎擾
//===========================
CTimer *CGame::GetTimer()
{
	return m_pTimer;
}