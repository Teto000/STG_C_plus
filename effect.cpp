//===================================
//
// �G�t�F�N�g�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Effect, 0, sizeof(Effect));	//�\���̂̃N���A
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
	m_Effect.pos = pos;			//�ʒu
	m_Effect.nLife = 100;		//����
	m_Effect.fRadius = 50.0f;	//���a
	m_Effect.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//�F

	CObject2D::Init(m_Effect.pos);

	CObject2D::SetSize(m_Effect.fRadius, m_Effect.fRadius);	//�T�C�Y�̐ݒ�

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
	m_Effect.fRadius -= 1.5f;

	//���X�ɓ����ɂ���
	m_Effect.col.a -= 0.05f;

	if (m_Effect.fRadius <= 0.0f || m_Effect.col.a <= 0.0f)
	{//�������Ȃ��ď����� or ���S�ɓ����Ȃ�
		//�G�t�F�N�g�̏���
		Uninit();
		CObject2D::Release();
	}
	else
	{
		//�T�C�Y�̐ݒ�
		SetSize(m_Effect.fRadius, m_Effect.fRadius);

		//�F�̐ݒ�
		CObject2D::SetColor(m_Effect.col);
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