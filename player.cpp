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
#include "application.h"
#include "object2D.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"
#include "mp.h"
#include "skill.h"
#include "level.h"
#include "hpfream.h"
#include "barrier.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CPlayer::fPlayerSpeed = 7.0f;
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
	m_nMagic = 0;				//MP
	m_nMaxMagic = 0;			//�ő�MP
	m_nRemMagic = 0;			//�c��MP
	m_nAttack = 0;				//�U����
	m_nLevel = 0;				//���x��
	m_nShotTime = 0;			//�e�̔��ˎ���
	m_nCntShotTime = 0;			//�e�̔��ˎ��Ԃ𐔂���
	m_nCntInvincible = 0;		//���G���Ԃ𐔂���
	m_nCntSkill[nMaxSkill] = {};//�X�L���̎g�p�\���Ԃ𐔂���
	m_nCntTime = 0;				//�e�N�X�`���A�j���[�V�����J�E���g
	m_nSpeed = 0.0f;			//���x
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_bSlill[nMaxSkill] = {};	//�X�L���g�p�\���ǂ���
	m_type = PLAYERSTATE_NORMAL;//���
	m_Hp = nullptr;				//HP�N���X
	m_Mp = nullptr;				//MP�N���X
	m_Level = nullptr;			//���x���N���X
	m_Bullet = nullptr;			//�e�N���X
	m_pHpFream = nullptr;		//HP�t���[���N���X
	m_pBarrier = nullptr;		//�o���A�N���X
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
	m_nMagic = 100;				//MP
	m_nMaxMagic = 100;			//�ő�MP
	m_nRemMagic = 100;			//�c��MP
	m_fWidth = 70.0f;			//��
	m_fHeight = 80.0f;			//����
	m_nAttack = 15;				//�U����
	m_nShotTime = 20;			//�e�̔��ˎ���
	m_nSpeed = fPlayerSpeed;	//���x

	for (int i = 0; i < nMaxSkill; i++)
	{
		m_nCntSkill[i] = 0;
		m_bSlill[i] = false;
	}

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//�e�N�X�`���̐ݒ�

	m_pos = CObject2D::GetPosition();

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexCIE(0.0f, 0.5f);

	//--------------------------
	// HP�̕\��
	//--------------------------
	m_Hp = CHp::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);
	m_Hp->SetLife(m_nLife, m_nRemLife);	//����HP�̐ݒ�

	//--------------------------
	// MP�̕\��
	//--------------------------
	m_Mp = CMp::Create(D3DXVECTOR3(520.0f, 110.0f, 0.0f), 600.0f, 20.0f);
	m_Mp->SetMP(m_nMagic, m_nRemMagic);	//����HP�̐ݒ�

	//--------------------------
	// ���x���̐���
	//--------------------------
	m_Level = CLevel::Create();

	//--------------------------
	// �t���[���̐���
	//--------------------------
	m_pHpFream = CHpFream::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);

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
	//D3DXVECTOR3 move = MoveJoypad();

	//---------------------------
	// �e�N�X�`���A�j���[�V����
	//---------------------------
	Animation();

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
	CObject2D::SetScreenY(m_pos.y, 0.0f + 200.0f, SCREEN_HEIGHT - 140.0f);
	
	//--------------------
	// ���x���ɂ��ω�
	//--------------------
	m_nLevel = m_Level->GetLevel();	//���x���̎擾
	//m_nAttack += (10 * (m_nLevel -1));

	//--------------------------
	// �e�̔���
	//--------------------------
	if (!CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//�o���A�͈̔͊O�Ȃ�
		m_nCntShotTime++;
		m_nCntShotTime %= m_nShotTime;	//���ˎ��Ԃ����Z�b�g

		m_Bullet->ShotBullet(m_pos, m_nLevel, m_nCntShotTime);	//�e�̔���
	}

	//--------------------------
	// �X�L���̔���
	//--------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (!m_bSlill[i] && m_nMagic >= 10)
		{//�X�L�����g�p���Ă��Ȃ� & MP��10�ȏ�Ȃ�
			SetSkill();
		}
	}

	//--------------------------
	// �X�L���̌��ʂ��؂��
	//--------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (m_bSlill[i])
		{//�X�L���g�p��ԂȂ�
			m_nCntSkill[i]++;

			if (m_nCntSkill[i] >= 600)
			{
				m_bSlill[i] = false;
				m_nCntSkill[i] = 0;
			}
			else if (m_nCntSkill[i] >= 300)
			{//5�b�o�߂�����
				m_nAttack = 10;				//�U����
				m_nShotTime = 20;			//�e�̔��ˎ���
				m_nSpeed = fPlayerSpeed;	//���x
			}
		}
	}

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

		Sleep(300);

		//���U���g��ʂɈڍs
		CApplication::SetMode(CApplication::MODE_RESULT);
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
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//�㍶�ړ�
			m_move.x += sinf(-D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//�����ړ�
			m_move.x += sinf(-D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * m_nSpeed;		//���ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W) == true)
		{//W�L�[�������ꂽ
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//��E�ړ�
			m_move.x += sinf(D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//���E�ړ�
			m_move.x += sinf(D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * m_nSpeed;		//�E�ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//W�L�[�������ꂽ
		m_move.y += cosf(-D3DX_PI * 1.0f) * m_nSpeed;			//��ړ�
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//S�L�[�������ꂽ
		m_move.y += cosf(D3DX_PI * 0.0f) * m_nSpeed;			//���ړ�
	}

	return m_move;
}

//===========================
// �W���C�p�b�h���g�����ړ�
//===========================
D3DXVECTOR3 CPlayer::MoveJoypad()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetJoypad();
	D3DXVECTOR3 stick = joypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0);

	//if (joypad->IsJoyPadUse(0) == false)
	//{//�W���C�p�b�h���g���Ă��Ȃ��Ȃ�
	//	return ;
	//}

	//�X�e�B�b�N�𓮂����l�̐ݒ�
	float fMoveValue = 0.5f;

	//-----------------------------------
	// �E�ړ�
	//-----------------------------------
	if (stick.x >= fMoveValue)
	{
		if (stick.y <= -fMoveValue)
		{//���ړ�
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;
			m_move.x += sinf(D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (stick.y >= fMoveValue)
		{//�O�ړ�
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;
			m_move.x += sinf(D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * m_nSpeed;
		}
	}
	//-----------------------------------
	// ���ړ�
	//-----------------------------------
	else if (stick.x <= -fMoveValue)
	{
		// �X�e�B�b�N��|���������ֈړ�����
		if (stick.y <= -fMoveValue)
		{//���ړ�
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;
			m_move.x += sinf(-D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (stick.y >= fMoveValue)
		{//�O�ړ�
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;
			m_move.x += sinf(-D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * m_nSpeed;
		}
	}
	//-----------------------------------
	// ���ړ�
	//-----------------------------------
	else if (stick.y <= -fMoveValue)
	{
		m_move.y += cosf(-D3DX_PI * 1.0f) * m_nSpeed;
	}
	//-----------------------------------
	// �O�ړ�
	//-----------------------------------
	else if (stick.y >= fMoveValue)
	{
		m_move.y += cosf(D3DX_PI * 0.0f) * m_nSpeed;
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
	if (CInputKeyboard::Trigger(DIK_U) && !m_bSlill[0])
	{//1�L�[�������ꂽ��
		if (m_nLife + 50 >= m_nMaxLife)
		{//�񕜂��ď���Ȃ�
			m_nLife = m_nMaxLife;	//�̗͂��ő�ɂ���
		}
		else
		{//����ȊO�Ȃ�
			m_nLife += 50;	//�̗͂���
		}

		//�c��̗͂��v�Z
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP�������̏���
		m_Hp->SetLife(m_nLife, m_nRemLife);

		//MP�̌���
		AddMagic(-10);

		m_bSlill[0] = true;

		//�T�E���h�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// �e���̋���
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_I) && !m_bSlill[1])
	{//2�L�[�������ꂽ��
		//���ˊԊu�̌���
		m_nShotTime = 10;

		//MP�̌���
		AddMagic(-10);

		m_bSlill[1]= true;

		//�T�E���h�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// �U���͏㏸
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_O) && !m_bSlill[2])
	{
		//�U���͂̏㏸
		m_nAttack = 30;

		//MP�̌���
		AddMagic(-10);

		m_bSlill[2] = true;

		//�T�E���h�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// ���x�㏸
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_P) && !m_bSlill[3])
	{
		//���x�̏㏸
		m_nSpeed = 10.0f;

		//MP�̌���
		AddMagic(-10);

		m_bSlill[3] = true;

		//�T�E���h�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
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

//============================
// �e�N�X�`���A�j���[�V����
//============================
void CPlayer::Animation()
{
	m_nCntTime++;
	m_nCntTime %= 80;	//���Z�b�g

	if (m_nCntTime >= 40)
	{
		CObject2D::SetTexCIE(0.0f, 0.5f);	//�e�N�X�`�����W�̐ݒ�
	}
	else
	{
		CObject2D::SetTexCIE(0.5f, 1.0f);
	}
}

//===========================
// HP�̉��Z
//===========================
void CPlayer::AddLife(int nValue)
{
	if (m_nLife + nValue < m_nMaxLife)
	{
		m_nLife += nValue;	//�v���C���[�̗̑͂̉��Z
	}
	else
	{
		m_nLife = m_nMaxLife;
	}

	//�c��̗͂��v�Z
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP�������̏���
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// MP�̉��Z
//===========================
void CPlayer::AddMagic(int nValue)
{
	if (m_nMagic + nValue < m_nMaxMagic)
	{//�ő�MP�𒴂��Ȃ��Ȃ�
		m_nMagic += nValue;	//�v���C���[��MP�̉��Z
	}
	else 
	{
		//MP���ő�ɂ���
		m_nMagic = m_nMaxMagic;
	}

	//�c��MP���v�Z
	m_nRemMagic = m_nMagic * 100 / m_nMaxMagic;

	//MP�������̏���
	m_Mp->SetMP(m_nMagic, m_nRemMagic);
}

//===========================
// �F�̐ݒ�
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// �ړ��ʂ̎擾
//===========================
D3DXVECTOR3 CPlayer::GetMove()
{
	return m_move;
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