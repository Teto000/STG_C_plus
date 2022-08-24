//=====================================
//
// �I�u�W�F�N�g�̏���
// Author : Sato Teruto
//
//=====================================

//--------------------
// �C���N���[�h
//--------------------
#include "object.h"
#include "object2D.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CObject *CObject::m_pObject[MAX_OBJECT] = {};
//int CObject::m_nNumAll = 0;

//=============================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================
CObject::~CObject()
{

}
//=============================
// �S�ĉ��
//=============================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			//���
			m_pObject[i]->Uninit();
		}
	}
}

//=============================
// �S�čX�V
//=============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Update();	//�I�u�W�F�N�g�̍X�V
		}
	}
}

//=============================
// �S�ĕ`��
//=============================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] != nullptr)
		{
			m_pObject[i]->Draw();	//�I�u�W�F�N�g�̕`��
		}
	}
}

//=============================
// �����̎擾
//=============================
int CObject::GetNumAll()
{
	//return m_nNumAll;
	return 0;
}

//=============================
// �������
//=============================
void CObject::Release()
{
	//NULL�`�F�b�N
	if (m_pObject[m_nID] != nullptr)
	{
		int nID = m_nID;			//�ԍ���ۑ�
//		m_pObject[nID]->Uninit();
		delete m_pObject[nID];		//�I�u�W�F�N�g�̉��
		m_pObject[nID] = nullptr;	//NULL�ɂ���
		//m_nNumAll--;				//���������炷
	}
}

//=============================
// �I�u�W�F�N�g�̎擾
//=============================
CObject *CObject::GETObject(int nCnt)
{
	return m_pObject[nCnt];
}

//=============================
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================
void CObject::SetObjType(EObjType ObjType)
{
	m_ObjType = ObjType;
}

//=============================
// �I�u�W�F�N�g�̎�ނ̎擾
//=============================
CObject::EObjType CObject::GetObjType()
{
	return m_ObjType;
}