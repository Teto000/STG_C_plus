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
	//---------------------------
	// 爆発構造体の定義
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXCOLOR col;		//色
		int nLife;			//寿命
		float fWidth;		//幅
		float fHeight;		//高さ
	}Explosion;

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
	Explosion m_Explosion;	//爆発構造体

	//----------------
	// 静的メンバ変数
	//----------------
};

#endif // !_EXPLOSION_H_