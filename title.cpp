//===================================
//
// �^�C�g���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"
#include "sound.h"
#include "gamemode.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CBg		  *CTitle::m_pBG[MaxBg] = {};			//�w�i
CGameMode *CTitle::m_pGameMode[MaxMode] = {};	//�Q�[�����[�h

//===========================
// �R���X�g���N�^
//===========================
CTitle::CTitle()
{
	nCntTime = 0;	//�A�j���[�V�����J�E���g
	nNumber = 0;	//�I�𒆂̔ԍ�
	m_bPressEneter = false;	//�G���^�[�L�[�������ꂽ��
}

//===========================
// �f�X�g���N�^
//===========================
CTitle::~CTitle()
{

}

//===========================
// ������
//===========================
HRESULT CTitle::Init()
{
	//�w�i�̐���
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_TITLE);

	m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f)
					, CBg::BGTYPE_TITLE_LOGO);

	m_pBG[2]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f)
					, CBg::BGTYPE_TITLE_ENTER);

	//�T�E���h�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CTitle::Uninit()
{
	//�T�E���h�̒�~
	CSound::StopSound(CSound::SOUND_LABEL_TITLE);
}

//===========================
// �X�V
//===========================
void CTitle::Update()
{
	if (!m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		{
			D3DXVECTOR3 timePos(SCREEN_WIDTH / 2, 300.0f, 0.0f);
			D3DXVECTOR3 scorePos(SCREEN_WIDTH / 2, 500.0f, 0.0f);

			m_pGameMode[0] = CGameMode::Create(timePos, CGameMode::GAMEMODE_TIME);
			m_pGameMode[1] = CGameMode::Create(scorePos, CGameMode::GAMEMODE_SCORE);
		}

		m_bPressEneter = true;
	}
	//�Q�[����ʂɈڍs
	else if (m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		CApplication::SetMode(CApplication::MODE_GAME);
		return;
	}

	//���[�h�I������
	SelectMode();
}

//===========================
// ���[�h�I������
//===========================
void CTitle::SelectMode()
{
	if (m_pGameMode[nNumber])
	{
		nCntTime++;
		nCntTime %= AnimationTime;

		if (nCntTime < 40)
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		}
	}

	//�I��ԍ��؂�ւ�����
	ChangeNumber();
}

//===========================
// �I��ԍ��؂�ւ�����
//===========================
void CTitle::ChangeNumber()
{
	if (nNumber == 0)
	{
		if (CInputKeyboard::Trigger(DIK_W) || CInputKeyboard::Trigger(DIK_S))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber = 1;
		}
	}
	else if (nNumber == 1)
	{
		if (CInputKeyboard::Trigger(DIK_W) || CInputKeyboard::Trigger(DIK_S))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber = 0;
		}
	}
}

//===========================
// �w�i�̎擾
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG[0];
}