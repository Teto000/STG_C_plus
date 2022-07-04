//===================================
//
// オブジェクト2Dの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "object2D.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "input_keybord.h"

//------------------------
// マクロ定義
//------------------------
#define	ROT		(0.05f)		//回転角度の増加量
#define	SCAL	(0.01f)		//拡縮の値の増加量

//===========================
// コンストラクタ
//===========================
CObject2D::CObject2D() : CObject()
{
	m_pVtxBuff = nullptr;	//頂点バッファへのポインタ

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
	m_fRot = 0.0f;		//回転角度
	m_fScal = 0.0f;		//大きさ
}

//===========================
// デストラクタ
//===========================
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//===========================
// 初期化
//===========================
HRESULT CObject2D::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//頂点フォーマット
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置
	m_pos = pos;

	//------------------------
	// 頂点座標の設定
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//------------------------
	// 頂点座標の設定(回転)
	//------------------------
	/*float fLength = sqrtf((m_fWidth * m_fHeight) + (m_fWidth * m_fHeight)) / 2;	//対角線の長さを算出する
	float fAngle = atan2f(m_fWidth, m_fHeight);									//対角線の角度を算出

	//------------------------
	// 頂点情報を設定
	//------------------------
	pVtx[0].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.z = 0.0f;*/

	//------------------------
	// rhwの設定
	//------------------------
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//------------------------
	// 頂点カラーの設定
	//------------------------
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//------------------------
	// テクスチャ座標の設定
	//------------------------
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
// 終了
//===========================
void CObject2D::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//===========================
// 更新
//===========================
void CObject2D::Update()
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
  	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//===============================
	// ポリゴンの回転・拡縮
	//===============================
	/*m_fRot -= ROT;		//回転角度を加算
	m_fScal += SCAL;	//拡縮の変動
	m_fWidth += sinf(2.0f * m_fScal);	//幅の計算
	m_fHeight += sinf(2.0f * m_fScal);	//高さの計算*/

	//------------------------
	// 頂点座標の設定
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//------------------------
	// 頂点座標の設定(回転)
	//------------------------
	/*float fLength = sqrtf((m_fWidth * m_fHeight) + (m_fWidth * m_fHeight)) / 2;	//対角線の長さを算出する
	float fAngle = atan2f(m_fWidth, m_fHeight);									//対角線の角度を算出

	//------------------------
	// 頂点情報を設定
	//------------------------
	pVtx[0].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRot - (0 + fAngle)) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRot - (0 - fAngle)) * fLength;
	pVtx[3].pos.z = 0.0f;*/

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================
// 描画
//===========================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = CApplication::GetTexture();

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
						   0,					//描画する最初の頂点インデックス
						   2);					//描画するプリミティブ数
}

//===========================
// 位置の設定
//===========================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CObject2D::GetPosition()
{
	return m_pos;
}

//===========================
// 移動量の加算
//===========================
D3DXVECTOR3 CObject2D::AddMove(D3DXVECTOR3 move)
{
	m_pos += move;

	return m_pos;
}

//===========================
// 大きさの設定
//===========================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;		//幅の設定
	m_fHeight = fHeight;	//高さの設定
}

//===========================
// テクスチャ座標の設定
//===========================
void CObject2D::SetTexCIE(float left ,float fRight)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(left, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(left, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fRight, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================
// テクスチャの設定
//===========================
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//===========================
// 頂点座標の設定
//===========================
void CObject2D::SetVtxCIE(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth / 2, fHeight / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth / 2, fHeight / 2, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================
// 頂点座標の設定(特殊)
//===========================
void CObject2D::SetVtxCIE_Gauge(D3DXVECTOR3 pos, 
	float fLeft,float fRight, float fUp, float fDown)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = pos + D3DXVECTOR3(-fLeft / 2, -fUp / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fRight / 2, -fUp / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fLeft / 2, fDown / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fRight / 2, fDown / 2, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================
// 幅の取得
//===========================
float CObject2D::GetWidth()
{
	return m_fWidth;
}

//===========================
// 高さの取得
//===========================
float CObject2D::GetHeight()
{
	return m_fHeight;
}

//===========================
// 色の設定
//===========================
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// 頂点カラーの設定
	//------------------------
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================
// スコアの設定処理
//=====================
void CObject2D::SetScore(int nScore)
{
	int aPosTexU[m_nMaxScore];	//各桁の数字を格納

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = nScore % 1000000 / 100000;
	aPosTexU[1] = nScore % 100000 / 10000;
	aPosTexU[2] = nScore % 10000 / 1000;
	aPosTexU[3] = nScore % 1000 / 100;
	aPosTexU[4] = nScore % 100 / 10;
	aPosTexU[5] = nScore % 10 / 1;

	//テクスチャ座標の設定
	for (int i = 0; i < m_nMaxScore; i++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================
// スコアの加算処理
//=====================
void CObject2D::AddScore(int nScore, int nValue)
{
	int aPosTexU[m_nMaxScore];

	//スコアの加算
	nScore += nValue;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = nScore % 1000000 / 100000;
	aPosTexU[1] = nScore % 100000 / 10000;
	aPosTexU[2] = nScore % 10000 / 1000;
	aPosTexU[3] = nScore % 1000 / 100;
	aPosTexU[4] = nScore % 100 / 10;
	aPosTexU[5] = nScore % 10 / 1;

	//テクスチャ座標の設定
	for (int i = 0; i < m_nMaxScore; i++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[i] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[i] * 0.1f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分集める
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}