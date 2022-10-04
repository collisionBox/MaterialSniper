#include "DxLib.h"
#include "environment.h"
#include "bullet.h"

Bullet::Bullet()
{
	handle = LoadGraph("img/bulletMark.png");
}

Bullet::~Bullet()
{
	DeleteGraph(handle);
}

void Bullet::Init()
{

}

void Bullet::Update(bool& flag, int& posX, int& posY)
{
	if (flag)
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			OnClicBehavior(posX, posY);
			isClic = true;
			drawFlag = true;
			
		}
	}
	Draw();
}

void Bullet::Draw()
{
	if (drawFlag)
	{
		DrawRotaGraph(x, y, 1, 0, handle, true);
	}
	
}

void Bullet::OnClicBehavior(int& posX, int& posY)
{
	if (!isClic)
	{
		x = posX;
		y = posY;
	}
	

}
