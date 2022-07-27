//=====================================
//
// バレットヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _BULLET_H_
#define _BULLET_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// バレットクラス
//--------------------------
class CBullet : public CObject2D
{
public:
	//---------------------------
	// 弾の列挙型の定義
	//---------------------------
	typedef enum
	{
		BULLETSTATE_NORMAL = 0,
		BULLETSTATE_HORMING,
		BULLETSTATE_CHARGE,
		BULLETSTATE_MAX
	}BULLETSTATE;

	//---------------------------
	// 弾の構造体の定義
	//---------------------------
	struct Bullet
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//回転
		int nLife;			//寿命
		float fWidth;		//幅
		float fHeight;		//高さ
		BULLETSTATE type;	//種類
	};

	CBullet();				//コンストラクタ
	~CBullet() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//ホーミング弾
	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);

	//----------------
	// 静的メンバ関数
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type);
	static void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	//----------------
	// 定数定義
	//----------------
	static const float fBulletSpeed;	//弾の速度
	static const int nShotTime = 20;	//弾の発射時間
	static const int nMaxHoming = 3;	//ホーミング弾発射の最大数

	//----------------
	// メンバ変数
	//----------------s
	Bullet m_Bullet;		//弾の構造体
	D3DXVECTOR3 m_Tirget;	//ホーミング目標の位置

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nShotTime;		//弾の発射時間を数える
	static int m_nChageTime;	//弾のチャージ時間
	static float fBulletSpeed_Homing;	//弾の速度
};

#endif // !_BULLET_H_