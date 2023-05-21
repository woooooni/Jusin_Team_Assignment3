#include "stdafx.h"
#include "CollisionMgr_TW.h"
#include "Obj_TW.h"


CCollisionMgr_TW::CCollisionMgr_TW()
{
}


CCollisionMgr_TW::~CCollisionMgr_TW()
{
}


void CCollisionMgr_TW::Collision_RectEx(vector<CObj_TW*> _Dest, vector<CObj_TW*> _Sour, bool _bPush)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float    fX = 0.f, fY = 0.f;
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->GetPos().y > Sour->GetPos().y)
					{
						if (_bPush) Sour->Set_PosY(-fY);
						Dest->OnCollision(COLLISION_DIR::DIR_UP, Sour);
						Sour->OnCollision(COLLISION_DIR::DIR_DOWN, Dest);
					}
					else // 하 충돌
					{
						if (_bPush) Sour->Set_PosY(fY);
						Dest->OnCollision(COLLISION_DIR::DIR_DOWN, Sour);
						Sour->OnCollision(COLLISION_DIR::DIR_UP, Dest);
					}
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->GetPos().x > Sour->GetPos().x)
					{
						if (_bPush) Sour->Set_PosX(-fX);
						Dest->OnCollision(COLLISION_DIR::DIR_LEFT, Sour);
						Sour->OnCollision(COLLISION_DIR::DIR_RIGHT, Dest);
					}

					// 우 충돌
					else
					{
						if (_bPush) Sour->Set_PosX(fX);
						Dest->OnCollision(COLLISION_DIR::DIR_RIGHT, Sour);
						Sour->OnCollision(COLLISION_DIR::DIR_LEFT, Dest);
					}
				}
			}
		}
	}
}

bool CCollisionMgr_TW::Check_Rect(CObj_TW * pDest, CObj_TW * pSour, float * pX, float * pY)
{
	if (!pDest->IsActive() || !pSour->IsActive())
		return false;

	/*if (pDest->GetState() == STATE::DIE || pSour->GetState() == STATE::DIE)
		return false;*/

	float fWidth = abs(pDest->GetPos().x - pSour->GetPos().x);
	float fHeight = abs(pDest->GetPos().y - pSour->GetPos().y);

	float fCX = (pDest->GetScale().x + pSour->GetScale().x) * 0.5f;
	float fCY = (pDest->GetScale().y + pSour->GetScale().y) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}
