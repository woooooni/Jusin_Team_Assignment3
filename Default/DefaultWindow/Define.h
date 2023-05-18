#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0

#define			PI			D3DX_PI

#define			VK_MAX			0xff




enum OBJ_TYPE
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_UI,
	OBJ_END
};

enum REND_TYPE
{
	REND_BACKGROUND,
	REND_OBJECT,
	REND_EFFECT,
	REND_UI,
	REND_END
};

enum SCENE_TYPE
{
	SCENE_START,
	SCENE_END,
};

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vSize;


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



extern HWND	g_hWnd;

static D3DXVECTOR3		Get_Mouse()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return{ float(pt.x), float(pt.y), 0.f };
}