//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "texture.h"
#include "renderer.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/Player.png",		//�v���C���[

	/* ���@�G�l�~�[�@���@*/
	"data/TEXTURE/Enemy/Bird.png",		//�G(��)
	"data/TEXTURE/Enemy/Red.png",		//�G(��)
	"data/TEXTURE/Enemy/Blue.png",		//�G(��)
	"data/TEXTURE/Enemy/Green.png",		//�G(��)
	"data/TEXTURE/Enemy/Pink.png",		//�G(��)
	"data/TEXTURE/Enemy/Big2.png",		//�傫���G

	/* �� �Q�[�� ���@*/
	"data/TEXTURE/Game/Bullet.png",		//�e
	"data/TEXTURE/Game/EnemyBullet.png",//�G�̒e
	"data/TEXTURE/Game/HitEffect.png",	//�n�[�g
	"data/TEXTURE/Game/Effect.jpg",		//�G�t�F�N�g
	"data/TEXTURE/Game/Barrier.png",	//�o���A

	/* �� BG ���@*/
	"data/TEXTURE/BG/Game.png",			//�w�i
	"data/TEXTURE/BG/Title.png",		//�^�C�g����ʂ̔w�i
	"data/TEXTURE/BG/TitleLogo.png",	//�^�C�g�����S
	"data/TEXTURE/BG/PressEnter.png",	//�v���X�G���^�[
	"data/TEXTURE/BG/TimeAttack.png",	//�^�C���A�^�b�N
	"data/TEXTURE/BG/ScoreAttack.png",	//�X�R�A�A�^�b�N
	"data/TEXTURE/BG/Result.png",		//���U���g��ʂ̔w�i
	"data/TEXTURE/BG/ResultText.png",	//���U���g��ʂ̕���

	/* �� UI ���@*/
	"data/TEXTURE/UI/Exp.png",			//�o���l
	"data/TEXTURE/UI/Level.png",		//���x��
	"data/TEXTURE/UI/HPFream.png",		//HP�o�[�̃t���[��

	/* �� �X�L�� ���@*/
	"data/TEXTURE/Skill/HPheal.png",		//�X�L��(�̗͉�)
	"data/TEXTURE/Skill/SpeedUp_Fire.png",	//�X�L��(�e������)
	"data/TEXTURE/Skill/AttackUp.png",		//�X�L��(�U���͏㏸)
	"data/TEXTURE/Skill/SpeedUp.png",		//�X�L��(���x�㏸)

	/* �� ���� ���@*/
	"data/TEXTURE/Number.png",		//����
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
