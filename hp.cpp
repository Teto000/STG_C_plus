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
#include "enemy.h"
#include "application.h"

//===========================
// �R���X�g���N�^
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_HP, 0, sizeof(HP));	//�\���̂̃N���A
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
	CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//���_���W�̐ݒ�
	CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
		-m_HP.fWidth / 2 + (m_HP.fLength * 100), -m_HP.fHeight / 2, m_HP.fHeight / 2);

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
	// �N���X�̎擾
	//-------------------
	CPlayer *pPlayer = CApplication::GetPlayer();	//�v���C���[
	CEnemy *pEnemy = CApplication::GetEnemy();		//�G

	//-------------------
	// HP�̌���
	//-------------------
	switch (m_HP.type)
	{
	//=============================
	// �v���C���[�̏���
	//=============================
	case HPTYPE_PLAYER:

		//�v���C���[�̗̑͂��擾
		m_HP.nLife = pPlayer->GetLife();

		//�v���C���[�̎c��̗͂��擾
		m_HP.nRemLife = pPlayer->GetRemLife();
		break;

	//=============================
	// �G�̏���
	//=============================
	case HPTYPE_ENEMY:

		//�G�̗̑͂��擾
		m_HP.nLife = pEnemy->GetLife();

		//�G�̎c��̗͂��擾
		m_HP.nRemLife = pEnemy->GetRemLife();
		break;

	default:
		break;
	}

	//HP�������̏���
	SubHP(m_HP.nLife, m_HP.nRemLife);
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

//===========================
// HP�������̏���
//===========================
void CHp::SubHP(int nLife, int nRemLife)
{
	//-------------------------
	// ���_���W�̐ݒ�
	//-------------------------
	if (nRemLife >= 1)
	{//�c��̗�(%)������Ȃ�
		//���̗͕̑��̍��W��ݒ�
		CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
			-m_HP.fWidth / 2 + (m_HP.fLength * nRemLife), -m_HP.fHeight / 2, m_HP.fHeight / 2);
	}
	else if (nRemLife == 0 && nLife > 0)
	{//�c��̗͂�0% ���� �̗͂�0����Ȃ��Ȃ�
		//1%���̃Q�[�W���ێ�
		CObject2D::SetVtxCIE_Gauge(m_HP.pos, -m_HP.fWidth / 2,
			-m_HP.fWidth / 2 + m_HP.fLength, -m_HP.fHeight / 2, m_HP.fHeight / 2);
	}

	//-------------------------
	// HP���Ƃ̏���
	//-------------------------
	if (nRemLife <= 0 && nLife <= 0)
	{//HP��0�ɂȂ��� ���� �̗͂��Ȃ�������
		//HP�o�[�̏���
		Uninit();
		CObject2D::Release();
	}
	else if (nRemLife <= 20)
	{//HP��20%�ȉ��ɂȂ�����
		//�ԐF�ɂ���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (nRemLife <= 50)
	{//HP��50%�ȉ��ɂȂ�����
		//���F�ɂ���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		//�ΐF�ɂ���
		CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}