//=====================================
//
// �G�̒e�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �o���b�g�N���X
//--------------------------
class CEnemyBullet : public CObject2D
{
public:
	CEnemyBullet();				//�R���X�g���N�^
	~CEnemyBullet() override;	//�f�X�g���N�^

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
	static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nAttack);

private:
	void CollisionEnemyBullet();	//������������

private:
	//----------------
	// �����o�ϐ�
	//----------------s
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//��]
	int m_nEnemyAttack;		//�G�̍U����
	float m_fWidth;			//��
	float m_fHeight;		//����
};

#endif // !_BULLET_H_