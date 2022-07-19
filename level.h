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
// プレイヤークラス
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

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif // !_LEVEL_H_