//=====================================
//
// �t�F�[�h�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _FADE_H_
#define _FADE_H_	

//--------------------
// �C���N���[�h
//--------------------
#include <d3dx9.h>
#include "object.h"
#include "application.h"
#include "object2D.h"

//-------------------------
// �^�C�g���N���X�̒�`
//-------------------------
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX
	};

	CFade();	//�R���X�g���N�^
	~CFade();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(CApplication::MODE modeNext);
	void Uninit();
	void Update();
	void Draw();
	void SetFade(CApplication::MODE modeNext);
	FADE GetFade(void);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	FADE	  m_fade;	//�t�F�[�h�̏��
	D3DXCOLOR m_col;	//�|���S��(�t�F�[�h)�̐F
	CApplication::MODE m_modeNext;	//���̉��(���[�h)
};

#endif