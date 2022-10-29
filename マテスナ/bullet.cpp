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
	if (tag.GetIsHit())
	{
		if (!fireFlag)
		{
			int x = aim.GetMouseX();
			int y = aim.GetMouseY();
			//ターゲットを原点として弾痕の座標を計算
			prevX = tag.GetX() - x;
			prevY = tag.GetY() - y;
			impactTime = gameTime;
			fireFlag = true;
		}
		else if (fireFlag && gameTime - impactTime > 1.5)
		{
			this->x = tag.GetX() - prevX;
			this->y = tag.GetY() - prevY;
			drawFlag = true;
			//tag.SetIsAlive();
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
	
	if (drawFlag)
	{

		
		if (flag)
		{
			DrawRotaGraph(x, y, exRate, 0, Markhandle, true);
		}

	}
}


