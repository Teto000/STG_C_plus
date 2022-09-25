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
CBg::CBg() : CObject(0)
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntClear = 0;
	m_fTexLeft = 0.0f;
	m_fTexRight = 0.0f;
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
	m_nCntAnim = 0;
	m_fTexLeft = 0.0f;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);
		m_fWidth = SCREEN_WIDTH;
		m_fHeight = SCREEN_HEIGHT;

		//�e�N�X�`�����W�̐ݒ�
		m_pObject2D->SetTexCIE(0.0f, 1.0f);

		switch (m_type)
		{
		case BGTYPE_GAME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_GAME);	//�e�N�X�`���̐ݒ�
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
			break;

		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE);
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
			break;

		case BGTYPE_TITLE_LOGO:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_LOGO);
			m_fWidth = 700.0f;
			m_fHeight = 300.0f;
			break;

		case BGTYPE_TITLE_ENTER:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_PRESSENTER);
			m_fWidth = 600.0f;
			m_fHeight = 100.0f;
			break;

		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_RESULT);
			m_fTexRight = 0.5f;
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
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
	if (m_pObject2D != nullptr)
	{
		//�J�E���g�̉��Z
		m_nCntAnim++;
		m_nCntAnim %= 10;

		m_nCntClear++;
		m_nCntClear %= 80;

		//�Q�[����� or �^�C�g����� or ���U���g��ʂȂ�
		if (m_type == BGTYPE_GAME || m_type == BGTYPE_TITLE || m_type == BGTYPE_RESULT
			&& m_nCntAnim == 0)
		{
			//�e�N�X�`�����W�̉��Z
			m_fTexLeft += 0.0005f;
			m_fTexRight += 0.0005f;

			//�e�N�X�`�����W�̐ݒ�
			m_pObject2D->SetTexCIE(m_fTexLeft, m_fTexRight);
		}

		//�v���X�G���^�[��_�ł�����
		if (m_type == BGTYPE_TITLE_ENTER)
		{
			if (m_nCntClear < 40)
			{
				m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
			}
		}
	}
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
	pBG->m_pObject2D = new CObject2D(0);

	if (pBG != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
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