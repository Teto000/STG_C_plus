//============================
//
// スコアヘッダー
// Author:Teruto Sato
//
//============================

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// スコアクラスの定義
//--------------------------
class CScore : public CObject2D
{
public:
	//----------------------
	// スコアの構造体
	//----------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		float fWidth;		//幅
		float fHeight;		//高さ
		float fSpace;		//間隔
	}Score;

	CScore();				//コンストラクタ
	~CScore() override;		//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//ゲッター
	int GetScore();

	//----------------
	// 静的メンバ関数
	//----------------
	static CScore *Create();
	static void AddScore(int nValue);

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxScore = 6;
	//----------------
	// メンバ変数
	//----------------
	Score m_Score;	//スコア構造体

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nScore;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};