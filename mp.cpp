//===================================
//
// MP�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "mp.h"
#include "main.h"
#include "object2D.h"
#include "application.h"

//===========================
// �R���X�g���N�^
//===========================
CMp::CMp() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_fLength = 0.0f;		//MP�o�[�̒���
}

//===========================
// �f�X�g���N�^
//===========================
CMp::~CMp()
{
}

//===========================
// ������
//===========================
HRESULT CMp::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_pos = pos;
	m_fLength = (m_fWidth / 100);

	CObject2D::Init(m_pos);
	CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	//���_���W�̐ݒ�
	CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
		-m_fWidth / 2 + (m_fLength * 100), -m_fHeight / 2, m_fHeight / 2);

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CMp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CMp::Update()
{
	CObject2D::Update();

	//MP�������̏���
	SubMP();
}

//===========================
// �`��
//===========================
void CMp::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CMp *CMp::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMp *pMP = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pMP = new CMp;	//����

	if (pMP != nullptr)
	{//NULL�`�F�b�N
	 //�\���̂ɒl����
		pMP->m_fWidth = fWidth;
		pMP->m_fHeight = fHeight;

		//������
		pMP->Init(pos);
		pMP->SetObjType(OBJTYPE_MP);
	}

	return pMP;
}

//===========================
// MP�̐ݒ�
//===========================
void CMp::SetMP(int nMp, int nRemMp)
{
	m_nMp = nMp;
	m_nRemMp = nRemMp;
}

//===========================
// MP�������̏���
//===========================
void CMp::SubMP()
{
	//-------------------------
	// ���_���W�̐ݒ�
	//-------------------------
	if (m_nRemMp >= 1)
	{//�c��̗�(%)������Ȃ�
	 //���̗͕̑��̍��W��ݒ�
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + (m_fLength * m_nRemMp), -m_fHeight / 2, m_fHeight / 2);
	}
	else if (m_nRemMp == 0 && m_nMp > 0)
	{//�c��̗͂�0% ���� �̗͂�0����Ȃ��Ȃ�
		//1%���̃Q�[�W���ێ�
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + m_fLength, -m_fHeight / 2, m_fHeight / 2);
	}
}