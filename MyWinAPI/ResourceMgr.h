#pragma once

class Texture;

class ResourceMgr
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:
	map<wstring, Texture*> m_mapTexture;
/// <summary>
/// 싱글톤 패턴 매크로
/// </summary>
public:
	SINGLE(ResourceMgr);
/// <summary>
/// 맴버 변수 선언
/// </summary>
public:
	Texture* loadTexture(const wstring& _key, const wstring& _relativePath);
	Texture* findeTexture(const wstring& _key);
	void releaseTexture(Texture* _texture);
};

