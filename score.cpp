//===================================
//
// �X�R�A�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <memory.h>
#include "score.h"
#include "texture.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int CScore::m_nScore = 0;
int CScore::m_aPosTexU[nMaxScore] = {};
int CScore::nNum = 0;

//===========================
// �R���X�g���N�^
//===========================
CScore::CScore() : CObject2D()
{
	memset(&m_Score, 0, sizeof(Score));	//�\���̂̃N���A
}

//===========================
// �f�X�g���N�^
//===========================
CScore::~CScore()
{

}

//===========================
// ������
//===========================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//�\���̂̏�����
	m_Score.pos = pos;
	m_Score.fWidth = 30.0f;		//��
	m_Score.fHeight = 50.0f;	//����
	m_Score.fSpace = 35.0f;		//�Ԋu

	m_nScore = 0;	//�X�R�A�̏����ݒ�

	CObject2D::Init(m_Score.pos);

	CObject2D::SetSize(m_Score.fWidth, m_Score.fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CScore::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CScore::Update()
{
	CObject2D::Update();

	//�����Ƃ̒l�����߂�
	m_aPosTexU[nNum] = m_nScore % (1000000 / (int)pow(10, nNum)) / (100000 / (int)pow(10, nNum));

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexCIE(0.0f + m_aPosTexU[nNum] * 0.1f, 0.1f + m_aPosTexU[nNum] * 0.1f);

	if (nNum >= nMaxScore - 1)
	{
		nNum = 0;
	}
	else 
	{
		nNum++;
	}
}
//===========================
// �`��
//===========================
void CScore::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CScore *CScore::Create()
{
	CScore *pScore = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	for (int i = 0; i < nMaxScore; i++)
	{
		pScore = new CScore;	//����

		if (pScore != nullptr)
		{//NULL�`�F�b�N
			//������
			pScore->Init(D3DXVECTOR3(1000.0f + (i * 35.0f), 50.0f, 0.0f));
			pScore->SetObjType(OBJTYPE_SCORE);
		}
	}

	return pScore;
}

//===========================
// ���l�̉��Z
//===========================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//===========================
// ���l�̎擾
//===========================
int CScore::GetScore()
{
	return m_nScore;
}