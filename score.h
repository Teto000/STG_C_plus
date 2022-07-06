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
	//----------------------
	// �X�R�A�̍\����
	//----------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		float fWidth;		//��
		float fHeight;		//����
		float fSpace;		//�Ԋu
	}Score;

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
	static CScore *Create();
	static void AddScore(int nValue);

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxScore = 6;
	//----------------
	// �����o�ϐ�
	//----------------
	Score m_Score;	//�X�R�A�\����

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static int m_nScore;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};