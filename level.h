//=====================================
//
// レベルヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _LEVEL_H_
#define _LEVEL_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// レベルクラス
//--------------------------
class CLevel : public CObject2D
{
public:
	CLevel();			//コンストラクタ
	~CLevel() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ関数
	//------------------
	static CLevel *Create();
	static void AddExp(int nValue);

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxLevel = 5;	//最大レベル

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//回転
	float m_fLength;	//幅

	//------------------
	// 静的メンバ変数
	//------------------
	static int m_nLevel;	//レベルの値
	static int m_nExp;		//経験値の値
};

#endif // !_LEVEL_H_