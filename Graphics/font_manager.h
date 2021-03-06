#pragma once

#include <vector>
#include "font.h"

class FontManager
{
public:
	static void add(Font* font);
	static Font* get(const std::string& name);
	static Font* get(const std::string& name, const unsigned int& size);
	static void clean();

private:
	FontManager();

private:
	static std::vector<Font*> m_Fonts;


};