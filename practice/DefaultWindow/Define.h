#pragma once

#define		WINCX		800
#define		WINCY		600

#define		PURE		= 0
#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

enum DIRECTION {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_LU,
	DIR_RU,
	DIR_END
};

enum OBJID {
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_MONSTER,
	OBJ_END
};

typedef struct tagInfo
{
	float		fX;		// 중점 x,y
	float		fY;
	float		fCX;	// 가로, 세로 길이
	float		fCY;

}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}


extern HWND		g_hWnd;

