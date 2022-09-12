//=====================================
//
// �A�C�e���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _ITEM_H_
#define _ITEM_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �A�C�e���N���X
//--------------------------
class CItem : public CObject2D
{
public:
	enum ITEMTYPE
	{
		ITEMTYPE_HPHEAL = 0,	//HP��
		ITEMTYPE_MPHEAL,		//MP��
		ITEMTYPE_MAX
	};

	CItem();			//�R���X�g���N�^
	~CItem() override;	//�f�X�g���N�^

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
	static CItem *Create(D3DXVECTOR3 pos, ITEMTYPE type);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//��]
	int m_nLife;			//����
	float m_fWidth;			//��
	float m_fHeight;		//����
	ITEMTYPE m_type;		//���
};

#endif // !_BULLET_H_