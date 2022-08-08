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

//--------------------------
// �v���C���[�N���X
//--------------------------
class CPlayer : public CObject2D
{
public:
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
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_rot;	//�ړ���
	int m_nLife;		//�̗�
	int m_nMaxLife;		//�ő�̗�
	int m_nRemLife;		//�c��̗�
	int m_nAttack;		//�U����
	int m_nShotTime;	//�e�̔��ˎ���
	int m_nCntShotTime;	//�e�̔��ˎ��Ԃ𐔂���
	float m_nSpeed;		//���x
	float m_fWidth;		//��
	float m_fHeight;	//����
	CHp* m_Hp;			//HP�N���X
	CLevel* m_Level;	//���x���N���X

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_