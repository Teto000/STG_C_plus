//===================================
//
// ���x���̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "level.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "exp.h"

//-----------------------------
// �ÓI�����o�ϐ��錾
//-----------------------------
int CLevel::m_nExpPoint;

//===========================
// �R���X�g���N�^
//===========================
CLevel::CLevel() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	m_nLevel = 0;
	m_fLength = 0.0f;	//��
	m_pExp = nullptr;
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
	m_fLength = 80;		//��
	m_nLevel = 1;		//���x��

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexCIE(0.0f, 0.2f);

	CObject2D::SetTexture(CTexture::TEXTURE_LEVEL);	//�e�N�X�`���̐ݒ�

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

	//�擾�����o���l�ŏo������Q�[�W����
	for (int i = 0; i < m_nExpPoint / (5 * m_nLevel); i++)
	{
		//�~�`�Ɉړ��������W�����߂�
		D3DXVECTOR3 CirclePos = CObject2D::MoveCircle(m_pos, m_rot.x, m_fLength * 0.6f);

		//�ʒu�̐ݒ�
		CObject2D::SetPosition(m_pos);

		//-----------------------
		// ���x���A�b�v�̏���
		//-----------------------
		if (m_nLevel > nMaxLevel)
		{//���x�����ő�Ȃ�
			return;
		}

		if (m_nExpPoint < (5 * m_nLevel))
		{//���o���l�ʂɒB���Ă��Ȃ��Ȃ�
			return;
		}

		//�o���l�Q�[�W�̐���
		m_pExp = CExp::Create(CirclePos, m_rot, m_fLength * 0.6f);

		if (m_rot.x >= 360.0f)
		{//�Q�[�W�����������
			m_rot.x -= 360.0f;	//���K��

			//�e�N�X�`�����W�̕ύX
			CObject2D::SetTexCIE(0.0f + (0.2f * m_nLevel), 0.2f + (0.2f * m_nLevel));
			m_nLevel++;		//���x���̉��Z
		}
		else
		{
			//�o���l�Q�[�W��z�u����p�x�����Z
			m_rot.x += 30.0f;
		}
	}

	//�o���l�̒l�����Z�b�g
	m_nExpPoint = 0;
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
		pLevel->Init(D3DXVECTOR3(120.0f, 75.0f, 0.0f));
		pLevel->SetObjType(OBJTYPE_LEVEL);
	}

	return pLevel;
}

//===========================
// ���x���̎擾
//===========================
int CLevel::GetLevel()
{
	return m_nLevel;
}

//===========================
// �o���l�̉��Z
//===========================
void CLevel::AddExp(int nValue)
{
	m_nExpPoint += nValue;
}