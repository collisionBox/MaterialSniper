#include "textWindow.h"

TextWindow::TextWindow()
{
	mx = 0; my = 0;
	mw = 0; mh = 0;
	mTextBuf[0]  = '\0';
	mFontName[0] = '\0';
	mFontPath[0] = '\0';

	mbFontReady = false;
}

TextWindow::~TextWindow()
{
	if (strlen(mFontPath))
	{
		RemoveFontResourceEx(mFontPath, FR_PRIVATE, NULL);
	}
}

void TextWindow::setWindowFont(const char* FontPath, const char* in_fontName)
{
	strcpy(mFontPath, FontPath);

	if (AddFontResourceEx(FontPath, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	strcpy(mFontName, in_fontName);

	ChangeFont(mFontName, DX_CHARSET_DEFAULT);
}

void TextWindow::setWindow(int posX, int posY, int in_w, int in_h)
{
	mx = posX;
	my = posY;
	mw = in_w;
	mh = in_h;
}

void TextWindow::setFontSize(int fontSize)
{
	mFontSize = fontSize;
	SetFontSize(mFontSize);
}

void TextWindow::setText(char *text, int letterNum)
{
	int textLen = strlen(text) * 2;

	if (letterNum > 512 - 1 || textLen > 512 - 1)
	{
		letterNum = 512 / 2 - 1;
		strncpy(mTextBuf, text, letterNum);
	}
	else
	{
		strncpy(mTextBuf, text, letterNum * 2);
	}

	mTextBuf[letterNum * 2] = '\0';
}

void TextWindow::drawWindow()
{
	const int ofs = 6;
	DrawBox(mx - ofs, my - ofs, 
		    mx + mw + ofs, my + mh + ofs,
		    0xff000000, TRUE);
	DrawRoundRect(mx - ofs, my - ofs,
				  mx + mw + ofs, my + mh + ofs,
		          ofs, ofs, 0xffffffff, TRUE);

	DrawRoundRect(mx, my,
		          mx + mw, my + mh, 
		          ofs, ofs, 0xff000000, TRUE);

	DrawString(mx + ofs, my, mTextBuf, GetColor(255, 255, 255));
}
