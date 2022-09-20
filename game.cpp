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
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "bg.h"
#include "skill.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;		//�v���C���[
CEnemy	  *CGame::m_pEnemy = nullptr;		//�G
CScore	  *CGame::m_pScore = nullptr;		//�X�R�A
CBg		  *CGame::m_pBG = nullptr;			//�w�i
CSkill	  *CGame::m_pSkill[nMaxSkill] = {};	//�X�L��

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
	for (int i = 0; i < 2; i++)
	{
		m_bSkill[i] = false;
		m_nSkillTime[i] = 0;
	}

	//�w�i�̐���
	m_pBG = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CBg::BGTYPE_GAME);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	//�X�R�A�̐���
	m_pScore = CScore::Create();

	m_pSkill[0] = CSkill::Create(CSkill::SKILLTYPE_HEAL);
	m_pSkill[1] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{

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

	//��ʑJ��
	/*if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_RESULT);
	}*/
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
	else if (m_nTime == nOneSecond * 15)
	{
		SetEnemy(1300.0f, 300.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 20)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 25)
	{
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 28)
	{
		SetEnemy(1300.0f, 500.0f, BIG);
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 33)
	{
		SetEnemy(1300.0f, 250.0f, HPITEM);
	}
	else if (m_nTime == nOneSecond * 38)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 300.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 40)
	{
		SetEnemy(1300.0f, 250.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 41)
	{
		SetEnemy(1300.0f, 250.0f, MPITEM);
	}
	else if (m_nTime == nOneSecond * 45)
	{
		SetEnemy(1300.0f, 400.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 47)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 600.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 49)
	{
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}

	else if (m_nTime == nOneSecond * 50)
	{
		m_nTime = 0;
	}
}

//===========================
// �G�̐���
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
	return m_pBG;
}