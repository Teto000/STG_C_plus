//=====================================
//
// ���U���g�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _RESULT_H_
#define _RESULT_H_	

//--------------------
// �C���N���[�h
//--------------------
#include <d3dx9.h>

//-----------------------
// �O���錾
//-----------------------
class CBg;		//�w�i
class CScore;	//�X�R�A

//-------------------------
// ���U���g�N���X�̒�`
//-------------------------
class CResult
{
public:
	CResult();	//�R���X�g���N�^
	~CResult();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CBg		*GetBG();		//�w�i�̎擾
	static CScore	*GetScore();	//�X�R�A�̎擾

private:
	//------------------
	// �萔
	//------------------
	static const int MaxBg = 2;	//�w�i�̍ő吔

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CBg		*m_pBG[MaxBg];	//�w�i�N���X
	static CScore	*m_pScore;		//�X�R�A�N���X
};

#endif