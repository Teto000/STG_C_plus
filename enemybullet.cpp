//===================================
//
// �e�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "enemybullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "application.h"
#include "damage.h"
#include "enemy.h"
#include "player.h"
#include "game.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CEnemyBullet::fBulletSpeed_Homing = 1.01f;	//�e�̑��x(�z�[�~���O)

//===========================
// �R���X�g���N�^
//===========================
CEnemyBullet::CEnemyBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ڕW
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]
	m_nEnemyAttack = 0;			//�G�̍U����
	m_nLife = 0;				//����
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_type = ENEMYBULLETTYPE_NORMAL;
}

//===========================
// �f�X�g���N�^
//===========================
CEnemyBullet::~CEnemyBullet()
{

}

//===========================
// ������
//===========================
HRESULT CEnemyBullet::Init(D3DXVECTOR3 pos)
{
	//----------------------------
	// �����o�ϐ��̏�����
	//----------------------------
	m_pos = pos;
	m_fWidth = 50.0f;
	m_fHeight = 50.0f;
	m_nLife = 300;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);			//�T�C�Y�̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CEnemyBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CEnemyBullet::Update()
{
	CObject2D::Update();

	m_nLife--;

	//----------------------
	// �z�[�~���O�e�Ȃ�
	//----------------------
	switch (m_type)
	{
	case ENEMYBULLETTYPE_HORMING:
		m_Tirget = CObject2D::GetTargetPos();	//�G�̈ʒu�̎擾

		if (m_Tirget.x == 0.0f, m_Tirget.y == 0.0f)
		{//�^�[�Q�b�g����������
			//���Ɍ������Ĕ��
			m_Tirget = D3DXVECTOR3(1280.0f, m_pos.y, 0.0f);
		}

		if (m_nLife >= 260)
		{
			//�G�Ɍ������ăz�[�~���O
			m_move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
			m_pos = CObject2D::AddMove(m_move);
		}
		else
		{
			m_pos = CObject2D::AddMove(m_move);
		}
		break;

	default:
		//�ړ��ʂ̉��Z
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//��ʊO�ɏo����
	if (CObject2D::OutScreen(m_pos))
	{
		Uninit();
		return;
	}

	if (CGame::GetPlayer()->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
	{//�v���C���[�����G��Ԃ���Ȃ��Ȃ�
		//������������
		CollisionEnemyBullet();
	}
}

//===========================
// �`��
//===========================
void CEnemyBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move
									, int nAttack, CEnemyBullet::ENEMYBULLETTYPE type)
{
	CEnemyBullet *pBullet = nullptr;

	//----------------------------------
	// �o���b�g�̐����Ə�����
	//----------------------------------
	pBullet = new CEnemyBullet;	//����

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		pBullet->m_move = move;				//�ړ��ʂ̑��
		pBullet->m_nEnemyAttack = nAttack;	//�U���͂̑��
		pBullet->m_type = type;				//���

		//������
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//===========================
// ������������
//===========================
void CEnemyBullet::CollisionEnemyBullet()
{
	CObject* pHitObject = CObject2D::GetCollision(OBJTYPE_PLAYER);

	if (pHitObject != nullptr)
	{//�v���C���[�Ɠ�������

		//pObject��CPlayer�^�Ƀ_�E���L���X�g
		CPlayer* pPlayer = (CPlayer*)pHitObject;

		pPlayer->SubLife(m_nEnemyAttack);	//�G�̗̑͂̌���

		//�e�̏���
		Uninit();
		return;
	}
}

//=======================
// �z�[�~���O�e
//=======================
D3DXVECTOR3 CEnemyBullet::Homing(float& posX, float& posY, float& moveX, float& moveY)
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