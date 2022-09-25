//=====================================
//
// �Q�[�����[�h�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_	

//--------------------
// �C���N���[�h
//--------------------
#include "object2D.h"

//--------------------
// �O���錾
//--------------------
class CBg;	//�w�i

//----------------------------
// �Q�[�����[�h�N���X�̒�`
//----------------------------
class CGameMode : public CObject
{
public:
	enum GAMEMODE
	{
		GAMEMODE_TIME = 0,	//�^�C���A�^�b�N
		GAMEMODE_SCORE,		//�X�R�A�A�^�b�N
		GAMEMODE_MAX
	};

	CGameMode();	//�R���X�g���N�^
	~CGameMode();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() override;		//�ʒu�̎擾
	float GetWidth() override;				//���̎擾
	float GetHeight() override;				//�����̎擾
	CObject2D* GetObject2D();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CGameMode *Create(D3DXVECTOR3 pos, GAMEMODE mode);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	CObject2D *m_pObject2D;	//�I�u�W�F�N�g2D
	D3DXVECTOR3 m_pos;		//�ʒu
	float m_fWidth;			//��
	float m_fHeight;		//����
	GAMEMODE m_mode;		//���[�h
	CBg*	m_pBg;			//�w�i
};

#endif