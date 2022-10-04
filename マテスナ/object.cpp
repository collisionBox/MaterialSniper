#include "DxLib.h"
#include "environment.h"
#include "object.h"

Target::Target()
{
	handle = LoadGraph("img/target.jpg");
}

Target::~Target()
{
}

void Target::Init()
{
	x = 100;
	y = 100;
}

void Target::Update()
{
	Behavior();
}

void Target::Draw(float exRate)
{
	
	DrawRotaGraph(x, y, exRate, 0,handle, false);
}

void Target::Behavior()
{
	
}

void Target::HitTest()
{
}
