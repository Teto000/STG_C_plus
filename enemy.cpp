//===================================
//
// �G�l�~�[�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
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

//===========================
// �R���X�g���N�^
//===========================
CEnemy::CEnemy() : CObject2D()
{
	memset(&m_Enemy, 0, sizeof(Enemy));	//�\���̂̃N���A
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
	m_Enemy.pos = pos;			//�ʒu
	m_Enemy.fWidth = 100.0f;	//��
	m_Enemy.fHeight = 100.0f;	//����
	m_Enemy.nLife = 120;		//�̗�
	m_Enemy.nMaxLife = 120;		//�ő�̗�
	m_Enemy.nRemLife = 100;		//�c��̗�

	CObject2D::Init(m_Enemy.pos);

	CObject2D::SetSize(m_Enemy.fWidth, m_Enemy.fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBIRD);	//�e�N�X�`���̐ݒ�

	//--------------------------
	// HP�̕\��
	//--------------------------
	//CHp::Create(D3DXVECTOR3(m_Enemy.pos.x, m_Enemy.pos.y - (m_Enemy.fHeight / 2 + 20.0f), m_Enemy.pos.z)
	//			, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Enemy.fWidth, 10.0f, CHp::HPTYPE_ENEMY);

	//--------------------------
	// �o���A�̐���
	//--------------------------
	//CBarrier::Create(m_Enemy.pos, m_Enemy.move, m_Enemy.fWidth, m_Enemy.fHeight);

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

	//--------------------------
	// �̗͂̌���
	//--------------------------
	if (CInputKeyboard::Press(DIK_LEFT))
	{
		SubLife(1);
	}

	//--------------------------
	// �I�������𖞂�������
	//--------------------------
	if (!IsUsed())
	{
		//��������
		Destroy();
	}
	else
	{
		//�c��̗͂��v�Z
		m_Enemy.nRemLife = m_Enemy.nLife * 100 / m_Enemy.nMaxLife;
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// �G�̐����Ə�����
	//----------------------------------
	pEnemy = new CEnemy;	//����

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
		//������
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//===========================
// �I����������
//===========================
bool CEnemy::IsUsed()
{
	if (m_Enemy.nLife <= 0)
	{
		return false;
	}

	return true;
}

//===========================
// ��������
//===========================
void CEnemy::Destroy()
{
	CLevel::AddExp(10);		//�o���l�̎擾

	//�G�̏���
	Uninit();
	CObject2D::Release();
}

//===========================
// �̗͂̌���
//===========================
void CEnemy::SubLife(int nLife)
{
	m_Enemy.nLife -= nLife;
}

//===========================
// �̗͂̎擾
//===========================
int CEnemy::GetLife()
{
	return m_Enemy.nLife;
}

//===========================
// �c��̗͂̎擾
//===========================
int CEnemy::GetRemLife()
{
	return m_Enemy.nRemLife;
}