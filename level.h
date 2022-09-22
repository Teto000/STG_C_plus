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
// �O���錾
//--------------------------
class CExp;		//�o���l

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
	
	int GetLevel();

private:
	void LevelUp();

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxLevel = 5;	//�ő僌�x��

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//��]
	int m_nLevel;		//���x���̒l
	float m_fLength;	//��
	CExp* m_pExp;		//�o���l

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static int m_nExpPoint;		//�o���l�̒l
};

#endif // !_LEVEL_H_