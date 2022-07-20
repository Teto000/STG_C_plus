//=====================================
//
// �o���l�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _EXP_H_
#define _EXP_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �o���l�N���X
//--------------------------
class CExp : public CObject2D
{
public:
	CExp();			//�R���X�g���N�^
	~CExp() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CExp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float m_fLength);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//��]
	float m_fLength;	//���a
};

#endif // !_EXP_H_