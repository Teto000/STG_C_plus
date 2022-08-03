//=====================================
//
// スキルヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _SKILL_H_
#define _SKILL_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// スキルクラス
//--------------------------
class CSkill : public CObject2D
{
public:
	//---------------------------
	// スキル列挙型の定義
	//---------------------------
	enum SKILLTYPE
	{
		SKILLTYPE_HEAL = 0,			//回復
		SKILLTYPE_SPEEDUP_FIRE,		//発射速度強化
	};

	//---------------------------
	// スキル構造体の定義
	//---------------------------
	struct Skill
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 move;	//移動量
		float fWidth;		//幅
		float fHeight;		//高さ
		SKILLTYPE type;		//種類
	};

	CSkill();			//コンストラクタ
	~CSkill() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CSkill *Create(SKILLTYPE type);

private:
	//----------------
	// 定数
	//----------------
	static const float nSkillSpeed;
	static const int nMaxTimer = 60;

	//----------------
	// メンバ変数
	//----------------
	Skill m_Skill;
	int m_nCntTimer;
};

#endif // !_PLAYER_H_