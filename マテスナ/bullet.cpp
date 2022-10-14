#include "DxLib.h"
#include "environment.h"
#include "bullet.h"
#include "object.h"
#include "aim.h"
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

}

void Bullet::Update(Aim& aim, Target& tag)
{

	if (tag.GetIsHit() == true)
	{
		drawFlag = true;
		x = aim.GetMouseX();
		y = aim.GetMouseY();
		if (tag.GetType() == MOVE)
		{
			x += tag.GetSpeed();

		}
	}
}

void Bullet::Draw()
{
}

void Bullet::DrawBulletMark(float& exRate)
{
	if (drawFlag)
	{
		DrawRotaGraph(x, y, exRate, 0, Markhandle, true);

	}
	
}

