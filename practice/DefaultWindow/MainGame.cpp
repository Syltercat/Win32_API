#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "CollisionMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);

	for (int i = 0; i < 3; i++) {
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(250.f), float(130.f * (i + 1))));
	}
}

void CMainGame::Update()
{
	for (size_t i = 0; i < OBJ_END; i++) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int Result = (*iter)->Update();
			if (OBJ_DEAD == Result) {
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else ++iter;
		}

	}
}

void CMainGame::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; i++) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Late_Update();
		}
	}
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	for (size_t i = 0; i < OBJ_END; i++) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Render(m_hDC);
		}
	}
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);	

	for (size_t i = 0; i < OBJ_END; i++) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
