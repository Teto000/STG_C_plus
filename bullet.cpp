//===================================
//
// �e�̏���
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
#include "player.h"
#include "explosion.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CBullet::fBulletSpeed = 5.0f;	//�e�̑��x

int CBullet::s_nShotTime;		//�e�̔��ˎ��Ԃ𐔂���
int CBullet::s_nChageTime;		//�e�̃`���[�W����

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

	if (m_aBullet.type == BULLETSTATE_NORMAL)
	{
		CObject2D::SetSize(50.0f, 50.0f);	//�T�C�Y�̐ݒ�
	}
	else if (m_aBullet.type == BULLETSTATE_CHARGE)
	{
		CObject2D::SetSize(80.0f, 80.0f);
	}

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
	m_aBullet.pos = CObject2D::AddMove(m_aBullet.move);

	CObject2D::Update();

	//�����̌���
	m_aBullet.nLife--;

	//�������s����
	if (m_aBullet.nLife <= 0.0f)
	{
		CExplosion::Create(m_aBullet.pos);//�����̐���
		Uninit();
		CObject2D::Release();	//�e�̊J��
	}

	//��ʒ[�̏���
	if (m_aBullet.pos.x >= 1280.0f)
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
				CExplosion::Create(m_aBullet.pos);//�����̐���

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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// �o���b�g�̐����Ə�����
	//----------------------------------
	pBullet = new CBullet;	//����

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		//������
		pBullet->m_aBullet.move = move;		//�ړ��ʂ̑��
		pBullet->m_aBullet.type = type;		//��ނ̑��
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//=======================
// �e�̔���
//=======================
void CBullet::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	rot.x = rot.x - D3DX_PI / 2;	//�E��O�ɕύX

	s_nShotTime++;
	s_nShotTime %= nShotTime;	//���ˎ��Ԃ����Z�b�g

	//---------------------------
	// �ʏ�e
	//---------------------------
	if (!CInputKeyboard::Press(DIK_1) && s_nShotTime == 0)
	{//SPACE�L�[��������Ă���� ���� �e�̔��ˎ��Ԃ�0�Ȃ�
		//�v���C���[�̌����ɒe�𔭎˂���
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_NORMAL);
	}

	//---------------------------
	// �`���[�W�V���b�g
	//---------------------------
	if (CInputKeyboard::Press(DIK_1))
	{//1�L�[��������Ă����
		s_nChageTime++;		//�`���[�W���Ԃ����Z

		if (s_nChageTime >= 40)
		{//�`���[�W���Ԃ�10�ȏ�Ȃ�
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//�v���C���[�̐F��ύX
		}
	}

	if (CInputKeyboard::Release(DIK_1) && s_nChageTime >= 40)
	{//1�L�[�𗣂����Ƃ� ���� �`���[�W��ԂȂ�
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_CHARGE);

		s_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
		s_nShotTime = 0;	//�ʏ�e�̂̔��ˎ��ԃ��Z�b�g
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�v���C���[�̐F��ύX
	}
	else if (CInputKeyboard::Release(DIK_1) && s_nChageTime < 40)
	{
		s_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
	}
}