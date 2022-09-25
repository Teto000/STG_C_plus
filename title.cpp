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

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CBg *CTitle::m_pBG[MaxBg] = {};	//�w�i

//===========================
// �R���X�g���N�^
//===========================
CTitle::CTitle()
{

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
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// �w�i�̎擾
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG[0];
}