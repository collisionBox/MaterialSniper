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
	impactTime = 0;
	impactFlag = false;
	drawFlag = false;
	fireFlag = false;
}

void Bullet::Update(Aim& aim, Target& tag, float gameTime)
{
	if (tag.GetIsHit())
	{
		fireFlag = true;


	}
	if (!tag.GetAlive())
	{
		impactFlag = false;
		fireFlag = false;
		drawFlag = false;
		tag.SetIsHit();
	}
	if (!fireFlag)
	{
		int x = aim.GetMouseX();
		int y = aim.GetMouseY();
		//�^�[�Q�b�g�����_�Ƃ��Ēe���̍��W���v�Z
		prevX = tag.GetX() - x;
		prevY = tag.GetY() - y;
		impactTime = gameTime;
	}
	else if (fireFlag)
	{
		
		this->x = tag.GetX() - prevX;
		this->y = tag.GetY() - prevY;
		if (!drawFlag && gameTime > impactTime + 1.5)
		{
			drawFlag = true;
			impactFlag = true;
		}
	}
}

void Bullet::Draw()
{
}

void Bullet::DrawBulletMark(float& mouseX, float& mouseY, int& objX, int& objY, float& exRate, bool& flag)
{
	
	
	if (drawFlag)
	{
		if (flag)//�G�C����
		{
			DrawCircle(x, y, 10, green, true);
			DrawGraph(x, y, Markhandle, false);
			DrawRotaGraph(x, y, exRate, 0, Markhandle, true);
		}

	}
}


