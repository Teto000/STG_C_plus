//=====================================
//
// プレイヤーヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// プレイヤークラス
//--------------------------
class CPlayer : public CObject2D
{
public:
	//---------------------------
	// プレイヤー構造体の定義
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//移動量
		D3DXCOLOR col;		//色
		int nLife;			//体力
		int nMaxLife;		//最大体力
		int nRemLife;		//残り体力
		int nAttack;		//攻撃力
		float nSpeed;		//速度
		float fWidth;		//幅
		float fHeight;		//高さ
	}Player;

	CPlayer();				//コンストラクタ
	~CPlayer() override;	//デストラクタ

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
	static CPlayer *Create();

private:
	//----------------
	// メンバ変数
	//----------------
	Player m_Player;	//プレイヤー構造体

	//----------------
	// 静的メンバ変数
	//----------------
};

#endif // !_PLAYER_H_