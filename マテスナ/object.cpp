#include "DxLib.h"
#include "environment.h"

Target::Target()
{
	handle = LoadGraph("img/target.jpg");
	GetGraphSize(handle, &imgSizeX, &imgSizeY);
	imgHalfSizeX = imgSizeX / 2;
	imgHalfSizeY = imgSizeY / 2;
	zoomCalculation = imgSizeX / 6 * 3 + imgSizeX;
	filterHandle = LoadGraph("img/target.jpg");
	GraphFilter(filterHandle, DX_GRAPH_FILTER_GAUSS, 16, 80);
	alpha = 0;
	Init();
}

Target::~Target()
{
}

void Target::Init()
{
	x = GetRand(1920 - imgSizeX) + imgHalfSizeX;
	y = GetRand(1080 - imgSizeY) + imgHalfSizeY;
	z = 10;
	r = 10;
	alpha = 0;
	fadeFlag = false;
	isAlive = false;
	prevAlive = false;
	isHit = false;
}

void Target::Update(Bullet& bul, float& gameTime)
{
	Behavior(bul,gameTime);
}

void Target::Draw(float mouseX, float mouseY, float& exRate, bool& flag,
	Bullet& bullet)
{
	int prevX = (int)(mouseX - x);
	int prevY = (int)(mouseY - y);
	zoomX = x - prevX;
	zoomY = y - prevY;
	
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//描画
	if (flag)//エイム時
	{
		DrawRotaGraph(zoomX, zoomY, exRate, 0, handle, false);
		bullet.DrawBulletMark(mouseX, mouseY, zoomX, zoomY, exRate, flag);

		DrawCircle(zoomX, zoomY, (minR + (0 * 9 ))*3, green, false);

	}
	else//非エイム時
	{
 		
		DrawRotaGraph(x, y, onNozoomExRate, 0, filterHandle, false);
		bullet.DrawBulletMark(mouseX,mouseY, x, y, exRate, flag);

		DrawCircle(x, y, minR+(5*9), green, false);

	}
	//bullet.DrawBulletMark(mouseX, mouseY, exRate, flag);
	// 描画ブレンドモードをノーブレンドに戻す。
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	
	DrawFormatString(100, 800, green, "%d:%d\n%d:%d\n%d;%d", x,y,zoomX,zoomY,mouseX,mouseY);
	//DrawBox(imgHalfSizeX, imgHalfSizeY, 1920 - imgHalfSizeX, 1080 - imgHalfSizeY, red, true);
	int X = abs(mouseX - this->x);
	for (int i = maxR; i >= 0; i -= 5)
	{


		if (i < X)
		{
			//DrawCircle(x, y, i, green, false);
		}
	}
	DrawFormatString(100, 500, green, "%f", deadTime);

}

void Target::Behavior(Bullet& bul, float& gameTime)
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))
	{
		fadeFlag = true;

	}*/
	if (!isAlive && !prevAlive)
	{

		fadeFlag = true;
	}


	if (fadeFlag)
	{
		alpha += deltaAlphaNum;
		if (alpha >= 255)
		{
			alpha = 255;
			isAlive = true;
			fadeFlag = false;
			prevAlive = isAlive;
		}
	}


	if (prevAlive && !isAlive)
	{
		if (bul.GetImpactFlag())
		{
			if (gameTime - deadTime > waitTime)
			{
				alpha -= deltaAlphaNum;
			}
		}



		if (alpha < 0)
		{
			prevAlive = isAlive;
			x = GetRand(1920 - imgSizeX) + imgHalfSizeX;
			y = GetRand(1080 - imgSizeY) + imgHalfSizeY;

		}

	}
}
void Target::HitTest(int& mouseX, int& mouseY, bool flag, float& gameTime)
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
		lx = x - imgHalfSizeX;
		ly = y - imgHalfSizeY;
		rx = x + imgHalfSizeX;
		ry = y + imgHalfSizeY;
	}

	if (isAlive)
	{
		if (lx <= mouseX && ly <= mouseY &&
			rx >= mouseX && ry >= mouseY)
		{
			float x = abs(mouseX - this->x);
			float y = abs(mouseY - this->y);
			float distance = sqrtf(x * x + y * y);
			if (distance <= minR + (0 * 9) * 3)//クリティカル判定
			{

			}


			//if ()
			{
				deadTime = gameTime;
				isHit = true;
				isAlive = false;
			}
		}
	}
}

