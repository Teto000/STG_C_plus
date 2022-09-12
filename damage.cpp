//===================================
//
// �_���[�W����
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "damage.h"
#include "texture.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int CDamage::m_nValue = 0;
int CDamage::m_nNum = 0;

//===========================
// �R���X�g���N�^
//===========================
CDamage::CDamage() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	m_nLife = 0;
	m_nDigit = 0;			//����
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_fSpace = 0.0f;		//�Ԋu
	m_aPosTexU[m_nDigit] = {};
}

//===========================
// �f�X�g���N�^
//===========================
CDamage::~CDamage()
{

}

//===========================
// ������
//===========================
HRESULT CDamage::Init(D3DXVECTOR3 pos)
{
	//�\���̂̏�����
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 70;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CDamage::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CDamage::Update()
{
	CObject2D::Update();

	//�����̌v�Z
	int nFirst = (int)pow(10, m_nDigit);
	int nSecond = (int)pow(10, (m_nDigit - 1));
	int nDigit = (int)pow(10, m_nNum);

	//�����Ƃ̒l�����߂�
	m_aPosTexU[m_nNum] = m_nValue % (nFirst / nDigit) / (nSecond / nDigit);

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexCIE(m_aPosTexU[m_nNum] * 0.1f, m_aPosTexU[m_nNum] * 0.1f + 0.1f);

	//�z���i�߂�
	if (m_nNum >= m_nDigit - 1)
	{
		m_nNum = 0;
	}
	else
	{
		m_nNum++;
	}

	//---------------------
	// �����̌���
	//---------------------
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	if (m_nLife <= 55)
	{
		//---------------------
		// �_���[�W�\�L�̈ړ�
		//---------------------
		/*m_move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		m_pos = CObject2D::AddMove(m_move);*/

		CObject2D::SetSize(m_fWidth, m_fHeight);

		//---------------------
		// �����ɂ���
		//---------------------
		m_col.a -= 0.05f;
		CObject2D::SetColor(m_col);

		if (m_col.a <= 0.0f)
		{
			Uninit();
			return;
		}
	}
	
}

//===========================
// �`��
//===========================
void CDamage::Draw()
{
	CObject2D::Draw();
}

//====================================
// ����(�ʒu,��,����,�Ԋu,����,���l)
//====================================
CDamage *CDamage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
						int nDigit, int nNumber)
{
	CDamage *pNumber = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	for (int i = 0; i < nDigit; i++)
	{
		pNumber = new CDamage;	//����

		if (pNumber != nullptr)
		{//NULL�`�F�b�N
			//�����o�ϐ��ɑ��
			pNumber->m_fWidth = fWidth;		//��
			pNumber->m_fHeight = fHeight;	//����
			pNumber->m_fSpace = fSpace;		//�Ԋu
			pNumber->m_nDigit = nDigit;		//����
			pNumber->m_nValue = nNumber;			//�l

			//������
			pNumber->Init(D3DXVECTOR3(pos.x + i * fSpace, pos.y, pos.z));
			pNumber->SetObjType(OBJTYPE_SCORE);
		}
	}
	return pNumber;
}