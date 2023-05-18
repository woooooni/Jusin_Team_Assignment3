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
	void			SetTargetObj(CObj_TW* _obj)		{ m_pTargetObj = _obj; }
	D3DXVECTOR3		GetLookAt()						{ return m_vCurLookAt; }

	D3DXVECTOR3 GetRenderPos(D3DXVECTOR3 _vObjPos)	{ return _vObjPos - m_vDiff; }
	D3DXVECTOR3 GetRealPos(D3DXVECTOR3 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void SetCameraMode(CAMERA_MODE _eMode)			{ m_eMode = _eMode; }


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

private:
	void CalDiff();
	void Follow();

public:
	void Initialize();
	void Update();
	void Render(HDC _dc);


private:
	D3DXVECTOR3					m_vLookAt;				//	ī�޶� ���� ��ġ.
	D3DXVECTOR3					m_vPrevLookAt;			//	ī�޶� ���� ���������� ��ġ.
	D3DXVECTOR3					m_vCurLookAt;			//	���� ��ġ�� ���� ��ġ ���� ��ġ.
	D3DXVECTOR3					m_vResolution;			//  ī�޶� �ػ�.


	CObj_TW*					m_pTargetObj;			//	ī�޶� Ÿ�� ������Ʈ.
	D3DXVECTOR3					m_vDiff;				//	�ػ� �߽���ġ�� ī�޶� LookAt���� ���� ��.

	float						m_fTime;				// Ÿ���� ���󰡴µ� �ɸ��� �ð�.
	float						m_fSpeed;				// Ÿ���� ���󰡴� �ӵ�.
	float						m_fAccTime;				// Ÿ���� ���󰡴µ� ����� �����ð�.

	float						m_fShakeForce;

	list<tCamEffect>			m_lCamEffect;
	CAMERA_MODE					m_eMode;
};