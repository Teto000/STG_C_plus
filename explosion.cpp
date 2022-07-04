//===================================
//
// �����̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Explosion, 0, sizeof(m_Explosion));	//�\���̂̃N���A
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
	m_Explosion.nLife = 100;
	m_Explosion.pos = pos;
	m_Explosion.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Explosion.fWidth = 80.0f;
	m_Explosion.fHeight = 80.0f;

	CObject2D::Init(m_Explosion.pos);

	CObject2D::SetSize(m_Explosion.fWidth, m_Explosion.fHeight);	//�T�C�Y�̐ݒ�

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
	m_Explosion.fWidth += 3;
	m_Explosion.fHeight += 3;

	CObject2D::SetPosition(m_Explosion.pos);	//�ʒu�̐ݒ�
	CObject2D::SetSize(m_Explosion.fWidth, m_Explosion.fHeight);	//�T�C�Y�̐ݒ�
	CObject2D::SetVtxCIE(m_Explosion.pos, m_Explosion.fWidth, m_Explosion.fHeight);	//���_���W�̐ݒ�

	//--------------------
	// ���X�ɓ���
	//--------------------
	m_Explosion.col.a -= 0.05f;
	SetColor(m_Explosion.col);
	
	//--------------------
	// ����
	//--------------------
	//�����̌���
	m_Explosion.nLife--;

	//�������s����
	if (m_Explosion.nLife <= 0)
	{
		CObject2D::Uninit();
		CObject2D::Release();	//���
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