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
	int prevX = mouseX - x;
	int prevY = mouseY - y;
	zoomX = x - prevX;
	zoomY = y - prevY;

	// �`��u�����h���[�h���A���t�@�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//�`��
	if (flag)//�G�C����
	{
		DrawRotaGraph(zoomX, zoomY, exRate, 0, handle, false);
		
	}
	else//��G�C����
	{
		DrawRotaGraph(x, y, 1, 0, handle, false);
		
	}
	// �`��u�����h���[�h���m�[�u�����h�ɖ߂��B
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
	if (flag)
	{
		lx = zoomX - (imgSize / 6 * 3 + imgSize);zoom�̒l�������Ŏg���Ă��邩�ǂ����m�F
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
	int f = 0;
	if (CheckHitKey(KEY_INPUT_M))
	{
		if (f)
		{
			f = false;
		}
		else
		{
			f = true;
		}
	}
	DrawBox(lx, ly, rx, ry, red, f);

	if (isAlive)
	{
		if (lx >= mouseX && ly >= mouseY &&
			rx <= mouseX && ry <= mouseY)
		{
			isHit = true;
		}
	}
}
