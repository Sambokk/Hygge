#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::deleteObjectInGroup(GROUP_TYPE _targetGroup)
{
	safeDeleteVector(m_objects[(UINT)_targetGroup]);
}

/// <summary>
/// 모든 오브젝트 삭제
/// </summary>
void Scene::deleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		deleteObjectInGroup((GROUP_TYPE)i);
	}
}


void Scene::update(KeyMgr* _keyManager)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_objects[i].size(); j++)
		{
			if (!m_objects[i][j]->isRemove())
			{
				m_objects[i][j]->update();
			}
		}
	}
}

void Scene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_objects[i].size(); j++)
		{
			if (!m_objects[i][j]->isRemove())
			{
				m_objects[i][j]->finalUpdate();
			}
		}
	}
}

void Scene::render(HDC _dc, Graphics* _grapics)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<Object*>::iterator iterator = m_objects[i].begin();

		for (; iterator != m_objects[i].end();)
		{
			if (!(*iterator)->isRemove())
			{
				(*iterator)->render(_dc, _grapics);
				++iterator;
			}
			else
			{
				iterator = m_objects[i].erase(iterator);
			}
		}
	}
}

void Scene::exit()
{
	deleteAll();
}
