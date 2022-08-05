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

//===========================
// �R���X�g���N�^
//===========================
CBarrier::CBarrier() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
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

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));	//�F�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//�e�N�X�`���̐ݒ�

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

	if (CObject2D::GetCollision(OBJTYPE_BULLET))
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
CBarrier *CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	CBarrier *pBarrier = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------zz
	pBarrier = new CBarrier;	//����

	if (pBarrier != nullptr)
	{//NULL�`�F�b�N
		//�\���̂ɑ��
		pBarrier->m_move = move;				//�ړ���
		pBarrier->m_fWidth = fWidth + 50.0f;	//��
		pBarrier->m_fHeight = fHeight + 50.0f;	//����

		//������
		pBarrier->Init(pos);
		pBarrier->SetObjType(OBJTYPE_BARRIER);
	}

	return pBarrier;
}