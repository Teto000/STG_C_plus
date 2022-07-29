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
	struct HP
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		int nLife;			//体力受け取り用
		int nRemLife;		//残り体力受け取り用
		float fWidth;		//幅
		float fHeight;		//高さ
		float fLength;		//HPバーの長さ
		HPTYPE type;		//種類
	};
	
	CHp();				//コンストラクタ
	~CHp() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SubHP(int nLife, int nRemLife);	//HP減少時の処理

	//------------------
	// 静的メンバ関数
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, HPTYPE typez);

private:
	//------------------
	// メンバ変数
	//------------------
	HP m_HP;	//HP構造体
};

#endif // !_HP_H_