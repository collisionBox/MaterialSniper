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

void Bullet::Update(Aim& aim, Target& tag, float& gameTime, float& deltaTime)
{	
	//if (tag.GetIsHit())
	if(aim.GetIsLeftClick())
	{
		if (!fireFlag)
		{
			float x = aim.GetMouseX();
			float y = aim.GetMouseY();
			//ターゲットを原点として弾痕の座標を計算
			prevX = tag.GetX() - x;
			prevY = tag.GetY() - y;
			fireFlag = true;
		}
		
	}
	if (fireFlag)
	{
		if (tag.GetZ() > z)
		{
			z += initialV * deltaTime;
		}
		if (tag.GetZ() < z)
		{
			tag.HitTest(x, y, aim.GetIsClick(), gameTime);
			z = 0;
			fireFlag = false;

		}
		

	}

	this->x = tag.GetX() - prevX;
	this->y = tag.GetY() - prevY;
	if (tag.GetIsHit())
	{
		drawFlag = true;

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

void Bullet::DrawBulletMark(float& mouseX, float& mouseY, float& objX, float& objY, float& exRate, bool& flag)
{
	
	if (drawFlag)
	{

		
		if (flag)
		{
			DrawRotaGraphF(x, y, exRate, 0, Markhandle, true);
		}

	}
}


