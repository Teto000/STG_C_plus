//=====================================
//
// �G�l�~�[�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _ENEMY_H_
#define _ENEMY_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �G�l�~�[�N���X
//--------------------------
class CEnemy : public CObject2D
{
public:
	CEnemy();			//�R���X�g���N�^
	~CEnemy() override;	//�f�X�g���N�^

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
	static CEnemy *Create();

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_CntTime;	//�e�N�X�`���؂�ւ����Ԃ̃J�E���g
};

#endif // !_PLAYER_H_