//===================================
//
// �G�l�~�[�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "bullet.h"
#include "texture.h"
#include "hp.h"
#include "barrier.h"
#include "explosion.h"
#include "level.h"
#include "score.h"
#include "enemybullet.h"
#include "game.h"
#include "player.h"

//===========================
// �R���X�g���N�^
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//�ʒu
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_rot = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//��]
	m_nLife = 0;				//�̗�
	m_nMaxLife = 0;				//�ő�̗�
	m_nRemLife = 0;				//�c��̗�
	m_nAttack = 0;				//�U����
	m_nCntAttack = 0;			//�U���^�C�~���O
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_fTargetRot = 0.0f;		//�v���C���[�܂ł̊p�x
	m_type = ENEMYTYPE_MAX;		//���
	m_Hp = nullptr;				//HP�o�[
	m_EnemyBullet = nullptr;	//�G�̒e
	m_pExplosion = nullptr;		//����
	m_pBarrier = nullptr;		//�o���A
}

//===========================
// �f�X�g���N�^
//===========================
CEnemy::~CEnemy()
{

}

//===========================
// ������
//===========================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_pos = pos;		//�ʒu
	m_nRemLife = 100;	//�c��̗�
	m_nAttack = 5;

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_fWidth = 250.0f;	//��
		m_fHeight = 350.0f;	//����
		SetLife(3000);
		break;

	case ENEMYTYPE_BIG:
		m_move.x = -2.0f;	//�ړ���
		m_fWidth = 170.0f;	//��
		m_fHeight = 170.0f;	//����
		SetLife(500);
		break;

	default:
		m_move.x = -3.0f;	//�ړ���
		m_fWidth = 100.0f;	//��
		m_fHeight = 100.0f;	//����
		SetLife(100);
		break;
	}

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//�e�N�X�`���̐ݒ�

	//--------------------------
	// HP�̕\��
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_Hp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_Hp->SetLife(m_nLife, m_nRemLife);
		m_Hp->SetMove(m_move);
	}

	//--------------------------
	// �o���A�̐���
	//--------------------------
	//m_pBarrier->Create(m_pos, m_move, m_fWidth, m_fHeight);

	return S_OK;
}

//===========================
// �I��
//===========================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CEnemy::Update()
{
	CObject2D::Update();

	//-------------------------------
	// �J�E���g
	//-------------------------------
	//�e�N�X�`��
	m_nCntTime++;
	m_nCntTime %= nMaxTexTime;	//���Z�b�g

	//�U���^�C�~���O
	m_nCntAttack++;
	m_nCntAttack %= 30;

	//-------------------------------
	// �v���C���[�̈ʒu��ۑ�
	//-------------------------------
	if (CGame::GetPlayer()->GetLife() > 0)
	{//�v���C���[�������Ă���Ȃ�
		m_targetPos = CGame::GetPlayer()->GetPosition();
	}

	//�v���C���[�܂ł̊p�x
	D3DXVECTOR2 vec = m_pos - m_targetPos;
	D3DXVec2Normalize(&vec, &vec);

	//-------------------------------
	// �e�N�X�`�����W�̕ύX
	//-------------------------------
	if (m_nCntTime >= nHalfTexTime)
	{
		CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
	}
	else
	{
		CObject2D::SetTexCIE(0.5f, 1.0f);
	}

	//-------------------------------
	// �v���C���[�Ɍ������ĉ�]
	//-------------------------------
	/*if (m_targetPos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXVECTOR2 vec = m_pos - m_targetPos;

		m_fTargetRot = -atan2f(vec.y, vec.x);

		if (m_rot.x != m_fTargetRot)
		{
			m_rot.x += 0.1f;
		}

		//�p�x�̐��K��
		if (m_rot.x >= D3DX_PI)
		{
			m_rot.x -= D3DX_PI;
		}
		else if (m_rot.x <= -D3DX_PI)
		{
			m_rot.x += D3DX_PI;
		}

		CObject2D::SetVtxCIE_Rot(m_pos, m_rot, m_fWidth, m_fHeight);
	}*/

	//-------------------------------
	// �G�̈ړ�
	//-------------------------------
	m_pos = CObject2D::AddMove(m_move);

	//--------------------------
	// �G�̍U��
	//--------------------------
	m_nCntShotTime++;
	m_nCntShotTime %= nShotTime;	//���ˎ��Ԃ����Z�b�g

	if (m_nCntShotTime == 0)
	{
		switch (m_type)
		{
		//----------------------
		// �{�X�̍U��
		//----------------------
		case ENEMYTYPE_BOSS:
			BossAttack();
			break;

		case ENEMYTYPE_BIG:
			for (int i = 0; i < 5; i++)
			{
				m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-vec.x * 4.0f, -vec.y * (i + 1), 0.0f), m_nAttack);
			}
			break;

		case ENEMYTYPE_HORMING:

			break;

		default:
			m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-8.0f, 0.0f, 0.0f), m_nAttack);
			break;
		}
	}

	//--------------------------
	// �̗͂��s����
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);				//�o���l�̎擾
		CScore::AddScore(10);			//�X�R�A�̉��Z
		m_pExplosion->Create(m_pos);	//�����̐���

		//�G�̏���
		Uninit();
		return;
	}
	//--------------------------
	// ��ʊO�ɏo��
	//--------------------------
	else if (CObject2D::OutScreen(m_pos))
	{
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// �G�̐����Ə�����
	//----------------------------------
	pEnemy = new CEnemy;	//����

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
		//�\���̂ɑ��
		pEnemy->m_type = type;

		//������
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//===========================
// �̗͂̐ݒ�
//===========================
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
	m_nMaxLife = nLife;
}

//===========================
// �̗͂̌���
//===========================
void CEnemy::SubLife(int nLife)
{
	m_nLife -= nLife;

	//�c��̗͂��v�Z
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP�������̏���
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// �{�X�̍U��
//===========================
void CEnemy::BossAttack()
{
	if (CInputKeyboard::Trigger(DIK_M))
	{
		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR3 pos(300.0f + (i * 200.0f), 0.0f - (i * 50.0f), 0.0f);
			D3DXVECTOR3 move(-5.0f, 9.0f, 0.0f);
			m_EnemyBullet->Create(pos, move, m_nAttack);
		}
	}
}

//===========================
// �̗͂̎擾
//===========================
int CEnemy::GetLife()
{
	return m_nLife;
}

//===========================
// �c��̗͂̎擾
//===========================
int CEnemy::GetRemLife()
{
	return m_nRemLife;
}

//===========================
// �U���͂̐ݒ�
//===========================
int CEnemy::GetAttack()
{
	return m_nAttack;
}