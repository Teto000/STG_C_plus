//===================================
//
// HP�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
#include "hp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "player.h"
#include "application.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------

//===========================
// �R���X�g���N�^
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_HP, 0, sizeof(m_HP));	//�\���̂̃N���A
}

//===========================
// �f�X�g���N�^
//===========================
CHp::~CHp()
{

}

//===========================
// ������
//===========================
HRESULT CHp::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_HP.pos = pos;

	CObject2D::Init(m_HP.pos);

	CObject2D::SetSize(80.0f, 100.0f);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//�e�N�X�`���̐ݒ�

	m_HP.pos = CObject2D::GetPosition();

	return S_OK;
}

//===========================
// �I��
//===========================
void CHp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CHp::Update()
{
	CObject2D::Update();

	//-------------------
	// HP�̌���
	//-------------------
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GETObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		//�I�u�W�F�N�g�̎�ނ̎擾
		CObject::EObjType type = pObject->GetObjType();

		//=============================
		// �v���C���[�̏���
		//=============================
		if (type == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = CApplication::GetPlayer();

			//�v���C���[�̎c��̗͂��擾
			int PlayerLife = pPlayer->GetRemLife();

			//���_���W�̐ݒ�
			CObject2D::SetVtxCIE_SP(m_HP.pos, m_HP.fWidth,
				m_HP.fWidth / 2 + (m_HP.fLength * PlayerLife), m_HP.fHeight, m_HP.fHeight);

			//--------------------
			// HP��0�ɂȂ�����
			//--------------------
			if (m_HP.fLength * PlayerLife <= 0)
			{
				Uninit();
				CObject2D::Release();
			}
		}
	}
}

//===========================
// �`��
//===========================
void CHp::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CHp *CHp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE type)
{
	CHp *pHP = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pHP = new CHp;	//����

	//�\���̂ɒl����
	pHP->m_HP.pos = pos;
	pHP->m_HP.move = move;
	pHP->m_HP.fWidth = fWidth;
	pHP->m_HP.fHeight = fHeight;
	pHP->m_HP.type = type;

	if (pHP != nullptr)
	{//NULL�`�F�b�N
		//������
		pHP->Init(pHP->m_HP.pos);
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}