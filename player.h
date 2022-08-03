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
	struct Player
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
	};

	CPlayer();				//コンストラクタ
	~CPlayer() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSkill();

	//ゲッター
	int GetLife();
	int GetRemLife();
	int GetAttack();

	//------------------
	// 静的メンバ関数
	//------------------
	static CPlayer *Create();
	static void SetCol(D3DXCOLOR col);	//色の設定

private:
	D3DXVECTOR3 OperationPlayer();	//操作

private:
	//------------------
	// 定数定義
	//------------------
	static const float fPlayerSpeed;		//プレイヤーの速度
	static const int nPlayerLife = 300;		//プレイヤーの体力
	static const int nMaxLife = 100;		//最大体力(%)

	//------------------
	// メンバ変数
	//------------------
	Player m_Player;	//プレイヤー構造体
	int m_nShotTime;	//弾の発射時間を数える

	//------------------
	// 静的メンバ変数
	//------------------
	static int nShotTime;	//弾の発射時間
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_