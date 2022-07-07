//=====================================
//
// エフェクトヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _EFFECT_H_
#define _EFFECT_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// エネミークラス
//--------------------------
class CEffect : public CObject2D
{
public:
	//--------------------------
	// エフェクト構造体の定義
	//--------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXCOLOR col;		//色
		float fRadius;		//半径(大きさ)
	}Effect;

	CEffect();				//コンストラクタ
	~CEffect() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CEffect *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// メンバ変数
	//----------------
	Effect m_Effect;	//エフェクト構造体
};

#endif // !_EFFECT_H_