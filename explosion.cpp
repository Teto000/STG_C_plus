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
	m_nCnterAnim = 0;
	m_nPatternAnim = 0;
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
	CObject2D::Init(pos);

	CObject2D::SetSize(80.0f, 80.0f);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexCIE(0.0f, 1.0f / TEX_DIVISION);	//�e�N�X�`�����W�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_EXPLOSION);	//�e�N�X�`���̐ݒ�

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

	float fPart = (1.0f / TEX_DIVISION);

	m_nCnterAnim++;

	if ((m_nCnterAnim % TEX_DIVISION) == 0)
	{
		m_nPatternAnim++;

		CObject2D::SetTexCIE((fPart *m_nPatternAnim), (fPart * (m_nPatternAnim + 1)));

		if (m_nPatternAnim >= TEX_DIVISION)
		{//�p�^�[�����ő吔�ɒB������
			m_nCnterAnim = 0;
			m_nPatternAnim = 0;
			CObject2D::Uninit();
			CObject2D::Release();	//���
		}
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