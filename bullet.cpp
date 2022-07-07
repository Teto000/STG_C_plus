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
#include "score.h"
#include "effect.h"
#include "enemy.h"

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
	memset(&m_Bullet, 0, sizeof(m_Bullet));	//�\���̂̃N���A
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_Bullet.pos = pos;
	m_Bullet.nLife = 100;
	m_Bullet.fWidth = 50.0f;
	m_Bullet.fHeight = 50.0f;

	CObject2D::Init(m_Bullet.pos);

	if (m_Bullet.type == BULLETSTATE_NORMAL)
	{
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//�T�C�Y�̐ݒ�
	}
	else if (m_Bullet.type == BULLETSTATE_CHARGE)
	{
		CObject2D::SetSize(m_Bullet.fWidth * 1.5f, m_Bullet.fHeight * 1.5f);
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
	CObject2D::Update();

	if (m_Bullet.type == BULLETSTATE_HORMING)
	{
		D3DXVECTOR3 move = Homing(m_Bullet.pos.x, m_Bullet.pos.y, m_Bullet.move.x, m_Bullet.move.y);
		m_Bullet.pos = CObject2D::AddMove(move);
	}
	else
	{
		//�ړ��ʂ̉��Z
		m_Bullet.pos = CObject2D::AddMove(m_Bullet.move);
	}

	//�G�t�F�N�g�̐���
	CEffect::Create(m_Bullet.pos);

	//�����̌���
	m_Bullet.nLife--;

	//�������s����
	if (m_Bullet.nLife <= 0.0f)
	{
		CExplosion::Create(m_Bullet.pos);//�����̐���
		Uninit();
		CObject2D::Release();	//�e�̊J��
	}
	//�ڕW�n�_�ɒe���������甚��
	//else if (m_Bullet.pos.x <= m_tirget.x + 5.0f && m_Bullet.pos.x >= m_tirget.x - 5.0f
	//	&& m_Bullet.pos.y <= m_tirget.y + 5.0f && m_Bullet.pos.y >= m_tirget.y - 5.0f)
	//{
	//	CExplosion::Create(m_Bullet.pos);//�����̐���
	//	Uninit();
	//	CObject2D::Release();	//�e�̊J��
	//}

	//��ʒ[�̏���
	if (m_Bullet.pos.x >= 1280.0f)
	{
		Uninit();
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

			m_Tirget = EnemyPos;

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
				CExplosion::Create(m_Bullet.pos);//�����̐���
				CScore::AddScore(50);

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
		pBullet->m_Bullet.move = move;		//�ړ��ʂ̑��
		pBullet->m_Bullet.type = type;		//��ނ̑��
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
		//Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_NORMAL);
		Create(pos, D3DXVECTOR3(0.0f,0.0f,0.0f), BULLETSTATE_HORMING);
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

//=======================
// �z�[�~���O�e
//=======================
D3DXVECTOR3 CBullet::Homing(float& posX, float& posY, float& moveX, float& moveY)
{
	//�e�̌��̑��x
	float vx0 = moveX, vy0 = moveY;

	//���@�����̑��x�x�N�g��(vx1,vy1)�����߂�
	float vx1, vy1;

	//�ڕW�܂ł̋���d�����߂�
	float d = sqrtf((m_Tirget.x - posX) * (m_Tirget.x - posX)
		+ (m_Tirget.y - posY) * (m_Tirget.y - posY));

	if (d)
	{
		vx1 = (m_Tirget.x - posX) / d * fBulletSpeed;
		vy1 = (m_Tirget.y - posY) / d * fBulletSpeed;
	}
	else
	{
		vx1 = 0;
		vy1 = fBulletSpeed;
	}

	//�E������p�x����̑��x�x�N�g��(vx2,vy2)�����߂�
	float rad = (D3DX_PI / 180) * 3.0f;
	float vx2 = cosf(rad) * vx0 - sinf(rad) * vy0;
	float vy2 = sinf(rad) * vx0 + cosf(rad) * vy0;

	//���@�����Ɛ���p�x����̂ǂ���ɋȂ��邩�����߂�
	if (vx0 * vx1 + vy0 * vy1 >= vx0 * vx2 + vy0 * vy2)
	{//���@����������\�͈͓��̏ꍇ
	 //���@�����ɋȂ���
		moveX = vx1;
		moveY = vy1;
	}
	else
	{
		//���@����������\�͈͊O�̏ꍇ
		//��������p�x����̑��x�x�N�g��(vx3,vy3)�����߂�
		float vx3 = cosf(rad) * vx0 + sinf(rad) * vy0;
		float vy3 = -sinf(rad) * vx0 + cosf(rad) * vy0;

		//�e���玩�@�ւ̑��Έʒu�x�N�g��(px,py)�����߂�
		float px = m_Tirget.x - posX, py = m_Tirget.y - posY;

		//�E��肩����肩�����߂�
		if (px * vx2 + py * vy2 >= px * vx3 + py * vy3)
		{//�E���̏ꍇ
			moveX = vx2;
			moveY = vy2;
		}
		else
		{//�����̏ꍇ
			moveX = vx3;
			moveY = vy3;
		}
	}

	return D3DXVECTOR3(moveX, moveY, 0.0f);
}