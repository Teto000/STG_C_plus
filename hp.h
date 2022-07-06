//=====================================
//
// HP�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _HP_H_
#define _HP_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �v���C���[�N���X
//--------------------------
class CHp : public CObject2D
{
public:
	//---------------------------
	// HP�񋓌^�̒�`
	//---------------------------
	typedef enum
	{
		HPTYPE_NOMAL = 0,
		HPTYPE_PLAYER,
		HPTYPE_ENEMY,
		HPTYPE_MAX,
	}HPTYPE;

	//---------------------------
	// HP�\���̂̒�`
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		float fWidth;		//��
		float fHeight;		//����
		float fLength;		//HP�o�[�̒���
		HPTYPE type;		//���
	}HP;
	
	CHp();				//�R���X�g���N�^
	~CHp() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Subtract(int nRemLife);	//HP�������̏���

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE type);

private:
	//------------------
	// �萔��`
	//------------------

	//------------------
	// �����o�ϐ�
	//------------------
	HP m_HP;	//HP�\����
	int m_nPlayerLife;	//�v���C���[�̗͎̑󂯎��p
	int m_nEnemyLife;	//�G�l�~�[�̗͎̑󂯎��p

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
};

#endif // !_HP_H_