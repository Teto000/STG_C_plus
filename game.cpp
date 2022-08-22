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
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "bg.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;	//�v���C���[
CEnemy	  *CGame::m_pEnemy = nullptr;	//�G
CScore	  *CGame::m_pScore = nullptr;	//�X�R�A
CBg		  *CGame::m_pBG = nullptr;		//�w�i

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{
	m_EnemyCnt = 0;
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

	//�w�i�̐���
	m_pBG = CBg::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	//�X�R�A�̐���
	m_pScore = CScore::Create();

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{
	//�I�u�W�F�N�g�̑S���
	CObject::ReleaseAll();
}

//===========================
// �X�V
//===========================
void CGame::Update()
{
	//m_EnemyCnt++;
	//m_EnemyCnt %= 80;

	//if (m_EnemyCnt == 0)
	//{
	//	int nRand = rand() % 520 + 200;

	//	//�G�̐���
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1300, (float)nRand, 0.0f),
	//								CEnemy::ENEMYTYPE_NORMAL);
	//}
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