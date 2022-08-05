//===================================
//
// �X�L������
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Skill, 0, sizeof(Skill));	//�\���̂̃N���A

	m_nCntTimer = 0;
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
	m_Skill.move = D3DXVECTOR3(nSkillSpeed, 0.0f, 0.0f);
	m_Skill.fWidth = 300.0f;
	m_Skill.fHeight = 80.0f;
	m_Skill.pos = D3DXVECTOR3(pos.x - (m_Skill.fWidth / 2), pos.y - (m_Skill.fHeight / 2), pos.z);

	CObject2D::Init(m_Skill.pos);

	CObject2D::SetSize(m_Skill.fWidth, m_Skill.fHeight);

	switch (m_Skill.type)
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
	//��ʒ[����ړ�
	if (m_Skill.pos.x >= (m_Skill.fWidth / 2))
	{
		//�ړ��̒�~
		m_Skill.move.x = 0;

		//�^�C�}�[�����Z
		m_nCntTimer++;

		if (m_nCntTimer >= nMaxTimer)
		{//��莞�Ԍo��
			//��ʒ[���猩���Ȃ��Ȃ�����
			m_Skill.move.x = -nSkillSpeed;
			m_nCntTimer = 0;
		}
	}
	//��ʊO�ɏ�������
	else if (m_Skill.move.x <= 0.0f && m_Skill.pos.x + (m_Skill.fWidth / 2) <= 0.0f)
	{
		//�X�L���\���̏���
		Uninit();
		return;
	}

	//�ʒu�Ɉړ��ʂ����Z
	m_Skill.pos = CObject2D::AddMove(m_Skill.move);
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
		//�\���̂ɑ��
		pSkill->m_Skill.type = type;

		//������
		pSkill->Init(D3DXVECTOR3(0.0f, 720.0f, 0.0f));
		pSkill->SetObjType(OBJTYPE_SKILL);
	}

	return pSkill;
}