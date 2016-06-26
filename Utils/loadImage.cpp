#include "loadImage.h"

GLubyte* loadImage(const char* filename, unsigned int& width, unsigned int& height)
{
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filename, 0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, filename);

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	width = FreeImage_GetWidth(imagen);
	height = FreeImage_GetHeight(imagen);

	GLubyte* textura = new GLubyte[4 * width * height];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).

	for (int j = 0; j < width * height; j++) {
		textura[j * 4 + 0] = pixeles[j * 4 + 2];
		textura[j * 4 + 1] = pixeles[j * 4 + 1];
		textura[j * 4 + 2] = pixeles[j * 4 + 0];
		textura[j * 4 + 3] = pixeles[j * 4 + 3];
		//cout<<j<<": "<<textura[j*4+0]<<"**"<<textura[j*4+1]<<"**"<<textura[j*4+2]<<"**"<<textura[j*4+3]<<endl;
	}

	return textura;

	//FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//FIBITMAP *dib = nullptr;

	//fif = FreeImage_GetFileType(filename, 0);
	//if (fif == FIF_UNKNOWN)
	//{
	//	fif = FreeImage_GetFIFFromFilename(filename);
	//}
	//if (fif == FIF_UNKNOWN)
	//{
	//	return nullptr;
	//}

	//if (FreeImage_FIFSupportsReading(fif))
	//{
	//	dib = FreeImage_Load(fif, filename);
	//}
	//if (!dib)
	//{
	//	return nullptr;
	//}

	//BYTE* pixels = FreeImage_GetBits(dib);

	//width = FreeImage_GetWidth(dib);
	//height = FreeImage_GetHeight(dib);

	//int size = width * height * (FreeImage_GetBPP(dib) / 8);
	//BYTE* result = new BYTE[size];
	//memcpy(result, pixels, size);

	//FreeImage_Unload(dib);
	//return result;
}