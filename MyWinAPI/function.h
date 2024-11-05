#pragma once

#include "pch.h"
#include "Object.h"

/// <summary>
/// 이벤트 유형과 필요한 정보를 이벤트 매니저로 정보전달하는 함수들입니다
/// </summary>

void instantiate(Object* _osbj, GROUP_TYPE _type);
void destroy(Object* _obj);
void changeScene(SCENE_TYPE _nextScene);

template<typename T> // 함수 템플릿(함수와는 다르다!!!). 원하는 타입을 찾아 호출 시킴(?)
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