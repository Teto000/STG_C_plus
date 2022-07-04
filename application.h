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
class CTexture;		//�e�N�X�`��
class CSound;		//�T�E���h
class CPlayer;		//�v���C���[
class CEnemy;		//�G
class CScore;		//�X�R�A

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
	static CTexture  *GetTexture();		//�e�N�X�`���̎擾
	static CSound	 *GetSound();		//�T�E���h�̎擾
	static CPlayer	 *GetPlayer();		//�v���C���[�̎擾

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CRenderer	*m_pRenderer;	//�����_���[�N���X
	static CInput		*m_pInput;		//�C���v�b�g�N���X
	static CTexture		*m_pTexture;	//�e�N�X�`���N���X
	static CSound		*m_pSound;		//�T�E���h�N���X
	static CPlayer		*m_pPlayer;		//�v���C���[�N���X
	static CEnemy		*m_pEnemy;		//�G�N���X
	static CScore		*m_pScore;		//�X�R�A�N���X
};

#endif // !_APPLICATION_H_