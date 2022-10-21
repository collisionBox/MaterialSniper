#include "DxLib.h"
#include "environment.h"

Bullet::Bullet()
{
	Markhandle = LoadGraph("img/bulletMark.png");
	Init();
}

Bullet::~Bullet()
{
	DeleteGraph(Markhandle);
}

void Bullet::Init()
{
	drawFlag = false;
	fireFlag = false;
}

void Bullet::Update(Aim& aim, Target& tag)
{
	if (tag.GetIsHit())
	{
		if (!fireFlag)
		{
			x = aim.GetMouseX();
			y = aim.GetMouseY();
			fireFlag = true;
		}
		else if (fireFlag)
		{
			drawFlag = true;
			
		}
	}

	if (!tag.GetAlive())
	{
		fireFlag = false;
		drawFlag = false;
		tag.SetIsHit();
	}
}

void Bullet::Draw()
{
}

void Bullet::DrawBulletMark(float& mouseX, float& mouseY, float& exRate, bool& flag)
{
	if (drawFlag)
	{
		int prevX = mouseX - x;
		int prevY = mouseY - y;
		int zoomX = x - prevX;
		int zoomY = y - prevY;
		if (flag)
		{
			DrawRotaGraph(zoomX, zoomY, exRate, 0, Markhandle, true);
			DrawFormatString(100, 100, green, "%f:%f", zoomX, zoomY);
		}
		printfDx("%f:%f", zoomX, zoomY);

	}
}
照準と弾痕のずれの修正
具体的な値を画面にだして確認　prevMousePosXらとzoomXらの

