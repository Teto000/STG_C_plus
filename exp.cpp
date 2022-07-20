//===================================
//
// 経験値の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "exp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//===========================
// コンストラクタ
//===========================
CExp::CExp() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_fLength = 0.0f;	//半径
}

//===========================
// デストラクタ
//===========================
CExp::~CExp()
{

}

//===========================
// 初期化
//===========================
HRESULT CExp::Init(D3DXVECTOR3 pos)
{
	//位置の代入
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexture(CTexture::TEXTURE_EXP);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CExp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CExp::Update()
{
	CObject2D::Update();
}

//===========================
// 描画
//===========================
void CExp::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CExp *CExp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	CExp *pExp = nullptr;

	//----------------------------------
	// 経験値の生成と初期化
	//----------------------------------
	pExp = new CExp;	//生成

	if (pExp != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pExp->m_rot = rot;			//回転
		pExp->m_fLength = fLength;	//半径

		//初期化
		pExp->Init(pos);
		pExp->SetObjType(OBJTYPE_EXP);
	}

	return pExp;
}