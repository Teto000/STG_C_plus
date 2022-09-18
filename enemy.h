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
class CItem;			//�A�C�e���N���X

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
		ENEMYTYPE_HORMING,		//�z�[�~���O���Ă���G
		ENEMYTYPE_HPITEM,		//HP�񕜃A�C�e���𗎂Ƃ��G
		ENEMYTYPE_MPITEM,		//MP�񕜃A�C�e���𗎂Ƃ��G
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
	D3DXVECTOR3 GetMove();
	int GetLife();
	int GetRemLife();
	int GetAttack();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);

private:
	void Animation();					//�e�N�X�`���A�j���[�V����
	void Move();						//�ړ�����
	void CntAttack();					//�U���܂ł̎��Ԃ𐔂���
	void Attack();						//�U������
	void BossAttack(D3DXVECTOR2 vec);	//�{�X�G�̍U��
	bool Destroy();						//�����鏈��
	D3DXVECTOR3 Homing(float& posX, float& posY,
					float& moveX, float& moveY);	//�z�[�~���O�e

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);
	static const int nShotTime = 100;	//�e�̔��ˎ���
	static const float fBulletSpeed_Homing;	//�z�[�~���O�e�̑��x

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_Tirget;			//�z�[�~���O�ڕW�̈ʒu
	D3DXVECTOR3 m_targetPos;		//�ړI�̈ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rot;				//��]
	int m_nLife;					//�̗�
	int m_nMaxLife;					//�ő�̗�
	int m_nRemLife;					//�c��̗�
	int m_nCntShotTime;				//�e�̔��ˎ��Ԃ𐔂���
	int m_nCntTime;					//�e�N�X�`���؂�ւ����Ԃ̃J�E���g
	int m_nAttack;					//�U����
	int m_nCntHorming;				//�z�[�~���O���Ԃ̃J�E���g
	float m_fWidth;					//��
	float m_fHeight;				//����
	float m_fTargetRot;				//�v���C���[�܂ł̊p�x
	float m_fChangeAngle;			//�ϓ�����ړ���
	bool m_bChangeAttack;			//�U���ω����邩�ǂ���
	ENEMYTYPE m_type;				//���

	CHp* m_pHp;						//����
	CEnemyBullet*	m_pEnemyBullet;	//�G�̒e
	CExplosion*		m_pExplosion;	//����
	CBarrier*		m_pBarrier;		//�o���A
	CHpFream*		m_pHpFream;		//HP�t���[���N���X
	CItem*			m_pItem;		//�A�C�e���N���X
};

#endif // !_ENEMY_H_