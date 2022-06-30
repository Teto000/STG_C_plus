//===================================
//
// HP�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
#include "hp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "player.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------

//===========================
// �R���X�g���N�^
//===========================
CHp::CHp() : CObject2D()
{
	memset(&m_aHP, 0, sizeof(m_aHP));	//�\���̂̃N���A
}

//===========================
// �f�X�g���N�^
//===========================
CHp::~CHp()
{

}

//===========================
// ������
//===========================
HRESULT CHp::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_aHP.pos = pos;

	CObject2D::Init(m_aHP.pos);

	CObject2D::SetSize(80.0f, 100.0f);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//�e�N�X�`���̐ݒ�

	m_aHP.pos = CObject2D::GetPosition();

	return S_OK;
}

//===========================
// �I��
//===========================
void CHp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CHp::Update()
{
	CObject2D::Update();

	//-------------------
	// HP�̌���
	//-------------------
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GETObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		//�I�u�W�F�N�g�̎�ނ̎擾
		CObject::EObjType type = pObject->GetObjType();

		////=============================
		//// �v���C���[�̏���
		////=============================
		//if (type == OBJTYPE_PLAYER)
		//{
		//	//�v���C���[�̎c��̗͂��擾
		//	int PlayerLife = GetRemLife();

		//	//--------------------
		//	// HP��0�ɂȂ�����
		//	//--------------------
		//	if (m_aHP.fLength * pPlayer->nRemLife <= 0)
		//	{
		//		Uninit();
		//		CObject2D::Release();
		//	}

		//	//---------------------------
		//	// ���_���W�̈ړ�
		//	//---------------------------
		//	pVtx[0].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2, -hp->fHeight / 2, 0.0f);
		//	pVtx[1].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2 + (hp->fLength * pPlayer->nRemLife), -hp->fHeight / 2, 0.0f);
		//	pVtx[2].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2, hp->fHeight / 2, 0.0f);
		//	pVtx[3].pos = hp->pos + D3DXVECTOR3(-hp->fWidth / 2 + (hp->fLength * pPlayer->nRemLife), hp->fHeight / 2, 0.0f);
		//}
	}
}

//===========================
// �`��
//===========================
void CHp::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CHp *CHp::Create()
{
	CHp *pHP = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pHP = new CHp;	//����

	if (pHP != nullptr)
	{//NULL�`�F�b�N
	 //������
		pHP->Init(D3DXVECTOR3(400.0f, SCREEN_HEIGHT / 2, 0.0f));
		pHP->SetObjType(OBJTYPE_HP);
	}

	return pHP;
}