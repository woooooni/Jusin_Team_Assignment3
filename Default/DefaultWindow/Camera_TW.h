#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKE,
	ZOOM_IN,
	ZOOM_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT	eEffect;
	float		fDuration;
	float		fCurTime;
};



class CObj_TW;

class CCamera_TW
{
	SINGLETON(CCamera_TW);


public:
	void Initialize();
	void Update();
	void Render(HDC _dc);

public:
	void SetLookAt(D3DXVECTOR3 _vLook, bool _bForce = false)
	{
		m_vLookAt = _vLook;
		if (_bForce)
		{
			float fMoveDist = D3DXVec3Length(&(m_vLookAt - m_vPrevLookAt));
			m_fSpeed = 0.f;
			m_fAccTime = 999999999.f;
		}
		else
		{
			float fMoveDist = D3DXVec3Length(&(m_vLookAt - m_vPrevLookAt));
			m_fSpeed = fMoveDist / m_fTime;
			m_fAccTime = 0;
		}
	}
	void			SetTargetObj(CObj_TW* _obj);
	CObj_TW*		GetTargetObj() { return m_pTargetObj; }

	D3DXVECTOR3		GetLookAt()						{ return m_vCurLookAt; }

	D3DXVECTOR3 GetRenderPos(D3DXVECTOR3 _vObjPos)	{ return _vObjPos - m_vDiff; }
	D3DXVECTOR3 GetRealPos(D3DXVECTOR3 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void SetCameraMode(CAMERA_MODE _eMode)			{ m_eMode = _eMode; }

	float	GetMagnification()						{ return m_fMagnification; }

public:
	void CamShake(float _fDuration, float _fForce)
	{
		if (0.f == _fDuration)
			assert(nullptr);

		tCamEffect eft = {};
		eft.eEffect = CAM_EFFECT::SHAKE;
		eft.fDuration = _fDuration;
		eft.fCurTime = 0.f;

		m_lCamEffect.push_back(eft);

		m_fShakeForce = _fForce;
	}

	void ZoomIn(float _fDuration)
	{
		if (0.f == _fDuration)
			assert(nullptr);

		tCamEffect eft = {};
		eft.eEffect = CAM_EFFECT::ZOOM_IN;
		eft.fDuration = _fDuration;
		eft.fCurTime = 0.f;

		m_lCamEffect.push_back(eft);
	}

private:
	void CalDiff();
	void Follow();



private:
	D3DXVECTOR3					m_vLookAt;				//	카메라가 보는 위치.
	D3DXVECTOR3					m_vPrevLookAt;			//	카메라가 보는 이전프레임 위치.
	D3DXVECTOR3					m_vCurLookAt;			//	이전 위치와 현재 위치 보정 위치.
	D3DXVECTOR3					m_vResolution;			//  카메라 해상도.


	CObj_TW*					m_pTargetObj;			//	카메라 타겟 오브젝트.
	CObj_TW*					m_pPreTargetObj;		//	카메라 이전 타겟 오브젝트.
	D3DXVECTOR3					m_vDiff;				//	해상도 중심위치와 카메라 LookAt간의 차이 값.

	float						m_fTime;				// 타겟을 따라가는데 걸리는 시간.
	float						m_fSpeed;				// 타겟을 따라가는 속도.
	float						m_fAccTime;				// 타겟을 따라가는데 들었던 누적시간.
	float						m_fMagnification;		// 카메라 배율

	float						m_fShakeForce;

	list<tCamEffect>			m_lCamEffect;
	CAMERA_MODE					m_eMode;
};
