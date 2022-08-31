//===================================
//
// プレイヤーの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "player.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"
#include "skill.h"
#include "level.h"
#include "hpfream.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CPlayer::fPlayerSpeed = (30.0f / 5.0f);
D3DXCOLOR CPlayer::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

//===========================
// コンストラクタ
//===========================
CPlayer::CPlayer() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_nLife = 0;				//体力
	m_nMaxLife = 0;				//最大体力
	m_nRemLife = 0;				//残り体力
	m_nAttack = 0;				//攻撃力
	m_nShotTime = 0;			//弾の発射時間
	m_nCntShotTime = 0;			//弾の発射時間を数える
	m_nCntInvincible = 0;		//無敵時間を数える
	m_nSpeed = 0.0f;			//速度
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_type = PLAYERSTATE_NORMAL;//状態
	m_Hp = nullptr;				//HPクラス
	m_Level = nullptr;			//レベルクラス
	m_Bullet = nullptr;			//弾クラス
	m_pHpFream = nullptr;		//HPフレームクラス
}

//===========================
// デストラクタ
//===========================
CPlayer::~CPlayer()
{

}

//===========================
// 初期化
//===========================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;
	m_nLife = nPlayerLife;		//体力
	m_nMaxLife = nPlayerLife;	//最大体力
	m_nRemLife = nMaxLife;		//残り体力
	m_fWidth = 80.0f;			//幅
	m_fHeight = 100.0f;			//高さ
	m_nAttack = 40;				//攻撃力
	m_nShotTime = 20;			//弾の発射時間
	m_nSpeed = fPlayerSpeed;	//速度

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_pos = CObject2D::GetPosition();

	//--------------------------
	// HPの表示
	//--------------------------
	m_Hp = CHp::Create(D3DXVECTOR3(520.0f, 80.0f, 0.0f), 600.0f, 80.0f);
	m_Hp->SetLife(m_nLife, m_nRemLife);	//初期HPの設定

	//--------------------------
	// レベルの生成
	//--------------------------
	m_Level = CLevel::Create();

	//--------------------------
	// フレームの生成
	//--------------------------
	m_pHpFream = CHpFream::Create(D3DXVECTOR3(520.0f, 80.0f, 0.0f), 600.0f, 80.0f);

	return S_OK;
}

//===========================
// 終了
//===========================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CPlayer::Update()
{
	CObject2D::Update();

	//--------------------
	// プレイヤーの操作
	//--------------------
	D3DXVECTOR3 move = OperationPlayer();

	//--------------------
	// 移動量を更新(減衰)
	//--------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//--------------------
	// 位置に移動量を加算
	//--------------------
	m_pos = CObject2D::AddMove(m_move);

	//--------------------
	// 画面端の設定
	//--------------------
	CObject2D::SetScreenX(m_pos.x, 0.0f + m_fWidth / 2, SCREEN_WIDTH - m_fWidth / 2);
	CObject2D::SetScreenY(m_pos.y, 0.0f + 200.0f, SCREEN_HEIGHT - m_fHeight / 2);

	//--------------------------
	// 弾の発射
	//--------------------------
	m_nCntShotTime++;
	m_nCntShotTime %= m_nShotTime;	//発射時間をリセット

	{
		int nLevel = m_Level->GetLevel();	//レベルの取得
		m_Bullet->ShotBullet(m_pos, nLevel, m_nCntShotTime);	//弾の発射
	}

	//--------------------------
	// スキルの発動
	//--------------------------
	SetSkill();

	//------------------------
	// 敵との当たり判定
	//------------------------
	if (m_type != PLAYERSTATE_INVINCIBLE && CObject2D::GetCollision(OBJTYPE_ENEMY))
	{//無敵でない状態 かつ 敵と当たったら
		m_nLife -= 20;	//プレイヤーの体力の減少

		//残り体力を計算
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP減少時の処理
		m_Hp->SetLife(m_nLife, m_nRemLife);

		m_type = PLAYERSTATE_INVINCIBLE;
	}

	//----------------------------
	// 無敵時間
	//----------------------------
	if (m_type == PLAYERSTATE_INVINCIBLE)
	{
		InvincibleTime();
	}

	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		//敵の消滅
		Uninit();
		return;
	}

	CObject2D::SetColor(m_col);
}

//===========================
// 描画
//===========================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CPlayer *CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pPlayer = new CPlayer;	//生成

	if (pPlayer != nullptr)
	{//NULLチェック
		//初期化
		pPlayer->Init(D3DXVECTOR3(400.0f, SCREEN_HEIGHT / 2, 0.0f));
		pPlayer->SetObjType(OBJTYPE_PLAYER);
	}

	return pPlayer;
}

//===========================
// プレイヤーの操作
//===========================
D3DXVECTOR3 CPlayer::OperationPlayer()
{
	if (CInputKeyboard::Press(DIK_A) == true)
	{//Aキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//上左移動
			m_move.x += sinf(-D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//下左移動
			m_move.x += sinf(-D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * fPlayerSpeed;		//左移動
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//Dキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//上右移動
			m_move.x += sinf(D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//下右移動
			m_move.x += sinf(D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * fPlayerSpeed;			//右移動
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//Wキーが押された
		m_move.y += cosf(-D3DX_PI * 1.0f) * fPlayerSpeed;			//上移動
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//Sキーが押された
		m_move.y += cosf(D3DX_PI * 0.0f) * fPlayerSpeed;				//下移動
	}

	return m_move;
}

//===========================
// スキルの発動
//===========================
void CPlayer::SetSkill()
{
	//-----------------------
	// 体力の回復
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_1))
	{//1キーが押されたら
		CSkill::Create(CSkill::SKILLTYPE_HEAL);

		if (m_nLife + 30 >= m_nMaxLife)
		{//回復して上限なら
			m_nLife = m_nMaxLife;	//体力を最大にする
		}
		else
		{//それ以外なら
			m_nLife += 30;	//体力を回復
		}

		//残り体力を計算
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP減少時の処理
		m_Hp->SetLife(m_nLife, m_nRemLife);
	}

	//-----------------------
	// 弾速の強化
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_2))
	{//2キーが押されたら
		CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);

		m_nShotTime = 15;
	}
}

//===========================
// 無敵時間
//===========================
void CPlayer::InvincibleTime()
{
	m_nCntInvincible++;

	//色の変更
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	if (m_nCntInvincible >= 120)
	{//無敵時間が終わったら
		m_type = PLAYERSTATE_NORMAL;	//通常の状態に戻す
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_nCntInvincible = 0;
	}
}

//===========================
// 体力の減少
//===========================
void CPlayer::SubLife(int nAttack)
{
	m_nLife -= nAttack;	//プレイヤーの体力の減少

	//残り体力を計算
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP減少時の処理
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// 色の設定
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// 体力の取得
//===========================
int CPlayer::GetLife()
{
	return m_nLife;
}

//===========================
// 残り体力の取得
//===========================
int CPlayer::GetRemLife()
{
	return m_nRemLife;
}

//===========================
// 攻撃力の取得
//===========================
int CPlayer::GetAttack()
{
	return m_nAttack;
}

//===========================
// プレイヤーの状態の取得
//===========================
CPlayer::PLAYERSTATE CPlayer::GetState()
{
	return m_type;
}