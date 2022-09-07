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
CObject *CObject::m_pObject[3][MAX_OBJECT] = {};

//================================
// �R���X�g���N�^(�C�j�V�����C�U)
//================================
CObject::CObject(int nPriority)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[nPriority][i] == nullptr)
		{
			m_pObject[nPriority][i] = this;
			m_nID = i;
			m_ObjType = OBJTYPE_MAX;
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
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				//���
				m_pObject[i][j]->Uninit();
			}
		}
	}
}

//=============================
// �S�čX�V
//=============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Update();	//�I�u�W�F�N�g�̍X�V
			}
		}
	}
}

//=============================
// �S�ĕ`��
//=============================
void CObject::DrawAll()
{
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Draw();	//�I�u�W�F�N�g�̕`��
			}
		}
	}
}

//=============================
// �����̎擾
//=============================
int CObject::GetNumAll()
{
	return 0;
}

//=============================
// �������
//=============================
void CObject::Release()
{
	//NULL�`�F�b�N
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		if (m_pObject[i][m_nID] != nullptr)
		{
			int nID = m_nID;				//�ԍ���ۑ�
			delete m_pObject[i][nID];		//�I�u�W�F�N�g�̉��
			m_pObject[i][nID] = nullptr;	//NULL�ɂ���]
			return;
		}
	}
}

//=============================
// �I�u�W�F�N�g�̎擾
//=============================
CObject *CObject::GETObject(int nPriority, int nCnt)
{
	return m_pObject[nPriority][nCnt];
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