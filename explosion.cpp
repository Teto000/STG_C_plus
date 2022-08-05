//===================================
//
// �����̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "explosion.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//------------------------
// �}�N����`
//------------------------
#define TEX_DIVISION	(8)	//�e�N�X�`���̕�����

//------------------------
//�ÓI�����o�ϐ�
//------------------------


//===========================
// �R���X�g���N�^
//===========================
CExplosion::CExplosion() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	m_nLife = 0;		//����
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//===========================
// �f�X�g���N�^
//===========================
CExplosion::~CExplosion()
{

}

//===========================
// ������
//===========================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	//------------------
	// �\���̂̏�����
	//------------------
	m_nLife = 100;
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth = 80.0f;
	m_fHeight = 80.0f;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_RING);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CExplosion::Update()
{
	CObject2D::Update();

	//--------------------
	// �g��
	//--------------------
	m_fWidth += 3;
	m_fHeight += 3;

	CObject2D::SetPosition(m_pos);	//�ʒu�̐ݒ�
	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	//--------------------
	// ���X�ɓ���
	//--------------------
	m_col.a -= 0.05f;
	SetColor(m_col);
	
	//--------------------
	// ����
	//--------------------
	//�����̌���
	m_nLife--;

	//�������s����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = nullptr;

	//----------------------------------
	// �G�N�X�v���[�W�����̐����Ə�����
	//----------------------------------
	pExplosion = new CExplosion;	//����

	if (pExplosion != nullptr)
	{//NULL�`�F�b�N
		//������
		pExplosion->Init(pos);
		pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	}

	return pExplosion;
}