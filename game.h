//=====================================
//
// ゲームヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------
// インクルード
//--------------------
#include <d3dx9.h>

//-----------------------
// 前方宣言
//-----------------------
class CPlayer;	//プレイヤー
class CEnemy;	//敵
class CScore;	//スコア
class CBg;		//背景
class CSkill;	//スキル

//-------------------------
// ゲームクラスの定義
//-------------------------
class CGame
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// 静的メンバ関数
	//------------------
	static CPlayer	*GetPlayer();	//プレイヤーの取得
	static CScore	*GetScore();	//スコアの取得
	static CBg		*GetBG();		//背景の取得

private:
	void SetEnemy();

private:
	//------------------
	// 定数
	//------------------
	static const int nOneSecond = 60;	//一秒
	static const int nMaxSkill = 2;		//スキルの最大数

	//------------------
	// メンバ変数
	//------------------
	int m_EnemyCnt;
	int m_nTime;

	//------------------
	// 静的メンバ変数
	//------------------
	static CPlayer	*m_pPlayer;		//プレイヤークラス
	static CEnemy	*m_pEnemy;		//敵クラス
	static CScore	*m_pScore;		//スコアクラス
	static CBg		*m_pBG;			//背景クラス
	static CSkill	*m_pSkill[nMaxSkill];	//スキルクラス
};

#endif // !_APPLICATION_H_