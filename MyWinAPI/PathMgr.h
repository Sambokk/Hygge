#pragma once

class PathMgr
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:
	wchar_t m_contentPath[255]; // 경로 이름
/// <summary>
/// 싱글톤 패턴 매크로
/// </summary>
public:
	SINGLE(PathMgr);
/// <summary>
/// 맴버 함수 선언 
/// </summary>
public:
	void initialize();
/// <summary>
/// 함수의 선언과 정의
/// </summary>
public:
	const wchar_t* getContentPath() { return m_contentPath; }
};