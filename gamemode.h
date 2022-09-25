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

//----------------------------
// �Q�[�����[�h�N���X�̒�`
//----------------------------
class CGameMode : public CObject2D
{
public:
	CGameMode();	//�R���X�g���N�^
	~CGameMode();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CGameMode *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	float m_fWidth;		//��
	float m_fHeight;	//����
};

#endif