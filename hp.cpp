//===================================
//
// HP�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_nLife = 0;			//�̗͎󂯎��p
	m_nRemLife = 0;			//�c��̗͎󂯎��p
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_fLength = 0.0f;		//HP�o�[�̒���
	m_type = HPTYPE_MAX;	//���
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
	m_pos = pos;
	m_fLength = (m_fWidth / 100);

	CObject2D::Init(m_pos);
	CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//���_���W�̐ݒ�
	CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
		-m_fWidth / 2 + (m_fLength * 100), -m_fHeight / 2, m_fHeight / 2);

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

	//-------------------
	// �ړ�
	//-------------------
	CObject2D::AddMove(m_move);

	//-------------------
	// HP�̌���
	//-------------------
	switch (m_type)
	{
	//=============================
	// �v���C���[�̏���
	//=============================
	case HPTYPE_PLAYER:

		//�v���C���[�̗̑͂��擾
		m_nLife = pPlayer->GetLife();

		//�v���C���[�̎c��̗͂��擾
		m_nRemLife = pPlayer->GetRemLife();
		break;

	default:
		break;
	}

	//HP�������̏���
	SubHP();
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
	pHP->m_pos = pos;
	pHP->m_move = move;
	pHP->m_fWidth = fWidth;
	pHP->m_fHeight = fHeight;
	pHP->m_type = type;

	if (pHP != nullptr)
	{//NULL�`�F�b�N
		//������
		pHP->Init(pHP->m_pos);
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}

//===========================
// HP�̐ݒ�
//===========================
void CHp::SetLife(int nLife, int nRemLife)
{
	m_nLife = nLife;
	m_nRemLife = nRemLife;
}

//===========================
// HP�������̏���
//===========================
void CHp::SubHP()
{
	//-------------------------
	// ���_���W�̐ݒ�
	//-------------------------
	if (m_nRemLife >= 1)
	{//�c��̗�(%)������Ȃ�
		//���̗͕̑��̍��W��ݒ�
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + (m_fLength * m_nRemLife), -m_fHeight / 2, m_fHeight / 2);
	}
	else if (m_nRemLife == 0 && m_nLife > 0)
	{//�c��̗͂�0% ���� �̗͂�0����Ȃ��Ȃ�
		//1%���̃Q�[�W���ێ�
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + m_fLength, -m_fHeight / 2, m_fHeight / 2);
	}

	//-------------------------
	// HP���Ƃ̏���
	//-------------------------
	if (m_nRemLife <= 0 && m_nLife <= 0)
	{//HP��0�ɂȂ��� ���� �̗͂��Ȃ�������
		//HP�o�[�̏���
		Uninit();
		return;
	}
	else if (m_nRemLife <= 20)
	{//HP��20%�ȉ��ɂȂ�����
		//�ԐF�ɂ���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_nRemLife <= 50)
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