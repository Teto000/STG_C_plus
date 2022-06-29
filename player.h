//=====================================
//
// �v���C���[�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �v���C���[�N���X
//--------------------------
class CPlayer : public CObject2D
{
public:
	//---------------------------
	// �v���C���[�\���̂̒�`
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 rot;	//�ړ���
		D3DXCOLOR col;		//�F
		int nLife;			//�̗�
		int nMaxLife;		//�ő�̗�
		int nRemLife;		//�c��̗�
		int nAttack;		//�U����
		float nSpeed;		//���x
		float fWidth;		//��
		float fHeight;		//����
	}Player;

	CPlayer();				//�R���X�g���N�^
	~CPlayer() override;	//�f�X�g���N�^

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
	static CPlayer *Create();
	static void SetCol(D3DXCOLOR col);	//�F�̐ݒ�

private:
	D3DXVECTOR3 OperationPlayer();	//����

private:
	//------------------
	// �萔��`
	//------------------
	static const float fPlayerSpeed;	//�v���C���[�̑��x

	//------------------
	// �����o�ϐ�
	//------------------
	Player m_Player;	//�v���C���[�\����

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_