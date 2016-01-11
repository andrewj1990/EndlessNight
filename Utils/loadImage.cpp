#include "loadImage.h"

BYTE* loadImage(const char* filename, unsigned int* width, unsigned int* height)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = nullptr;

	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(filename);
	}
	if (fif == FIF_UNKNOWN)
	{
		return nullptr;
	}

	if (FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, filename);
	}
	if (!dib)
	{
		return nullptr;
	}

	BYTE* result = FreeImage_GetBits(dib);

	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);

	//FreeImage_Unload(dib);
	return result;
}