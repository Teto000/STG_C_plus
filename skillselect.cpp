//===================================
//
// �X�L���I����ʂ̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "skillselect.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CBg *CSkillSelect::m_pBG = nullptr;	//�w�i

//===========================
// �R���X�g���N�^
//===========================
CSkillSelect::CSkillSelect()
{

}

//===========================
// �f�X�g���N�^
//===========================
CSkillSelect::~CSkillSelect()
{

}

//===========================
// ������
//===========================
HRESULT CSkillSelect::Init()
{
	//�w�i�̐���
	m_pBG->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_SKILLSELECT);

	return S_OK;
}

//===========================
// �I��
//===========================
void CSkillSelect::Uninit()
{

}

//===========================
// �X�V
//===========================
void CSkillSelect::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// �w�i�̎擾
//===========================
CBg *CSkillSelect::GetBG()
{
	return m_pBG;
}