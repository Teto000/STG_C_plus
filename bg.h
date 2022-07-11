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
	static CBg *Create();

private:
	//----------------
	// �����o�ϐ�
	//----------------
	CObject2D *m_pObject2D;		//�I�u�W�F�N�g2D
	D3DXVECTOR3 m_pos;			//�ʒu
	float m_fWidth;				//��
	float m_fHeight;			//����
};

#endif // !_BG_H_