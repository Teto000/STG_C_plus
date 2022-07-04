//=====================================
//
// アプリケーションヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_	

//--------------------
// インクルード
//--------------------
#include <d3dx9.h>

//-----------------------
// 前方宣言
//-----------------------
class CRenderer;	//レンダラー
class CInput;		//インプット
class CTexture;		//テクスチャ
class CSound;		//サウンド
class CPlayer;		//プレイヤー
class CEnemy;		//敵
class CScore;		//スコア

//-------------------------------------
// アプリケーションクラスの定義
//-------------------------------------
class CApplication
{
public:
	CApplication();		//コンストラクタ
	~CApplication();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// 静的メンバ関数
	//------------------
	static CRenderer *GetRenderer();	//レンダラーの取得
	static CInput	 *GetInput();		//インプットの取得
	static CTexture  *GetTexture();		//テクスチャの取得
	static CSound	 *GetSound();		//サウンドの取得
	static CPlayer	 *GetPlayer();		//プレイヤーの取得

private:
	//------------------
	// 静的メンバ変数
	//------------------
	static CRenderer	*m_pRenderer;	//レンダラークラス
	static CInput		*m_pInput;		//インプットクラス
	static CTexture		*m_pTexture;	//テクスチャクラス
	static CSound		*m_pSound;		//サウンドクラス
	static CPlayer		*m_pPlayer;		//プレイヤークラス
	static CEnemy		*m_pEnemy;		//敵クラス
	static CScore		*m_pScore;		//スコアクラス
};

#endif // !_APPLICATION_H_