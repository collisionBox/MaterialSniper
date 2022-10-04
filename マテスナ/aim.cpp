#include "DxLib.h"
#include "environment.h"
#include "Aim.h"
#include "object.h"

Aim::Aim()
{
	// âÊëúÇì«Ç›çûÇﬁ
	handle = LoadGraph("img/test.png");
	bgHandle = handle;
	crosshairHandle = LoadGraph("img/crosshair.png");

}
Aim::~Aim()
{
	DeleteGraph(handle);
	DeleteGraph(crosshairHandle);
}
void Aim::Init()
{
	isRightClick = false;
	prevMousePosX = windowX / 2;
	prevMousePosY = windowY / 2;
}
void Aim::Update(Target tag)
{

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		Zoom();
		isRightClick = true;
		
	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)
	{
		ExRate = 1.0f;
		isRightClick = false;
	}
	Draw(tag);
}

void Aim::Draw(Target tag)
{

	DrawRotaGraph2(prevMousePosX, prevMousePosY, prevMousePosX, prevMousePosY, ExRate, 0, handle, false);
	tag.Draw(ExRate);
	if (isRightClick)
	{
		DrawRotaGraph(prevMousePosX, prevMousePosY, 1, 0, crosshairHandle, true);
	}
	
	//DrawFormatString(50, 50, white, "%d\n%d", prevMousePosX, prevMousePosY);

}

void Aim::Zoom()
{
	MouseBehavior();
	ExRate = magnificationRate;

}

void Aim::MouseBehavior()
{
	GetMousePoint(&mouseX, &mouseY);
	if (mouseX <= 0)
	{
		mouseX = 0;
	}
	if (mouseX >= windowX)
	{
		mouseX = windowX;
	}
	if (mouseY <= 0)
	{
		mouseY = 0;
	}
	if (mouseY >= windowY)
	{
		mouseY = windowY;
	}
	prevMousePosX = mouseX;
	prevMousePosY = mouseY;
}
