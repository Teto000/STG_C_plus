//===================================
//
// レベルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "level.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "exp.h"

//===========================
// コンストラクタ
//===========================
CLevel::CLevel() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_fLength = 0.0f;	//幅
}

//===========================
// デストラクタ
//===========================
CLevel::~CLevel()
{

}

//===========================
// 初期化
//===========================
HRESULT CLevel::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 100;	//幅

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexture(CTexture::TEXTURE_RING);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CLevel::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CLevel::Update()
{
	CObject2D::Update();

	//円形に移動する
	D3DXVECTOR3 CirclePos = CObject2D::MoveCircle(m_pos, m_rot.x, m_fLength * 0.6f);

	//位置の設定
	CObject2D::SetPosition(m_pos);

	if (CInputKeyboard::Trigger(DIK_K))
	{
		CExp::Create(CirclePos,m_rot,m_fLength * 0.6f);	//経験値ゲージの生成

		m_rot.x += 30.0f;
	}
}

//===========================
// 描画
//===========================
void CLevel::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CLevel *CLevel::Create()
{
	CLevel *pLevel = nullptr;

	//----------------------------------
	// レベルの生成と初期化
	//----------------------------------
	pLevel = new CLevel;	//生成

	if (pLevel != nullptr)
	{//NULLチェック
		//初期化
		pLevel->Init(D3DXVECTOR3(120.0f, 100.0f, 0.0f));
		pLevel->SetObjType(OBJTYPE_LEVEL);
	}

	return pLevel;
}