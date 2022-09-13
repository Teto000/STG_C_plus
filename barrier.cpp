//===================================
//
// �o���A�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "barrier.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "game.h"
#include "bullet.h"
#include "player.h"

//===========================
// �R���X�g���N�^
//===========================
CBarrier::CBarrier() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_playermove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�̈ړ���
	m_nLife = 0;		//�̗�
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//===========================
// �f�X�g���N�^
//===========================
CBarrier::~CBarrier()
{

}

//===========================
// ������
//===========================
HRESULT CBarrier::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_pos = pos;	//�ʒu
	m_nLife = 100;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�F�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_BARRIER);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CBarrier::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CBarrier::Update()
{
	CObject2D::Update();

	switch (m_type)
	{
	case BARRIERTYPE_PLAYER:
		//�v���C���[�̑��x���擾
		m_playermove = CGame::GetPlayer()->GetMove();
		m_pos = CObject2D::AddMove(m_playermove);
		break;

	case BARRIERTYPE_ENEMY:
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//�̗͂��s����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CBarrier::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
							float fWidth, float fHeight, BARRIERTYPE type)
{
	CBarrier *pBarrier = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pBarrier = new CBarrier;	//����

	if (pBarrier != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pBarrier->m_move = move;				//�ړ���
		pBarrier->m_fWidth = fWidth + 30.0f;	//��
		pBarrier->m_fHeight = fHeight + 30.0f;	//����
		pBarrier->m_type = type;				//���

		//������
		pBarrier->Init(pos);
		pBarrier->SetObjType(OBJTYPE_BARRIER);
	}

	return pBarrier;
}

//===========================
// �̗͂̌���
//===========================
void CBarrier::SubLife(CBullet::BULLETTYPE type)
{
	switch (type)
	{
	//�`���[�W�V���b�g
	case CBullet::BULLETTYPE_HORMING:
		m_nLife = 0;
		break;

	default:
		m_nLife -= 10;
		break;
	}
}

//===========================
// ��ނ̎擾
//===========================
CBarrier::BARRIERTYPE CBarrier::GetType()
{
	return m_type;
}