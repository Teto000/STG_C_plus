//===================================
//
// スキル処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include <memory.h>
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
	memset(&m_Skill, 0, sizeof(Skill));	//構造体のクリア

	m_nCntTimer = 0;
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
	m_Skill.move = D3DXVECTOR3(nSkillSpeed, 0.0f, 0.0f);
	m_Skill.fWidth = 300.0f;
	m_Skill.fHeight = 80.0f;
	m_Skill.pos = D3DXVECTOR3(pos.x - (m_Skill.fWidth / 2), pos.y - (m_Skill.fHeight / 2), pos.z);

	CObject2D::Init(m_Skill.pos);

	CObject2D::SetSize(m_Skill.fWidth, m_Skill.fHeight);

	switch (m_Skill.type)
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
	if (m_Skill.pos.x >= (m_Skill.fWidth / 2))
	{
		//移動の停止
		m_Skill.move.x = 0;

		//タイマーを加算
		m_nCntTimer++;

		if (m_nCntTimer >= nMaxTimer)
		{//一定時間経過
			//画面端から見えなくなったら
			m_Skill.move.x = -nSkillSpeed;
			m_nCntTimer = 0;
		}
	}
	//画面外に消えたら
	else if (m_Skill.move.x <= 0.0f && m_Skill.pos.x + (m_Skill.fWidth / 2) <= 0.0f)
	{
		//スキル表示の消去
		Uninit();
		return;
	}

	//位置に移動量を加算
	m_Skill.pos = CObject2D::AddMove(m_Skill.move);
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
		pSkill->m_Skill.type = type;

		//初期化
		pSkill->Init(D3DXVECTOR3(0.0f, 720.0f, 0.0f));
		pSkill->SetObjType(OBJTYPE_SKILL);
	}

	return pSkill;
}