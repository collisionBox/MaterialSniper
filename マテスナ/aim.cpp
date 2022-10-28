#include "DxLib.h"
#include "environment.h"

Aim::Aim()
{
	// �摜��ǂݍ���
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
void Aim::Init()//������
{
	isRightClick = false;
	isLeftClick = false;
	fireFlag = true;
	reloadFlag = false;
	nowTime = 0;
	magazin = maxMagazin + 1;
	carriedNum = carriedNumMax - maxMagazin;
	x = windowX / 2;
	y = windowY / 2;
	aimming = lectilHandle;
}

void Aim::Update(Target& tag, Bullet& bullet, float& gameTime, float& deltaTime)
{

	
	MouseBehavior(tag, gameTime, deltaTime);
	Draw(tag,bullet);
	
}

void Aim::Draw(Target& tag, Bullet& bullet)
{
	//�f�o�b�O�p�ɔw�i�𔖂�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph2(x, y, x, y, ExRate, 0, handle, false);//�w�i(�}�E�X�𒆐S�Ɋg��)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

	tag.Draw(x, y, ExRate, isRightClick,bullet);//�I
	
	DrawRotaGraph(x, y, 1, 0, aimming, true);//�N���X�w�A

	DrawFormatString(50, 50, green, "%f:%f", x,y);
	DrawCircle(x, y, 5, red, true);
	
}

void Aim::MouseBehavior(Target& tag, float& gameTime, float& deltaTime)
{
	GetMousePoint(&mouseX, &mouseY);
	//��ʊO�ɂłȂ��悤�ɂ���
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
	x = mouseX;
	y = mouseY;
	//�E�N���b�N�i�G�C���j����
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)//������Ă���Ƃ�
	{
		//LShift�i���~�߁j����
		if (CheckHitKey(KEY_INPUT_LSHIFT) != 0)//������Ă���Ƃ�
		{
			omega = 0.008;
		}
		else if (CheckHitKey(KEY_INPUT_LSHIFT) == 0)//������Ă��Ȃ��Ƃ�
		{
			omega = 0.012f;
		}	
		v += omega;
		x += 15 * cos(v);
		y += 15 * sin(v * 2);
		ExRate = magnificationRate;
		aimming = scorpHandle;
		isRightClick = true;

	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)//������Ă��Ȃ��Ƃ�
	{
		ExRate = 1.0f;
		aimming = lectilHandle;
		isRightClick = false;
	}
	if (fireFlag)//�e����������
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
			int subtrahend = (maxMagazin + 1) - magazin;//�g�s�����������
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
