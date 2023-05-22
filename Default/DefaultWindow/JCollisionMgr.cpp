#include "stdafx.h"
#include "JCollisionMgr.h"
#include "JBall.h"
#include "JPlayer.h"

CJCollisionMgr::CJCollisionMgr()
{
}


CJCollisionMgr::~CJCollisionMgr()
{
}

void CJCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
	RECT rc;
	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			RECT rcDest = { Dest->Get_vecPoint()[0].x, Dest->Get_vecPoint()[0].y, Dest->Get_vecPoint()[2].x, Dest->Get_vecPoint()[2].y };
			RECT rcSour = { Sour->Get_vecPoint()[0].x, Sour->Get_vecPoint()[0].y, Sour->Get_vecPoint()[2].x, Sour->Get_vecPoint()[2].y };

			if (IntersectRect(&rc, &rcDest, &rcSour))
			{
				Dest->Collide(Sour->Get_Type(), Sour);
				Sour->Collide(Dest->Get_Type(), Dest);
			}
		}
	}
}

void CJCollisionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			if (RectEx_Check(Dest, Sour, &fX, &fY))
			{
				// 상 하 충돌
				if (fX > fY)
				{
					if (Dest->Get_Info().vPos.y < Sour->Get_Info().vPos.y)
					{
						
						Dest->Collide(Sour->Get_Type(), Sour);

						static_cast<CJBall*>(Sour)->Set_Dir(DIR_BOTTOM);
						Sour->Collide(Dest->Get_Type(), Dest);
					}
					else
					{
						Dest->Collide(Sour->Get_Type(), Sour);

						static_cast<CJBall*>(Sour)->Set_Dir(DIR_TOP);
						Sour->Collide(Dest->Get_Type(), Dest);
					}
				}
				// 좌 우 충돌
				else
				{
					if (Dest->Get_Info().vPos.x < Sour->Get_Info().vPos.x)
					{
						Dest->Collide(Sour->Get_Type(), Sour);

						static_cast<CJBall*>(Sour)->Set_Dir(DIR_RIGHT);
						Sour->Collide(Dest->Get_Type(), Dest);
					}
					else
					{
						Dest->Collide(Sour->Get_Type(), Sour);

						static_cast<CJBall*>(Sour)->Set_Dir(DIR_LEFT);
						Sour->Collide(Dest->Get_Type(), Dest);
					}
				}
			}
		}
	}
}

bool CJCollisionMgr::RectEx_Check(CObj * pDst, CObj * pSrc, float * _X, float * _Y)
{
	float fWidth = 0.f;
	float fHeight = 0.f;

	fWidth = fabs(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	fHeight = fabs(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float fRadiusX = (105.f) * 0.5f;
	float fRadiusY = (25.f) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*_X = fRadiusX - fWidth;
		*_Y = fRadiusY - fHeight;
		return true;
	}

	return false;
}

void CJCollisionMgr::Collision_SphereRect(list<CObj*> Dst, vector<CObj*> Src)
{
	RECT rc;
	for (auto& Dest : Dst)
	{
		for (auto& Sour : Src)
		{
			RECT rcDest = { Dest->Get_vecPoint()[0].x, Dest->Get_vecPoint()[0].y, Dest->Get_vecPoint()[2].x, Dest->Get_vecPoint()[2].y };
			RECT rcSour = { Sour->Get_vecPoint()[0].x, Sour->Get_vecPoint()[0].y, Sour->Get_vecPoint()[2].x, Sour->Get_vecPoint()[2].y };

			if (IntersectRect(&rc, &rcDest, &rcSour))
			{
				Dest->Collide(Sour->Get_Type(), Sour);
				Sour->Collide(Dest->Get_Type(), Dest);
			}
		}
	}
}

void CJCollisionMgr::Collide(CObj * _pTemp, CObj * _pSrc)
{


}

void CJCollisionMgr::TestTile(CObj * pDst, CObj * pSrc)
{

	float fWidth = 0.f;
	float fHeight = 0.f;

	fWidth = fabs(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	fHeight = fabs(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float fRadiusX = (21.f) * 0.5f;
	float fRadiusY = (21.f) * 0.5f;

	float fOverX = fRadiusX - fWidth;
	float fOverY = fRadiusY - fHeight;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		// 상하 충돌
		if (fOverX > fOverY)
		{
			if (pDst->Get_Info().vPos.y < pSrc->Get_Info().vPos.y)
			{
				static_cast<CJBall*>(pDst)->Set_Dir(DIR_TOP);
				pDst->Collide(pSrc->Get_Type(), pSrc);
				pSrc->Collide(pDst->Get_Type(), pDst);
			}
			else
			{
				static_cast<CJBall*>(pDst)->Set_Dir(DIR_BOTTOM);
				pDst->Collide(pSrc->Get_Type(), pSrc);
				pSrc->Collide(pDst->Get_Type(), pDst);
			}
		}
		// 좌우 충돌
		else
		{
			if (pDst->Get_Info().vPos.x < pSrc->Get_Info().vPos.x)
			{
				static_cast<CJBall*>(pDst)->Set_Dir(DIR_LEFT);
				pDst->Collide(pSrc->Get_Type(), pSrc);
				pSrc->Collide(pDst->Get_Type(), pDst);
			}
			else
			{
				static_cast<CJBall*>(pDst)->Set_Dir(DIR_RIGHT);
				pDst->Collide(pSrc->Get_Type(), pSrc);
				pSrc->Collide(pDst->Get_Type(), pDst);
			}
		}
	}
}

bool CJCollisionMgr::LineSphere_Collision(CObj* _pDest, CObj* _pSrc, const float& _fRad)
{
	//// 라인 오브젝트는 왼쪽 포인트(vLP)와, 오른쪽 포인트(vRP)를 멤버변수로 갖는다.
	//float lineLength = D3DXVec3Length(&(_pSrc->Get_Info().vLP - _pSrc->Get_Info().vRP));
	//float d1 = D3DXVec3Length(&(_pSrc->Get_Info().vLP - _pDest->Get_Info().vPos));
	//float d2 = D3DXVec3Length(&(_pSrc->Get_Info().vRP - _pDest->Get_Info().vPos));

	//// Check if any endpoint is inside the circle
	//if (d1 <= _fRad || d2 <= _fRad)
	//	return true;

	//// Check if any point on the line is within the circle's radius
	//float dx = _pSrc->Get_Info().vRP.x - _pSrc->Get_Info().vLP.x;
	//float dy = _pSrc->Get_Info().vRP.y - _pSrc->Get_Info().vLP.y;
	//float dot = ((_pDest->Get_Info().vPos.x - _pSrc->Get_Info().vLP.x) * dx + (_pDest->Get_Info().vPos.y - _pSrc->Get_Info().vLP.y) * dy) / (lineLength * lineLength);
	//float closestX = _pSrc->Get_Info().vLP.x + dot * dx;
	//float closestY = _pSrc->Get_Info().vLP.y + dot * dy;
	//D3DXVECTOR3 closestPoint = { closestX, closestY, 0.f };
	//float distanceToClosest = D3DXVec3Length(&(_pDest->Get_Info().vPos - closestPoint));
	//if (distanceToClosest <= _fRad)
	//	return true;
	//return false;
	return false;
}