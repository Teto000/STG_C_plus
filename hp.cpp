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
#include "object2D.h"
#include "player.h"
#include "application.h"

//===========================
// �R���X�g���N�^
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_HP, 0, sizeof(HP));	//�\���̂̃N���A
	m_nPlayerLife = 0;
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
	m_HP.fLength = (m_HP.fWidth / 100);

	CObject2D::Init(m_HP.pos);

	//���_���W�̐ݒ�
	CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
		-m_HP.fWidth / 2 + (m_HP.fLength * m_nPlayerLife), -m_HP.fHeight, m_HP.fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//�e�N�X�`���̐ݒ�

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
			m_nPlayerLife = pPlayer->GetRemLife();

			//���_���W�̐ݒ�
			CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
				-m_HP.fWidth / 2 + (m_HP.fLength * m_nPlayerLife), -m_HP.fHeight, m_HP.fHeight);

			//--------------------
			// HP��0�ɂȂ�����
			//--------------------
			if (m_HP.fLength * m_nPlayerLife <= 0)
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