//============================
//
// �i���o�[�w�b�_�[
// Author:Teruto Sato
//
//============================
#ifndef _DAMAGE_H_
#define _DAMAGE_H_	//��d�C���N���[�h�h�~

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �i���o�[�N���X�̒�`
//--------------------------
class CDamage : public CObject2D
{
public:
	CDamage();				//�R���X�g���N�^
	~CDamage() override;		//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CDamage *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
							int nDigit, int nNumber);

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxDigit = 6;		//�ő包��

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXCOLOR	m_col;	//�F
	int m_nDigit;		//����
	int m_nLife;		//����
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fSpace;		//�Ԋu
	int m_aPosTexU[nMaxDigit];

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nValue;	//�l
	static int m_nNum;		//�z��J�E���g�p
};

#endif