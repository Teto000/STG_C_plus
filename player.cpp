//===================================
//
// �v���C���[�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "player.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"
#include "skill.h"
#include "level.h"
#include "hpfream.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CPlayer::fPlayerSpeed = (30.0f / 5.0f);
D3DXCOLOR CPlayer::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

//===========================
// �R���X�g���N�^
//===========================
CPlayer::CPlayer() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_nLife = 0;				//�̗�
	m_nMaxLife = 0;				//�ő�̗�
	m_nRemLife = 0;				//�c��̗�
	m_nAttack = 0;				//�U����
	m_nShotTime = 0;			//�e�̔��ˎ���
	m_nCntShotTime = 0;			//�e�̔��ˎ��Ԃ𐔂���
	m_nCntInvincible = 0;		//���G���Ԃ𐔂���
	m_nSpeed = 0.0f;			//���x
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_type = PLAYERSTATE_NORMAL;//���
	m_Hp = nullptr;				//HP�N���X
	m_Level = nullptr;			//���x���N���X
	m_Bullet = nullptr;			//�e�N���X
	m_pHpFream = nullptr;		//HP�t���[���N���X
}

//===========================
// �f�X�g���N�^
//===========================
CPlayer::~CPlayer()
{

}

//===========================
// ������
//===========================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	//�ʒu�̐ݒ�
	m_pos = pos;
	m_nLife = nPlayerLife;		//�̗�
	m_nMaxLife = nPlayerLife;	//�ő�̗�
	m_nRemLife = nMaxLife;		//�c��̗�
	m_fWidth = 80.0f;			//��
	m_fHeight = 100.0f;			//����
	m_nAttack = 40;				//�U����
	m_nShotTime = 20;			//�e�̔��ˎ���
	m_nSpeed = fPlayerSpeed;	//���x

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//�e�N�X�`���̐ݒ�

	m_pos = CObject2D::GetPosition();

	//--------------------------
	// HP�̕\��
	//--------------------------
	m_Hp = CHp::Create(D3DXVECTOR3(520.0f, 80.0f, 0.0f), 600.0f, 80.0f);
	m_Hp->SetLife(m_nLife, m_nRemLife);	//����HP�̐ݒ�

	//--------------------------
	// ���x���̐���
	//--------------------------
	m_Level = CLevel::Create();

	//--------------------------
	// �t���[���̐���
	//--------------------------
	m_pHpFream = CHpFream::Create(D3DXVECTOR3(520.0f, 80.0f, 0.0f), 600.0f, 80.0f);

	return S_OK;
}

//===========================
// �I��
//===========================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CPlayer::Update()
{
	CObject2D::Update();

	//--------------------
	// �v���C���[�̑���
	//--------------------
	D3DXVECTOR3 move = OperationPlayer();

	//--------------------
	// �ړ��ʂ��X�V(����)
	//--------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//--------------------
	// �ʒu�Ɉړ��ʂ����Z
	//--------------------
	m_pos = CObject2D::AddMove(m_move);

	//--------------------
	// ��ʒ[�̐ݒ�
	//--------------------
	CObject2D::SetScreenX(m_pos.x, 0.0f + m_fWidth / 2, SCREEN_WIDTH - m_fWidth / 2);
	CObject2D::SetScreenY(m_pos.y, 0.0f + 200.0f, SCREEN_HEIGHT - m_fHeight / 2);

	//--------------------------
	// �e�̔���
	//--------------------------
	m_nCntShotTime++;
	m_nCntShotTime %= m_nShotTime;	//���ˎ��Ԃ����Z�b�g

	{
		int nLevel = m_Level->GetLevel();	//���x���̎擾
		m_Bullet->ShotBullet(m_pos, nLevel, m_nCntShotTime);	//�e�̔���
	}

	//--------------------------
	// �X�L���̔���
	//--------------------------
	SetSkill();

	//------------------------
	// �G�Ƃ̓����蔻��
	//------------------------
	if (m_type != PLAYERSTATE_INVINCIBLE && CObject2D::GetCollision(OBJTYPE_ENEMY))
	{//���G�łȂ���� ���� �G�Ɠ���������
		m_nLife -= 20;	//�v���C���[�̗̑͂̌���

		//�c��̗͂��v�Z
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP�������̏���
		m_Hp->SetLife(m_nLife, m_nRemLife);

		m_type = PLAYERSTATE_INVINCIBLE;
	}

	//----------------------------
	// ���G����
	//----------------------------
	if (m_type == PLAYERSTATE_INVINCIBLE)
	{
		InvincibleTime();
	}

	//--------------------------
	// �̗͂��s����
	//--------------------------
	if (m_nLife <= 0)
	{
		//�G�̏���
		Uninit();
		return;
	}

	CObject2D::SetColor(m_col);
}

//===========================
// �`��
//===========================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CPlayer *CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	pPlayer = new CPlayer;	//����

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		//������
		pPlayer->Init(D3DXVECTOR3(400.0f, SCREEN_HEIGHT / 2, 0.0f));
		pPlayer->SetObjType(OBJTYPE_PLAYER);
	}

	return pPlayer;
}

//===========================
// �v���C���[�̑���
//===========================
D3DXVECTOR3 CPlayer::OperationPlayer()
{
	if (CInputKeyboard::Press(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W) == true)
		{//W�L�[�������ꂽ
			m_move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//�㍶�ړ�
			m_move.x += sinf(-D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//�����ړ�
			m_move.x += sinf(-D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * fPlayerSpeed;		//���ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W) == true)
		{//W�L�[�������ꂽ
			m_move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//��E�ړ�
			m_move.x += sinf(D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//���E�ړ�
			m_move.x += sinf(D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * fPlayerSpeed;			//�E�ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//W�L�[�������ꂽ
		m_move.y += cosf(-D3DX_PI * 1.0f) * fPlayerSpeed;			//��ړ�
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//S�L�[�������ꂽ
		m_move.y += cosf(D3DX_PI * 0.0f) * fPlayerSpeed;				//���ړ�
	}

	return m_move;
}

//===========================
// �X�L���̔���
//===========================
void CPlayer::SetSkill()
{
	//-----------------------
	// �̗͂̉�
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_1))
	{//1�L�[�������ꂽ��
		CSkill::Create(CSkill::SKILLTYPE_HEAL);

		if (m_nLife + 30 >= m_nMaxLife)
		{//�񕜂��ď���Ȃ�
			m_nLife = m_nMaxLife;	//�̗͂��ő�ɂ���
		}
		else
		{//����ȊO�Ȃ�
			m_nLife += 30;	//�̗͂���
		}

		//�c��̗͂��v�Z
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP�������̏���
		m_Hp->SetLife(m_nLife, m_nRemLife);
	}

	//-----------------------
	// �e���̋���
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_2))
	{//2�L�[�������ꂽ��
		CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);

		m_nShotTime = 15;
	}
}

//===========================
// ���G����
//===========================
void CPlayer::InvincibleTime()
{
	m_nCntInvincible++;

	//�F�̕ύX
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	if (m_nCntInvincible >= 120)
	{//���G���Ԃ��I�������
		m_type = PLAYERSTATE_NORMAL;	//�ʏ�̏�Ԃɖ߂�
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_nCntInvincible = 0;
	}
}

//===========================
// �̗͂̌���
//===========================
void CPlayer::SubLife(int nAttack)
{
	m_nLife -= nAttack;	//�v���C���[�̗̑͂̌���

	//�c��̗͂��v�Z
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP�������̏���
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// �F�̐ݒ�
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// �̗͂̎擾
//===========================
int CPlayer::GetLife()
{
	return m_nLife;
}

//===========================
// �c��̗͂̎擾
//===========================
int CPlayer::GetRemLife()
{
	return m_nRemLife;
}

//===========================
// �U���͂̎擾
//===========================
int CPlayer::GetAttack()
{
	return m_nAttack;
}

//===========================
// �v���C���[�̏�Ԃ̎擾
//===========================
CPlayer::PLAYERSTATE CPlayer::GetState()
{
	return m_type;
}