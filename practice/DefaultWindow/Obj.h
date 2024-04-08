#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize()	PURE;
	virtual int	Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release()		PURE;

	void Set_Pos(float _fX, float _fY) {
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void Set_Direction(DIRECTION eDir) {
		m_eDirection = eDir;
	}
	RECT Get_Rect() {
		return m_tRect;
	}
	INFO Get_Info() {
		return m_tInfo;
	}
	void Set_Dead(){ m_Dead = true; }

protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDirection;
	float		m_fSpeed;
	bool		m_Dead;

};

