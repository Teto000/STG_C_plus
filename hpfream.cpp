//===================================
//
// HP�t���[���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "hpfream.h"
#include "main.h"
#include "object2D.h"
#include "application.h"

//===========================
// �R���X�g���N�^
//===========================
CHpFream::CHpFream() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
}

//===========================
// �f�X�g���N�^
//===========================
CHpFream::~CHpFream()
{
}

//===========================
// ������
//===========================
HRESULT CHpFream::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_HPFREAM);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CHpFream::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CHpFream::Update()
{
	CObject2D::Update();

	//-------------------
	// �ړ�
	//-------------------
	m_pos = CObject2D::AddMove(m_move);
}

//===========================
// �`��
//===========================
void CHpFream::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CHpFream *CHpFream::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CHpFream *pHpFream = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pHpFream = new CHpFream;	//����

	if (pHpFream != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pHpFream->m_fWidth = fWidth;
		pHpFream->m_fHeight = fHeight;

		//������
		pHpFream->Init(pos);
		pHpFream->SetObjType(OBJTYPE_HP);
	}

	return pHpFream;
}

//===========================
// �ړ��ʂ̐ݒ�
//===========================
void CHpFream::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}