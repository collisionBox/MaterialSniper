#include "DxLib.h"
#include "environment.h"
#include "Aim.h"
#include "object.h"

Aim::Aim()
{
	// �摜��ǂݍ���
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
		if (GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z))
		{
			tag.HitTest(prevMousePosX, prevMousePosY, isRightClick);
		}
		
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph2(prevMousePosX, prevMousePosY, prevMousePosX, prevMousePosY, ExRate, 0, handle, false);//�w�i(�}�E�X�𒆐S�Ɋg��)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	tag.Draw(prevMousePosX, prevMousePosY, ExRate, isRightClick);//�I
	if (isRightClick)
	{
		//DrawRotaGraph(prevMousePosX, prevMousePosY, 1, 0, crosshairHandle, true);//�N���X�w�A
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
