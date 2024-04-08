#include "stdafx.h"
#include "CollisionMgr.h"

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT rc{};
	for (auto& Dst : _Dst) {
		for (auto& Src : _Src) {
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect()))) {
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}