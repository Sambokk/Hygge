#pragma once

class Res
{
/// <summary>
/// �ɹ� ����
/// </summary>
private:
	wstring m_key;			// ���ҽ� Ű
	wstring m_relativePath; // ��� ���
/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
public:
	Res();
	~Res();
/// <summary>
/// �ɹ� �Լ� ����� ����
/// </summary>
public:
	void setKey(const wstring& _key) { m_key = _key; }
	void setRelativePath(const wstring& _path) { m_relativePath = _path; }

	const wstring& getKey() { return m_key; }
	const wstring& getRelativePath() { return m_relativePath; }
};

