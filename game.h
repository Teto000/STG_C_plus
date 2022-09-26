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
#include "application.h"

//-----------------------
// �O���錾
//-----------------------
class CPlayer;	//�v���C���[
class CEnemy;	//�G
class CScore;	//�X�R�A
class CBg;		//�w�i
class CSkill;	//�X�L��
class CTimer;	//�^�C��

//-------------------------
// �Q�[���N���X�̒�`
//-------------------------
class CGame
{
public:
	enum MODE
	{
		MODE_TIME = 0,	//�^�C���A�^�b�N
		MODE_SCORE,		//�X�R�A�A�^�b�N
		MODE_MAX
	};

	enum EnemyName
	{
		NORMAL = 0,	//�ʏ�G
		HORMING,	//�z�[�~���O
		HPITEM,		//HP�A�C�e��
		MPITEM,		//MP�A�C�e��
		BIG,		//�傫���G
		MAX
	};

	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	void SetMode(CApplication::GAMEMODE mode);

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CPlayer	*GetPlayer();	//�v���C���[�̎擾
	static CScore	*GetScore();	//�X�R�A�̎擾
	static CBg		*GetBG();		//�w�i�̎擾
	static CTimer	*GetTimer();	//���Ԃ̎擾

	static void SetMode(MODE mode);

private:
	void AppearEnemy();
	void SetEnemy(float X, float Y, EnemyName type);

private:
	//------------------
	// �萔
	//------------------
	static const int nOneSecond = 60;	//��b
	static const int nMaxBg = 3;		//�w�i�̍ő吔
	static const int nMaxSkill = 4;		//�X�L���̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	int m_EnemyCnt;
	int m_nTime;
	int m_nSkillTime[nMaxSkill];
	bool m_bSkill[nMaxSkill];
	EnemyName m_type;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CPlayer	*m_pPlayer;				//�v���C���[�N���X
	static CEnemy	*m_pEnemy;				//�G�N���X
	static CScore	*m_pScore;				//�X�R�A�N���X
	static CBg		*m_pBG[nMaxBg];			//�w�i�N���X
	static CSkill	*m_pSkill[nMaxSkill];	//�X�L���N���X
	static CTimer	*m_pTimer;				//�^�C�}�[�N���X

	static MODE m_mode;
};

#endif