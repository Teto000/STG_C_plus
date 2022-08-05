//===================================
//
// 消える数値を表示する処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "number.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CNumber::m_nValue = 0;
int CNumber::m_nNum = 0;

//===========================
// コンストラクタ
//===========================
CNumber::CNumber() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_nDigit = 0;			//桁数
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_fSpace = 0.0f;		//間隔
	m_aPosTexU[m_nDigit] = {};
}

//===========================
// デストラクタ
//===========================
CNumber::~CNumber()
{

}

//===========================
// 初期化
//===========================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CNumber::Update()
{
	CObject2D::Update();

	//桁数の計算
	int nFirst = (int)pow(10, m_nDigit);
	int nSecond = (int)pow(10, (m_nDigit - 1));
	int nDigit = (int)pow(10, m_nNum);

	//桁ごとの値を求める
	m_aPosTexU[m_nNum] = m_nValue % (nFirst / nDigit) / (nSecond / nDigit);

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(m_aPosTexU[m_nNum] * 0.1f, m_aPosTexU[m_nNum] * 0.1f + 0.1f);

	//配列を進める
	if (m_nNum >= m_nDigit - 1)
	{
		m_nNum = 0;
	}
	else
	{
		m_nNum++;
	}

	//縦に縮小
	m_fHeight -= 1.5f;

	CObject2D::SetSize(m_fWidth, m_fHeight);

	if (m_fHeight <= 0)
	{//高さが無くなったら
		Uninit();
		return;
	}
}

//===========================
// 描画
//===========================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//====================================
// 生成(位置,幅,高さ,間隔,桁数,数値)
//====================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
						int nDigit, int nNumber)
{
	CNumber *pNumber = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	for (int i = 0; i < nDigit; i++)
	{
		pNumber = new CNumber;	//生成

		if (pNumber != nullptr)
		{//NULLチェック
			//構造体に代入
			pNumber->m_fWidth = fWidth;		//幅
			pNumber->m_fHeight = fHeight;	//高さ
			pNumber->m_fSpace = fSpace;		//間隔
			pNumber->m_nDigit = nDigit;		//桁数
			pNumber->m_nValue = nNumber;			//値

			//初期化
			pNumber->Init(D3DXVECTOR3(pos.x + i * fSpace, pos.y, pos.z));
			pNumber->SetObjType(OBJTYPE_SCORE);
		}
	}
	return pNumber;
}