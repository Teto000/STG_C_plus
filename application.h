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
class CGame;		//ゲーム
class CTitle;		//タイトル
class CResult;		//リザルト
class CSkillSelect;	//スキルセレクト
class CFade;		//フェード

class CRenderer;	//レンダラー
class CInput;		//インプット
class CTexture;		//テクスチャ
class CSound;		//サウンド

//-------------------------------------
// アプリケーションクラスの定義
//-------------------------------------
class CApplication
{
public:
	//--------------------------------
	// ゲームモードの列挙型の定義
	//--------------------------------
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル
		MODE_GAME,			//ゲーム
		MODE_RESULT,		//リザルト
		MODE_SKILLSELECT,	//スキルセレクト
		MODE_FADE,			//フェード
		MODE_MAX
	};

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
	static void SetMode(MODE mode);		//モードの設定
	static MODE GetMode();				//モードの取得

	static CRenderer *GetRenderer();	//レンダラーの取得
	static CInput	 *GetInput();		//インプットの取得
	static CTexture  *GetTexture();		//テクスチャの取得
	static CSound	 *GetSound();		//サウンドの取得

private:
	//------------------
	// 静的メンバ変数
	//------------------
	static CGame*			m_pGame;		//ゲームクラス
	static CTitle*			m_pTitle;		//タイトルクラス
	static CResult*			m_pResult;		//リザルトクラス
	static CSkillSelect*	m_pSkillSelect;	//スキルセレクトクラス
	static CFade*			m_pFade;		//フェードクラス
	static MODE				m_mode;			//ゲームモード

	static CRenderer*		m_pRenderer;	//レンダラークラス
	static CInput*			m_pInput;		//インプットクラス
	static CTexture*		m_pTexture;		//テクスチャクラス
	static CSound*			m_pSound;		//サウンドクラス
};

#endif // !_APPLICATION_H_