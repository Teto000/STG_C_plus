//============================
//
// タイマーヘッダー
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
class CTimer : public CObject2D
{
public:
	CTimer();				//コンストラクタ
	~CTimer() override;		//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CTimer *Create();

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxScore = 3;

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	int m_nCntTime;		//時間を数える
	float m_fWidth;		//幅
	float m_fHeight;	//高さ

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nTime;
	static int m_aPosTexU[nMaxScore];
	static int nNum;
};