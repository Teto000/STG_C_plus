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
	m_Score.fWidth = 15.0f;		//��
	m_Score.fHeight = 25.0f;	//����
	m_Score.fInterval = 35.0f;	//�Ԋu

	CObject2D::Init(m_Score.pos);

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
	pScore = new CScore;	//����

	if (pScore != nullptr)
	{//NULL�`�F�b�N
		//������
		pScore->Init(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));
		pScore->SetObjType(OBJTYPE_SCORE);
	}

	return pScore;
}