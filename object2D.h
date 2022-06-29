//=====================================
//
// オブジェクト2Dヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	//二重インクルード防止

//--------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "texture.h"

//--------------------------------
// オブジェクト2Dクラスの定義
//--------------------------------
class CObject2D : public CObject
{
public:
	CObject2D();					//コンストラク
	virtual ~CObject2D() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	
	D3DXVECTOR3 AddMove(D3DXVECTOR3 move);		//移動量の加算

	//セッター
	void SetPosition(D3DXVECTOR3 pos);			//位置の設定
	void SetSize(float fWidth, float fHeight);	//大きさの設定
	void SetTexCIE(float left, float fRight);	//テクスチャ座標の設定
	void SetTexture(CTexture::TEXTURE texture);	//テクスチャの設定
	void SetColor(D3DXCOLOR col);				//色の設定

	//ゲッター
	D3DXVECTOR3 GetPosition() override;		//位置の取得
	float GetWidth() override;				//幅の取得
	float GetHeight() override;				//高さの取得

private:
	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fRot;		//回転角度
	float m_fScal;		//大きさ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	CTexture::TEXTURE m_texture;		//テクスチャ
};

#endif // !_OBJECT_H_