//===================================
//
// �G�l�~�[�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "enemy.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "object2D.h"
#include "input_keybord.h"
#include "sound.h"
#include "bullet.h"
#include "texture.h"
#include "hp.h"
#include "barrier.h"
#include "explosion.h"
#include "level.h"
#include "score.h"
#include "enemybullet.h"
#include "game.h"
#include "player.h"
#include "hpfream.h"
#include "item.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CEnemy::fBulletSpeed_Homing = 1.01f;	//�e�̑��x(�z�[�~���O)
int CEnemy::m_nLevel = 1;	//���x��

//===========================
// �R���X�g���N�^
//===========================
CEnemy::CEnemy() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ڕW�ʒu
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_rot = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//��]
	m_nLife = 0;				//�̗�
	m_nMaxLife = 0;				//�ő�̗�
	m_nRemLife = 0;				//�c��̗�
	m_nAttack = 0;				//�U����
	m_nCntHorming = 0;			//�z�[�~���O���Ԃ̃J�E���g
	m_fWidth = 0.0f;			//��
	m_fHeight = 0.0f;			//����
	m_fTargetRot = 0.0f;		//�v���C���[�܂ł̊p�x
	m_fChangeAngle = 0.0f;		//�ϓ�����ړ���
	m_fTexLeft = 0.0f;			//�e�N�X�`�����W����
	m_fTexRight = 0.0f;			//�e�N�X�`�����W�E��
	m_bChangeAttack = false;	//�U���ω�
	m_type = ENEMYTYPE_MAX;		//���
	m_pHp = nullptr;			//HP�o�[
	m_pEnemyBullet = nullptr;	//�G�̒e
	m_pExplosion = nullptr;		//����
	m_pBarrier = nullptr;		//�o���A
	m_pHpFream = nullptr;		//HP�t���[��
	m_pItem = nullptr;			//�A�C�e��
}

//===========================
// �f�X�g���N�^
//===========================
CEnemy::~CEnemy()
{

}

//===========================
// ������
//===========================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	//�����l�̐ݒ�
	m_pos = pos;					//�ʒu
	m_nRemLife = 100;				//�c��̗�
	m_fWidth = 80.0f;				//��
	m_fHeight = 80.0f;				//����
	m_fTexRight = 1.0f;				//�e�N�X�`�����W�E��	

	CObject2D::Init(m_pos);

	//-------------------------------
	// �G�̎�ނ��Ƃ̏���ݒ�
	//-------------------------------
	switch (m_type)
	{
	//�ʏ�̓G
	case ENEMYTYPE_NORMAL:
		m_move.x = -2.0f;			//�ړ���
		SetLife(50 * m_nLevel);		//�̗�
		m_nAttack = 10 * m_nLevel;	//�U����
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_RED);	//�e�N�X�`���̐ݒ�
		break;

	//�z�[�~���O����G
	case ENEMYTYPE_HORMING:
		SetLife(100 * m_nLevel);		//�̗�
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BLUE);	//�e�N�X�`���̐ݒ�
		break;

	case ENEMYTYPE_HPITEM:
		m_move.x = -3.0f;	//�ړ���
		SetLife(100 * m_nLevel);		//�̗�
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_GREEN);	//�e�N�X�`���̐ݒ�
		break;

	case ENEMYTYPE_MPITEM:
		m_move.x = -3.0f;	//�ړ���
		SetLife(100 * m_nLevel);		//�̗�
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_PINK);	//�e�N�X�`���̐ݒ�
		break;

	case ENEMYTYPE_BIG:
		m_fTexRight = 0.5f;
		m_nAttack = 20 * m_nLevel;	//�U����
		m_move.x = -2.0f;			//�ړ���
		m_fWidth = 200.0f;			//��
		m_fHeight = 200.0f;			//����
		SetLife(250 * m_nLevel);	//�̗�
		CObject2D::SetTexture(CTexture::TEXTURE_ENEMY_BIG);	//�e�N�X�`���̐ݒ�
		break;

	default:
		break;
	}

	CObject2D::SetTexCIE(m_fTexLeft, m_fTexRight);	//�e�N�X�`�����W�ݒ�
	CObject2D::SetSize(m_fWidth, m_fHeight);		//�T�C�Y�̐ݒ�

	//--------------------------
	// HP�̕\��
	//--------------------------
	{
		//HP�̈ʒu��ݒ�
		D3DXVECTOR3 hpPos(m_pos.x, m_pos.y - (m_fHeight / 2 + 20.0f), m_pos.z);

		m_pHp = CHp::Create(hpPos, m_fWidth, 10.0f);//HP�̐���
		m_pHp->SetLife(m_nLife, m_nRemLife);		//HP�ɑ̗͂�ݒ�
		m_pHp->SetMove(m_move);						//HP�Ɉړ��ʂ�ݒ�
	}

	//--------------------------
	// �o���A�̐���
	//--------------------------
	/*{
		int nData = rand() % 9;

		if (nData == 0)
		{//�{�X�ȊO�̓G ���� �����_���Ȓl��1�̎�
			//�o���A�̐���
			m_pBarrier->Create(m_pos, m_move, m_fWidth, m_fHeight, CBarrier::BARRIERTYPE_ENEMY);
		} 
	}*/

	return S_OK;
}

//===========================
// �I��
//===========================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// �X�V
//===========================
void CEnemy::Update()
{
	CObject2D::Update();

	//--------------------------
	// �e�N�X�`���A�j���[�V����
	//--------------------------
	Animation();

	//--------------------------
	// �ړ�����
	//--------------------------
	Move();

	//--------------------------
	// �U������
	//--------------------------
	CntAttack();

	//--------------------
	// ��ʒ[�̐ݒ�
	//--------------------
	CObject2D::SetScreenY(m_pos.y, 0.0f + 200.0f, SCREEN_HEIGHT - 140.0f);

	//--------------------------
	// �����鏈��
	//--------------------------
	if (Destroy())
	{
		//�G�̏���
		Uninit();
		return;
	}
}

//===========================
// �`��
//===========================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//===========================
// ����
//===========================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	//----------------------------------
	// �G�̐����Ə�����
	//----------------------------------
	pEnemy = new CEnemy;	//����

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pEnemy->m_type = type;

		//������
		pEnemy->Init(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
	}

	return pEnemy;
}

//=======================
// ���x���A�b�v
//=======================
void CEnemy::AddLevel()
{
	m_nLevel++;
}

//============================
// �e�N�X�`���A�j���[�V����
//============================
void CEnemy::Animation()
{
	switch (m_type)
	{
	case ENEMYTYPE_BIG:
		//�e�N�X�`���؂�ւ����Ԃ̉��Z
		m_nCntTime++;
		m_nCntTime %= 80;	//���Z�b�g

		if (m_nCntTime % 40 == 0)
		{
			m_fTexLeft += 0.5f;
			m_fTexRight += 0.5f;

			//�e�N�X�`�����W�̐ݒ�
			CObject2D::SetTexCIE(m_fTexLeft, m_fTexRight);
		}
		break;

	default:
		break;
	}
}

//=======================
// �ړ�����
//=======================
void CEnemy::Move()
{
	switch (m_type)
	{
	/* �� �ʏ�̓G �� */
	case ENEMYTYPE_NORMAL:
		//�㉺�ړ�
		m_fChangeAngle += 0.01f;	//�p�x�̉��Z
		m_move.y = sinf(D3DX_PI * m_fChangeAngle);	//�㉺�̈ړ��ʂ��v�Z
		break;

	/* �� �z�[�~���O����G �� */
	case ENEMYTYPE_HORMING:
		m_nCntHorming++;	//�z�[�~���O���Ԃ̃J�E���g

		if (m_nCntHorming <= 200)
		{//�J�E���g��200�ȉ��Ȃ�
			//�v���C���[�̈ʒu���擾
			m_Tirget = CGame::GetPlayer()->GetPosition();

			//�z�[�~���O�̈ړ��ʂ��擾
			m_move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
		}
		break;

	case ENEMYTYPE_HPITEM:
		break;

	case ENEMYTYPE_MPITEM:
		break;

	case ENEMYTYPE_BIG:
		//�㉺�ړ�
		m_fChangeAngle += 0.01f;	//�p�x�̉��Z
		m_move.y = sinf(D3DX_PI * m_fChangeAngle);	//�㉺�̈ړ��ʂ��v�Z
		break;

	default:
		break;
	}

	m_pos = CObject2D::AddMove(m_move);	//�G�̈ړ�
	m_pHp->SetMove(m_move);				//HP�o�[�̈ړ��ʂ̐ݒ�
}

//=======================
// �U���܂ł̎��Ԃ𐔂���
//=======================
void CEnemy::CntAttack()
{
	//�J�E���g�̉��Z
	m_nCntShotTime++;
	m_nCntShotTime %= nShotTime;

	//----------------------------
	// �J�E���g��0�ɂȂ�����
	//----------------------------
	if (m_nCntShotTime == 0)
	{
		//�U������
		Attack();
	}
}

//=======================
// �U������
//=======================
void CEnemy::Attack()
{
	//-------------------------------
	// �v���C���[�̈ʒu��ۑ�
	//-------------------------------
	if (CGame::GetPlayer()->GetLife() > 0)
	{//�v���C���[�������Ă���Ȃ�
		m_targetPos = CGame::GetPlayer()->GetPosition();
	}

	//�v���C���[�܂ł̊p�x
	D3DXVECTOR2 vec = m_pos - m_targetPos;
	D3DXVec2Normalize(&vec, &vec);

	//-------------------------------
	// �U��
	//-------------------------------
	switch (m_type)
	{
		/* �� �ʏ�̓G �� */
	case ENEMYTYPE_NORMAL:
	{
		D3DXVECTOR3 pos(m_pos.x - m_fWidth / 2, m_pos.y, m_pos.z);
		m_pEnemyBullet->Create(pos, D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nAttack);
	}
		break;

		/* �� �傫���G �� */
	case ENEMYTYPE_BIG:
		for (int i = 0; i < 3; i++)
		{
			D3DXVECTOR3 move(-vec.x * 4.0f, -vec.y * (i + 1), 0.0f);
			m_pEnemyBullet->Create(m_pos, move, m_nAttack);
		}
		break;

	default:
		break;
	}

	//�T�E���h�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_SE_ENEMYATTACK);
}

//=======================
// �����鏈��
//=======================
bool CEnemy::Destroy()
{
	//--------------------------
	// �̗͂��s����
	//--------------------------
	if (m_nLife <= 0)
	{
		CLevel::AddExp(5 * m_nLevel);	//�o���l�̎擾
		//m_pExplosion->Create(m_pos);	//�����̐���

		switch (m_type)
		{
		case ENEMYTYPE_NORMAL:
			CScore::AddScore(100 * m_nLevel);			//�X�R�A�̉��Z
			break;

		case ENEMYTYPE_HORMING:
			CScore::AddScore(150 * m_nLevel);
			break;

		case ENEMYTYPE_HPITEM:
			//�A�C�e���̐���
			m_pItem = CItem::Create(m_pos, CItem::ITEMTYPE_HPHEAL);
			CScore::AddScore(100 * m_nLevel);
			break;

		case ENEMYTYPE_MPITEM:
			//�A�C�e���̐���
			m_pItem = CItem::Create(m_pos, CItem::ITEMTYPE_MPHEAL);
			CScore::AddScore(100 * m_nLevel);
			break;

		case ENEMYTYPE_BIG:
			CLevel::AddExp(10 * m_nLevel);	//�o���l�̎擾
			CScore::AddScore(300 * m_nLevel);
			break;

		default:
			break;
		}

		return true;
	}

	//--------------------------
	// ��ʊO�ɏo��
	//--------------------------
	if (m_pos.x <= 0.0f || m_pos.y <= 0.0f || m_pos.y >= SCREEN_HEIGHT)
	{
		return true;
	}

	//--------------------------
	// ����
	//--------------------------
	if (CObject2D::GetCollision(OBJTYPE_PLAYER) && m_type == ENEMYTYPE_HORMING)
	{//�v���C���[�Ɠ������� && �z�[�~���O����G�Ȃ�
		CLevel::AddExp(10);					//�o���l�̎擾
		CGame::GetPlayer()->AddLife(-15);	//�v���C���[�̗̑͂����炷
		return true;
	}

	return false;
}

//=======================
// �z�[�~���O
//=======================
D3DXVECTOR3 CEnemy::Homing(float& posX, float& posY, float& moveX, float& moveY)
{
	//�e�̌��̑��x
	float vx0 = moveX, vy0 = moveY;

	//���@�����̑��x�x�N�g��(vx1,vy1)�����߂�
	float vx1, vy1;

	//�ڕW�܂ł̋���d�����߂�
	float d = sqrtf((m_Tirget.x - posX) * (m_Tirget.x - posX)
		+ (m_Tirget.y - posY) * (m_Tirget.y - posY));

	if (d)
	{
		vx1 = (m_Tirget.x - posX) / d * fBulletSpeed_Homing;
		vy1 = (m_Tirget.y - posY) / d * fBulletSpeed_Homing;
	}
	else
	{
		vx1 = 0;
		vy1 = fBulletSpeed_Homing;
	}

	//�E������p�x����̑��x�x�N�g��(vx2,vy2)�����߂�
	float rad = (D3DX_PI / 180) * 5.0f; //����p�x���
	float vx2 = cosf(rad) * vx0 - sinf(rad) * vy0;
	float vy2 = sinf(rad) * vx0 + cosf(rad) * vy0;

	//���@�����Ɛ���p�x����̂ǂ���ɋȂ��邩�����߂�
	if (vx0 * vx1 + vy0 * vy1 >= vx0 * vx2 + vy0 * vy2)
	{//���@����������\�͈͓��̏ꍇ
	 //���@�����ɋȂ���
		moveX = vx1;
		moveY = vy1;
	}
	else
	{
		//���@����������\�͈͊O�̏ꍇ
		//��������p�x����̑��x�x�N�g��(vx3,vy3)�����߂�
		float vx3 = cosf(rad) * vx0 + sinf(rad) * vy0;
		float vy3 = -sinf(rad) * vx0 + cosf(rad) * vy0;

		//�e���玩�@�ւ̑��Έʒu�x�N�g��(px,py)�����߂�
		float px = m_Tirget.x - posX, py = m_Tirget.y - posY;

		//�E��肩����肩�����߂�
		if (px * vx2 + py * vy2 >= px * vx3 + py * vy3)
		{//�E���̏ꍇ
			moveX = vx2;
			moveY = vy2;
		}
		else
		{//�����̏ꍇ
			moveX = vx3;
			moveY = vy3;
		}
	}

	moveX *= fBulletSpeed_Homing;
	moveY *= fBulletSpeed_Homing;

	return D3DXVECTOR3(moveX, moveY, 0.0f);
}

//===========================
// �ړ��ʂ̎擾
//===========================
D3DXVECTOR3 CEnemy::GetMove()
{
	return m_move;
}

//===========================
// �̗͂̐ݒ�
//===========================
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
	m_nMaxLife = nLife;
}

//===========================
// �̗͂̌���
//===========================
void CEnemy::SubLife(int nLife)
{
	m_nLife -= nLife;

	//�c��̗͂��v�Z
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP�������̏���
	m_pHp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// �̗͂̎擾
//===========================
int CEnemy::GetLife()
{
	return m_nLife;
}

//===========================
// �c��̗͂̎擾
//===========================
int CEnemy::GetRemLife()
{
	return m_nRemLife;
}

//===========================
// �U���͂̐ݒ�
//===========================
int CEnemy::GetAttack()
{
	return m_nAttack;
}