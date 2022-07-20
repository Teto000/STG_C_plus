//===================================
//
// ���x���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "level.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "exp.h"

//===========================
// �R���X�g���N�^
//===========================
CLevel::CLevel() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	m_fLength = 0.0f;	//��
}

//===========================
// �f�X�g���N�^
//===========================
CLevel::~CLevel()
{

}

//===========================
// ������
//===========================
HRESULT CLevel::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 100;	//��

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexture(CTexture::TEXTURE_RING);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CLevel::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CLevel::Update()
{
	CObject2D::Update();

	//�~�`�Ɉړ�����
	D3DXVECTOR3 CirclePos = CObject2D::MoveCircle(m_pos, m_rot.x, m_fLength * 0.6f);

	//�ʒu�̐ݒ�
	CObject2D::SetPosition(m_pos);

	if (CInputKeyboard::Trigger(DIK_K))
	{
		CExp::Create(CirclePos,m_rot,m_fLength * 0.6f);	//�o���l�Q�[�W�̐���

		m_rot.x += 30.0f;
	}
}

//===========================
// �`��
//===========================
void CLevel::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CLevel *CLevel::Create()
{
	CLevel *pLevel = nullptr;

	//----------------------------------
	// ���x���̐����Ə�����
	//----------------------------------
	pLevel = new CLevel;	//����

	if (pLevel != nullptr)
	{//NULL�`�F�b�N
		//������
		pLevel->Init(D3DXVECTOR3(120.0f, 100.0f, 0.0f));
		pLevel->SetObjType(OBJTYPE_LEVEL);
	}

	return pLevel;
}