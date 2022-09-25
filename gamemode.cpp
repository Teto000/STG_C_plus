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

//===========================
// �R���X�g���N�^
//===========================
CGameMode::CGameMode() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
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
	m_fWidth = 300.0f;
	m_fHeight = 50.0f;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CGameMode::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CGameMode::Update()
{
	CObject2D::Update();
}

//===========================
// �`��
//===========================
void CGameMode::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CGameMode *CGameMode::Create(D3DXVECTOR3 pos)
{
	CGameMode *pGameMode = nullptr;

	//----------------------------------
	// �G�N�X�v���[�W�����̐����Ə�����
	//----------------------------------
	pGameMode = new CGameMode;	//����

	if (pGameMode != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
		//������
		pGameMode->Init(pos);
		pGameMode->SetObjType(OBJTYPE_EXPLOSION);
	}

	return pGameMode;
}