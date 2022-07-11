//=====================================
//
// バリアヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _BARRIER_H_
#define _BARRIER_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// バレットクラス
//--------------------------
class CBarrier : public CObject2D
{
public:
	//---------------------------
	// 弾の構造体の定義
	//---------------------------
	struct Barrier
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		float fWidth;		//幅
		float fHeight;		//高さ
	};

	CBarrier();				//コンストラクタ
	~CBarrier() override;	//デストラクタ

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
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight);

private:
	//----------------
	// メンバ変数
	//----------------s
	Barrier m_Barrier;
};

#endif // !_BARRIER_H_