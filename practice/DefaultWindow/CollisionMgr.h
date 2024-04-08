#pragma once
#include "Obj.h"
class CollisionMgr :
    public CObj
{
public:
    CollisionMgr();
    ~CollisionMgr();

    static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);
};

