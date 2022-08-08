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

//--------------------------
// プレイヤークラス
//--------------------------
class CPlayer : public CObject2D
{
public:
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
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_rot;	//移動量
	int m_nLife;		//体力
	int m_nMaxLife;		//最大体力
	int m_nRemLife;		//残り体力
	int m_nAttack;		//攻撃力
	int m_nShotTime;	//弾の発射時間
	int m_nCntShotTime;	//弾の発射時間を数える
	float m_nSpeed;		//速度
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	CHp* m_Hp;			//HPクラス
	CLevel* m_Level;	//レベルクラス

	//------------------
	// 静的メンバ変数
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_