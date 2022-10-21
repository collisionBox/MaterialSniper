#include "DxLib.h"
#include "environment.h"


Director::Director()
{
	bulletHandle = CreateFontToHandle(NULL, 40, 4);
	reloadStringHandle = CreateFontToHandle(NULL, 20, 3);
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawFormatStringToHandle(x, y - 30, white, reloadStringHandle, "Reload");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawFormatStringToHandle(x, y, white, bulletHandle, "%d / %d", aim.GetMagazin(), aim.GetCarriedNum());
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
