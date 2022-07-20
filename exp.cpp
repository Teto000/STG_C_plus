//===================================
//
// �o���l�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "exp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//===========================
// �R���X�g���N�^
//===========================
CExp::CExp() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	m_fLength = 0.0f;	//���a
}

//===========================
// �f�X�g���N�^
//===========================
CExp::~CExp()
{

}

//===========================
// ������
//===========================
HRESULT CExp::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̑��
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexture(CTexture::TEXTURE_EXP);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CExp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CExp::Update()
{
	CObject2D::Update();
}

//===========================
// �`��
//===========================
void CExp::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CExp *CExp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	CExp *pExp = nullptr;

	//----------------------------------
	// �o���l�̐����Ə�����
	//----------------------------------
	pExp = new CExp;	//����

	if (pExp != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pExp->m_rot = rot;			//��]
		pExp->m_fLength = fLength;	//���a

		//������
		pExp->Init(pos);
		pExp->SetObjType(OBJTYPE_EXP);
	}

	return pExp;
}