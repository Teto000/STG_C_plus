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
	struct Player
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
	};

	CPlayer();				//�R���X�g���N�^
	~CPlayer() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSkill();

	//�Q�b�^�[
	int GetLife();
	int GetRemLife();
	int GetAttack();

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
	static const float fPlayerSpeed;		//�v���C���[�̑��x
	static const int nPlayerLife = 300;		//�v���C���[�̗̑�
	static const int nMaxLife = 100;		//�ő�̗�(%)

	//------------------
	// �����o�ϐ�
	//------------------
	Player m_Player;	//�v���C���[�\����
	int m_nShotTime;	//�e�̔��ˎ��Ԃ𐔂���

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static int nShotTime;	//�e�̔��ˎ���
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_