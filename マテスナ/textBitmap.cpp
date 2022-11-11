#include "DxLib.h"
#include "textBitmap.h"

const int maxImgNum = 256;
TextBitmap::TextBitmap()
{
	for (int i = 0; i < maxImgNum; i++)
	{
		fontMap[i] = -1;
	}
}

TextBitmap::~TextBitmap()
{
	for (int i = 0; i < maxImgNum; i++)
	{
		DeleteGraph(fontImg[i]);
	}
}

void TextBitmap::SetFontImg(int numX, int numY, char* fontImgFlieName)
{
	int tmpImg, imgX, imgY;

	tmpImg = LoadGraph(fontImgFlieName);
	if (tmpImg == -1)
	{
		printfDx("fontFile load failed:[%s]", fontImgFlieName);
		return;
	}
	GetGraphSize(tmpImg, &imgX, &imgY);
	DeleteGraph(tmpImg);

	sizeX = imgX / numX;
	sizeY = imgY / numY;
	LoadDivGraph(fontImgFlieName, numX * numY, numX, numY, sizeX, sizeY, fontImg);

}

void TextBitmap::TextDraw(int x, int y, char* string)
{
	int textX, textY, img;
	textX = x;
	textY = y;
	while (*string)
	{
		if (*string == '\n')
		{
			textX = x;
			textY += sizeY;
			string++;
			continue;
		}
		img = IsString(*string);
		if (img >= 0)
		{
			DrawGraph(textX, textY, fontImg[img], true);
		}
		textX += sizeX;
		string++;
	}
	
}

void TextBitmap::InitMapText(char* initMapText)
{
	int num = 0;
	char* p;

	p = initMapText;
	char n = 0;
	while (*p && n < 255)
	{
		fontMap[*p++] = n++;
	}
}

int TextBitmap::IsString(char c)
{
	return fontMap[c];
}

