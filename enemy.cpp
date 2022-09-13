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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
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
	m_fChangeMove = 0.0f;		//�ϓ�����ړ���
	m_type = ENEMYTYPE_MAX;		//���
	m_pHp = nullptr;				//HP�o�[
	m_pEnemyBullet = nullptr;	//�G�̒e
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
	//�ʒu�̐ݒ�
	m_pos = pos;		//�ʒu
	m_nRemLife = 100;	//�c��̗�
	m_nAttack = 5;		//�U����

	CObject2D::Init(m_pos);

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BLUE);	//�e�N�X�`���̐ݒ�

	//-------------------------------
	// �G�̎�ނ��Ƃ̏���ݒ�
	//-------------------------------
	/*switch (m_type)
	{
	case 0:
		break;

	default:*/
		m_move.x = -3.0f;	//�ړ���
		m_fWidth = 80.0f;	//��
		m_fHeight = 80.0f;	//����
		SetLife(100);		//�̗�
	//	break;
	//}

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	//--------------------------
	// HP�̕\��
	//--------------------------
	{
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_pHp = CHp::Create(hpPos, m_fWidth, 10.0f);
		m_pHp->SetLife(m_nLife, m_nRemLife);
		m_pHp->SetMove(m_move);
	}

	//--------------------------
	// �o���A�̐���
	//--------------------------
	{
		int nData = rand() % 9;

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
	// �G�̈ړ�
	//-------------------------------
	//�㉺�ړ�
	m_fChangeMove += 0.01f;
	m_move.y = sinf(D3DX_PI * m_fChangeMove);

	m_pos = CObject2D::AddMove(m_move);

	m_pHp->SetMove(m_move);

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
	if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
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
	m_pHp->SetLife(m_nLife, m_nRemLife);
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