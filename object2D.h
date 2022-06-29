//=====================================
//
// �I�u�W�F�N�g2D�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "texture.h"

//--------------------------------
// �I�u�W�F�N�g2D�N���X�̒�`
//--------------------------------
class CObject2D : public CObject
{
public:
	CObject2D();					//�R���X�g���N
	virtual ~CObject2D() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	
	D3DXVECTOR3 AddMove(D3DXVECTOR3 move);		//�ړ��ʂ̉��Z

	//�Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos);			//�ʒu�̐ݒ�
	void SetSize(float fWidth, float fHeight);	//�傫���̐ݒ�
	void SetTexCIE(float left, float fRight);	//�e�N�X�`�����W�̐ݒ�
	void SetTexture(CTexture::TEXTURE texture);	//�e�N�X�`���̐ݒ�
	void SetColor(D3DXCOLOR col);				//�F�̐ݒ�

	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() override;		//�ʒu�̎擾
	float GetWidth() override;				//���̎擾
	float GetHeight() override;				//�����̎擾

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fRot;		//��]�p�x
	float m_fScal;		//�傫��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::TEXTURE m_texture;		//�e�N�X�`��
};

#endif // !_OBJECT_H_