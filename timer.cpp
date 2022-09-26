//===================================
//
// �^�C�}�[����
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include "timer.h"
#include "texture.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int CTimer::m_nTime = 0;
int CTimer::m_aPosTexU[nMaxScore] = {};
int CTimer::nNum = 0;

//===========================
// �R���X�g���N�^
//===========================
CTimer::CTimer() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTime = 0;
	m_fWidth = 0.0f;
	m_fHeight = 0.0;
	m_mode = MODE_MAX;
}

//===========================
// �f�X�g���N�^
//===========================
CTimer::~CTimer()
{

}

//===========================
// ������
//===========================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	//�\���̂̏�����
	m_pos = pos;
	m_nTime = 0;

	if (m_mode == MODE_GAME)
	{
		m_fWidth = 30.0f;
		m_fHeight = 50.0f;
	}
	else if (m_mode == MODE_RESULT)
	{
		m_fWidth = 60.0f;
		m_fHeight = 100.0f;
	}

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CTimer::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CTimer::Update()
{
	CObject2D::Update();

	if (m_mode == MODE_GAME)
	{
		m_nCntTime++;
		m_nCntTime %= 60;

		if (m_nCntTime == 0)
		{
			m_nTime++;
		}
	}
	
	if (m_nTime % 3 == 0)
	{
		//�����Ƃ̒l�����߂�
		m_aPosTexU[nNum] = (m_nTime / 3) % (1000 / (int)pow(10, nNum)) / (100 / (int)pow(10, nNum));
	}

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexCIE(0.0f + m_aPosTexU[nNum] * 0.1f, 0.1f + m_aPosTexU[nNum] * 0.1f);

	//�z���i�߂�
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
void CTimer::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CTimer *CTimer::Create(MODE mode)
{
	CTimer *pTimer = nullptr;

	//----------------------------------
	// �v���C���[�̐����Ə�����
	//----------------------------------
	for (int i = 0; i < nMaxScore; i++)
	{
		pTimer = new CTimer;	//����

		if (pTimer != nullptr)
		{//NULL�`�F�b�N
			//�����o�ϐ��ɑ��
			pTimer->m_mode = mode;

			//������
			if (pTimer->m_mode == MODE_GAME)
			{
				pTimer->Init(D3DXVECTOR3(900.0f + (i * 30.0f), 70.0f, 0.0f));
			}
			else if (pTimer->m_mode == MODE_RESULT)
			{
				pTimer->Init(D3DXVECTOR3(550.0f + (i * 70.0f), 320.0f, 0.0f));
			}

			pTimer->SetObjType(OBJTYPE_SCORE);
		}
	}

	return pTimer;
}

//===========================
// ���Ԃ̐ݒ�
//===========================
void CTimer::SetTime(int nTime)
{
	m_nTime = nTime;
}

//===========================
// ���Ԃ̎擾
//===========================
int CTimer::GetTime()
{
	return m_nTime;
}