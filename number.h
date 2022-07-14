//============================
//
// �i���o�[�w�b�_�[
// Author:Teruto Sato
//
//============================
#ifndef _NUMBER_H_
#define _NUMBER_H_	//��d�C���N���[�h�h�~

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �i���o�[�N���X�̒�`
//--------------------------
class CNumber : public CObject2D
{
public:
	//--------------------------
	// �i���o�[�\���̂̒�`
	//--------------------------
	struct Number
	{
		D3DXVECTOR3 pos;	//�ʒu
		int nLife;			//����
		int nDigit;			//����
		float fWidth;		//��
		float fHeight;		//����
		float fSpace;		//�Ԋu
	};

	CNumber();				//�R���X�g���N�^
	~CNumber() override;		//�f�X�g���N�^

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
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
							int nDigit, int nNumber);

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxDigit = 6;		//�ő包��

	//----------------
	// �����o�ϐ�
	//----------------
	Number m_Number;	//�i���o�[�\����
	int m_aPosTexU[nMaxDigit];

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nValue;	//�l
	static int m_nNum;		//�z��J�E���g�p
};

#endif