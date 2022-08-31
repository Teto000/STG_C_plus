//=====================================
//
// HP�t���[���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _HPFREAM_H_
#define _HPFREAM_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// HP�t���[���N���X
//--------------------------
class CHpFream : public CObject2D
{
public:
	CHpFream();				//�R���X�g���N�^
	~CHpFream() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//�Z�b�^�[
	void SetMove(D3DXVECTOR3 move);

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CHpFream *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	float m_fWidth;		//��
	float m_fHeight;	//����
};

#endif