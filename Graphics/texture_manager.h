#pragma once

#include <vector>
#include "texture.h"

class TextureManager
{
public:
	static void add(Texture* texture);
	static Texture* get(const std::string& name);
	static void clean();

private:
	TextureManager();

private:
	static std::vector<Texture*> m_Textures;

};