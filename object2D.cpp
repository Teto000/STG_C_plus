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

	//------------------------
	// 頂点座標の設定
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

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

//===========================
// 左右画面端の設定
//===========================
void CObject2D::SetScreenX(float posX, float fLeft, float fRight)
{
	if (posX <= fLeft)
	{
		posX = fLeft;
	}
	else if (posX >= fRight)
	{
		posX = fRight;
	}

	m_pos.x = posX;
}

//===========================
// 上下画面端の設定
//===========================
void CObject2D::SetScreenY(float posY, float fUp, float fDown)
{
	if (posY <= fUp)
	{
		posY = fUp;
	}
	else if (posY >= fDown)
	{
		posY = fDown;
	}

	m_pos.y = posY;
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
	pVtx[0].pos = pos + D3DXVECTOR3(fLeft, fUp, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fRight, fUp, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(fLeft, fDown, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fRight, fDown, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================
// 頂点座標の設定(スコア)
//===========================
void CObject2D::SetVtxCIE_Score(D3DXVECTOR3 pos, float fWidth, float fHeight,float fSpace)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth / 2, fHeight / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth / 2, fHeight / 2, 0.0f);

	pos.x += fSpace;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=========================================
// αブレンディングを加算合成に設定
//=========================================
void CObject2D::SetAddALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスの取得

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//=========================================
// αブレンディングを元に戻す
//=========================================
void CObject2D::ResAddALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスの取得

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CObject2D::GetPosition()
{
	return m_pos;
}

//===========================
// 相手の位置の取得
//===========================
D3DXVECTOR3 CObject2D::GetTargetPos()
{
	return m_TargetPos;
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
// 当たり判定の取得
//===========================
bool CObject2D::GetCollision(CObject::EObjType TirgetType)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GETObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		//オブジェクトの種類の取得
		CObject::EObjType type = pObject->GetObjType();

		//------------------
		// 自分の情報を取得
		//------------------
		D3DXVECTOR3 SourcePos = CObject2D::GetPosition();	//位置
		float SourceWidth = CObject2D::GetWidth();			//幅
		float SourceHeight = CObject2D::GetHeight();		//高さ

		if (type == TirgetType)
		{//オブジェクトの種類が目的の相手なら
			//------------------
			// 相手の情報を取得
			//------------------
			m_TargetPos = pObject->GetPosition();			//位置
			float TirgetWidth = pObject->GetWidth();		//幅
			float TirgetHeight = pObject->GetHeight();		//高さ


			float fLeft = m_TargetPos.x - (TirgetWidth / 2);		//敵の左側
			float fRight = m_TargetPos.x + (TirgetWidth / 2);		//敵の右側
			float fTop = m_TargetPos.y - (TirgetHeight / 2);		//敵の上側
			float fBottom = m_TargetPos.y + (TirgetHeight / 2);		//敵の下側

			//------------------
			// 当たり判定
			//------------------
			if (SourcePos.x + SourceWidth / 2 >= fLeft && SourcePos.x - SourceWidth / 2 <= fRight
				&& SourcePos.y - SourceHeight / 2 <= fBottom && SourcePos.y + SourceHeight / 2 >= fTop)
			{
				return true;
			}
		}
	}
	return false;
}