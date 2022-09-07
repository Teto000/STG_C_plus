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
class CGame;		//�Q�[��
class CTitle;		//�^�C�g��
class CResult;		//���U���g
class CSkillSelect;	//�X�L���Z���N�g
class CFade;		//�t�F�[�h

class CRenderer;	//�����_���[
class CInput;		//�C���v�b�g
class CTexture;		//�e�N�X�`��
class CSound;		//�T�E���h

//-------------------------------------
// �A�v���P�[�V�����N���X�̒�`
//-------------------------------------
class CApplication
{
public:
	//--------------------------------
	// �Q�[�����[�h�̗񋓌^�̒�`
	//--------------------------------
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_SKILLSELECT,	//�X�L���Z���N�g
		MODE_FADE,			//�t�F�[�h
		MODE_MAX
	};

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
	static void SetMode(MODE mode);		//���[�h�̐ݒ�
	static MODE GetMode();				//���[�h�̎擾

	static CRenderer *GetRenderer();	//�����_���[�̎擾
	static CInput	 *GetInput();		//�C���v�b�g�̎擾
	static CTexture  *GetTexture();		//�e�N�X�`���̎擾
	static CSound	 *GetSound();		//�T�E���h�̎擾

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CGame*			m_pGame;		//�Q�[���N���X
	static CTitle*			m_pTitle;		//�^�C�g���N���X
	static CResult*			m_pResult;		//���U���g�N���X
	static CSkillSelect*	m_pSkillSelect;	//�X�L���Z���N�g�N���X
	static CFade*			m_pFade;		//�t�F�[�h�N���X
	static MODE				m_mode;			//�Q�[�����[�h

	static CRenderer*		m_pRenderer;	//�����_���[�N���X
	static CInput*			m_pInput;		//�C���v�b�g�N���X
	static CTexture*		m_pTexture;		//�e�N�X�`���N���X
	static CSound*			m_pSound;		//�T�E���h�N���X
};

#endif // !_APPLICATION_H_