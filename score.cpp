//===================================
//
// スコアの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
#include "score.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CScore::m_nScore = 0;
int CScore::m_aPosTexU[nMaxScore] = {};
int CScore::nNum = 0;

//===========================
// コンストラクタ
//===========================
CScore::CScore() : CObject2D()
{
	memset(&m_Score, 0, sizeof(Score));	//構造体のクリア
}

//===========================
// デストラクタ
//===========================
CScore::~CScore()
{

}

//===========================
// 初期化
//===========================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_Score.pos = pos;
	m_Score.fWidth = 30.0f;		//幅
	m_Score.fHeight = 50.0f;	//高さ
	m_Score.fSpace = 35.0f;		//間隔

	m_nScore = 0;	//スコアの初期設定

	CObject2D::Init(m_Score.pos);

	CObject2D::SetSize(m_Score.fWidth, m_Score.fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CScore::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CScore::Update()
{
	CObject2D::Update();

	//桁ごとの値を求める
	m_aPosTexU[nNum] = m_nScore % (1000000 / (int)pow(10, nNum)) / (100000 / (int)pow(10, nNum));

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(0.0f + m_aPosTexU[nNum] * 0.1f, 0.1f + m_aPosTexU[nNum] * 0.1f);

	//配列を進める
	if (nNum >= nMaxScore - 1)
	{
		nNum = 0;
	}
	else 
	{
		nNum++;
	}
}
//===========================
// 描画
//===========================
void CScore::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CScore *CScore::Create()
{
	CScore *pScore = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	for (int i = 0; i < nMaxScore; i++)
	{
		pScore = new CScore;	//生成

		if (pScore != nullptr)
		{//NULLチェック
			//初期化
			pScore->Init(D3DXVECTOR3(1000.0f + (i * 35.0f), 50.0f, 0.0f));
			pScore->SetObjType(OBJTYPE_SCORE);
		}
	}

	return pScore;
}

//===========================
// 数値の加算
//===========================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//===========================
// 数値の取得
//===========================
int CScore::GetScore()
{
	return m_nScore;
}