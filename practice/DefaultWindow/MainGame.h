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

// 1. �׸��⸦ �׸� ��
// 2. �����̽��ٸ� ���� �Ѿ��� ��µ� �� �� ���