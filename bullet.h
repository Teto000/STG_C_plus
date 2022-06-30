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
		BULLETSTATE_BEAM,
		BULLETSTATE_CHARGE,
		BULLETSTATE_MAX
	}BULLETSTATE;

	//---------------------------
	// 弾の構造体の定義
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//回転
		int nLife;			//寿命
		float fWidth;		//幅
		float fHeight;		//高さ
		BULLETSTATE type;	//種類
	}Bullet;

	CBullet();				//コンストラクタ
	~CBullet() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

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
	static const int nShotTime = 30;	//弾の発射時間

	//----------------
	// メンバ変数
	//----------------
	Bullet m_aBullet;	//弾の構造体

	//----------------
	// 静的メンバ変数
	//----------------
	static int s_nShotTime;		//弾の発射時間を数える
	static int s_nChageTime;	//弾のチャージ時間
};

#endif // !_BULLET_H_