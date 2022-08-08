//=====================================
//
// HP�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _HP_H_
#define _HP_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �v���C���[�N���X
//--------------------------
class CHp : public CObject2D
{
public:
	CHp();				//�R���X�g���N�^
	~CHp() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int nLife, int nRemLife);
	void SubHP();	//HP�������̏���
	void SetMove(D3DXVECTOR3 move);		//�ړ��ʂ̐ݒ�

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nLife;		//�̗͎󂯎��p
	int m_nRemLife;		//�c��̗͎󂯎��p
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fLength;	//HP�o�[�̒���
};

#endif // !_HP_H_