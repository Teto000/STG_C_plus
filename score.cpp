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
	m_Score.fWidth = 15.0f;		//幅
	m_Score.fHeight = 25.0f;	//高さ
	m_Score.fInterval = 35.0f;	//間隔

	CObject2D::Init(m_Score.pos);

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
	pScore = new CScore;	//生成

	if (pScore != nullptr)
	{//NULLチェック
		//初期化
		pScore->Init(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));
		pScore->SetObjType(OBJTYPE_SCORE);
	}

	return pScore;
}