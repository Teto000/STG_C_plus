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
	//---------------------------
	// �����\���̂̒�`
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXCOLOR col;		//�F
		int nLife;			//����
		float fWidth;		//��
		float fHeight;		//����
	}Explosion;

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
	Explosion m_Explosion;	//�����\����

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
};

#endif // !_EXPLOSION_H_