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
		ENEMYTYPE_CURVE,		//上下にカーブする敵
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

	void SubLife(int nLife);	//体力の減少

	//ゲッター
	int GetLife();
	int GetRemLife();

	//----------------
	// 静的メンバ関数
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);

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
	int m_nCntAttack;			//攻撃タイミングを数える
	float m_fWidth;				//幅
	float m_fHeight;			//高さ
	ENEMYTYPE m_type;			//種類

	CHp* m_Hp;					//寿命
	CEnemyBullet* m_EnemyBullet;//敵の弾
	CExplosion*	m_pExplosion;	//爆発
};

#endif // !_PLAYER_H_