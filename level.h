//=====================================
//
// ���x���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _LEVEL_H_
#define _LEVEL_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// ���x���N���X
//--------------------------
class CLevel : public CObject2D
{
public:
	CLevel();			//�R���X�g���N�^
	~CLevel() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CLevel *Create();
	static void AddExp(int nValue);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//��]
	float m_fLength;	//��

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static int m_nValue;	//�l
};

#endif // !_LEVEL_H_