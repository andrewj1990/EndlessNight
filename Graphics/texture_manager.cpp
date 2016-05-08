#include "texture_manager.h"

std::vector<Texture*> TextureManager::m_Textures;
std::unordered_map<std::string, Texture*> TextureManager::m_TextureMap;

void TextureManager::add(Texture* texture)
{
	m_Textures.push_back(texture);

	std::string textureKey = texture->getName() + "_" + std::to_string(texture->getIndexY()) + "_" + std::to_string(texture->getIndexX());
	m_TextureMap.emplace(textureKey, texture);
}

Texture* TextureManager::get(const std::string& name)
{
	for (Texture* texture : m_Textures)
	{
		if (texture->getName() == name)
		{
			return texture;
		}
	}

	return nullptr;
}

Texture* TextureManager::get(const std::string& name, const int& row, const int& col)
{
	std::string textureKey = name + "_" + std::to_string(col) + "_" + std::to_string(row);

	return m_TextureMap[textureKey];
}

void TextureManager::clean()
{
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		delete m_Textures[i];
	}
}