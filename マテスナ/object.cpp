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
	director = new Director;
	Init();
}

Target::~Target()
{
	if (director != nullptr)
	{
		delete director;
		director = nullptr;
	}
}

void Target::Init()
{
	x = (float)(GetRand(1920 - imgSizeX) + imgHalfSizeX);
	y = (float)(GetRand(1080 - imgSizeY) + imgHalfSizeY);
	z = 10;
	r = 10;
	alpha = 0;
	hitNum = 0;
	criticalNum = 0;
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
	float prevX = mouseX - x;
	float prevY = mouseY - y;
	zoomX = x - prevX;
	zoomY = y - prevY;
	
	float x, y;
	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//描画
	if (flag)//エイム時
	{
		x = zoomX;
		y = zoomY;

	}
	else//非エイム時
	{
		x = this->x;
		y = this->y;
		
		//DrawCircle(this->x, this->y, minR+(5*9), green, false);

	}
	DrawRotaGraphF(x, y, exRate, 0, handle, false);

	// 描画ブレンドモードをノーブレンドに戻す。
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	
	bullet.DrawBulletMark(mouseX, mouseY, zoomX, zoomY, exRate, flag);
	/*for (float i = 0; i < 9.8f; i += 0.9f)
{
	DrawCircle(x, y, (minR + (i * 5.8)) * exRate, white, false);

}*/
	//DrawFormatString(100, 800, green, "%d:%d", hitNum, criticalNum);
	//DrawFormatString(100, 500, green, "%f", deadTime);
	//DrawBox(imgSizeX, imgSizeY, (1920 - imgSizeX) + imgHalfSizeX, (1080 - imgSizeY - 100) + imgHalfSizeY, red, false);

}

void Target::Behavior(Bullet& bul, float& gameTime)
{
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
		
			if (gameTime - deadTime > waitTime)
			{
				alpha -= deltaAlphaNum;
			}
		



		if (alpha < 0)
		{
			prevAlive = isAlive;
			x = (float)(GetRand(1920 - imgHalfSizeX));
			y = (float)(GetRand(1080 - imgHalfSizeY));

		}

	}
}
void Target::HitTest(float& mouseX, float& mouseY, bool flag, float& gameTime)
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

			int prevPoint = 100;
			for (float i = 0; i < 9.8f; i += 0.9f)
			{
				if (distance <= (minR + (i * 5.9f)) * 3.0f)
				{
					point += prevPoint;
					break;
				}
				prevPoint -= 10;
			}
#if 0
			if (distance <= minR + (0 * 9) * 3)//クリティカル判定
			{
				criticalNum++;
			}
			else if (distance <= (minR + (5 * 9)) * 3)
			{
				director->BreakNum();
				hitNum++;
				
			}
#endif
			deadTime = gameTime;
			isHit = true;
			isAlive = false;
		}
	}
}

