//=====================================
//
// �w�i�̃w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _BG_H_
#define _BG_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �o���b�g�N���X
//--------------------------
class CBg : public CObject
{
public:
	enum BGTYPE
	{
		BGTYPE_GAME = 0,	//�Q�[�����
		BGTYPE_TITLE,		//�^�C�g�����
		BGTYPE_RESULT,		//���U���g���
		BGTYPE_MAX
	};

	CBg();				//�R���X�g���N�^
	~CBg() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() override;		//�ʒu�̎擾
	float GetWidth() override;				//���̎擾
	float GetHeight() override;				//�����̎擾

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CBg *Create(D3DXVECTOR3 pos, BGTYPE type);

private:
	//----------------
	// �����o�ϐ�
	//----------------
	CObject2D *m_pObject2D;		//�I�u�W�F�N�g2D
	D3DXVECTOR3 m_pos;			//�ʒu
	float m_fWidth;				//��
	float m_fHeight;			//����
	BGTYPE m_type;				//���
};

#endif // !_BG_H_