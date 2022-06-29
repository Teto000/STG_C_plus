//===================================
//
// �o���b�g�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
#include "bullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CBullet::fBulletSpeed = 5.0f;	//�e�̑��x

//===========================
// �R���X�g���N�^
//===========================
CBullet::CBullet() : CObject2D()
{
	memset(&m_aBullet, 0, sizeof(m_aBullet));	//�\���̂̃N���A
}

//===========================
// �f�X�g���N�^
//===========================
CBullet::~CBullet()
{

}

//===========================
// ������
//===========================
HRESULT CBullet::Init(D3DXVECTOR3 pos)
{
	//�����o�ϐ��̏�����
	m_aBullet.move = D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f);
	m_aBullet.nLife = 100;

	CObject2D::Init(pos);

	CObject2D::SetSize(50.0f, 50.0f);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CBullet::Update()
{
	//�ړ��ʂ̉��Z
	CObject2D::AddMove(m_aBullet.move);

	CObject2D::Update();

	D3DXVECTOR3 pos = CObject2D::GetPosition();

	//�����̌���
	m_aBullet.nLife--;

	//�������s����
	if (m_aBullet.nLife <= 0.0f)
	{
		CObject2D::Release();	//�e�̊J��
		//CExplosion::Create(pos);//�����̐���
	}

	//��ʒ[�̏���
	if (pos.x >= 1280.0f)
	{
		CObject2D::Release();
	}

	//------------------------
	// �G�Ƃ̓����蔻��
	//------------------------
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

		//------------------
		// �e�̏����擾
		//------------------
		D3DXVECTOR3 BulletPos = CObject2D::GetPosition();	//�ʒu
		float BulletWidth = CObject2D::GetWidth();			//��
		float BulletHeight = CObject2D::GetHeight();		//����

		if (type == OBJTYPE_ENEMY)
		{//�I�u�W�F�N�g�̎�ނ��G�Ȃ�
			//------------------
			// �G�̏����擾
			//------------------
			D3DXVECTOR3 EnemyPos = pObject->GetPosition();	//�ʒu
			float EnemyWidth = pObject->GetWidth();			//��
			float EnemyHeight = pObject->GetHeight();		//����

			float fLeft = EnemyPos.x - (EnemyWidth / 2);	//�G�̍���
			float fRight = EnemyPos.x + (EnemyWidth / 2);	//�G�̉E��
			float fTop = EnemyPos.y - (EnemyHeight / 2);	//�G�̏㑤
			float fBottom = EnemyPos.y + (EnemyHeight / 2);	//�G�̉���

			//------------------
			// �����蔻��
			//------------------
			if (BulletPos.x + BulletWidth / 2 >= fLeft && BulletPos.x - BulletWidth / 2 <= fRight
				&& BulletPos.y - BulletHeight / 2 <= fBottom && BulletPos.y + BulletHeight / 2 >= fTop)
			{
				//�e�̏���
				Uninit();
				CObject2D::Release();
			}
		}
	}
}

//===========================
// �`��
//===========================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CBullet *CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// �o���b�g�̐����Ə�����
	//----------------------------------
	pBullet = new CBullet;	//����

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		//������
		pBullet->Init(pos);
		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}