#include "stdafx.h"
#include "JTileMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CJTileMgr*		CJTileMgr::m_pInstance = nullptr;

CJTileMgr::CJTileMgr()
{
}


CJTileMgr::~CJTileMgr()
{
	Release();
}

void CJTileMgr::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float(TILECX * j) + (TILECX >> 1);
			float	fY = float(TILECY * i) + (TILECY >> 1);

			VECTOR  vPos = { fX, fY, 0.f };

			CObj*		pObj = CAbstractFactory<CJTile>::Create(vPos);
			m_vecTile.push_back(pObj);
		}
	}

}

void CJTileMgr::Update(void)
{
	for (auto iter = m_vecTile.begin();
		iter != m_vecTile.end();)
	{
		(*iter)->Update();

		if ((*iter)->Get_Dead())
		{
			Safe_Delete<CObj*>(*iter);
			*iter = nullptr;
			iter = m_vecTile.erase(iter);
		}
		else if(!(*iter)->Get_Dead())
		{
			++iter;
		}
			
	}

	/*for (auto& iter : m_vecTile)
		iter->Update();*/
}

void CJTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CJTileMgr::Render(HDC hDC)
{
	for (auto& iter : m_vecTile)
		iter->Render(hDC);

}

void CJTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CJTileMgr::Picking_Tile(POINT _pt, int _iDrawID, int _iOption)
{
	int		j = _pt.x / TILECX;
	int		i = _pt.y / TILECY;

	int		iIndex = i * TILEX + j;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CJTile*>(m_vecTile[iIndex])->Set_Tile(_iDrawID, _iOption);
}

void CJTileMgr::Save_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("save File"), L"Fail", MB_OK);
		return;
	}

	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	for(auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CJTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CJTile*>(iter)->Get_Option();

		WriteFile(hFile, &(iter->Get_Info().vPos), sizeof(VECTOR), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);		
	}

	CloseHandle(hFile);
}

void CJTileMgr::Load_Tile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",		
		GENERIC_READ,			
		NULL,					
		NULL,					
		OPEN_EXISTING,			
		FILE_ATTRIBUTE_NORMAL,	
		NULL);					

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	VECTOR	vPos = { 0.f, 0.f, 0.f };
	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;
	
	while (true)
	{
		ReadFile(hFile, &vPos, sizeof(VECTOR), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		if (iDrawID == 0)
			continue;

		CObj*	pObj = CAbstractFactory<CJTile>::Create(vPos);
		dynamic_cast<CJTile*>(pObj)->Set_Tile(iDrawID, iOption);
		m_vecTile.push_back(pObj);
	}

	CloseHandle(hFile);
}

CObj* CJTileMgr::Get_Tile(CObj * pObj)
{
	if (m_vecTile.empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance = 0.f;

	for (auto& iter :m_vecTile)
	{
		if (iter->Get_Dead())
			continue;

		VECTOR Target = iter->Get_Info().vPos - pObj->Get_Info().vPos;

		float	fDiagonal = D3DXVec3Length(&Target);

		if ((!pTarget) || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}
