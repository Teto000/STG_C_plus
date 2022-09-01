//=====================================
//
// 敵の弾ヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// バレットクラス
//--------------------------
class CEnemyBullet : public CObject2D
{
public:
	//---------------------------
	// 敵の弾の列挙型の定義
	//---------------------------
	enum ENEMYBULLETTYPE
	{
		ENEMYBULLETTYPE_NORMAL = 0,
		ENEMYBULLETTYPE_HORMING,
		ENEMYBULLETTYPE_MAX
	};

	CEnemyBullet();				//コンストラクタ
	~CEnemyBullet() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);	//ホーミング弾

	//----------------
	// 静的メンバ関数
	//----------------
	static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
								int nAttack, CEnemyBullet::ENEMYBULLETTYPE type);

private:
	void CollisionEnemyBullet();	//当たった処理

private:
	//----------------
	// 定数定義
	//----------------
	static const float fBulletSpeed_Homing;	//ホーミング弾の速度

	//----------------
	// メンバ変数
	//----------------s
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_Tirget;	//ホーミング目標の位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//回転
	int m_nEnemyAttack;		//敵の攻撃力
	int m_nLife;			//寿命
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	ENEMYBULLETTYPE m_type;	//弾の種類
};

#endif // !_BULLET_H_