#include "DxLib.h"
#include "environment.h"
#include "object.h"
#include <math.h>
Target::Target()
{
	handle = LoadGraph("img/target.jpg");
	alpha = 0;
}

Target::~Target()
{
}

void Target::Init()
{
	x = 900;
	y = 500;
	alpha = 0;
	fadeFlag = false;
	isAlive = false;
	isHit = false;
}

void Target::Update()
{
	Behavior();
}

void Target::Draw(int mouseX, int mouseY, float exRate, bool flag)
{
	int zoomX = mouseX - x;
	int zoomY = mouseY - y;
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//描画
	if (flag)
	{
		DrawRotaGraph(x-zoomX, y-zoomY,  exRate, 0, handle, false);
	}
	else
	{
		DrawRotaGraph(x, y, exRate, 0, handle, false);
	}
	DrawFormatString(500, 500, red, "%d,%d", mouseX, mouseY);
	DrawCircle(mouseX * -3 + (150 * 2 / 3), mouseY * -3  , 5, red, true);
	// 描画ブレンドモードをノーブレンドに戻す。
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	

}

void Target::Behavior()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		fadeFlag = true;
		
	}
	if (fadeFlag && alpha <= 255)
	{
		alpha += deltaAlphaNum;
	}
	if (alpha >= 255)
	{
		isAlive = true;
	}
	
	
}

void Target::HitTest(int mouseX, int mouseY)
{
	int lx = x - imgHalfSize;
	int ly = y - imgHalfSize;
	int rx = x + imgHalfSize;
	int ry = y + imgHalfSize;
	DrawBox(lx, ly, rx, ry, red, false);
	if (isAlive)
	{
		if (lx >= mouseX && ly >= mouseY &&
			rx <= mouseX && ry <= mouseY)
		{
			isHit = true;
		}
	}
}
