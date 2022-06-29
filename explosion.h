//=====================================
//
// エクスプロージョンヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// エクスプロージョンクラス
//--------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();			//コンストラクタ
	~CExplosion() override;	//デストラクタ

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
	static CExplosion *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// メンバ変数
	//----------------

	//----------------
	// 静的メンバ変数
	//----------------
	int m_nCnterAnim;	//
	int m_nPatternAnim; //
};

#endif // !_EXPLOSION_H_