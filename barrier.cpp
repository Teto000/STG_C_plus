//===================================
//
// �o���A�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Barrier, 0, sizeof(Barrier));	//�\���̂̃N���A
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
	m_Barrier.pos = pos;	//�ʒu

	CObject2D::Init(m_Barrier.pos);

	CObject2D::SetSize(m_Barrier.fWidth, m_Barrier.fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));	//�F�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//�e�N�X�`���̐ݒ�

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
		pBarrier->m_Barrier.move = move;				//�ړ���
		pBarrier->m_Barrier.fWidth = fWidth + 50.0f;	//��
		pBarrier->m_Barrier.fHeight = fHeight + 50.0f;	//����

		//������
		pBarrier->Init(pos);
		pBarrier->SetObjType(OBJTYPE_BARRIER);
	}

	return pBarrier;
}