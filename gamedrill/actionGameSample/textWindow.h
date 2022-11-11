#pragma once

#include "game.h"

class TextWindow
{
public:
	TextWindow();
	~TextWindow();
	void setWindowFont(const char *FontPath ,const char* fontName);
	void setWindow(int posX, int posY, int w, int h);
	void setFontSize(int fontSize);
	void setText(char* text, int letterNum);
	void drawWindow();
	int  getNum() { return strlen(mTextBuf); }

private:
	int mx, my;
	int mw, mh;
	int mFontSize;
	char mTextBuf[1024];
	char mFontName[512];
	char mFontPath[512];
	bool mbFontReady;
};