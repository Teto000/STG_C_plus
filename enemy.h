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
// 前方宣言
//--------------------------
class CHp;				//HPクラス
class CEnemyBullet;		//敵の弾クラス
class CExplosion;		//爆発
class CBarrier;			//バリア
class CHpFream;			//HPフレームクラス

//--------------------------
// エネミークラス
//--------------------------
class CEnemy : public CObject2D
{
public:
	//---------------------------
	// 敵の列挙型の定義
	//---------------------------
	enum ENEMYTYPE
	{
		ENEMYTYPE_NORMAL = 0,	//直進する敵
		ENEMYTYPE_BIG,			//大きい敵
		ENEMYTYPE_HORMING,		//ホーミングしてくる敵
		ENEMYTYPE_BOSS,			//ボス敵
		ENEMYTYPE_MAX
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

	void SetLife(int nLife);	//体力の設定
	void SubLife(int nLife);	//体力の減少

	//ゲッター
	int GetLife();
	int GetRemLife();
	int GetAttack();

	//----------------
	// 静的メンバ関数
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);

private:
	void BossAttack();			//ボスの攻撃

private:
	//----------------
	// 定数定義
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);
	static const int nShotTime = 50;	//弾の発射時間

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_targetPos;	//目的の位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//回転
	int m_nLife;				//体力
	int m_nMaxLife;				//最大体力
	int m_nRemLife;				//残り体力
	int m_nCntShotTime;			//弾の発射時間を数える
	int m_nCntTime;				//テクスチャ切り替え時間のカウント
	int m_nAttack;				//攻撃力
	int m_nCntAttack;			//攻撃タイミングを数える
	float m_fWidth;				//幅
	float m_fHeight;			//高さ
	float m_fTargetRot;			//プレイヤーまでの角度
	ENEMYTYPE m_type;			//種類

	CHp* m_Hp;					//寿命
	CEnemyBullet* m_EnemyBullet;//敵の弾
	CExplosion*		m_pExplosion;//爆発
	CBarrier*		m_pBarrier;	//バリア
	CHpFream*	m_pHpFream;		//HPフレームクラス
};

#endif // !_PLAYER_H_