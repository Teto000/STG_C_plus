//===================================
//
// メインヘッダー
// Author : Sato Teruto
//
//===================================
#ifndef _MAIN_H_
#define _MAIN_H_	//二重インクルード防止

//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int GetFPS();	//FPSの取得

#endif // !_MAIN_H_