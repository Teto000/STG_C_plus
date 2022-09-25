//===================================
//
// �Q�[�����[�h�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "gamemode.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"
#include "bg.h"

//===========================
// �R���X�g���N�^
//===========================
CGameMode::CGameMode() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_mode = GAMEMODE_MAX;	//���[�h
	m_pBg = nullptr;
}

//===========================
// �f�X�g���N�^
//===========================
CGameMode::~CGameMode()
{

}

//===========================
// ������
//===========================
HRESULT CGameMode::Init(D3DXVECTOR3 pos)
{
	//------------------
	// �\���̂̏�����
	//------------------
	m_pos = pos;
	m_fWidth = 500.0f;
	m_fHeight = 100.0f;

	if (m_pObject2D != nullptr)
	{
		switch (m_mode)
		{
		case GAMEMODE_TIME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_TIME);
			break;

		case GAMEMODE_SCORE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_SCORE);
			break;

		default:
			break;
		}

		m_pObject2D->Init(m_pos);

		m_pObject2D->SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�
	}

	//---------------------
	// �w�i�̐���
	//---------------------
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), CBg::BGTYPE_SELECTMODE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGameMode::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CGameMode::Update()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Update();
	}
}

//===========================
// �`��
//===========================
void CGameMode::Draw()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Draw();
	}
}

//===========================
// ����
//===========================
CGameMode *CGameMode::Create(D3DXVECTOR3 pos, GAMEMODE mode)
{
	CGameMode *pGameMode = nullptr;

	//----------------------------------
	// �Q�[�����[�h�̐����Ə�����
	//----------------------------------
	pGameMode = new CGameMode;	//����
	pGameMode->m_pObject2D = new CObject2D(1);

	if (pGameMode != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pGameMode->m_mode = mode;

		//������
		pGameMode->Init(pos);
		pGameMode->SetObjType(OBJTYPE_BG);
	}

	return pGameMode;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CGameMode::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CGameMode::GetWidth()
{
	return m_fWidth;
}

//===========================
// �����̎擾
//===========================
float CGameMode::GetHeight()
{
	return m_fHeight;
}

//===========================
// �I�u�W�F�N�g�̎擾
//===========================
CObject2D* CGameMode::GetObject2D()
{
	return m_pObject2D;
}