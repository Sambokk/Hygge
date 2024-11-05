#include "pch.h"
#include "PathMgr.h"

#include "Core.h" // 디버깅용

PathMgr::PathMgr()
	: m_contentPath{}
{
}

PathMgr::~PathMgr()
{
}
/// <summary>
/// 솔루션 파일이 있는 폴더의 상위 폴더로 이동하여 상대 경로를 설정한 후, 
/// \\bin\\content\\ 문자열을 m_contentPath에 추가한다.
/// </summary>
void PathMgr::initialize()
{
	// 현재 경로를 얻음
	GetCurrentDirectory(255, m_contentPath);
	// 문자열 길이를 얻음
	int forePath = (int)wcslen(m_contentPath);

	// 상위 폴더로 가기위한 for문
	for (int i = forePath - 1; 0 <= i; --i)
	{
		if (m_contentPath[i] == '\\')
		{
			m_contentPath[i] = '\0';
			break;
		}
	}
	/* 이해를 위한 예시
	현재 경로가 `D:\Hygge\5_Project\MyWinApi` 라면
	i 가 뒤에서부터 시작해서 가장 먼저 만나는 \ 를 지워버린다
	결과적으로 경로는 `D:\Hygge\5_Project` 가 되버린다
	*/

	wcscat_s(m_contentPath, 255, L"\\bin\\content\\");
}
