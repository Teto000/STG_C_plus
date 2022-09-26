//============================
//
// �^�C�}�[�w�b�_�[
// Author:Teruto Sato
//
//============================

//--------------------------
// �C���N���[�h
//--------------------------
#include "object2D.h"

//--------------------------
// �X�R�A�N���X�̒�`
//--------------------------
class CTimer : public CObject2D
{
public:
	enum MODE
	{
		MODE_GAME = 0,	//�Q�[�����
		MODE_RESULT,	//���U���g���
		MODE_MAX
	};

	CTimer();				//�R���X�g���N�^
	~CTimer() override;		//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CTimer *Create(MODE mode);
	static void SetTime(int nTime);
	static int GetTime();

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxScore = 3;

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	int m_nCntTime;		//���Ԃ𐔂���
	float m_fWidth;		//��
	float m_fHeight;	//����
	MODE  m_mode;		//���[�h

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nTime;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};