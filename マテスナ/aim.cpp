#include "DxLib.h"
#include "environment.h"

Aim::Aim()
{
	// �摜��ǂݍ���
	//handle = LoadGraph("img/test.png");
	handle = LoadGraph("movie/bg.mp4");
	PlayMovieToGraph(handle);
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
	omega = nomalCameraShake;
	breath = 100;
	LShiftFlag = false;
	variableTime = 0;
}

void Aim::Update(Director director, Target& tag, Bullet& bullet, float& gameTime, float& deltaTime)
{

	
	MouseBehavior(director,tag, gameTime, deltaTime);
	Draw(tag,bullet);
	
}

void Aim::Draw(Target& tag, Bullet& bullet)
{
	//�f�o�b�O�p�ɔw�i�𔖂�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawRotaGraph2F(x, y, x, y, ExRate, 0, handle, false);//�w�i(�}�E�X�𒆐S�Ɋg��)
	DrawExtendGraph(0, 0, 1920, 1080, handle, false);
	if (GetMovieStateToGraph(handle) == 0)
	{
		SeekMovieToGraph(handle, 0);
		PlayMovieToGraph(handle);
	}
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

	tag.Draw(x, y, ExRate, isRightClick, bullet);//�I

	
	DrawRotaGraphF(x, y, 1, 0, aimming, true);//�N���X�w�A

	//DrawFormatString(50, 50, green, "%f:%f", x,y);
	//DrawCircle(x, y, 5, red, true);
	text.TextDraw(50, 0, "1234");
}

void Aim::MouseBehavior(Director director, Target& tag, float& gameTime, float& deltaTime)
{
	float xBehavior = (15 * cos(v)) / magnificationRate;
	float yBehavior = (15 * sin(v * 2)) / magnificationRate;
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
	x = (float)(mouseX);
	y = (float)(mouseY);
	//�E�N���b�N�i�G�C���j����
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)//������Ă���Ƃ�
	{
		
		xBehavior = 15 * cos(v);
		yBehavior = 15 * sin(v * 2);
		ExRate = magnificationRate;
		aimming = scorpHandle;
		isRightClick = true;

	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)//������Ă��Ȃ��Ƃ�
	{
		ExRate = 1.0f;
		aimming = lectilHandle;
		isRightClick = false;
		xBehavior = (15 * cos(v)) / magnificationRate;
		yBehavior = (15 * sin(v * 2)) / magnificationRate;
	}
	
	FireFlagBehavior();
	O2gauge(director,gameTime, deltaTime);
	v += omega;
	x += xBehavior;
	y += yBehavior;
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

void Aim::FireFlagBehavior()
{
	if (fireFlag)//�e����������
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z))
		{
			magazin -= 1;
			fireFlag = false;
			isLeftClick = true;
		}
	}
	if (!fireFlag && !(GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_Z)))
	{
		fireFlag = true;
		isLeftClick = false;
	}
}

void Aim::O2gauge(Director director, float& gameTIme, float& delatTime)
{
	float consumedO2 = 100 / stopBreathTime;//�����~�߂Ă����鎞�Ԃ������ʂ��v�Z
	if (!pantingFlag)
	{
		//LShift�i���~�߁j����
		if (CheckHitKey(KEY_INPUT_LSHIFT) != 0)//������Ă���Ƃ�
		{
			LShiftFlag = true;
		}
		else if (CheckHitKey(KEY_INPUT_LSHIFT) == 0)//������Ă��Ȃ��Ƃ�
		{
			LShiftFlag = false;
		}
	}
	
	if (LShiftFlag)
	{
		if (breath > 0)
		{
			breath -= consumedO2 * delatTime;
			omega = stopBreathCameraShake;
		}
		else if (breath <= 0)
		{
			breath = 0;
			pantingFlag = true;
			LShiftFlag = false;
			variableTime = gameTIme + 1.5;
		}
	}
	if (!LShiftFlag && !pantingFlag)
	{
		omega = nomalCameraShake;
		if (breath < 100)
		{
			breath += recoverO2 * delatTime;
		}
		else if (breath > 100)
		{
			breath = 100;
		}
	}
	if (pantingFlag)
	{
		omega = onPantingCameraShake;
		//if (variableTime <= gameTIme)
		{
			breath += recoverO2 * delatTime;
			if (breath > 100)
			{
				breath = 100;
				pantingFlag = false;
			}
		}
	}
	//DrawFormatString(500, 500, green, "%f", breath);
}
