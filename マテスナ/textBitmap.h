#pragma once

class TextBitmap
{
public:
	TextBitmap();
	~TextBitmap();
	void SetFontImg(int numX, int numY, char* fontImgFlieName);
	void TextDraw(int x, int y, char* string);
	void InitMapText(char* initMapText);
private:

	int fontImg[256];
	int fontMap[256];
	unsigned int sizeX;
	unsigned int sizeY;
	int IsString(char c);
};

