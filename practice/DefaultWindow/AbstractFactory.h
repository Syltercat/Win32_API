#pragma once
#include "Obj.h"

template<typename T>
class CAbstractFactory {
public:
	CAbstractFactory();
	~CAbstractFactory();

	static CObj* Create() {
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY, DIRECTION eDir = DIR_END) {
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		pObj->Set_Direction(eDir);
		return pObj;
	}
};