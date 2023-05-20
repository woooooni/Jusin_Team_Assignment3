#include "stdafx.h"
#include "LPlayer.h"
#include	"TimeMgr.h"
#include	"AbstractFactory.h"
#include	"LMyButton.h"
#include	"ObjMgr.h"
#include	"SceneMgr.h"
#include	"LMonsterMgr.h"
#include	"LItemMgr.h"


CLPlayer::CLPlayer()
{
}


CLPlayer::~CLPlayer()
{
	Release();
}

void CLPlayer::Initialize(void)
{
	m_tInfo = { { 400.f, 300.f,0.f },{ 1.f,0.f,0.f } ,{ 50.f, 50.f,0.f } };
	m_fSpeed = 3.f;
	m_eObjType = OBJ_PLAYER;

	m_vLineP[0] = { cosf(D3DXToRadian(75.f)) * m_tInfo.vSize.x * 0.5f, sinf(D3DXToRadian(75.f)) * m_tInfo.vSize.y* 0.5f ,0 };
	m_vLineP[1] = { cosf(D3DXToRadian(75.f)) * m_tInfo.vSize.x* 0.5f, -sinf(D3DXToRadian(75.f)) * m_tInfo.vSize.y* 0.5f ,0 };
	m_vLineP[2] = { -m_tInfo.vSize.x* 0.5f, 0,0 };


}

int CLPlayer::Update(void)
{
	Key_Input();


	return 0;
}

void CLPlayer::Render(HDC hDC)
{

	HBRUSH myB = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);



	vector<D3DXVECTOR3> vecSrc;

	D3DXMATRIX mSrc;
	for (size_t i = 0; i < 3; i++)
	{
		vecSrc.push_back(m_vLineP[i]);

		float fc = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &m_tInfo.vDir);

		float fAngle = acosf(fc);

		if (m_tInfo.vDir.y < 0)
			fAngle = 2.f * PI - fAngle;

		D3DXMatrixRotationZ(&mSrc, fAngle);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

		D3DXMatrixTranslation(&mSrc, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

	}


	MoveToEx(hDC, (int)vecSrc[0].x, (int)vecSrc[0].y, nullptr);
	LineTo(hDC, (int)vecSrc[1].x, (int)vecSrc[1].y);

	D3DXVECTOR3		vSrc = vecSrc[0] + ((vecSrc[1] - vecSrc[0]) * 0.5f);

	MoveToEx(hDC, (int)vSrc.x, (int)vSrc.y, nullptr);
	LineTo(hDC, (int)vecSrc[2].x, (int)vecSrc[2].y);

}

void CLPlayer::Release(void)
{
	CObj*		startBut = CAbstractFactory<CLMyButton>::Create({ { WINCX * 0.5f, WINCY * 0.5f , 0 },{},{ 300.f, 200.f, 0 } });
	startBut->Set_Name(L"게임 오버");
	static_cast<CLMyButton*>(startBut)->Set_ClickEvent([]()
	{
		CSceneMgr::Get_Inst()->Change_Scene(SCENE_START);
		CTimeMgr::GetInst()->SetTimeScale(1.f);
		CLMonsterMgr::Get_Inst()->Reset();
		CLItemMgr::GetInst()->Reset();

	});

	CObjMgr::Get_Inst()->Add_Obj(OBJ_UI, startBut);
}

void CLPlayer::Key_Input(void)
{



	D3DXVECTOR3 vTmp = ::Get_Mouse() - m_tInfo.vPos;

	float		dist = D3DXVec3Length(&vTmp);

	if (dist > 300.f)
		m_fSpeed = 300.f * DELTA_TIME;
	else if (dist > 100.f)
		m_fSpeed = 200.f * DELTA_TIME;
	else if (dist > 1.f)
		m_fSpeed = 100.f * DELTA_TIME;
	else
	{
		return;
	}

	D3DXVec3Normalize(&vTmp, &vTmp);

	m_tInfo.vDir = vTmp;



	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	m_tInfo.vPos.x = clamp<float>(m_tInfo.vPos.x, 50.f, WINCX - 50.f);
	m_tInfo.vPos.y = clamp<float>(m_tInfo.vPos.y, 50.f, WINCY - 50.f);

}

void CLPlayer::Collide(OBJ_TYPE p_type, CObj * p_targ)
{
	if (p_type == OBJ_MONSTER)
	{
		m_bDead = true;
		CTimeMgr::GetInst()->SetTimeScale(0.f);
	}

	
}

void CLPlayer::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}
