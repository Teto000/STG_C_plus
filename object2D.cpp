//===================================
//
// �I�u�W�F�N�g2D�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "object2D.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "input_keybord.h"

//------------------------
// �}�N����`
//------------------------
#define	ROT		(0.05f)		//��]�p�x�̑�����
#define	SCAL	(0.01f)		//�g�k�̒l�̑�����

//===========================
// �R���X�g���N�^
//===========================
CObject2D::CObject2D() : CObject()
{
	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
	m_fRot = 0.0f;		//��]�p�x
	m_fScal = 0.0f;		//�傫��
}

//===========================
// �f�X�g���N�^
//===========================
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//===========================
// ������
//===========================
HRESULT CObject2D::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu
	m_pos = pos;

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//------------------------
	// ���_���W�̐ݒ�(��])
	//------------------------
	/*float fLength = sqrtf((m_fWidth * m_fHeight) + (m_fWidth * m_fHeight)) / 2;	//�Ίp���̒������Z�o����
	float fAngle = atan2f(m_fWidth, m_fHeight);									//�Ίp���̊p�x���Z�o

	//------------------------
	// ���_����ݒ�
	//------------------------
	pVtx[0].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.z = 0.0f;*/

	//------------------------
	// rhw�̐ݒ�
	//------------------------
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//------------------------
	// �e�N�X�`�����W�̐ݒ�
	//------------------------
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
// �I��
//===========================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CObject2D::Update()
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
  	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//===============================
	// �|���S���̉�]�E�g�k
	//===============================
	/*m_fRot -= ROT;		//��]�p�x�����Z
	m_fScal += SCAL;	//�g�k�̕ϓ�
	m_fWidth += sinf(2.0f * m_fScal);	//���̌v�Z
	m_fHeight += sinf(2.0f * m_fScal);	//�����̌v�Z*/

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//------------------------
	// ���_���W�̐ݒ�(��])
	//------------------------
	/*float fLength = sqrtf((m_fWidth * m_fHeight) + (m_fWidth * m_fHeight)) / 2;	//�Ίp���̒������Z�o����
	float fAngle = atan2f(m_fWidth, m_fHeight);									//�Ίp���̊p�x���Z�o

	//------------------------
	// ���_����ݒ�
	//------------------------
	pVtx[0].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.z = 0.0f;*/

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �`��
//===========================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
						   0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
						   2);					//�`�悷��v���~�e�B�u��
}

//===========================
// �ʒu�̐ݒ�
//===========================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CObject2D::GetPosition()
{
	return m_pos;
}

//===========================
// �ړ��ʂ̉��Z
//===========================
D3DXVECTOR3 CObject2D::AddMove(D3DXVECTOR3 move)
{
	m_pos += move;

	return m_pos;
}

//===========================
// �傫���̐ݒ�
//===========================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;		//���̐ݒ�
	m_fHeight = fHeight;	//�����̐ݒ�
}

//===========================
// �e�N�X�`�����W�̐ݒ�
//===========================
void CObject2D::SetTexCIE(float left ,float fRight)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(left, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fRight, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �e�N�X�`���̐ݒ�
//===========================
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//===========================
// ���_���W�̐ݒ�
//===========================
void CObject2D::SetVtxCIE(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth / 2, fHeight / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth / 2, fHeight / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// ���_���W�̐ݒ�(����)
//===========================
void CObject2D::SetVtxCIE_Gauge(D3DXVECTOR3 pos, 
	float fLeft,float fRight, float fUp, float fDown)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fLeft / 2, -fUp / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fRight / 2, -fUp / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fLeft / 2, fDown / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fRight / 2, fDown / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// ���̎擾
//===========================
float CObject2D::GetWidth()
{
	return m_fWidth;
}

//===========================
// �����̎擾
//===========================
float CObject2D::GetHeight()
{
	return m_fHeight;
}

//===========================
// �F�̐ݒ�
//===========================
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================
// �X�R�A�̐ݒ菈��
//=====================
void CObject2D::SetScore(int nScore)
{
	int aPosTexU[m_nMaxScore];	//�e���̐������i�[

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = nScore % 1000000 / 100000;
	aPosTexU[1] = nScore % 100000 / 10000;
	aPosTexU[2] = nScore % 10000 / 1000;
	aPosTexU[3] = nScore % 1000 / 100;
	aPosTexU[4] = nScore % 100 / 10;
	aPosTexU[5] = nScore % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < m_nMaxScore; i++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================
// �X�R�A�̉��Z����
//=====================
void CObject2D::AddScore(int nScore, int nValue)
{
	int aPosTexU[m_nMaxScore];

	//�X�R�A�̉��Z
	nScore += nValue;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = nScore % 1000000 / 100000;
	aPosTexU[1] = nScore % 100000 / 10000;
	aPosTexU[2] = nScore % 10000 / 1000;
	aPosTexU[3] = nScore % 1000 / 100;
	aPosTexU[4] = nScore % 100 / 10;
	aPosTexU[5] = nScore % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < m_nMaxScore; i++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}