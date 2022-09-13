//===================================
//
// �G�l�~�[�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
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
#include "hpfream.h"
#include "item.h"

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
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_fTargetRot = 0.0f;		//�v���C���[�܂ł̊p�x
	m_type = ENEMYTYPE_MAX;		//���
	m_Hp = nullptr;				//HP�o�[
	m_EnemyBullet = nullptr;	//�G�̒e
	m_pExplosion = nullptr;		//����
	m_pBarrier = nullptr;		//�o���A
	m_pHpFream = nullptr;		//HP�t���[��
	m_pItem = nullptr;			//�A�C�e��
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
	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	//�ʒu�̐ݒ�
	m_pos = pos;		//�ʒu
	m_nRemLife = 100;	//�c��̗�
	m_nAttack = 5;

	CObject2D::Init(m_pos);
	CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BIRD);	//�e�N�X�`���̐ݒ�

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_fWidth = 250.0f;	//��
		m_fHeight = 350.0f;	//����
		SetLife(3000);
		break;

	case ENEMYTYPE_BIG:
		m_move.x = -2.0f;	//�ړ���
		m_fWidth = 100.0f;	//��
		m_fHeight = 100.0f;	//����
		SetLife(500);
		CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_DEVIL);
		break;

	case ENEMYTYPE_HORMING:
		m_move.x = -2.0f;	//�ړ���
		m_fWidth = 100.0f;	//��
		m_fHeight = 100.0f;	//����
		SetLife(500);
		break;

	default:
		m_move.x = -4.0f;	//�ړ���
		m_fWidth = 80.0f;	//��
		m_fHeight = 80.0f;	//����
		SetLife(100);
		CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
		break;
	}

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	//--------------------------
	// HP�̕\��
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_Hp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_Hp->SetLife(m_nLife, m_nRemLife);
		m_Hp->SetMove(m_move);

		//�t���[���̐���
		//m_pHpFream = CHpFream::Create(hpPos, m_fWidth, 15.0f);
		//m_pHpFream->SetMove(m_move);
	}

	//--------------------------
	// �o���A�̐���
	//--------------------------
	{
		int nData = rand() % 5;

		if (m_type != ENEMYTYPE_BOSS && nData == 1)
		{//�{�X�ȊO�̓G ���� �����_���Ȓl��1�̎�
			//�o���A�̐���
			m_pBarrier->Create(m_pos, m_move, m_fWidth, m_fHeight, CBarrier::BARRIERTYPE_ENEMY);
		}
	}

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
	if (m_type == ENEMYTYPE_NORMAL || m_type == ENEMYTYPE_BIG)
	{
		//�e�N�X�`��
		m_nCntTime++;
		m_nCntTime %= nMaxTexTime;	//���Z�b�g

		if (m_nCntTime >= nHalfTexTime)
		{
			CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
		}
		else
		{
			CObject2D::SetTexCIE(0.5f, 1.0f);
		}
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
	EnemyAttackCount(vec);

	//--------------------------
	// �̗͂��s����
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);				//�o���l�̎擾
		CScore::AddScore(10);			//�X�R�A�̉��Z
		m_pExplosion->Create(m_pos);	//�����̐���

		//-----------------------
		// �A�C�e���̐���
		//-----------------------
		//m_pItem = CItem::Create(m_pos,CItem::ITEMTYPE_HPHEAL);

		//�G�̏���
		Uninit();

		//-----------------------
		// �|�ꂽ�̂��{�X�Ȃ�
		//-----------------------
		if (m_type == ENEMYTYPE_BOSS)
		{
			//���U���g��ʂɈڍs
			CApplication::SetMode(CApplication::MODE_RESULT);
		}
		return;
	}
	//--------------------------
	// ��ʊO�ɏo��
	//--------------------------
	else if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
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
		//�����o�ϐ��ɑ��
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

//===============================
// �G�̍U���^�C�~���O�𐔂���
//===============================
void CEnemy::EnemyAttackCount(D3DXVECTOR2 vec)
{
	m_nCntShotTime++;

	switch (m_type)
	{
	case ENEMYTYPE_BOSS:
		m_nCntShotTime %= nShotTime * 2;
		break;

	case ENEMYTYPE_BIG:
		m_nCntShotTime %= nShotTime * 2;
		break;

	case ENEMYTYPE_HORMING:
		m_nCntShotTime %= nShotTime;
		break;

	default:
		m_nCntShotTime %= nShotTime;
		break;
	}

	//----------------------------
	// �J�E���g��0�ɂȂ�����
	//----------------------------
	if (m_nCntShotTime == 0)
	{
		EnemyAttack(vec);
	}
}

//===========================
// �G�̍U������
//===========================
void CEnemy::EnemyAttack(D3DXVECTOR2 vec)
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
			m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-vec.x * 4.0f, -vec.y * (i + 1), 0.0f)
				, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_NORMAL);
		}
		break;

	case ENEMYTYPE_HORMING:
		m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f)
			, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_HORMING);
		break;

	default:
		m_EnemyBullet->Create(m_pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f)
			, m_nAttack, CEnemyBullet::ENEMYBULLETTYPE_NORMAL);
		break;
	}
}

//===========================
// �{�X�̍U��
//===========================
void CEnemy::BossAttack()
{
	
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