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
	SetEnemy();

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