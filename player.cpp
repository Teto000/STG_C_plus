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

	//--------------------------
	// �v���C���[�̈ړ�
	//--------------------------
	//���E�ړ�
	if (CInputKeyboard::Press(DIK_A))
	{//A�L�[�������ꂽ
		m_Player.pos.x -= PLAYER_SPEED;
	}
	else if (CInputKeyboard::Press(DIK_D))
	{//D�L�[�������ꂽ
		m_Player.pos.x += PLAYER_SPEED;
	}

	//�㉺�ړ�
	if (CInputKeyboard::Press(DIK_W))
	{//W�L�[�������ꂽ
		m_Player.pos.y -= PLAYER_SPEED;
	}
	else if (CInputKeyboard::Press(DIK_S))
	{//S�L�[�������ꂽ
		m_Player.pos.y += PLAYER_SPEED;
	}

	CObject2D::SetPosition(m_Player.pos);
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