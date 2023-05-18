#include "stdafx.h"
#include "Camera_TW.h"
#include "Obj_TW.h"
#include "MainGame.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

CCamera_TW::CCamera_TW()
	: m_pTargetObj(nullptr)
	, m_fTime(.5f)
	, m_fSpeed(10.f)
	, m_fAccTime(.2f)
	, m_eMode(CAMERA_MODE::NORMAL)
	, m_fShakeForce(10.f)
{

}

CCamera_TW::~CCamera_TW()
{
}


void CCamera_TW::Initialize()
{
	m_vResolution = D3DXVECTOR3{ 800.f, 600.f, 0.f };
	// m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
	m_vLookAt = m_vResolution;
}

void CCamera_TW::Update()
{
	switch (m_eMode)
	{
	case CAMERA_MODE::NORMAL:
		Follow();
		//LockMove();
		break;
	}

	CalDiff();
}

void CCamera_TW::Render(HDC _dc)
{

	if (!m_lCamEffect.empty())
	{
		tCamEffect& effect = m_lCamEffect.front();
		effect.fCurTime += DELTA_TIME;


		float fRatio = 0.f;
		fRatio = clamp(effect.fCurTime / effect.fDuration, 0.f, 1.f);


		if (CAM_EFFECT::SHAKE == effect.eEffect)
		{
			float fOffsetX = (std::rand() % static_cast<int>(m_fShakeForce * 2)) - m_fShakeForce;
			float fOffsetY = (std::rand() % static_cast<int>(m_fShakeForce * 2)) - m_fShakeForce;
			m_vLookAt += D3DXVECTOR3(fOffsetX, fOffsetY, 0.f);
		}

		if (effect.fDuration < effect.fCurTime)
		{
			m_lCamEffect.pop_front();
		}
	}
}


void CCamera_TW::CalDiff()
{
	m_fAccTime += DELTA_TIME;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		D3DXVECTOR3 vDir = m_vLookAt - m_vPrevLookAt;

		if (vDir.x >= 0.f || vDir.y >= 0.f)
		{
			D3DXVec3Normalize(&vDir, &vDir);
			m_vCurLookAt = m_vPrevLookAt + vDir * m_fSpeed * DELTA_TIME;
		}
	}

	D3DXVECTOR3 vCenter = m_vResolution / 2.f;


	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}

void CCamera_TW::Follow()
{
	if (m_pTargetObj)
	{
		D3DXVECTOR3 vObjPos = m_pTargetObj->GetPos();
		float vDist = sqrt(((m_vLookAt.x - vObjPos.x) * (m_vLookAt.x - vObjPos.x)) + ((m_vLookAt.y - vObjPos.y) * (m_vLookAt.y - vObjPos.y)));

		/*if (vDist > 200.f)*/
		m_vLookAt = m_pTargetObj->GetPos();
	}
}