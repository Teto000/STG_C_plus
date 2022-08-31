//===================================
//
// �e�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "bg.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//===========================
// �R���X�g���N�^
//===========================
CBg::CBg() : CObject()
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//===========================
// �f�X�g���N�^
//===========================
CBg::~CBg()
{

}

//===========================
// ������
//===========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);
		m_fWidth = SCREEN_WIDTH;
		m_fHeight = SCREEN_HEIGHT;

		switch (m_type)
		{
		case BGTYPE_GAME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG);	//�e�N�X�`���̐ݒ�
			break;

		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE);
			break;

		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_RESULT);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
	}

	return S_OK;
}

//===========================
// �I��
//===========================
void CBg::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CBg::Update()
{

}

//===========================
// �`��
//===========================
void CBg::Draw()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Draw();
	}
}

//===========================
// ����
//===========================
CBg *CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBG = nullptr;

	//----------------------------------
	// �w�i�̐����Ə�����
	//----------------------------------
	pBG = new CBg;	//����
	pBG->m_pObject2D = new CObject2D;

	if (pBG != nullptr)
	{//NULL�`�F�b�N
		pBG->m_type = type;

		//������
		pBG->Init(pos);
		pBG->SetObjType(OBJTYPE_BG);
	}

	return pBG;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CBg::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CBg::GetWidth()
{
	return m_fWidth;
}

//===========================
// �����̎擾
//===========================
float CBg::GetHeight()
{
	return m_fHeight;
}