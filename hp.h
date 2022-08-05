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
	
	CHp();				//�R���X�g���N�^
	~CHp() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int nLife, int nRemLife);
	void SubHP();	//HP�������̏���

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE typez);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nLife;		//�̗͎󂯎��p
	int m_nRemLife;		//�c��̗͎󂯎��p
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fLength;	//HP�o�[�̒���
	HPTYPE m_type;		//���
};

#endif // !_HP_H_