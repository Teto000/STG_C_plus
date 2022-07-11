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
#include <memory.h>
#include "player.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"

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
	memset(&m_Player, 0, sizeof(Player));	//�\���̂̃N���A
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
	m_Player.pos = pos;
	m_Player.nLife = nPlayerLife;	//�̗�
	m_Player.nMaxLife = nPlayerLife;//�ő�̗�
	m_Player.nRemLife = nMaxLife;	//�c��̗�
	m_Player.fWidth = 80.0f;		//��
	m_Player.fHeight = 100.0f;		//����
	m_Player.nAttack = 10;			//�U����
	m_Player.nSpeed = fPlayerSpeed;	//���x

	CObject2D::Init(m_Player.pos);

	CObject2D::SetSize(m_Player.fWidth, m_Player.fHeight);	//�T�C�Y�̐ݒ�

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//�e�N�X�`���̐ݒ�

	m_Player.pos = CObject2D::GetPosition();

	//--------------------------
	// HP�̕\��
	//--------------------------
	CHp::Create(D3DXVECTOR3(350.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				, 600.0f, 40.0f, CHp::HPTYPE_PLAYER);

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
	m_Player.move.x += (0.0f - move.x) * 0.4f;
	m_Player.move.y += (0.0f - move.y) * 0.4f;

	//--------------------
	// �ʒu�Ɉړ��ʂ����Z
	//--------------------
	m_Player.pos = CObject2D::AddMove(m_Player.move);

	//--------------------
	// ��ʒ[�̐ݒ�
	//--------------------
	CObject2D::SetScreenX(m_Player.pos.x, 0.0f + m_Player.fWidth / 2, SCREEN_WIDTH - m_Player.fWidth / 2);
	CObject2D::SetScreenY(m_Player.pos.y, 0.0f + 180.0f, SCREEN_HEIGHT - m_Player.fHeight / 2);

	//--------------------------
	// �e�̔���
	//--------------------------
	CBullet::ShotBullet(m_Player.pos, m_Player.rot);

	//--------------------------
	// �̗͂̌���
	//--------------------------
	if (CInputKeyboard::Press(DIK_L))
	{//L�L�[�������ꂽ
		m_Player.nLife--;	//�v���C���[�̗̑͂̌���
		m_Player.nRemLife = m_Player.nLife * 100 / m_Player.nMaxLife;	//�c��̗͂��v�Z
	}

	//------------------------
	// �G�Ƃ̓����蔻��
	//------------------------
	if (CObject2D::GetCollision(OBJTYPE_ENEMY) == true)
	{
		m_Player.nLife--;	//�v���C���[�̗̑͂̌���
		m_Player.nRemLife = m_Player.nLife * 100 / m_Player.nMaxLife;	//�c��̗͂��v�Z
	}
}

//===========================
// �`��
//===========================
void CPlayer::Draw()
{
	CObject2D::Draw();
	CObject2D::SetColor(m_col);
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
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//�㍶�ړ�
			m_Player.move.x += sinf(-D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//�����ړ�
			m_Player.move.x += sinf(-D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_Player.move.x += sinf(-D3DX_PI * 0.5f) * fPlayerSpeed;		//���ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W) == true)
		{//W�L�[�������ꂽ
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//��E�ړ�
			m_Player.move.x += sinf(D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//���E�ړ�
			m_Player.move.x += sinf(D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_Player.move.x += sinf(D3DX_PI * 0.5f) * fPlayerSpeed;			//�E�ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//W�L�[�������ꂽ
		m_Player.move.y += cosf(-D3DX_PI * 1.0f) * fPlayerSpeed;			//��ړ�
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//S�L�[�������ꂽ
		m_Player.move.y += cosf(D3DX_PI * 0.0f) * fPlayerSpeed;				//���ړ�
	}

	return m_Player.move;
}

//===========================
// �F�̐ݒ�
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// �c��̗͂̎擾
//===========================
int CPlayer::GetRemLife()
{
	return m_Player.nRemLife;
}