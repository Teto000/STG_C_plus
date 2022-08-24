//=====================================
//
// オブジェクトの処理
// Author : Sato Teruto
//
//=====================================

//--------------------
// インクルード
//--------------------
#include "object.h"
#include "object2D.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CObject *CObject::m_pObject[MAX_OBJECT] = {};
//int CObject::m_nNumAll = 0;

//=============================
// コンストラクタ
//=============================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{
			m_pObject[i] = this;
			m_nID = i;
			//m_nNumAll++;
			m_ObjType = OBJTYPE_INVALID;
			break;
		}
	}
}

//=============================
// デストラクタ
//=============================
CObject::~CObject()
{

}
//=============================
// 全て解放
//=============================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			//解放
			m_pObject[i]->Uninit();
		}
	}
}

//=============================
// 全て更新
//=============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Update();	//オブジェクトの更新
		}
	}
}

//=============================
// 全て描画
//=============================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Draw();	//オブジェクトの描画
		}
	}
}

//=============================
// 総数の取得
//=============================
int CObject::GetNumAll()
{
	//return m_nNumAll;
	return 0;
}

//=============================
// 解放する
//=============================
void CObject::Release()
{
	//NULLチェック
	if (m_pObject[m_nID] != nullptr)
	{
		int nID = m_nID;			//番号を保存
//		m_pObject[nID]->Uninit();
		delete m_pObject[nID];		//オブジェクトの解放
		m_pObject[nID] = nullptr;	//NULLにする
		//m_nNumAll--;				//総数を減らす
	}
}

//=============================
// オブジェクトの取得
//=============================
CObject *CObject::GETObject(int nCnt)
{
	return m_pObject[nCnt];
}

//=============================
// オブジェクトの種類の設定
//=============================
void CObject::SetObjType(EObjType ObjType)
{
	m_ObjType = ObjType;
}

//=============================
// オブジェクトの種類の取得
//=============================
CObject::EObjType CObject::GetObjType()
{
	return m_ObjType;
}