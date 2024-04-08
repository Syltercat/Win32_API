#pragma once

#include "Obj.h"
#include "Bullet.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	void		Key_Input();
	CObj*		Create_Bullet(DIRECTION eDir);

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }

private:
	typedef list<CObj*>* BULLETPOINTER;
	BULLETPOINTER m_pBullet;
};

