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
#include <memory.h>
#include "player.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"

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
	memset(&m_Player, 0, sizeof(Player));	//構造体のクリア
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
	m_Player.pos = pos;
	m_Player.nLife = nPlayerLife;	//体力
	m_Player.nMaxLife = nPlayerLife;//最大体力
	m_Player.nRemLife = nMaxLife;	//残り体力
	m_Player.fWidth = 80.0f;		//幅
	m_Player.fHeight = 100.0f;		//高さ
	m_Player.nAttack = 10;			//攻撃力
	m_Player.nSpeed = fPlayerSpeed;	//速度

	CObject2D::Init(m_Player.pos);

	CObject2D::SetSize(m_Player.fWidth, m_Player.fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_Player.pos = CObject2D::GetPosition();

	//--------------------------
	// HPの表示
	//--------------------------
	CHp::Create(D3DXVECTOR3(350.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				, 600.0f, 40.0f, CHp::HPTYPE_PLAYER);

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
	m_Player.move.x += (0.0f - move.x) * 0.4f;
	m_Player.move.y += (0.0f - move.y) * 0.4f;

	//--------------------
	// 位置に移動量を加算
	//--------------------
	m_Player.pos = CObject2D::AddMove(m_Player.move);

	//--------------------
	// 画面端の設定
	//--------------------
	CObject2D::SetScreenX(m_Player.pos.x, 0.0f + m_Player.fWidth / 2, SCREEN_WIDTH - m_Player.fWidth / 2);
	CObject2D::SetScreenY(m_Player.pos.y, 0.0f + 180.0f, SCREEN_HEIGHT - m_Player.fHeight / 2);

	//--------------------------
	// 弾の発射
	//--------------------------
	CBullet::ShotBullet(m_Player.pos, m_Player.rot);

	//--------------------------
	// 体力の減少
	//--------------------------
	if (CInputKeyboard::Press(DIK_L))
	{//Lキーが押された
		m_Player.nLife--;	//プレイヤーの体力の減少
		m_Player.nRemLife = m_Player.nLife * 100 / m_Player.nMaxLife;	//残り体力を計算
	}

	//------------------------
	// 敵との当たり判定
	//------------------------
	if (CObject2D::GetCollision(OBJTYPE_ENEMY) == true)
	{
		m_Player.nLife--;	//プレイヤーの体力の減少
		m_Player.nRemLife = m_Player.nLife * 100 / m_Player.nMaxLife;	//残り体力を計算
	}
}

//===========================
// 描画
//===========================
void CPlayer::Draw()
{
	CObject2D::Draw();
	CObject2D::SetColor(m_col);
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
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//上左移動
			m_Player.move.x += sinf(-D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//下左移動
			m_Player.move.x += sinf(-D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_Player.move.x += sinf(-D3DX_PI * 0.5f) * fPlayerSpeed;		//左移動
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//Dキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * fPlayerSpeed;		//上右移動
			m_Player.move.x += sinf(D3DX_PI * 0.75f) * fPlayerSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * fPlayerSpeed;		//下右移動
			m_Player.move.x += sinf(D3DX_PI * 0.25f) * fPlayerSpeed;
		}
		else
		{
			m_Player.move.x += sinf(D3DX_PI * 0.5f) * fPlayerSpeed;			//右移動
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//Wキーが押された
		m_Player.move.y += cosf(-D3DX_PI * 1.0f) * fPlayerSpeed;			//上移動
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//Sキーが押された
		m_Player.move.y += cosf(D3DX_PI * 0.0f) * fPlayerSpeed;				//下移動
	}

	return m_Player.move;
}

//===========================
// 色の設定
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// 残り体力の取得
//===========================
int CPlayer::GetRemLife()
{
	return m_Player.nRemLife;
}