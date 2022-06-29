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

//------------------------
// �}�N����`
//------------------------
#define PLAYER_SPEED	(5.0f)	//�v���C���[�̑��x

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------

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

	CObject2D::Init(m_Player.pos);

	CObject2D::SetSize(100.0f, 100.0f);	//�T�C�Y�̐ݒ�

	m_Player.pos = CObject2D::GetPosition();

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

	//�v���C���[�̑���
	D3DXVECTOR3 move = OperationPlayer();

	//�ړ��ʂ��X�V(����)
	m_Player.move.x += (0.0f - move.x) * 0.4f;
	m_Player.move.y += (0.0f - move.y) * 0.4f;

	CObject2D::AddMove(m_Player.move);
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
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * PLAYER_SPEED;		//�㍶�ړ�
			m_Player.move.x += sinf(-D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;		//�����ړ�
			m_Player.move.x += sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{
			m_Player.move.x += sinf(-D3DX_PI * 0.5f) * PLAYER_SPEED;		//���ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W) == true)
		{//W�L�[�������ꂽ
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * PLAYER_SPEED;		//��E�ړ�
			m_Player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//S�L�[�������ꂽ
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;		//���E�ړ�
			m_Player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{
			m_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;			//�E�ړ�
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//W�L�[�������ꂽ
		m_Player.move.y += cosf(-D3DX_PI * 1.0f) * PLAYER_SPEED;			//��ړ�
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//S�L�[�������ꂽ
		m_Player.move.y += cosf(D3DX_PI * 0.0f) * PLAYER_SPEED;				//���ړ�
	}

	return m_Player.move;
}