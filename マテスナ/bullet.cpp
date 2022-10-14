#include "DxLib.h"
#include "environment.h"

Bullet::Bullet()
{
	Markhandle = LoadGraph("img/bulletMark.png");
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
	if (tag.GetIsHit() == true )
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
}

void Bullet::Draw()
{
}

void Bullet::DrawBulletMark(int& zoomX, int& zoomY, int& mouseX, int& mouseY, float& exRate, bool& flag)
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
		}
		
		DrawFormatString(500, 500, black, " %d %d", zoomX, zoomY);
	}
	
}

