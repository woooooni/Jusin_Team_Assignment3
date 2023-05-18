#include "stdafx.h"
#include "LMonsterMgr.h"


CLMonsterMgr*	CLMonsterMgr::inst = nullptr;

CLMonsterMgr::CLMonsterMgr() : m_dCreateCoolTime(0), m_dLastCreatedTime(0)
{
}


CLMonsterMgr::~CLMonsterMgr()
{
}

void CLMonsterMgr::Create_Monster()
{
}
