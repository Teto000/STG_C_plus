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
	m_nLife = 0;			//�̗�
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_type = ITEMTYPE_MAX;	//���
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
	m_nLife = 150;		//����
	m_fWidth = 50.0f;	//��
	m_fHeight = 50.0f;	//����

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
	// �����̌�������
	//-------------------------------
	//�����̌���
	m_nLife--;

	if (m_nLife <= 0)
	{//�������s������
		Uninit();
		return;
	}

	//-------------------------------
	// �v���C���[�Ƃ̓����蔻��
	//-------------------------------
	if (CObject2D::GetCollision(OBJTYPE_PLAYER))
	{
		switch (m_type)
		{
		case ITEMTYPE_HPHEAL:
			//�v���C���[��MP����
			CGame::GetPlayer()->AddLife(30);
			Uninit();
			return;
			break;

		case ITEMTYPE_MPHEAL:
			//�v���C���[��MP����
			CGame::GetPlayer()->AddMagic(30);
			Uninit();
			return;
			break;

		default:
			break;
		}
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
CItem *CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pItem = new CItem;	//����

	if (pItem != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pItem->m_type = type;

		//������
		pItem->Init(pos);
		pItem->SetObjType(OBJTYPE_ITEM);
	}

	return pItem;
}