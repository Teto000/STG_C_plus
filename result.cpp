//===================================
//
// ���U���g�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "result.h"
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
CBg *CResult::m_pBG = nullptr;	//�w�i

//===========================
// �R���X�g���N�^
//===========================
CResult::CResult()
{

}

//===========================
// �f�X�g���N�^
//===========================
CResult::~CResult()
{

}

//===========================
// ������
//===========================
HRESULT CResult::Init()
{
	//�w�i�̐���
	m_pBG->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		, CBg::BGTYPE_RESULT);

	//�T�E���h�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//===========================
// �I��
//===========================
void CResult::Uninit()
{
	//�T�E���h�̒�~
	CSound::StopSound(CSound::SOUND_LABEL_RESULT);
}

//===========================
// �X�V
//===========================
void CResult::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		CApplication::SetMode(CApplication::MODE_TITLE);
	}
}

//===========================
// �w�i�̎擾
//===========================
CBg *CResult::GetBG()
{
	return m_pBG;
}