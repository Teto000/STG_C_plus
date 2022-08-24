//===================================
//
// �e�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "bullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "game.h"
#include "player.h"
#include "explosion.h"
#include "damage.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "barrier.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CBullet::fBulletSpeed = 10.0f;			//�e�̑��x
const float CBullet::fBulletSpeed_Homing = 1.05f;	//�e�̑��x(�z�[�~���O)
const float CBullet::nDefaultSize = 30.0f;			//�e�̊�{�̑傫��

int CBullet::m_nChageTime;	//�e�̃`���[�W����
int CBullet::m_nCntHorming;	

//===========================
// �R���X�g���N�^
//===========================
CBullet::CBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ڕW
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]
	m_nLife = 0;				//����
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_type = BULLETSTATE_MAX;	//���
	pExplosion = nullptr;		//����
	pDamage = nullptr;			//�_���[�W
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
	m_pos = pos;
	m_nLife = nDefaultLife;
	m_fWidth = nDefaultSize;
	m_fHeight = nDefaultSize;

	CObject2D::Init(m_pos);

	//----------------------------
	// ��ޕʂ̏��̐ݒ�
	//----------------------------
	if (m_type == BULLETSTATE_CHARGE)
	{//�`���[�W�V���b�g�Ȃ�
		m_fWidth *= 1.5f;
		m_fHeight *= 1.5f;
	}
	else if (m_type == BULLETSTATE_HORMING)
	{//�z�[�~���O�e�Ȃ�
		m_nLife *= 2;
	}
	else if (m_type == BULLETSTATE_OPTION)
	{
		m_fWidth *= 0.7f;
		m_fHeight *= 0.7f;
	}

	CObject2D::SetSize(m_fWidth, m_fHeight);			//�T�C�Y�̐ݒ�
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

	m_rot.x = 10.0f;

	SetVtxCIE_Rot(m_pos, m_rot, m_fWidth, m_fHeight);

	switch (m_type)
	{
	//----------------------
	// �z�[�~���O�e�Ȃ�
	//----------------------
	case BULLETSTATE_HORMING:
		m_Tirget = CObject2D::GetTargetPos();	//�G�̈ʒu�̎擾

		if (m_Tirget.x == 0.0f, m_Tirget.y == 0.0f)
		{//�^�[�Q�b�g����������
			//���Ɍ������Ĕ��
			m_Tirget = D3DXVECTOR3(1280.0f, m_pos.y, 0.0f);
		}
		
		if (m_nLife <= 150)
		{//�z�[�~���O�e�̎�����150�ȉ��Ȃ�
			//�G�Ɍ������ăz�[�~���O
			D3DXVECTOR3 move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
			m_pos = CObject2D::AddMove(move);
		}
		else
		{
			//�ړ��ʂ̉��Z
			m_pos = CObject2D::AddMove(m_move);
		}
		break;
	default:
		//�ړ��ʂ̉��Z
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//�G�t�F�N�g�̐���
	CEffect::Create(m_pos);

	//�����̌���
	m_nLife--;

	//�������s����
	if (m_nLife <= 0.0f)
	{
		//pExplosion->Create(m_pos);//�����̐���
		Uninit();
		return;
	}
	//��ʒ[�̏���
	else if (m_pos.x >= SCREEN_WIDTH)
	{
		Uninit();
		return;
	}

	//------------------------
	// ������������
	//------------------------
	CollisionBullet();
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
		pBullet->m_move = move;		//�ړ��ʂ̑��
		pBullet->m_type = type;		//��ނ̑��
		pBullet->Init(pos);

		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//=======================
// �e�̔���
//=======================
void CBullet::ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime)
{
	pos.x += 30.0f;	//���ˈʒu�̒���

	//---------------------------
	// ���x�����Ƃ̒e
	//---------------------------
	if (!CInputKeyboard::Press(DIK_SPACE) && nShotTime == 0)
	{//�`���[�W���Ă��Ȃ��� ���� �e�̔��ˎ��Ԃ�0�Ȃ�
		if (nLevel <= 2)
		{//���x��2�ȉ��Ȃ�
			//�E���ɒe�𔭎˂���
			Create(pos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETSTATE_NORMAL);
		}

		if (nLevel == 2)
		{//���x��2�Ȃ�
			D3DXVECTOR3 firstPos(pos.x, pos.y - 20.0f, pos.z);
			D3DXVECTOR3 secondPos(pos.x, pos.y + 20.0f, pos.z);

			//�������e�����E�ɔ��˂���
			Create(firstPos, D3DXVECTOR3(fBulletSpeed, -1.5f, 0.0f), BULLETSTATE_OPTION);
			Create(secondPos, D3DXVECTOR3(fBulletSpeed, 1.5f, 0.0f), BULLETSTATE_OPTION);
		}
		else if (nLevel >= 3)
		{//���x��3�Ȃ�
			D3DXVECTOR3 firstPos(pos.x, pos.y - 40.0f, pos.z);
			D3DXVECTOR3 secondPos(pos.x, pos.y + 40.0f, pos.z);

			//�e��2���ɑ��₷
			Create(firstPos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETSTATE_NORMAL);
			Create(secondPos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETSTATE_NORMAL);
		}

		if (nLevel >= 4 && m_nCntHorming >= 3)
		{//���x��4�Ȃ�
			D3DXVECTOR3 Pos(pos.x - 40.0f, pos.y - 40.0f, pos.z);
			Create(Pos, D3DXVECTOR3(-2.0f , -2.0f, 0.0f), BULLETSTATE_HORMING);
			m_nCntHorming = 0;
		}

		m_nCntHorming++;
	}

	//---------------------------
	// �`���[�W�V���b�g
	//---------------------------
	if (CInputKeyboard::Press(DIK_SPACE))
	{//SPACE�L�[��������Ă����
		m_nChageTime++;		//�`���[�W���Ԃ����Z

		if (m_nChageTime >= 40)
		{//�`���[�W���Ԃ�10�ȏ�Ȃ�
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//�v���C���[�̐F��ύX
		}
	}

	if (CInputKeyboard::Release(DIK_SPACE) && m_nChageTime >= 40)
	{//SPACE�L�[�𗣂����Ƃ� ���� �`���[�W��ԂȂ�
		//Create(pos, D3DXVECTOR3(-sinf(rot.x) * fBulletSpeed, -cosf(rot.x) * fBulletSpeed, 0.0f), BULLETSTATE_CHARGE);
		
		for (int i = 0; i < nMaxHoming; i++)
		{
			Create(pos, D3DXVECTOR3(-5.0f, (float)(nMaxHoming - (i * nMaxHoming)), 0.0f), BULLETSTATE_CHARGE);
		}

		m_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�v���C���[�̐F��ύX
	}
	else if (CInputKeyboard::Release(DIK_SPACE) && m_nChageTime < 40)
	{
		m_nChageTime = 0;	//�`���[�W���Ԃ����Z�b�g
	}
}

//=======================
// �����������̏���
//=======================
void CBullet::CollisionBullet()
{
	CObject* pHitObject = CObject2D::GetCollision(OBJTYPE_ENEMY);
	int PlayerAttack = CGame::GetPlayer()->GetAttack();

	if (pHitObject != nullptr)
	{//�G�Ɠ�������

		//pObject��CEnemy�^�Ƀ_�E���L���X�g
		CEnemy* pEnemy = (CEnemy*)pHitObject;

		if (m_type == BULLETSTATE_CHARGE)
		{//�`���[�W�V���b�g�Ȃ�
		 //�_���[�W�㏸
			pEnemy->SubLife(PlayerAttack * 3);	//�G�̗̑͂̌���
		}
		else
		{//����ȊO�Ȃ�
			pEnemy->SubLife(PlayerAttack);	//�G�̗̑͂̌���
		}

		pDamage->Create(m_pos, 20.0f, 30.0f, 20.0f, 2, PlayerAttack);	//�_���[�W�̕\��

		//�e�̏���
		Uninit();
		return;
	}
	else if (CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//�o���A�Ɠ�������
	 //�e�̏���
		Uninit();
		return;
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