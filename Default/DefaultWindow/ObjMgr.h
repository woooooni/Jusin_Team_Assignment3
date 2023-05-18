#pragma once
#include	"Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

	static		CObjMgr*		inst;
	list<CObj*>		m_ObjList[OBJ_END];
	list<OBJ_TYPE> m_DeleteList;
	list<CObj*>		m_RenderList[REND_END];


public:
	static		CObjMgr*		Get_Inst()
	{
		if (inst == nullptr)
		{
			inst = new CObjMgr;
		}

		return inst;
	}

	void		Add_Obj(OBJ_TYPE p_Type, CObj* p_Obj);



	void		Clear_Obj(OBJ_TYPE p_Type)
	{
		if (m_ObjList[p_Type].empty())
			return;

		for (auto& iter : m_ObjList[p_Type])
		{
			iter->Set_Dead();
		}

	}


	void		Clear_All()
	{
		for (auto& iter : m_ObjList)
		{
			if (iter.empty())
				continue;

			for (auto& iterB : iter)
			{
				iterB->Set_Dead();
			}
		}
	}


	list<CObj*>& 	Get_All(OBJ_TYPE p_T)
	{

		return m_ObjList[p_T];
	}

	CObj*		Get_Last(OBJ_TYPE p_Typ)
	{
		if (m_ObjList[p_Typ].empty())
			return nullptr;
		return m_ObjList[p_Typ].back();
	}

	CObj*		Find_Obj(CObj* p_Find)
	{
		for (auto& iterA : m_ObjList)
		{
			auto iter = find(iterA.begin(), iterA.end(), p_Find);

			if (iter != iterA.end() && (*iter) != nullptr && !(*iter)->Get_Dead())
				return *iter;
			else if (iter != iterA.end())
				return nullptr;
		}

		return nullptr;
	}



	void	Update()
	{
		for (auto& iter : m_ObjList)
		{
			for (auto i = iter.begin(); i != iter.end();)
			{
				if ((*i)->Get_Dead())
				{
					Safe_Delete<CObj*>(*i);
					*i = nullptr;
					i = iter.erase(i);
				}
				else
					++i;
			}
		}

		for (auto& iterA : m_ObjList)
		{
			for (auto& iterB : iterA)
			{
					iterB->Update();
			}
		}
	}
	void	Late_Update()
	{
		for (auto& iterA : m_ObjList)
		{
			for (auto& iterB : iterA)
			{


				iterB->Late_Update();

				if (!iterB->Get_Dead() && iterB->Get_Rend() != REND_END)
					m_RenderList[iterB->Get_Rend()].push_back(iterB);

			}
		}
	}
	void	Render(HDC hDC)
	{
		for (auto& iterA : m_RenderList)
		{
			for (auto& iterB : iterA)
			{
				iterB->Render(hDC);
			}

			iterA.clear();
		}
	}

	void	Update_ByType(OBJ_TYPE p_Type)
	{

		for (auto i = m_ObjList[p_Type].begin(); i != m_ObjList[p_Type].end();)
		{
			if ((*i)->Get_Dead())
			{
				Safe_Delete<CObj*>(*i);
				*i = nullptr;
				i = m_ObjList[p_Type].erase(i);
			}
			else
				++i;
		}

		for (auto& iter : m_ObjList[p_Type])
		{
				iter->Update();
		}
	}

	void	Late_Update_ByType(OBJ_TYPE p_Type)
	{
		for (auto& iter : m_ObjList[p_Type])
		{
			iter->Late_Update();

			if (!iter->Get_Dead() && iter->Get_Rend() != REND_END)
				m_RenderList[iter->Get_Rend()].push_back(iter);
		}
	}

};

