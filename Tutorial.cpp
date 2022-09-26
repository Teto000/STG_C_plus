//===================================
//
// �`���[�g���A���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "tutorial.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"
#include "sound.h"
#include "gamemode.h"
#include "game.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CBg	*CTutorial::m_pBG[MaxBg] = {};	//�w�i

//===========================
// �R���X�g���N�^
//===========================
CTutorial::CTutorial()
{
	m_bPressEneter = false;
}

//===========================
// �f�X�g���N�^
//===========================
CTutorial::~CTutorial()
{

}

//===========================
// ������
//===========================
HRESULT CTutorial::Init()
{
	//�w�i�̐���
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_TUTORIAL1);

	//�T�E���h�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CTutorial::Uninit()
{
	//�T�E���h�̒�~
	CSound::StopSound(CSound::SOUND_LABEL_TITLE);
}

//===========================
// �X�V
//===========================
void CTutorial::Update()
{
	if (!m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
			, CBg::BGTYPE_TUTORIAL2);

		m_bPressEneter = true;
	}
	else if(m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_TITLE);
	}
}