//===================================
//
// レンダリングヘッダー
// Author : Sato Teruto
//
//===================================
#ifndef _RENDERER_H_
#define _RENDERER_H_	//二重インクルード防止

//--------------------
// インクルード
//--------------------
#include <tchar.h> // _T
#include <d3dx9.h>

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace
{
	// ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	// ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("鳥々戯画");
}

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//==============================
// レンダリングクラスの定義
//==============================
class CRenderer
{
public:
	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ

	//-----------------
	// メンバ関数
	//-----------------
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	//デバイスの取得
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }

private:
	void DrawFPS();

	//-----------------
	// メンバ変数
	//-----------------
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Deviceオブジェクト
	LPD3DXFONT m_pFont;		// フォント
};

#endif // !_RENDERER_H_