//===================================
//
// �A�v���P�[�V�����̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"
#include "sound.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "game.h"
#include "title.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CTitle*		CApplication::m_pTitle = nullptr;			//�^�C�g���N���X
CGame*		CApplication::m_pGame = nullptr;			//�Q�[���N���X
CApplication::MODE	CApplication::m_mode = MODE_MAX;	//�Q�[�����[�h

CRenderer*	CApplication::m_pRenderer = nullptr;	//�����_���[
CInput*		CApplication::m_pInput = nullptr;	//�C���v�b�g
CTexture*	CApplication::m_pTexture = nullptr;	//�e�N�X�`��
CSound*		CApplication::m_pSound = nullptr;	//�T�E���h

//===========================
// �R���X�g���N�^
//===========================
CApplication::CApplication()
{

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

	//�����_�����O�̏�����
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�C���v�b�g�̏�����
	m_pInput->Init(hInstance, hWnd);

	//�T�E���h�̏�����
	//m_pSound->Init(hWnd);

	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CApplication::Uninit()
{
	//�I�u�W�F�N�g�̑S���
	CObject::ReleaseAll();

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

	//���[�h���Ƃ̍X�V
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case MODE_RESULT:
		break;

	default:
		break;
	}
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
// ���[�h�̐ݒ�
//===========================
void CApplication::SetMode(MODE mode)
{
	//���݂̃��[�h���I��
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		break;

	case MODE_RESULT:
		break;

	default:
		break;
	}

	//���[�h�̐؂�ւ�
	m_mode = mode;

	//�V�������[�h�̐���
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle = nullptr;
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;
	
	case MODE_GAME:
		m_pGame = nullptr;
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:
		break;

	default:
		break;
	}
}

//===========================
// ���[�h�̎擾
//===========================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
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