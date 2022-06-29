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

	//--------------------------
	// プレイヤーの移動
	//--------------------------
	//左右移動
	if (CInputKeyboard::Press(DIK_A))
	{//Aキーが押された
		m_Player.pos.x -= PLAYER_SPEED;
	}
	else if (CInputKeyboard::Press(DIK_D))
	{//Dキーが押された
		m_Player.pos.x += PLAYER_SPEED;
	}

	//上下移動
	if (CInputKeyboard::Press(DIK_W))
	{//Wキーが押された
		m_Player.pos.y -= PLAYER_SPEED;
	}
	else if (CInputKeyboard::Press(DIK_S))
	{//Sキーが押された
		m_Player.pos.y += PLAYER_SPEED;
	}

	CObject2D::SetPosition(m_Player.pos);
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