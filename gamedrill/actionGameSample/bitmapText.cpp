#include "bitmapText.h"

const int maxImageNum = 256;

BitmapText::BitmapText()
{
	mUseflag      = false;
	mBgalpha      = true ;

	for (int i = 0; i < maxImageNum; i++)
	{
		mFontMap[i] = -1;
	}
	R = G = B = 255;
	mShadowR = 64;
	mShadowG = 64;
	mShadowB = 64;

	mShadowOffsetX = 1;
	mShadowOffsetY = 1;

}

BitmapText::~BitmapText()
{
	// �t�H���g�C���[�W�̉��
	if (mUseflag)
	{
		for (int i = 0; i < maxImageNum; i++)
		{
			DeleteGraph(mFontImg[i]);
		}
	}
	mUseflag = false;
}

void BitmapText::setFontImage(int Xnum, int Ynum, char * fontImgfilename)
{
	int tmpImg, imgX, imgY;

	// �t�@�C�����ǂݍ���
	tmpImg = LoadGraph(fontImgfilename);
	if (tmpImg == -1)
	{
		printf("fontfile load failed:[%s]", fontImgfilename);
		return;
	}
	//�@�摜�T�C�Y�c���擾
	GetGraphSize(tmpImg, &imgX, &imgY);
	DeleteGraph(tmpImg);

	// �t�H���g1���̏c���T�C�Y�擾
	mSizeX = imgX / Xnum;
	mSizeY = imgY / Ynum;

	// �摜�ǂݍ���
	LoadDivGraph(fontImgfilename, Xnum*Ynum, Xnum, Ynum, mSizeX, mSizeY, mFontImg);
	mUseflag = true;
}

void BitmapText::textDraw(int x, int y, char * string)
{
	//�t�H���g�g�p�\��
	if (!mUseflag)
		return;

	//�e�L�X�g�`��J�n
	int text_x, text_y, img;
	text_x = x;
	text_y = y;

	while (*string)
	{

		// ���������s�̏ꍇ�͉��s�{�߂�
		if (*string == '\n')
		{
			text_x = x;
			text_y += mSizeY;
			string++;
			continue;
		}

		//�����`��
		img = isString(*string);
		if (img >= 0)
		{
			DrawGraph(text_x, text_y, mFontImg[img], mBgalpha);
		}

		// �����`��ʒu�i�߂�
		text_x += mSizeX;
		string++;
	}

	SetDrawBright(255, 255, 255);
}

void BitmapText::textDrawWithShadow(int x, int y, char * string)
{
	//�e�����`��
	SetDrawBright(mShadowR, mShadowG, mShadowB);
	textDraw(x + mShadowOffsetX, y + mShadowOffsetY, string);

	//�����`��
	SetDrawBright(R, G, B);
	textDraw(x, y, string);

}

void BitmapText::textDrawRandom(int x, int y, char* string, int maxRand, int countDown)
{
	char randloopWidth = 'z' - '!';
	char *randString;

	int cnt=0;
	while (string[cnt])
		cnt++;

	randString = new char[cnt + 1];

	//���݂̕������烉���_��������쐬
	cnt = 0;
	char randCount;
	while (*string)
	{
		randCount = (maxRand % randloopWidth - countDown) < 0 ? 0 : (maxRand % randloopWidth - countDown);
		randString[cnt] = *string + randCount;
		cnt++;
		string++;
	}
	randString[cnt] = '\0';

	textDraw(x, y, randString);

	delete[] randString;
}

void BitmapText::textDrawMessage(int x, int y, char * string, unsigned int display_lengh)
{
	// ���������J�E���g���A�\�����������{���̕�������葽����΂��̂܂ܕ\��
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDraw(x, y, string);
		return;
	}

	// ��������display_length���ŕ\��
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDraw(x, y, tmpStr);

	delete[] tmpStr;
}

void BitmapText::textDrawMessageWithShadow(int x, int y, char * string, unsigned int display_lengh)
{
	// ���������J�E���g���A�\�����������{���̕�������葽����΂��̂܂ܕ\��
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDrawWithShadow(x, y, string);
		return;
	}

	// ��������display_length���ŕ\��
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDrawWithShadow(x, y, tmpStr);

	delete[] tmpStr;
}


void BitmapText::setFontColor(int r, int g, int b)
{
	R = r; G = g; B = b;
	SetDrawBright(R, G, B);
}

void BitmapText::setFontColorShadow(int r, int g, int b)
{
	mShadowR = r;
	mShadowG = g;
	mShadowB = b;
}

void BitmapText::setFontShadowOffset(int ofsX, int ofsY)
{
	mShadowOffsetX = ofsX;
	mShadowOffsetY = ofsY;
}
	
void BitmapText::reMapText(char *remapText)
{
	int num = 0;
	char *p ;

	p = remapText;
	char n = 0;
	while (*p && n < 255)
	{
		mFontMap[*p++] = n++;
	}

}

int BitmapText::isString(char c)
{
	return mFontMap[c];
}
