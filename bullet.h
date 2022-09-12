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
// �O���錾
//--------------------------
class CExplosion;	//����
class CDamage;		//�_���[�W

//--------------------------
// �o���b�g�N���X
//--------------------------
class CBullet : public CObject2D
{
public:
	//---------------------------
	// �e�̗񋓌^�̒�`
	//---------------------------
	enum BULLETTYPE
	{
		BULLETTYPE_NORMAL = 0,
		BULLETTYPE_HORMING,
		BULLETTYPE_CHARGE,
		BULLETTYPE_OPTION,
		BULLETTYPE_MAX
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

	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);	//�z�[�~���O�e
	
	//�Z�b�^�[
	void SetBulletSize(float fLength);

	//�Q�b�^�[
	BULLETTYPE GetType();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);
	void ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime);

private:
	void CollisionBullet(CObject::EObjType ObjType);	//������������

private:
	//----------------
	// �萔��`
	//----------------
	static const int nMaxHoming = 3;		//�z�[�~���O�e���˂̍ő吔
	static const int nDefaultLife = 80;		//�e�̎����̊�l
	static const float fBulletSpeed;		//�e�̑��x
	static const float fBulletSpeed_Homing;	//�z�[�~���O�e�̑��x
	static const float nDefaultSize;		//�e�̑傫���̊�l

	//----------------
	// �����o�ϐ�
	//----------------s
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_Tirget;	//�z�[�~���O�ڕW�̈ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//��]
	int m_nLife;			//����
	int m_nPlayerAttack;	//�v���C���[�̍U����
	float m_fWidth;			//��
	float m_fHeight;		//����
	BULLETTYPE m_type;		//���
	CExplosion* pExplosion;	//����
	CDamage*	pDamage;	//�_���[�W

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nChageTime;	//�e�̃`���[�W����
	static int m_nCntHorming;	//�z�[�~���O�e�̔��˃J�E���g

};

#endif // !_BULLET_H_