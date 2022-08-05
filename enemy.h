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

//
//
//
class CHp;

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
		ENEMYTYPE_CURVE,		//�㉺�ɃJ�[�u����G
	};

	//---------------------------
	// �G�̍\���̂̒�`
	//---------------------------
	struct Enemy
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 rot;	//��]
		int nLife;			//�̗�
		int nMaxLife;		//�ő�̗�
		int nRemLife;		//�c��̗�
		float fWidth;		//��
		float fHeight;		//����
		ENEMYTYPE type;		//���
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
	bool IsUsed() override;

	void Destroy();

	void SubLife(int nLife);	//�̗͂̌���

	//�Q�b�^�[
	int GetLife();
	int GetRemLife();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);

	//----------------
	// �����o�ϐ�
	//----------------
	Enemy m_Enemy;
	CHp* m_Hp;
	int m_CntTime;	//�e�N�X�`���؂�ւ����Ԃ̃J�E���g
};

#endif // !_PLAYER_H_