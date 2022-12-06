#include "DxLib.h"
#include "environment.h"


Director::Director()
{
	bulletHandle = CreateFontToHandle(NULL, 40, 4);
	reloadStringHandle = CreateFontToHandle(NULL, 30, 3);
	text.SetFontImg(8, 5, "img/fontG.png");
	text.InitMapText("1234567890ABCDEFGHIJKLMOPQRSTUVWXYZ");
	Init();
}
Director::~Director()
{
	DeleteFontToHandle(bulletHandle);
	DeleteFontToHandle(reloadStringHandle);
}

void Director::Init()
{

	alpha = 0;
	gauge = 0;
	red = 0;
	breakNum = 0;
}

void Director::Update(Target& tag, Bullet& bullet, Aim& aim, float& gameTime)
{
	ReloadBlanking(aim);
	O2Gauge(aim);

}

void Director::O2Gauge(Aim& aim)
{
	gauge = aim.GetBreath();
	valiable = min + (max - min) * (gauge / 100);
	this->green = 255 * (gauge / 100);
	this->red = 255 - this->gauge;

	DrawBox(960 - 251, 950, 960 + 251, 1000, white, false);
	DrawBoxAA(min, 949, valiable, 999, GetColor(red, green, 0), true);
	//DrawFormatString(700, 700, green, "%f\n%d",gauge, valiable);
}

void Director::ReloadBlanking(Aim& aim)
{
	if (aim.GetMagazin() <= 2 && aim.GetMagazin() > 0)
	{
		alpha += blankingSpeed;
		if (alpha >= 255)
		{
			blankingSpeed *= -1;
		}
		else if (alpha <= 0)
		{
			blankingSpeed *= -1;
		}
	}
	else if (aim.GetMagazin() <= 0)
	{
		alpha = 255;
	}
	else
	{
		alpha = 0;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 113);
	DrawBox(x - 5, y - 40, x + 125, y + 55, GetColor(200, 200, 200), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//DrawFormatString(x, y, white, "Test");

	DrawFormatStringToHandle(x, y - 30, white, reloadStringHandle, "Reload");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	int a = aim.GetMagazin();
	DrawFormatString(x, y, white ,"%d / %d", a, aim.GetCarriedNum());
	text.test();
	text.TextDraw(x, y, "TEST");
	//DrawFormatString(0, 0, white, "%d", breakNum);
}



