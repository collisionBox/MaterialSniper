#include "DxLib.h"
#include "environment.h"
#include "bullet.h"
#include "object.h"
Target tag;
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

void Bullet::Update( int& posX, int& posY, float& exRate)
{
	if (tag.getIsHit() == true)
	{
		x = posX;
		y = posY;
		DrawBulletMark(exRate);
	}
}

void Bullet::Draw()
{
}

void Bullet::DrawBulletMark(float& exRate)
{
	
	DrawRotaGraph(x, y, exRate, 0, Markhandle, true);
	
}

