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

//===========================
// �R���X�g���N�^
//===========================
CEnemyBullet::CEnemyBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]
	m_nLife = 0;				//����
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
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
	m_nLife = 50;
	m_fWidth = 50.0f;
	m_fHeight = 50.0f;

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

	//�ړ��ʂ̉��Z
	m_pos = CObject2D::AddMove(m_move);

	if (CGame::GetPlayer()->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
	{//�v���C���[�����G��Ԃ���Ȃ��Ȃ�
		//������������
		CollisionEnemyBullet();
	}


	//�����̌���
	//m_nLife--;

	////�������s����
	//if (m_nLife <= 0.0f)
	//{
	//	Uninit();
	//	return;
	//}
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
CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nAttack)
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