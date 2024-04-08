#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
};

// 1. 그리기를 그릴 것
// 2. 스페이스바를 눌러 총알을 쏘는데 세 발 쏘기