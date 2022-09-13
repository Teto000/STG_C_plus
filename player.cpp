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
#include "application.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"
#include "mp.h"
#include "skill.h"
#include "level.h"
#include "hpfream.h"
#include "barrier.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CPlayer::fPlayerSpeed = 8.0f;
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
	m_nMagic = 0;				//MP
	m_nMaxMagic = 0;			//最大MP
	m_nRemMagic = 0;			//残りMP
	m_nAttack = 0;				//攻撃力
	m_nLevel = 0;				//レベル
	m_nShotTime = 0;			//弾の発射時間
	m_nCntShotTime = 0;			//弾の発射時間を数える
	m_nCntInvincible = 0;		//無敵時間を数える
	m_nCntSkill = 0;			//スキルの使用可能時間を数える
	m_nSpeed = 0.0f;			//速度
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_bSlill = false;			//スキル使用可能かどうか
	m_type = PLAYERSTATE_NORMAL;//状態
	m_Hp = nullptr;				//HPクラス
	m_Mp = nullptr;				//MPクラス
	m_Level = nullptr;			//レベルクラス
	m_Bullet = nullptr;			//弾クラス
	m_pHpFream = nullptr;		//HPフレームクラス
	m_pBarrier = nullptr;		//バリアクラス
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
	m_nMagic = 100;				//MP
	m_nMaxMagic = 100;				//最大MP
	m_nRemMagic = 100;				//残りMP
	m_fWidth = 80.0f;			//幅
	m_fHeight = 100.0f;			//高さ
	m_nAttack = 10;				//攻撃力
	m_nShotTime = 20;			//弾の発射時間
	m_nSpeed = fPlayerSpeed;	//速度

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_pos = CObject2D::GetPosition();

	//--------------------------
	// HPの表示
	//--------------------------
	m_Hp = CHp::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);
	m_Hp->SetLife(m_nLife, m_nRemLife);	//初期HPの設定

	//--------------------------
	// MPの表示
	//--------------------------
	m_Mp = CMp::Create(D3DXVECTOR3(520.0f, 110.0f, 0.0f), 600.0f, 20.0f);
	m_Mp->SetMP(m_nMagic, m_nRemMagic);	//初期HPの設定

	//--------------------------
	// レベルの生成
	//--------------------------
	m_Level = CLevel::Create();

	//--------------------------
	// フレームの生成
	//--------------------------
	m_pHpFream = CHpFream::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);

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
	
	//--------------------
	// レベルによる変化
	//--------------------
	m_nLevel = m_Level->GetLevel();	//レベルの取得

	//m_nAttack *= 1.0f + (0.1f * m_nLevel);

	//--------------------------
	// 弾の発射
	//--------------------------
	if (!CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//バリアの範囲外なら
		m_nCntShotTime++;
		m_nCntShotTime %= m_nShotTime;	//発射時間をリセット

		m_Bullet->ShotBullet(m_pos, m_nLevel, m_nCntShotTime);	//弾の発射
	}

	//--------------------------
	// スキルの発動
	//--------------------------
	if (!m_bSlill)
	{
		SetSkill();
	}

	//--------------------------
	// スキルの効果が切れる
	//--------------------------
	if (m_bSlill)
	{//スキル使用状態なら
		m_nCntSkill++;
		m_nCntSkill %= 300;

		if (m_nCntSkill == 0)
		{//5秒経過したら
			m_nAttack = 10;				//攻撃力
			m_nShotTime = 20;			//弾の発射時間
			m_nSpeed = fPlayerSpeed;	//速度

			m_bSlill = false;
		}
	}

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

		//リザルト画面に移行
		CApplication::SetMode(CApplication::MODE_RESULT);
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
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//上左移動
			m_move.x += sinf(-D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//下左移動
			m_move.x += sinf(-D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * m_nSpeed;		//左移動
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//Dキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//上右移動
			m_move.x += sinf(D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//下右移動
			m_move.x += sinf(D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * m_nSpeed;		//右移動
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//Wキーが押された
		m_move.y += cosf(-D3DX_PI * 1.0f) * m_nSpeed;			//上移動
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//Sキーが押された
		m_move.y += cosf(D3DX_PI * 0.0f) * m_nSpeed;			//下移動
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

		//MPの減少
		AddMagic(-10);

		m_bSlill = true;
	}

	//-----------------------
	// 弾速の強化
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_2))
	{//2キーが押されたら
		CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);

		//発射間隔の減少
		m_nShotTime = 10;

		//MPの減少
		AddMagic(-10);

		m_bSlill = true;
	}

	//-----------------------
	// 攻撃力上昇
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_3))
	{
		//攻撃力の上昇
		m_nAttack = 20;

		//MPの減少
		AddMagic(-10);

		m_bSlill = true;
	}

	//-----------------------
	// 速度上昇
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_4))
	{
		//速度の上昇
		m_nSpeed = 12.0f;

		//MPの減少
		AddMagic(-10);

		m_bSlill = true;
	}

	//-----------------------
	// バリアの生成
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_5))
	{
		//バリアの生成
		m_pBarrier = CBarrier::Create(m_pos, m_move, m_fWidth, m_fHeight,
										CBarrier::BARRIERTYPE_PLAYER);

		//MPの減少
		AddMagic(-10);

		m_bSlill = true;
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
// HPの加算
//===========================
void CPlayer::AddLife(int nValue)
{
	if (m_nLife + nValue < m_nMaxLife)
	{
		m_nLife += nValue;	//プレイヤーの体力の加算
	}
	else
	{
		m_nLife = m_nMaxLife;
	}

	//残り体力を計算
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP減少時の処理
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// MPの加算
//===========================
void CPlayer::AddMagic(int nValue)
{
	if (m_nMagic + nValue < m_nMaxMagic)
	{//最大MPを超えないなら
		m_nMagic += nValue;	//プレイヤーの体力の加算
	}
	else 
	{
		//MPを最大にする
		m_nMagic = m_nMaxMagic;
	}

	//残り体力を計算
	m_nRemMagic = m_nMagic * 100 / m_nMaxMagic;

	//MP減少時の処理
	m_Mp->SetMP(m_nMagic, m_nRemMagic);
}

//===========================
// 色の設定
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// 移動量の取得
//===========================
D3DXVECTOR3 CPlayer::GetMove()
{
	return m_move;
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