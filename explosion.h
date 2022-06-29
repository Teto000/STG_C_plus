//=====================================
//
// �G�N�X�v���[�W�����w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �G�N�X�v���[�W�����N���X
//--------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();			//�R���X�g���N�^
	~CExplosion() override;	//�f�X�g���N�^

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
	static CExplosion *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// �����o�ϐ�
	//----------------

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	int m_nCnterAnim;	//
	int m_nPatternAnim; //
};

#endif // !_EXPLOSION_H_