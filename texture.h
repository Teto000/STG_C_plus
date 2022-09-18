//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_PLAYER = 0,			//�v���C���[

		/* ���@�G�l�~�[�@���@*/
		TEXTURE_ENEMY_BIRD,			//�G(��)
		TEXTURE_ENEMY_RED,			//�G(��)
		TEXTURE_ENEMY_BLUE,			//�G(��)
		TEXTURE_ENEMY_GREEN,		//�G(��)
		TEXTURE_ENEMY_PINK,			//�G(��)

		/* �� �Q�[�� ��*/
		TEXTURE_BULLET,				//�e
		TEXTURE_EXPLOSION,			//����
		TEXTURE_RING,				//��
		TEXTURE_EFFECT,				//�G�t�F�N�g
		TEXTURE_BARRIER,			//�o���A

		/* �� BG ��*/
		TEXTURE_BG_GAME,			//�Q�[����ʂ̔w�i
		TEXTURE_BG_TITLE,			//�^�C�g����ʂ̔w�i
		TEXTURE_BG_RESULT,			//���U���g��ʂ̔w�i
		TEXTURE_BG_SKILLSELECT,		//�X�L���Z���N�g��ʂ̔w�i

		/* �� UI ��*/
		TEXTURE_EXP,				//�o���l
		TEXTURE_LEVEL,				//���x��
		TEXTURE_HPFREAM,			//HP�o�[�̃t���[��

		/* �� �X�L�� ��*/
		TEXTURE_SKILL_HPHEAL,		//�X�L��(�̗͉�)
		TEXTURE_SKILL_SPEEDUP_FIRE,	//�X�L��(�e������)

		/* �� ���� ��*/
		TEXTURE_NUMBER,				//����

		TEXTURE_MAX,
		TEXTURE_NONE,			//�g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
