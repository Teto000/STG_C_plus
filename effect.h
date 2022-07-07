//=====================================
//
// �G�t�F�N�g�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _EFFECT_H_
#define _EFFECT_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �G�l�~�[�N���X
//--------------------------
class CEffect : public CObject2D
{
public:
	//--------------------------
	// �G�t�F�N�g�\���̂̒�`
	//--------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXCOLOR col;		//�F
		float fRadius;		//���a(�傫��)
	}Effect;

	CEffect();				//�R���X�g���N�^
	~CEffect() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CEffect *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	Effect m_Effect;	//�G�t�F�N�g�\����
};

#endif // !_EFFECT_H_