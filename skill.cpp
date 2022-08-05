//===================================
//
// スキル処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "skill.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CSkill::nSkillSpeed = 7.0f;	//速度

//===========================
// コンストラクタ
//===========================
CSkill::CSkill() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nCntTimer = 0;		//文字の表示時間
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_type = SKILLTYPE_MAX;	//種類
}

//===========================
// デストラクタ
//===========================
CSkill::~CSkill()
{

}

//===========================
// 初期化
//===========================
HRESULT CSkill::Init(D3DXVECTOR3 pos)
{
	//構造体に代入
	m_move = D3DXVECTOR3(nSkillSpeed, 0.0f, 0.0f);
	m_fWidth = 300.0f;
	m_fHeight = 80.0f;
	m_pos = D3DXVECTOR3(pos.x - (m_fWidth / 2), pos.y - (m_fHeight / 2), pos.z);

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	switch (m_type)
	{
	case SKILLTYPE_HEAL:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_HPHEAL);	//テクスチャの設定
		break;

	case SKILLTYPE_SPEEDUP_FIRE:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_SPEEDUP_FIRE);	//テクスチャの設定
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================
// 終了
//===========================
void CSkill::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CSkill::Update()
{
	CObject2D::Update();

	//--------------------------
	// スキル表示
	//--------------------------
	//画面端から移動
	if (m_pos.x >= (m_fWidth / 2))
	{
		//移動の停止
		m_move.x = 0;

		//タイマーを加算
		m_nCntTimer++;

		if (m_nCntTimer >= nMaxTimer)
		{//一定時間経過
			//画面端から見えなくなったら
			m_move.x = -nSkillSpeed;
			m_nCntTimer = 0;
		}
	}
	//画面外に消えたら
	else if (m_move.x <= 0.0f && m_pos.x + (m_fWidth / 2) <= 0.0f)
	{
		//スキル表示の消去
		Uninit();
		return;
	}

	//位置に移動量を加算
	m_pos = CObject2D::AddMove(m_move);
}

//===========================
// 描画
//===========================
void CSkill::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CSkill *CSkill::Create(SKILLTYPE type)
{
	CSkill *pSkill = nullptr;

	//----------------------------------
	// 敵の生成と初期化
	//----------------------------------
	pSkill = new CSkill;	//生成

	if (pSkill != nullptr)
	{//NULLチェック
		//構造体に代入
		pSkill->m_type = type;

		//初期化
		pSkill->Init(D3DXVECTOR3(0.0f, 720.0f, 0.0f));
		pSkill->SetObjType(OBJTYPE_SKILL);
	}

	return pSkill;
}