#pragma once

class Texture;

class ResourceMgr
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:
	map<wstring, Texture*> m_mapTexture;
/// <summary>
/// �̱��� ���� ��ũ��
/// </summary>
public:
	SINGLE(ResourceMgr);
/// <summary>
/// �ɹ� ���� ����
/// </summary>
public:
	Texture* loadTexture(const wstring& _key, const wstring& _relativePath);
	Texture* findeTexture(const wstring& _key);
	void releaseTexture(Texture* _texture);
};

