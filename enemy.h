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
	//---------------------------
	// 敵の構造体の定義
	//---------------------------
	struct Enemy
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//回転
		int nLife;			//体力
		int nMaxLife;		//最大体力
		int nRemLife;		//残り体力
		float fWidth;		//幅
		float fHeight;		//高さ
	};

	CEnemy();			//コンストラクタ
	~CEnemy() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SubLife(int nLife);	//体力の減少

	//ゲッター
	int GetLife();
	int GetRemLife();

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
	Enemy m_Enemy;

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_CntTime;	//テクスチャ切り替え時間のカウント
};

#endif // !_PLAYER_H_