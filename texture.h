//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		TEXTURE_PLAYER = 0,			//プレイヤー

		/* ↓　エネミー　↓　*/
		TEXTURE_ENEMY_BIRD,			//敵(鳥)
		TEXTURE_ENEMY_RED,			//敵(赤)
		TEXTURE_ENEMY_BLUE,			//敵(青)
		TEXTURE_ENEMY_GREEN,		//敵(緑)
		TEXTURE_ENEMY_PINK,			//敵(桃)

		/* ↓ ゲーム ↓*/
		TEXTURE_BULLET,				//弾
		TEXTURE_EXPLOSION,			//爆発
		TEXTURE_RING,				//輪
		TEXTURE_EFFECT,				//エフェクト
		TEXTURE_BARRIER,			//バリア

		/* ↓ BG ↓*/
		TEXTURE_BG_GAME,			//ゲーム画面の背景
		TEXTURE_BG_TITLE,			//タイトル画面の背景
		TEXTURE_BG_RESULT,			//リザルト画面の背景
		TEXTURE_BG_SKILLSELECT,		//スキルセレクト画面の背景

		/* ↓ UI ↓*/
		TEXTURE_EXP,				//経験値
		TEXTURE_LEVEL,				//レベル
		TEXTURE_HPFREAM,			//HPバーのフレーム

		/* ↓ スキル ↓*/
		TEXTURE_SKILL_HPHEAL,		//スキル(体力回復)
		TEXTURE_SKILL_SPEEDUP_FIRE,	//スキル(弾速強化)

		/* ↓ 共通 ↓*/
		TEXTURE_NUMBER,				//数字

		TEXTURE_MAX,
		TEXTURE_NONE,			//使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
