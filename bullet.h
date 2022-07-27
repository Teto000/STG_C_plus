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
		BULLETSTATE_MAX
	}BULLETSTATE;

	//---------------------------
	// �e�̍\���̂̒�`
	//---------------------------
	struct Bullet
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 rot;	//��]
		int nLife;			//����
		float fWidth;		//��
		float fHeight;		//����
		BULLETSTATE type;	//���
	};

	CBullet();				//�R���X�g���N�^
	~CBullet() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//�z�[�~���O�e
	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type);
	static void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	//----------------
	// �萔��`
	//----------------
	static const float fBulletSpeed;	//�e�̑��x
	static const int nShotTime = 20;	//�e�̔��ˎ���
	static const int nMaxHoming = 3;	//�z�[�~���O�e���˂̍ő吔

	//----------------
	// �����o�ϐ�
	//----------------s
	Bullet m_Bullet;		//�e�̍\����
	D3DXVECTOR3 m_Tirget;	//�z�[�~���O�ڕW�̈ʒu

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nShotTime;		//�e�̔��ˎ��Ԃ𐔂���
	static int m_nChageTime;	//�e�̃`���[�W����
	static float fBulletSpeed_Homing;	//�e�̑��x
};

#endif // !_BULLET_H_