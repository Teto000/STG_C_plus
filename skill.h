//=====================================
//
// �X�L���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _SKILL_H_
#define _SKILL_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �X�L���N���X
//--------------------------
class CSkill : public CObject2D
{
public:
	//---------------------------
	// �X�L���񋓌^�̒�`
	//---------------------------
	enum SKILLTYPE
	{
		SKILLTYPE_HEAL = 0,			//��
		SKILLTYPE_SPEEDUP_FIRE,		//���ˑ��x����
		SKILLTYPE_ATTACKUP,			//�U���͏㏸
		SKILLTYPE_SPEEDUP,			//���x�㏸
		SKILLTYPE_MAX,
	};

	CSkill();			//�R���X�g���N�^
	~CSkill() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CSkill *Create(SKILLTYPE type);

private:
	//----------------
	// �萔
	//----------------
	static const float nSkillSpeed;
	static const int nMaxTimer = 60;

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nCntTimer;	//�����̕\������
	float m_fWidth;		//��
	float m_fHeight;	//����
	SKILLTYPE m_type;	//���
};

#endif // !_PLAYER_H_