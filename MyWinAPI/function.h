#pragma once

#include "pch.h"
#include "Object.h"

/// <summary>
/// �̺�Ʈ ������ �ʿ��� ������ �̺�Ʈ �Ŵ����� ���������ϴ� �Լ����Դϴ�
/// </summary>

void instantiate(Object* _osbj, GROUP_TYPE _type);
void destroy(Object* _obj);
void changeScene(SCENE_TYPE _nextScene);

template<typename T> // �Լ� ���ø�(�Լ��ʹ� �ٸ���!!!). ���ϴ� Ÿ���� ã�� ȣ�� ��Ŵ(?)
void safeDeleteVector(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void safeDeleteMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); iter++)
	{
		if (iter->second != nullptr)
			delete iter->second;
	}
	_map.clear();
}