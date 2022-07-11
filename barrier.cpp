//===================================
//
// �G�l�~�[�̏���
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
	m_Barrier.pos = pos;			//�ʒu
	m_Barrier.nLife = 120;		//�̗�
	m_Barrier.fWidth = 100.0f;	//��
	m_Barrier.fHeight = 100.0f;	//����

	CObject2D::Init(m_Barrier.pos);

	CObject2D::SetSize(m_Barrier.fWidth, m_Barrier.fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//�e�N�X�`���̐ݒ�

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
	CBarrier *pEnemy = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------zz
	pEnemy = new CBarrier;	//����

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
	 //������
		pEnemy->Init(D3DXVECTOR3(800.0f, SCREEN_HEIGHT / 2, 0.0f));
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}