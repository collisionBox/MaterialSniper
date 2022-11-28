#pragma once

class TextBitmap
{
public:
	static TextBitmap& GetInstance()
	{
		static TextBitmap text;
		return text;
	}
	TextBitmap();
	~TextBitmap();
	void SetFontImg(int numX, int numY, const char* fontImgFlieName);
	//void SetFontImg();
	void TextDraw(int x, int y, const char* string);
	void InitMapText(const char* initMapText);
	void test();
	int a;
private:
	int fontImg[256];
	int fontMap[256];
	unsigned int sizeX;
	unsigned int sizeY;
	int IsString(char c);
};

