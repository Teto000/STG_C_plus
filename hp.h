//=====================================
//
// HPヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _HP_H_
#define _HP_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// プレイヤークラス
//--------------------------
class CHp : public CObject2D
{
public:
	//---------------------------
	// HP列挙型の定義
	//---------------------------
	typedef enum
	{
		HPTYPE_NOMAL = 0,
		HPTYPE_PLAYER,
		HPTYPE_ENEMY,
		HPTYPE_MAX,
	}HPTYPE;

	//---------------------------
	// HP構造体の定義
	//---------------------------
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		float fWidth;		//幅
		float fHeight;		//高さ
		float fLength;		//HPバーの長さ
		HPTYPE type;		//種類
	}HP;
	
	CHp();				//コンストラクタ
	~CHp() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Subtract(int nRemLife);	//HP減少時の処理

	//------------------
	// 静的メンバ関数
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE type);

private:
	//------------------
	// 定数定義
	//------------------

	//------------------
	// メンバ変数
	//------------------
	HP m_HP;	//HP構造体
	int m_nPlayerLife;	//プレイヤーの体力受け取り用
	int m_nEnemyLife;	//エネミーの体力受け取り用

	//------------------
	// 静的メンバ変数
	//------------------
};

#endif // !_HP_H_