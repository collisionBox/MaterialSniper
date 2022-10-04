#include "DxLib.h"
#include "environment.h"
#include "ImageEffects.h"

void Effect::Init()
{
	fxMillTime = 0;
	fxMillTimeMax = 0;
	fxInterMillTime = 0;
	fxInterMillTimeMax = 0;
	alpha = 0.0f;
	fx = GraFxNone;
}

void Effect::GraphicfxStart(GraphicFx* fx, int millTime, int millInterval, float deltaTime)
{
	fxMillTime = 0;
	if (millTime == GraFxInfinity)
	{
		fxMillTimeMax = GraFxInfinity;
	}
	else
	{
		fxMillTimeMax = (millTime / 1000.0f) * deltatime;
	}

	return;
}//https://www.youtube.com/watch?v=LQBefExp8bw FPS計算スクリプトから
