//===================================
//
// �X�L������
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "skill.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CSkill::nSkillSpeed = 7.0f;	//���x

//===========================
// �R���X�g���N�^
//===========================
CSkill::CSkill() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_nCntTimer = 0;		//�����̕\������
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_type = SKILLTYPE_MAX;	//���
}

//===========================
// �f�X�g���N�^
//===========================
CSkill::~CSkill()
{

}

//===========================
// ������
//===========================
HRESULT CSkill::Init(D3DXVECTOR3 pos)
{
	//�\���̂ɑ��
	m_fWidth = 300.0f;
	m_fHeight = 80.0f;
	m_pos = D3DXVECTOR3(pos.x - (m_fWidth / 2), pos.y - (m_fHeight / 2), pos.z);

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	switch (m_type)
	{
	case SKILLTYPE_HEAL:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_HPHEAL);	//�e�N�X�`���̐ݒ�
		break;

	case SKILLTYPE_SPEEDUP_FIRE:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_SPEEDUP_FIRE);	//�e�N�X�`���̐ݒ�
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================
// �I��
//===========================
void CSkill::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CSkill::Update()
{
	CObject2D::Update();

	//--------------------------
	// �X�L���\��
	//--------------------------

	//�ʒu�Ɉړ��ʂ����Z
	m_pos = CObject2D::AddMove(m_move);
}

//===========================
// �`��
//===========================
void CSkill::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CSkill *CSkill::Create(SKILLTYPE type)
{
	CSkill *pSkill = nullptr;

	//----------------------------------
	// �G�̐����Ə�����
	//----------------------------------
	pSkill = new CSkill;	//����

	if (pSkill != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pSkill->m_type = type;

		//������
		switch (pSkill->m_type)
		{
		case SKILLTYPE_HEAL:
			pSkill->Init(D3DXVECTOR3(300.0f, 720.0f, 0.0f));
			break;

		case SKILLTYPE_SPEEDUP_FIRE:
			pSkill->Init(D3DXVECTOR3(600.0f, 720.0f, 0.0f));
			break;

		default:
			break;
		}
		pSkill->SetObjType(OBJTYPE_SKILL);
	}

	return pSkill;
}