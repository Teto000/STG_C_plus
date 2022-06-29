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
class CPlayer;		//プレイヤー

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

private:
	//------------------
	// 静的メンバ変数
	//------------------
	static CRenderer	*m_pRenderer;	//レンダラークラス
	static CInput		*m_pInput;		//インプットクラス
	static CPlayer		*m_pPlayer;		//プレイヤークラス
};

#endif // !_APPLICATION_H_