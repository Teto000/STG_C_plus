//=====================================
//
// MP�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _MP_H_
#define _MP_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// MP�N���X
//--------------------------
class CMp : public CObject2D
{
public:
	CMp();				//�R���X�g���N�^
	~CMp() override;	//�f�X�g���N�^

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
	static CMp *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fLength;	//HP�o�[�̒���
};

#endif