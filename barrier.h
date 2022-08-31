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
	CBarrier();				//コンストラクタ
	~CBarrier() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	void SubLife(int nAttack);

	//----------------
	// 静的メンバ関数
	//----------------
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight);

private:
	//----------------
	// メンバ変数
	//----------------s
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	int m_nLife;		//体力
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif // !_BARRIER_H_