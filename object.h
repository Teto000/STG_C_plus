//=====================================
//
// �I�u�W�F�N�g�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _OBJECT_H_
#define _OBJECT_H_	

//--------------------------
// �C���N���[�h
//--------------------------
#include <d3dx9.h>

//------------------------
// �}�N����`
//------------------------
#define MAX_OBJECT	(60)	//�I�u�W�F�N�g�̍ő吔

//--------------------------
// �I�u�W�F�N�g�N���X
//--------------------------
class CObject
{
public:
	//------------------------
	// �I�u�W�F�N�g�̎��
	//------------------------
	enum EObjType
	{
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_BULLET,		//�e
		OBJTYPE_EXPLOSION,	//����
		OBJTYPE_HP,			//HP
		OBJTYPE_MAX,
		OBJTYPE_INVALID
	};

	CObject();			//�R���X�g���N�^
	virtual ~CObject();	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//----------------
	// �ÓI�����o�֐�
	//----------------
	//static void CreateAll();
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static int GetNumAll();

	CObject *GETObject(int nCnt);
	void SetObjType(EObjType ObjType);	//��ނ̐ݒ�
	EObjType GetObjType();				//��ނ̎擾

	//�Q�b�^�[
	virtual D3DXVECTOR3 GetPosition() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

protected:
	void Release();

private:
	//----------------
	// �����o�ϐ�
	//----------------

	//----------------
	// �ÓI�����o�ϐ�
	//----------------
	static CObject *m_pObject[MAX_OBJECT];	//�I�u�W�F�N�g
	//	static int m_nNumAll;	//�I�u�W�F�N�g�̐�
	int m_nID;					//�i�[��̔ԍ�
	EObjType m_ObjType;	//�I�u�W�F�N�g�̎��
};

#endif // !_OBJECT_H_