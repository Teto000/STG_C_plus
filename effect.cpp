//===================================
//
// �G�t�F�N�g�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "effect.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"

//===========================
// �R���X�g���N�^
//===========================
CEffect::CEffect() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	m_fRadius = 0.0f;	//���a(�傫��)
}

//===========================
// �f�X�g���N�^
//===========================
CEffect::~CEffect()
{

}

//===========================
// ������
//===========================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	//�\���̂̏�����
	m_pos = pos;			//�ʒu
	m_fRadius = 50.0f;	//���a
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//�F

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fRadius, m_fRadius);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_EFFECT);		//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CEffect::Update()
{
	CObject2D::Update();

	//���X�ɏ���������
	m_fRadius -= 1.0f;

	//���X�ɓ����ɂ���
	m_col.a -= 0.05f;

	if (m_fRadius <= 0.0f || m_col.a <= 0.0f)
	{//�������Ȃ��ď����� or ���S�ɓ����Ȃ�
		//�G�t�F�N�g�̏���
		Uninit();
		return;
	}
	else
	{
		//�T�C�Y�̐ݒ�
		SetSize(m_fRadius, m_fRadius);

		//�F�̐ݒ�
		CObject2D::SetColor(m_col);
	}
}

//===========================
// �`��
//===========================
void CEffect::Draw()
{
	//���u�����f�B���O�����Z�����ɐݒ�
	CObject2D::SetAddALPHA();

	CObject2D::Draw();

	//���u�����f�B���O�����ɖ߂�
	CObject2D::ResAddALPHA();
}

//===========================
// ����
//===========================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect *pEffect = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pEffect = new CEffect;	//����

	if (pEffect != nullptr)
	{//NULL�`�F�b�N
		//������
		pEffect->Init(pos);
		pEffect->SetObjType(OBJTYPE_EFFECT);
	}

	return pEffect;
}