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
		BULLETSTATE_OPTION,
		BULLETSTATE_MAX
	}BULLETSTATE;

	CBullet();				//コンストラクタ
	~CBullet() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	void CollisionBullet();
	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);	//ホーミング弾

	//----------------
	// 静的メンバ関数
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETSTATE type);
	void ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime);

private:
	//----------------
	// 定数定義
	//----------------
	static const int nMaxHoming = 3;		//ホーミング弾発射の最大数
	static const int nDefaultLife = 50;		//弾の寿命の基準値
	static const float fBulletSpeed;		//弾の速度
	static const float fBulletSpeed_Homing;	//弾の速度
	static const float nDefaultSize;		//弾の大きさの基準値

	//----------------
	// メンバ変数
	//----------------s
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//回転
	int m_nLife;			//寿命
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	BULLETSTATE m_type;		//種類
	D3DXVECTOR3 m_Tirget;	//ホーミング目標の位置

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nChageTime;	//弾のチャージ時間
	static int m_nCntHorming;	//ホーミング弾の発射カウント

};

#endif // !_BULLET_H_