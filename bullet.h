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
		BULLETSTATE_BEAM,
		BULLETSTATE_CHARGE,
		BULLETSTATE_MAX
	}BULLETSTATE;

	typedef enum
	{
		BULLETGATE_PLAYER = 0,
		BULLETGATE_EQUIP,
		BULLETGATE_MAX
	}BULLETGATE;

	//---------------------------
	// �e�̍\���̂̒�`
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 rot;	//��]
		int nLife;			//����
		float fWidth;		//��
		float fHeight;		//����
		bool bUse;			//�g�p���Ă��邩
		BULLETSTATE type;	//���
		BULLETGATE gate;	//���ˌ�
	}Bullet;

	CBullet();				//�R���X�g���N�^
	~CBullet() override;	//�f�X�g���N�^

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
	static CBullet *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// �萔��`
	//----------------
	static const float fBulletSpeed;	//�e�̑��x

	//----------------
	// �����o�ϐ�
	//----------------
	Bullet m_aBullet;	//�e�̍\����
};

#endif // !_BULLET_H_