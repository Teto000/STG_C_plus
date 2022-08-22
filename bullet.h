//=====================================
//
// �o���b�g�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _BULLET_H_
#define _BULLET_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �o���b�g�N���X
//--------------------------
class CBullet : public CObject2D
{
public:
	//---------------------------
	// �e�̗񋓌^�̒�`
	//---------------------------
	typedef enum
	{
		BULLETSTATE_NORMAL = 0,
		BULLETSTATE_HORMING,
		BULLETSTATE_CHARGE,
		BULLETSTATE_OPTION,
		BULLETSTATE_MAX
	}BULLETSTATE;

	CBullet();				//�R���X�g���N�^
	~CBullet() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	void CollisionBullet();
	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);	//�z�[�~���O�e

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type);
	void ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime);

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxHoming = 3;		//�z�[�~���O�e���˂̍ő吔
	static const int nDefaultLife = 50;		//�e�̎����̊�l
	static const float fBulletSpeed;		//�e�̑��x
	static const float fBulletSpeed_Homing;	//�e�̑��x
	static const float nDefaultSize;		//�e�̑傫���̊�l

	//----------------
	// �����o�ϐ�
	//----------------s
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//��]
	int m_nLife;			//����
	float m_fWidth;			//��
	float m_fHeight;		//����
	BULLETSTATE m_type;		//���
	D3DXVECTOR3 m_Tirget;	//�z�[�~���O�ڕW�̈ʒu

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nChageTime;	//�e�̃`���[�W����
	static int m_nCntHorming;	//�z�[�~���O�e�̔��˃J�E���g

};

#endif // !_BULLET_H_