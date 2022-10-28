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

void Bullet::Update(Aim& aim, Target& tag, float gameTime)
{
	if (!tag.GetIsHit())
	{
		x = aim.GetMouseX();
		y = aim.GetMouseY();

	}
	if (tag.GetIsHit())
	{
		if (!fireFlag)
		{
			fireFlag = true;
		}
		else if (fireFlag )
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

void Bullet::DrawBulletMark(float& mouseX, float& mouseY, int& objX, int& objY, float& exRate, bool& flag)
{
	if (!drawFlag)
	{
		int prevX = objX - mouseX;
		int prevY = objY - mouseY;
		x = objX - prevX;
		y = objY - prevY;
		
	}
	
	if (drawFlag)
	{
		int prevX = mouseX - x;
		int prevY = mouseY - y;
		zoomX = x - prevX;
		zoomY = y - prevY;
		
		if (flag)
		{
			DrawRotaGraph(zoomX, zoomY, exRate, 0, Markhandle, true);
		}

	}
}


