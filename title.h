//=====================================
//
// �^�C�g���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _TITLE_H_
#define _TITLE_H_	

//--------------------
// �C���N���[�h
//--------------------
#include <d3dx9.h>

//-----------------------
// �O���錾
//-----------------------
class CBg;			//�w�i
class CGameMode;	//�Q�[�����[�h

//-------------------------
// �^�C�g���N���X�̒�`
//-------------------------
class CTitle
{
public:
	CTitle();	//�R���X�g���N�^
	~CTitle();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CBg	*GetBG();	//�w�i�̎擾

private:
	void SelectMode();
	void ChangeNumber();

private:
	//------------------
	// �萔
	//------------------
	static const int MaxBg = 3;		//�w�i�̍ő吔
	static const int MaxMode = 2;	//���[�h�̍ő吔
	static const int AnimationTime = 80;

	//------------------
	// �����o�ϐ�
	//------------------
	int nCntTime;			//�A�j���[�V�����J�E���g
	int nNumber;			//�I�𒆂̔ԍ�
	bool m_bPressEneter;	//�G���^�[�L�[�������ꂽ��

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CBg		 *m_pBG[MaxBg];			//�w�i�N���X
	static CGameMode *m_pGameMode[MaxMode];	//�Q�[�����[�h�N���X
};

#endif