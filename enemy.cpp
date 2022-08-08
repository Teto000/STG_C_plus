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

//===========================
// �R���X�g���N�^
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	m_nLife = 0;			//�̗�
	m_nMaxLife = 0;			//�ő�̗�
	m_nRemLife = 0;			//�c��̗�
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_type = ENEMYTYPE_MAX;	//���
	m_Hp = nullptr;
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
	m_fWidth = 100.0f;	//��
	m_fHeight = 100.0f;	//����
	m_nLife = 120;		//�̗�
	m_nMaxLife = 120;	//�ő�̗�
	m_nRemLife = 100;	//�c��̗�

	m_move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);

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
	//CBarrier::Create(m_pos, m_move, m_fWidth, m_fHeight);

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

	//�e�N�X�`���J�E���g
	m_CntTime++;
	m_CntTime %= nMaxTexTime;	//���Z�b�g

	//-------------------------------
	// �e�N�X�`�����W�̕ύX
	//-------------------------------
	if (m_CntTime >= nHalfTexTime)
	{
		CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
	}
	else
	{
		CObject2D::SetTexCIE(0.5f, 1.0f);
	}

	//-------------------------------
	// �G�̈ړ�
	//-------------------------------
	switch (m_type)
	{
	case ENEMYTYPE_NORMAL:
		CObject2D::AddMove(m_move);
		break;

	case ENEMYTYPE_CURVE:
		m_move.x = sinf(m_move.x);
		CObject2D::AddMove(m_move);
		break;

	default:
		break;
	}

	//--------------------------
	// �̗͂��s����
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(10);		//�o���l�̎擾
		CScore::AddScore(10);	//�X�R�A�̉��Z

		//�G�̏���
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