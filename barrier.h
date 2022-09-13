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
#include "bullet.h"

//--------------------------
// �o���b�g�N���X
//--------------------------
class CBarrier : public CObject2D
{
public:
	enum BARRIERTYPE
	{
		BARRIERTYPE_PLAYER = 0,
		BARRIERTYPE_ENEMY,
		BARRIERTYPE_MAX
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

	void SubLife(CBullet::BULLETTYPE type);

	//�Q�b�^�[
	CBarrier::BARRIERTYPE GetType();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
							float fWidth, float fHeight, BARRIERTYPE type);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_playermove;	//�v���C���[�̈ړ���
	int m_nLife;				//�̗�
	float m_fWidth;				//��
	float m_fHeight;			//����
	BARRIERTYPE m_type;			//���
};

#endif // !_BARRIER_H_