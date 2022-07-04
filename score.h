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
		int nScore;			//�l
		float fWidth;		//��
		float fHeight;		//����
		float fInterval;	//�Ԋu
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

	static void SetScore(int nScore);
	static void AddScore(int nValue);

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CScore *Create();

private:
	//----------------
	// �萔
	//----------------
	static const int m_nMaxScore = 6;	//�X�R�A�̌��̍ő吔

	//----------------
	// �����o�ϐ�
	//----------------
	Score m_Score;	//�X�R�A�\����
};