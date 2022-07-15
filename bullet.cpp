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
#include "number.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "barrier.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CBullet::fBulletSpeed = 10.0f;	//�e�̑��x
float CBullet::fBulletSpeed_Homing = 1.05f;	//�e�̑��x(�z�[�~���O)

int CBullet::m_nShotTime;		//�e�̔��ˎ��Ԃ𐔂���
int CBullet::m_nChageTime;		//�e�̃`���[�W����

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
	//----------------------------
	// �����o�ϐ��̏�����
	//----------------------------
	m_Bullet.pos = pos;
	m_Bullet.fWidth = 50.0f;
	m_Bullet.fHeight = 50.0f;

	CObject2D::Init(m_Bullet.pos);

	//----------------------------
	// ��ޕʂ̏��̐ݒ�
	//----------------------------
	if (m_Bullet.type == BULLETSTATE_NORMAL)
	{
		m_Bullet.nLife = 100;
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//�T�C�Y�̐ݒ�
	}
	else if (m_Bullet.type == BULLETSTATE_CHARGE)
	{
		m_Bullet.nLife = 100;
		CObject2D::SetSize(m_Bullet.fWidth * 1.5f, m_Bullet.fHeight * 1.5f);
	}
	else if (m_Bullet.type == BULLETSTATE_HORMING)
	{
		m_Bullet.nLife = 200;
		CObject2D::SetSize(m_Bullet.fWidth, m_Bullet.fHeight);	//�T�C�Y�̐ݒ�
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
	{//�z�[�~���O�e�Ȃ�
		m_Tirget = CObject2D::GetTargetPos();	//�G�̈ʒu�̎擾
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
	//��ʒ[�̏���
	else if (m_Bullet.pos.x >= SCREEN_WIDTH)
	{
		Uninit();
		CObject2D::Release();
	}

	//------------------------
	// �����蔻��
	//------------------------
	if (CObject2D::GetCollision(OBJTYPE_ENEMY))
	{//�G�Ɠ�������
		CExplosion::Create(m_Bullet.pos);	//�����̐���

		CScore::AddScore(1);

		//�_���[�W�̕\��
		CNumber::Create(m_Bullet.pos, 20.0f, 30.0f, 20.0f, 2, 87);

		//�e�̏���
		Uninit();
		CObject2D::Release();
	}
	else if (CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//�o���A�Ɠ�������
		//�e�̏���
		Uninit();
		CObject2D::Release();
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

	m_nShotTime++;
	m_nShotTime %= nShotTime;	//���ˎ��Ԃ����Z�b�g

	//---------------------------
	// �ʏ�e
	//---------------------------
	if (!CInputKeyboard::Press(DIK_1) && m_nShotTime == 0)
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
		m_nChageTime++;		//�`���[�W���Ԃ����Z

		if (m_nChageTime >= 40)
		{//�`���[�W���Ԃ�10�ȏ�Ȃ�
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//�v���C���[�̐F��ύX
		}
	}

	if (CInputKeyboard::Release(DIK_1) && m_nChageTime >= 40)
	{//1�L�[�𗣂����Ƃ� ���� �`���[�W��ԂȂ�
		Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_CHARGE);

		m_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
		m_nShotTime = 0;	//�ʏ�e�̂̔��ˎ��ԃ��Z�b�g
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�v���C���[�̐F��ύX
	}
	else if (CInputKeyboard::Release(DIK_1) && m_nChageTime < 40)
	{
		m_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
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
		vx1 = (m_Tirget.x - posX) / d * fBulletSpeed_Homing;
		vy1 = (m_Tirget.y - posY) / d * fBulletSpeed_Homing;
	}
	else
	{
		vx1 = 0;
		vy1 = fBulletSpeed_Homing;
	}

	//�E������p�x����̑��x�x�N�g��(vx2,vy2)�����߂�
	float rad = (D3DX_PI / 180) * 5.0f; //����p�x���
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

	moveX *= fBulletSpeed_Homing;
	moveY *= fBulletSpeed_Homing;

	return D3DXVECTOR3(moveX, moveY, 0.0f);
}