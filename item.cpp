//===================================
//
// �A�C�e���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "item.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//===========================
// �R���X�g���N�^
//===========================
CItem::CItem() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	m_nLife = 0;		//�̗�
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//===========================
// �f�X�g���N�^
//===========================
CItem::~CItem()
{

}

//===========================
// ������
//===========================
HRESULT CItem::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;		//�ʒu
	m_nLife = 50;		//����
	m_fWidth = 30.0f;	//��
	m_fHeight = 30.0f;	//����

	CObject2D::Init(m_pos);

	//------------------
	// �ݒ�
	//------------------
	CObject2D::SetSize(m_fWidth, m_fHeight);			//�傫��
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//�e�N�X�`��

	return S_OK;
}

//===========================
// �I��
//===========================
void CItem::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CItem::Update()
{
	CObject2D::Update();

	//-------------------------------
	// �v���C���[�Ƃ̓����蔻��
	//-------------------------------
	if (CObject2D::GetCollision(OBJTYPE_PLAYER))
	{
		//�v���C���[��MP����
		CGame::GetPlayer()->AddMagic(30);
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CItem::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CItem *CItem::Create(D3DXVECTOR3 pos)
{
	CItem *pItem = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pItem = new CItem;	//����

	if (pItem != nullptr)
	{//NULL�`�F�b�N
		//������
		pItem->Init(pos);
		pItem->SetObjType(OBJTYPE_ITEM);
	}

	return pItem;
}