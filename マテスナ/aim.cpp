#include "DxLib.h"
#include "environment.h"

Aim::Aim()
{
	// 画像を読み込む
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
	isLeftClick = false;
	prevMousePosX = windowX / 2;
	prevMousePosY = windowY / 2;
}

void Aim::Update(Target& tag, Bullet& bullet, float& gameTime, float& deltaTime)
{

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		Zoom(gameTime, deltaTime);
		isRightClick = true;
		if (GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z))
		{
			tag.HitTest(mouseX, mouseY, isRightClick, gameTime);
		}
		
	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)
	{
		ExRate = 1.0f;
		isRightClick = false;
	}
	
	Draw(tag,bullet);
	
}

void Aim::Draw(Target& tag, Bullet& bullet)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph2(prevMousePosX, prevMousePosY, prevMousePosX, prevMousePosY, ExRate, 0, handle, false);//背景(マウスを中心に拡大)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	tag.Draw(prevMousePosX, prevMousePosY, ExRate, isRightClick,bullet);//的
	if (isRightClick)
	{
		DrawRotaGraph(prevMousePosX, prevMousePosY, 1, 0, crosshairHandle, true);//クロスヘア
	}
	
	//DrawFormatString(50, 50, white, "%d\n%d", prevMousePosX, prevMousePosY);
	DrawCircle(prevMousePosX, prevMousePosY, 5, red, true);
}

void Aim::Zoom(float& time, float& deltaTime)
{
	MouseBehavior(time, deltaTime);
	ExRate = magnificationRate;

}

void Aim::MouseBehavior(float& time, float& deltaTime)
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
	//prevMousePosX += cos(time / 2)*100 *deltaTime;
	//prevMousePosY += sin(time * 2) *100* deltaTime;
}
