#include "DxLib.h"
#include "environment.h"

Target::Target()
{
	handle = LoadGraph("img/target.jpg");

	filterHandle = LoadGraph("img/target.jpg");;
	GraphFilter(filterHandle, DX_GRAPH_FILTER_GAUSS, 16, 80);
	alpha = 0;
}

Target::~Target()
{
}

void Target::Init(ObjType type)
{
	this->type = type;
	x = 1500;
	y = 500;
	r = 10;
	alpha = 0;
	fadeFlag = false;
	isAlive = false;
	isHit = false;
}

void Target::Update()
{
	Behavior();
}

void Target::Draw(int& mouseX, int& mouseY, float& exRate, bool& flag,
	Bullet& bullet)
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
		DrawCircle(zoomX, zoomY, (minR + (5 * 9 ))*3, green, false);

	}
	else//非エイム時
	{
 		
		DrawRotaGraph(x, y, 1, 0, filterHandle, false);
		DrawCircle(x, y, minR+(5*9), green, false);

	}
	bullet.DrawBulletMark(zoomX,zoomY, mouseX, mouseY, exRate, flag);
	// 描画ブレンドモードをノーブレンドに戻す。
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	
	DrawFormatString(100, 800, black, "%d:%d\n%d:%d\n%d;%d", lx, ly, rx, ry, mouseX, mouseY);
	
	int X = abs(mouseX - this->x);
	for (int i = maxR; i >= 0; i -= 5)
	{


		if (i < X)
		{
			//DrawCircle(x, y, i, green, false);
		}
	}
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
		lx = zoomX - zoomCalculation;
		ly = zoomY - zoomCalculation;
		rx = zoomX + zoomCalculation;
		ry = zoomY + zoomCalculation;
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
			
			int x = abs(mouseX - this->x);
			
			//if ()
			{
				isHit = true;
			}
		}
	}
}

