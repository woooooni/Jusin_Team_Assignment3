#pragma once

extern HWND	g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			VK_MAX		0xff

#define			SINGLETON(type) public:\
						static type* GetInst()\
						{\
							static type manager;\
							return &manager;\
						}\
						private:\
							type();\
							~type();


#define			PI			3.1415926535
#define			DELTA_TIME	CTimeMgr::GetInst()->GetfDT()

static D3DXVECTOR3        Get_Mouse()
{
	POINT  pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	return	{ float(pt.x), float(pt.y), 0.f };
}





enum OBJ_TYPE
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_GROUND,
	OBJ_LASER,
	OBJ_BULLET,
	OBJ_UI,
	OBJ_END
};

enum class COLLISION_DIR
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
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
	SCENE_TAWON,
	SCENE_END,
};

enum class CAMERA_MODE
{
	NORMAL,
	END
};

enum class STATE
{
	IDLE,
	MOVE,
	HANG,
	JUMP,
	TIME_REWIND,
	DIE,
	END
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


template<typename T1>
T1 clamp(T1 src, T1 min, T1 max)
{
	if (src > max)
		return max;
	if (src < min)
		return min;
	return src;
};




