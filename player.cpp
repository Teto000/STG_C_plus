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

//------------------------
// マクロ定義
//------------------------
#define PLAYER_SPEED	(5.0f)	//プレイヤーの速度

//------------------------
// 静的メンバ変数宣言
//------------------------

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

	CObject2D::Init(m_Player.pos);

	CObject2D::SetSize(100.0f, 100.0f);	//サイズの設定

	m_Player.pos = CObject2D::GetPosition();

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

	//プレイヤーの操作
	D3DXVECTOR3 move = OperationPlayer();

	//移動量を更新(減衰)
	m_Player.move.x += (0.0f - move.x) * 0.4f;
	m_Player.move.y += (0.0f - move.y) * 0.4f;

	CObject2D::AddMove(m_Player.move);
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
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * PLAYER_SPEED;		//上左移動
			m_Player.move.x += sinf(-D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;		//下左移動
			m_Player.move.x += sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{
			m_Player.move.x += sinf(-D3DX_PI * 0.5f) * PLAYER_SPEED;		//左移動
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//Dキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_Player.move.y += cosf(-D3DX_PI * 0.75f) * PLAYER_SPEED;		//上右移動
			m_Player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;		//下右移動
			m_Player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{
			m_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;			//右移動
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//Wキーが押された
		m_Player.move.y += cosf(-D3DX_PI * 1.0f) * PLAYER_SPEED;			//上移動
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//Sキーが押された
		m_Player.move.y += cosf(D3DX_PI * 0.0f) * PLAYER_SPEED;				//下移動
	}

	return m_Player.move;
}