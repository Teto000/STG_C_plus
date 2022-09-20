//=====================================
//
// �Q�[���w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------
// �C���N���[�h
//--------------------
#include <d3dx9.h>

//-----------------------
// �O���錾
//-----------------------
class CPlayer;	//�v���C���[
class CEnemy;	//�G
class CScore;	//�X�R�A
class CBg;		//�w�i
class CSkill;	//�X�L��

//-------------------------
// �Q�[���N���X�̒�`
//-------------------------
class CGame
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CPlayer	*GetPlayer();	//�v���C���[�̎擾
	static CScore	*GetScore();	//�X�R�A�̎擾
	static CBg		*GetBG();		//�w�i�̎擾

private:
	void SetEnemy();

private:
	//------------------
	// �萔
	//------------------
	static const int nOneSecond = 60;	//��b
	static const int nMaxSkill = 2;		//�X�L���̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	int m_EnemyCnt;
	int m_nTime;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CPlayer	*m_pPlayer;		//�v���C���[�N���X
	static CEnemy	*m_pEnemy;		//�G�N���X
	static CScore	*m_pScore;		//�X�R�A�N���X
	static CBg		*m_pBG;			//�w�i�N���X
	static CSkill	*m_pSkill[nMaxSkill];	//�X�L���N���X
};

#endif // !_APPLICATION_H_