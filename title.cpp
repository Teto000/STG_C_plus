//===================================
//
// �^�C�g���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "title.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CBg *CTitle::m_pBG = nullptr;	//�w�i

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
	m_pBG->Create();

	return S_OK;
}

//===========================
// �I��
//===========================
void CTitle::Uninit()
{

}

//===========================
// �X�V
//===========================
void CTitle::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// �w�i�̎擾
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG;
}