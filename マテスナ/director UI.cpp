#include "DxLib.h"
#include "environment.h"


Director::Director()
{
	bulletHandle = CreateFontToHandle(NULL, 40, 4);
	reloadStringHandle = CreateFontToHandle(NULL, 30, 3);
	Init();
}
Director::~Director()
{
}

void Director::Init()
{
	alpha = 0;
}

void Director::Update(Target& tag, Bullet& bullet, Aim& aim, float& gameTime)
{
	ReloadBlanking(aim);
	Draw(tag, bullet, aim, gameTime);
}

void Director::Draw(Target& tag, Bullet& bullet, Aim& aim, float& gameTime)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 113);
	DrawBox(x - 5, y - 40, x + 125, y + 55, GetColor(30, 30, 30), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawFormatStringToHandle(x, y - 30, white, reloadStringHandle, "Reload");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	O2Gauge(aim);
	DrawFormatStringToHandle(x, y, white, bulletHandle, "%d / %d", aim.GetMagazin(), aim.GetCarriedNum());
}

void Director::O2Gauge(Aim& aim)
{
	int min = 710;
	int max = 1210;
	int valiable = min + (max * (aim.GetBreath() / 100));
	DrawBox(960 - 251, 950, 960 + 251, 1000, white, false);
	DrawBox(min, 949, 960 + 250, 999, green, true);
	//�l�����A���^�C���Ɏg���ĂȂ��I
	
}

void Director::ReloadBlanking(Aim& aim)
{
	if (aim.GetMagazin() <= 2)
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
	else
	{
		alpha = 0;
	}

}

void Director::Sean()
{
	
}
