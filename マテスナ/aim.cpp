#include "DxLib.h"
#include "environment.h"

Aim::Aim()
{
	// âÊëúÇì«Ç›çûÇﬁ
	handle = LoadGraph("img/test.png");
	bgHandle = handle;
	scorpHandle = LoadGraph("img/crosshair.png");
	lectilHandle = LoadGraph("img/lectil.png");
	Init();
}
Aim::~Aim()
{
	DeleteGraph(handle);
	DeleteGraph(lectilHandle);
	DeleteGraph(scorpHandle);
}
void Aim::Init()
{
	isRightClick = false;
	isLeftClick = false;
	fireFlag = true;
	reloadFlag = false;
	nowTime = 0;
	magazin = maxMagazin + 1;
	carriedNum = carriedNumMax - maxMagazin;
	prevMousePosX = windowX / 2;
	prevMousePosY = windowY / 2;
	aimming = lectilHandle;
}

void Aim::Update(Target& tag, Bullet& bullet, float& gameTime, float& deltaTime)
{

	
	MouseBehavior(tag, gameTime, deltaTime);
	Draw(tag,bullet);
	
}

void Aim::Draw(Target& tag, Bullet& bullet)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph2(prevMousePosX, prevMousePosY, prevMousePosX, prevMousePosY, ExRate, 0, handle, false);//îwåi(É}ÉEÉXÇíÜêSÇ…ägëÂ)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	tag.Draw(prevMousePosX, prevMousePosY, ExRate, isRightClick,bullet);//ìI
	
	//DrawRotaGraph(prevMousePosX, prevMousePosY, 1, 0, aimming, true);//ÉNÉçÉXÉwÉA

	DrawFormatString(50, 50, green, "%f:%f", prevMousePosX,prevMousePosY);
	DrawCircle(prevMousePosX, prevMousePosY, 5, red, true);
	
}

void Aim::MouseBehavior(Target& tag, float& gameTime, float& deltaTime)
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
	prevMousePosX += cos(gameTime)*15;
	prevMousePosY += sin(gameTime*2)*15;
	
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		ExRate = magnificationRate;
		aimming = scorpHandle;
		isRightClick = true;

	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)
	{
		ExRate = 1.0f;
		aimming = lectilHandle;
		isRightClick = false;
	}
	if (fireFlag)
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z))
		{
			magazin -= 1;
			tag.HitTest(mouseX, mouseY, isRightClick, gameTime);
			fireFlag = false;

		}
	}
	if (!fireFlag && !(GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z)))
	{
		fireFlag = true;
	}
	
	MagazinDirector(gameTime);
}

void Aim::MagazinDirector(float& gameTime)
{
	if (CheckHitKey(KEY_INPUT_R) && magazin < maxMagazin + 1)
	{
		nowTime = gameTime;
		reloadFlag = true;
	}
	if (reloadFlag)
	{
		if (gameTime - nowTime >= reloadTime)
		{
			int subtrahend = (maxMagazin + 1) - magazin;//ågçsêîÇ©ÇÁà¯Ç≠êî
			carriedNum -=subtrahend;
			if (magazin >= 1)
			{
				magazin = maxMagazin + 1;
			}
			else if(magazin == 0)
			{
				magazin = maxMagazin;
			}
			fireFlag = true;
			reloadFlag = false;
		}
	}
	
	if (magazin <= 0)
	{
		fireFlag = false;
	}
	if (magazin <= 0 && carriedNum <= 0)
	{
		fireFlag = false;
	}
}
