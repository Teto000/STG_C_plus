//===================================
//
// �A�v���P�[�V�����̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
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
// �ÓI�����o�ϐ��錾
//------------------------
CRenderer *CApplication::m_pRenderer = nullptr;	//�����_���[
CInput	  *CApplication::m_pInput = nullptr;	//�C���v�b�g
CTexture  *CApplication::m_pTexture = nullptr;	//�e�N�X�`��
CSound	  *CApplication::m_pSound = nullptr;	//�T�E���h
CPlayer	  *CApplication::m_pPlayer = nullptr;	//�v���C���[
CEnemy	  *CApplication::m_pEnemy = nullptr;	//�G
CScore	  *CApplication::m_pScore = nullptr;	//�X�R�A
CBg		  *CApplication::m_pBG = nullptr;		//�w�i

//===========================
// �R���X�g���N�^
//===========================
CApplication::CApplication()
{
	m_EnemyCnt = 0;
}

//===========================
// �f�X�g���N�^
//===========================
CApplication::~CApplication()
{

}

//===========================
// ������
//===========================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	//--------------------------
	// �C���X�^���X�̐���
	//--------------------------
	m_pRenderer = new CRenderer;	//�����_�����O
	m_pInput = new CInput;			//�C���v�b�g
	m_pTexture = new CTexture;		//�e�N�X�`��
	m_pSound = new CSound;			//�T�E���h

	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	//�����_�����O�̏�����
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�C���v�b�g�̏�����
	m_pInput->Init(hInstance, hWnd);

	//�T�E���h�̏�����
	//m_pSound->Init(hWnd);

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
void CApplication::Uninit()
{
	//�e�N�X�`���̏I��
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//�����_�����O�̏I��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�C���v�b�g�̏I��
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//�I�u�W�F�N�g�̑S���
	CObject::ReleaseAll();

	//�T�E���h�̏I��
	/*if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}*/

}

//===========================
// �X�V
//===========================
void CApplication::Update()
{
	//�C���v�b�g�̍X�V
	m_pInput->Update();	//�ŏ��ɂ��

	//�����_�����O�̍X�V
	m_pRenderer->Update();

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
// �`��
//===========================
void CApplication::Draw()
{
	//�����_�����O�̕`��
	m_pRenderer->Draw();
}

//===========================
// �����_�����O�̎擾
//===========================
CRenderer *CApplication::GetRenderer()
{
	return m_pRenderer;
}

//===========================
// �C���v�b�g�̎擾
//===========================
CInput *CApplication::GetInput()
{
	return m_pInput;
}

//===========================
// �e�N�X�`���̎擾
//===========================
CTexture *CApplication::GetTexture()
{
	return m_pTexture;
}

//===========================
// �T�E���h�̎擾
//===========================
CSound *CApplication::GetSound()
{
	return m_pSound;
}

//===========================
// �v���C���[�̎擾
//===========================
CPlayer *CApplication::GetPlayer()
{
	return m_pPlayer;
}

//===========================
// �X�R�A�̎擾
//===========================
CScore *CApplication::GetScore()
{
	return m_pScore;
}