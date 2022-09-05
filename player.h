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
// �O���錾
//--------------------------
class CHp;		//HP�N���X
class CLevel;	//���x���N���X
class CBullet;	//�e�N���X
class CHpFream;	//HP�t���[���N���X

//--------------------------
// �v���C���[�N���X
//--------------------------
class CPlayer : public CObject2D
{
public:
	enum PLAYERSTATE
	{
		PLAYERSTATE_NORMAL = 0,	//�ʏ�
		PLAYERSTATE_INVINCIBLE,	//���G
		PLAYERSTATE_MAX
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
	void SubLife(int nAttack);	//�̗͂̌���

	//�Q�b�^�[
	int GetLife();
	int GetRemLife();
	int GetAttack();
	PLAYERSTATE GetState();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CPlayer *Create();
	static void SetCol(D3DXCOLOR col);	//�F�̐ݒ�

private:
	D3DXVECTOR3 OperationPlayer();	//����
	void InvincibleTime();			//���G����

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
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//�ړ���
	int m_nLife;			//�̗�
	int m_nMaxLife;			//�ő�̗�
	int m_nRemLife;			//�c��̗�
	int m_nAttack;			//�U����
	int m_nLevel;			//���x��
	int m_nShotTime;		//�e�̔��ˎ���
	int m_nCntShotTime;		//�e�̔��ˎ��Ԃ𐔂���
	int m_nCntInvincible;	//���G���Ԃ𐔂���
	int m_nCntSkill;		//�X�L���̎g�p�\���Ԃ𐔂���
	float m_nSpeed;			//���x
	float m_fWidth;			//��
	float m_fHeight;		//����
	bool m_bSlill;			//�X�L���g�p�\���ǂ���
	PLAYERSTATE m_type;		//���
	CHp* m_Hp;				//HP�N���X
	CLevel* m_Level;		//���x���N���X
	CBullet* m_Bullet;		//�e�N���X
	CHpFream*m_pHpFream;	//HP�t���[���N���X

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_