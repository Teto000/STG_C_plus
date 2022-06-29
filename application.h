//=====================================
//
// �A�v���P�[�V�����w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_	

//--------------------
// �C���N���[�h
//--------------------
#include <d3dx9.h>

//-----------------------
// �O���錾
//-----------------------
class CRenderer;	//�����_���[
class CInput;		//�C���v�b�g
class CPlayer;		//�v���C���[

//-------------------------------------
// �A�v���P�[�V�����N���X�̒�`
//-------------------------------------
class CApplication
{
public:
	CApplication();		//�R���X�g���N�^
	~CApplication();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CRenderer *GetRenderer();	//�����_���[�̎擾
	static CInput	 *GetInput();		//�C���v�b�g�̎擾

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CRenderer	*m_pRenderer;	//�����_���[�N���X
	static CInput		*m_pInput;		//�C���v�b�g�N���X
	static CPlayer		*m_pPlayer;		//�v���C���[�N���X
};

#endif // !_APPLICATION_H_