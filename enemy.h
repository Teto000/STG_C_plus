//=====================================
//
// エネミーヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _ENEMY_H_
#define _ENEMY_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// エネミークラス
//--------------------------
class CEnemy : public CObject2D
{
public:
	CEnemy();			//コンストラクタ
	~CEnemy() override;	//デストラクタ

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
	static CEnemy *Create();

private:
	//----------------
	// 定数定義
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_CntTime;	//テクスチャ切り替え時間のカウント
};

#endif // !_PLAYER_H_