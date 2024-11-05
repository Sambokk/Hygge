#pragma once

class Res
{
/// <summary>
/// 맴버 변수
/// </summary>
private:
	wstring m_key;			// 리소스 키
	wstring m_relativePath; // 상대 경로
/// <summary>
/// 생성자와 소멸자
/// </summary>
public:
	Res();
	~Res();
/// <summary>
/// 맴버 함수 선언과 정의
/// </summary>
public:
	void setKey(const wstring& _key) { m_key = _key; }
	void setRelativePath(const wstring& _path) { m_relativePath = _path; }

	const wstring& getKey() { return m_key; }
	const wstring& getRelativePath() { return m_relativePath; }
};

