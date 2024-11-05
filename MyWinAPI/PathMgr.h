#pragma once

class PathMgr
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:
	wchar_t m_contentPath[255]; // ��� �̸�
/// <summary>
/// �̱��� ���� ��ũ��
/// </summary>
public:
	SINGLE(PathMgr);
/// <summary>
/// �ɹ� �Լ� ���� 
/// </summary>
public:
	void initialize();
/// <summary>
/// �Լ��� ����� ����
/// </summary>
public:
	const wchar_t* getContentPath() { return m_contentPath; }
};