#include "DxLib.h"
#include "environment.h"
#include "object.h"

Target::Target()
{
	handle = LoadGraph("img/target.jpg");
	bulletMarkHandle = LoadGraph("img/bulletMark.png");
}

Target::~Target()
{
}

void Target::Init()
{
	x = 0;
	y = 0;
	exRate = defaultExRate;
}

void Target::Update()
{
	Behavior();
	Draw();
}

void Target::Draw()
{

	DrawRotaGraph(x, y, exRate, 0,handle, false);
	DrawRotaGraph(x, y, exRate, 0, bulletMarkHandle, true);
}

void Target::Behavior()
{
	
}

void Target::HitTest()
{
}
