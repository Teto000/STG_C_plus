//===================================
//
// �����鐔�l��\�����鏈��
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
#include "number.h"
#include "texture.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int CNumber::m_nValue = 0;
int CNumber::m_nNum = 0;

//===========================
// �R���X�g���N�^
//===========================
CNumber::CNumber() : CObject2D()
{
	memset(&m_Number, 0, sizeof(Number));	//�\���̂̃N���A
	m_aPosTexU[m_Number.nDigit] = {};
}

//===========================
// �f�X�g���N�^
//===========================
CNumber::~CNumber()
{

}

//===========================
// ������
//===========================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	//�\���̂̏�����
	m_Number.pos = pos;

	CObject2D::Init(m_Number.pos);

	CObject2D::SetSize(m_Number.fWidth, m_Number.fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CNumber::Update()
{
	CObject2D::Update();

	//�����̌v�Z
	int nFirst = (int)pow(10, m_Number.nDigit);
	int nSecond = (int)pow(10, (m_Number.nDigit - 1));
	int nDigit = (int)pow(10, m_nNum);

	//�����Ƃ̒l�����߂�
	m_aPosTexU[m_nNum] = m_nValue % (nFirst / nDigit) / (nSecond / nDigit);

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexCIE(m_aPosTexU[m_nNum] * 0.1f, m_aPosTexU[m_nNum] * 0.1f + 0.1f);

	//�z���i�߂�
	if (m_nNum >= m_Number.nDigit - 1)
	{
		m_nNum = 0;
	}
	else
	{
		m_nNum++;
	}

	//�c�ɏk��
	m_Number.fHeight -= 1.5f;

	CObject2D::SetSize(m_Number.fWidth, m_Number.fHeight);

	if (m_Number.fHeight <= 0)
	{//�����������Ȃ�����
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//====================================
// ����(�ʒu,��,����,�Ԋu,����,���l)
//====================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
						int nDigit, int nNumber)
{
	CNumber *pNumber = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	for (int i = 0; i < nDigit; i++)
	{
		pNumber = new CNumber;	//����

		if (pNumber != nullptr)
		{//NULL�`�F�b�N
			//�\���̂ɑ��
			pNumber->m_Number.fWidth = fWidth;		//��
			pNumber->m_Number.fHeight = fHeight;	//����
			pNumber->m_Number.fSpace = fSpace;		//�Ԋu
			pNumber->m_Number.nDigit = nDigit;		//����
			pNumber->m_nValue = nNumber;			//�l

			//������
			pNumber->Init(D3DXVECTOR3(pos.x + i * fSpace, pos.y, pos.z));
			pNumber->SetObjType(OBJTYPE_SCORE);
		}
	}
	return pNumber;
}