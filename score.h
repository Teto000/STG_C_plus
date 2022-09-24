//============================
//
// �X�R�A�w�b�_�[
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
class CScore : public CObject2D
{
public:
	enum MODE
	{
		MODE_GAME = 0,	//�Q�[�����
		MODE_RESULT,	//���U���g���
		MODE_MAX
	};

	CScore();				//�R���X�g���N�^
	~CScore() override;		//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//�Q�b�^�[
	int GetScore();

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CScore *Create(MODE mode);
	static void AddScore(int nValue);
	static void SetScore(int nScore);

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxScore = 6;

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fSpace;		//�Ԋu
	MODE  m_mode;		//���[�h

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nScore;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};