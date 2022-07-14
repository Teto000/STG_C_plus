//============================
//
// ナンバーヘッダー
// Author:Teruto Sato
//
//============================
#ifndef _NUMBER_H_
#define _NUMBER_H_	//二重インクルード防止

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// ナンバークラスの定義
//--------------------------
class CNumber : public CObject2D
{
public:
	//--------------------------
	// ナンバー構造体の定義
	//--------------------------
	struct Number
	{
		D3DXVECTOR3 pos;	//位置
		int nLife;			//寿命
		int nDigit;			//桁数
		float fWidth;		//幅
		float fHeight;		//高さ
		float fSpace;		//間隔
	};

	CNumber();				//コンストラクタ
	~CNumber() override;		//デストラクタ

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
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
							int nDigit, int nNumber);

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxDigit = 6;		//最大桁数

	//----------------
	// メンバ変数
	//----------------
	Number m_Number;	//ナンバー構造体
	int m_aPosTexU[nMaxDigit];

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nValue;	//値
	static int m_nNum;		//配列カウント用
};

#endif