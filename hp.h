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
	struct HP
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 move;	//�ړ���
		int nLife;			//�̗͎󂯎��p
		int nRemLife;		//�c��̗͎󂯎��p
		float fWidth;		//��
		float fHeight;		//����
		float fLength;		//HP�o�[�̒���
		HPTYPE type;		//���
	};
	
	CHp();				//�R���X�g���N�^
	~CHp() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SubHP(int nLife, int nRemLife);	//HP�������̏���

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE typez);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	HP m_HP;	//HP�\����
};

#endif // !_HP_H_