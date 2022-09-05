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
// 前方宣言
//--------------------------
class CHp;		//HPクラス
class CLevel;	//レベルクラス
class CBullet;	//弾クラス
class CHpFream;	//HPフレームクラス

//--------------------------
// プレイヤークラス
//--------------------------
class CPlayer : public CObject2D
{
public:
	enum PLAYERSTATE
	{
		PLAYERSTATE_NORMAL = 0,	//通常
		PLAYERSTATE_INVINCIBLE,	//無敵
		PLAYERSTATE_MAX
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
	void SubLife(int nAttack);	//体力の減少

	//ゲッター
	int GetLife();
	int GetRemLife();
	int GetAttack();
	PLAYERSTATE GetState();

	//------------------
	// 静的メンバ関数
	//------------------
	static CPlayer *Create();
	static void SetCol(D3DXCOLOR col);	//色の設定

private:
	D3DXVECTOR3 OperationPlayer();	//操作
	void InvincibleTime();			//無敵時間

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
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//移動量
	int m_nLife;			//体力
	int m_nMaxLife;			//最大体力
	int m_nRemLife;			//残り体力
	int m_nAttack;			//攻撃力
	int m_nLevel;			//レベル
	int m_nShotTime;		//弾の発射時間
	int m_nCntShotTime;		//弾の発射時間を数える
	int m_nCntInvincible;	//無敵時間を数える
	int m_nCntSkill;		//スキルの使用可能時間を数える
	float m_nSpeed;			//速度
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	bool m_bSlill;			//スキル使用可能かどうか
	PLAYERSTATE m_type;		//状態
	CHp* m_Hp;				//HPクラス
	CLevel* m_Level;		//レベルクラス
	CBullet* m_Bullet;		//弾クラス
	CHpFream*m_pHpFream;	//HPフレームクラス

	//------------------
	// 静的メンバ変数
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_