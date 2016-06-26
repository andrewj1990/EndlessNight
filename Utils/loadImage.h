#pragma once

#include <FreeImage.h>
#include <GL\glew.h>

GLubyte* loadImage(const char* filename, unsigned int& width, unsigned int& height);
