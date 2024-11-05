#include "pch.h"
#include "PathMgr.h"

#include "Core.h" // ������

PathMgr::PathMgr()
	: m_contentPath{}
{
}

PathMgr::~PathMgr()
{
}
/// <summary>
/// �ַ�� ������ �ִ� ������ ���� ������ �̵��Ͽ� ��� ��θ� ������ ��, 
/// \\bin\\content\\ ���ڿ��� m_contentPath�� �߰��Ѵ�.
/// </summary>
void PathMgr::initialize()
{
	// ���� ��θ� ����
	GetCurrentDirectory(255, m_contentPath);
	// ���ڿ� ���̸� ����
	int forePath = (int)wcslen(m_contentPath);

	// ���� ������ �������� for��
	for (int i = forePath - 1; 0 <= i; --i)
	{
		if (m_contentPath[i] == '\\')
		{
			m_contentPath[i] = '\0';
			break;
		}
	}
	/* ���ظ� ���� ����
	���� ��ΰ� `D:\Hygge\5_Project\MyWinApi` ���
	i �� �ڿ������� �����ؼ� ���� ���� ������ \ �� ����������
	��������� ��δ� `D:\Hygge\5_Project` �� �ǹ�����
	*/

	wcscat_s(m_contentPath, 255, L"\\bin\\content\\");
}
