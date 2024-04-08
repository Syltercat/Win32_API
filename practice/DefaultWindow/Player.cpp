#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"

CPlayer::CPlayer():m_pBullet(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState('W'))
		m_pBullet->push_back(Create_Bullet(DIR_UP));
	if (GetAsyncKeyState('S'))
		m_pBullet->push_back(Create_Bullet(DIR_DOWN));
	if (GetAsyncKeyState('A'))
		m_pBullet->push_back(Create_Bullet(DIR_LEFT));
	if (GetAsyncKeyState('D'))
		m_pBullet->push_back(Create_Bullet(DIR_RIGHT));

	if (GetAsyncKeyState(VK_SPACE)) {
		m_pBullet->push_back(Create_Bullet(DIR_LU));
		m_pBullet->push_back(Create_Bullet(DIR_RU));
		m_pBullet->push_back(Create_Bullet(DIR_UP));
	}
}

CObj* CPlayer::Create_Bullet(DIRECTION eDir)
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, eDir);
	return pBullet;
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	Key_Input();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}
