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
// �O���錾
//--------------------------
class CHp;				//HP�N���X
class CEnemyBullet;		//�G�̒e�N���X
class CExplosion;		//����
class CBarrier;			//�o���A
class CHpFream;			//HP�t���[���N���X

//--------------------------
// �G�l�~�[�N���X
//--------------------------
class CEnemy : public CObject2D
{
public:
	//---------------------------
	// �G�̗񋓌^�̒�`
	//---------------------------
	enum ENEMYTYPE
	{
		ENEMYTYPE_NORMAL = 0,	//���i����G
		ENEMYTYPE_BIG,			//�傫���G
		ENEMYTYPE_HORMING,		//�z�[�~���O���Ă���G
		ENEMYTYPE_BOSS,			//�{�X�G
		ENEMYTYPE_MAX
	};

	CEnemy();			//�R���X�g���N�^
	~CEnemy() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetLife(int nLife);	//�̗͂̐ݒ�
	void SubLife(int nLife);	//�̗͂̌���

	//�Q�b�^�[
	int GetLife();
	int GetRemLife();
	int GetAttack();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);

private:
	void BossAttack();			//�{�X�̍U��

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);
	static const int nShotTime = 50;	//�e�̔��ˎ���

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_targetPos;	//�ړI�̈ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//��]
	int m_nLife;				//�̗�
	int m_nMaxLife;				//�ő�̗�
	int m_nRemLife;				//�c��̗�
	int m_nCntShotTime;			//�e�̔��ˎ��Ԃ𐔂���
	int m_nCntTime;				//�e�N�X�`���؂�ւ����Ԃ̃J�E���g
	int m_nAttack;				//�U����
	int m_nCntAttack;			//�U���^�C�~���O�𐔂���
	float m_fWidth;				//��
	float m_fHeight;			//����
	float m_fTargetRot;			//�v���C���[�܂ł̊p�x
	ENEMYTYPE m_type;			//���

	CHp* m_Hp;					//����
	CEnemyBullet* m_EnemyBullet;//�G�̒e
	CExplosion*		m_pExplosion;//����
	CBarrier*		m_pBarrier;	//�o���A
	CHpFream*	m_pHpFream;		//HP�t���[���N���X
};

#endif // !_PLAYER_H_