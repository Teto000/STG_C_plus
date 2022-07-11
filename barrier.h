//=====================================
//
// �o���A�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _BARRIER_H_
#define _BARRIER_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �o���b�g�N���X
//--------------------------
class CBarrier : public CObject2D
{
public:
	//---------------------------
	// �e�̍\���̂̒�`
	//---------------------------
	struct Barrier
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		float fWidth;		//��
		float fHeight;		//����
	};

	CBarrier();				//�R���X�g���N�^
	~CBarrier() override;	//�f�X�g���N�^

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
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight);

private:
	//----------------
	// �����o�ϐ�
	//----------------s
	Barrier m_Barrier;
};

#endif // !_BARRIER_H_