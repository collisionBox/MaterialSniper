#include "DxLib.h"
#include "environment.h"
#include "object.h"
#include "bullet.h"
#include <math.h>
Target::Target()
{
	handle = LoadGraph("img/target.jpg");
	alpha = 0;
}

Target::~Target()
{
}

void Target::Init(ObjType type)
{
	this->type = type;
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

void Target::Draw(int& mouseX, int& mouseY, float& exRate, bool& flag, Bullet& bullet)
{
	int prevX = mouseX - x;
	int prevY = mouseY - y;
	zoomX = x - prevX;
	zoomY = y - prevY;

	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//描画
	if (flag)//エイム時
	{
		DrawRotaGraph(zoomX, zoomY, exRate, 0, handle, false);
		
	}
	else//非エイム時
	{
		DrawRotaGraph(x, y, 1, 0, handle, false);
		
	}
	bullet.DrawBulletMark(exRate);

	// 描画ブレンドモードをノーブレンドに戻す。
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	
	DrawFormatString(100, 800, black, "%d:%d\n%d:%d\n%d;%d", lx, ly, rx, ry, mouseX, mouseY);

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

void Target::HitTest(int& mouseX, int& mouseY, bool& flag)
{
	if (flag)//ズーム状態
	{
		lx = zoomX - (imgSize / 6 * 3 + imgSize);
		ly = zoomY - (imgSize / 6 * 3 + imgSize);
		rx = zoomX + (imgSize / 6 * 3 + imgSize);
		ry = zoomY + (imgSize / 6 * 3 + imgSize);
	}
	else
	{
		lx = x - imgHalfSize;
		ly = y - imgHalfSize;
		rx = x + imgHalfSize;
		ry = y + imgHalfSize;
	}
	
	if (isAlive)
	{
		if (lx <= mouseX && ly <= mouseY &&
			rx >= mouseX && ry >= mouseY)
		{
			isHit = true;
		}
	}
}

