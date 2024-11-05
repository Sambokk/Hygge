#include "pch.h"
#include "ResourceMgr.h"

#include "PathMgr.h"
#include "Texture.h"

ResourceMgr::ResourceMgr()
	: m_mapTexture{}
{
}

ResourceMgr::~ResourceMgr()
{
	map<wstring, Texture*>::iterator myIterator = m_mapTexture.begin();
	for (; myIterator != m_mapTexture.end(); ++myIterator)
	{
		delete myIterator->second;
	}
}

Texture* ResourceMgr::loadTexture(const wstring& _key, const wstring& _relativePath)
{
	Texture* texture = findeTexture(_key);
	if (texture != nullptr)
	{
		return texture;
	}

	wstring filePath = PathMgr::GetInstance()->getContentPath();
	filePath += _relativePath;

	// 텍스처를 생성하고 초기화합니다.
	texture = new Texture();
	texture->load(filePath);
	texture->setKey(_key);
	texture->setRelativePath(_relativePath);

	m_mapTexture.insert(make_pair(_key, texture));

	return texture;
}

Texture* ResourceMgr::findeTexture(const wstring& _key)
{
	map<wstring, Texture*>::iterator iterator = m_mapTexture.find(_key);

	if (iterator == m_mapTexture.end())
	{
		return nullptr;
	}

	return iterator->second;
}

void ResourceMgr::releaseTexture(Texture* _texture)
{
	// 텍스처를 찾아서 제거
	auto it = std::find_if(m_mapTexture.begin(), m_mapTexture.end(), [_texture](const auto& pair) {
		return pair.second == _texture;
		});

	if (it != m_mapTexture.end())
	{
		delete it->second;  // 텍스처 삭제
		m_mapTexture.erase(it);  // 맵에서 제거
	}
}
