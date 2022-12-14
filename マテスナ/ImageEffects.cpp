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
	//秒数を初期化
	fxMillTime = 0;
	//もし無限継続なら、実際のMAX時間を計算させない
	if (millTime == GraFxInfinity)
	{
		fxMillTimeMax = GraFxInfinity;
	}
	else
	{
		fxMillTimeMax = (millTime / 1000.0f) * deltaTime;
	}
	//間隔の初期化
	fxInterMillTime = 0;
	fxInterMillTimeMax = (millInterval / 1000.0f) * deltaTime;
	//種類を設定
	Fx = fx;
	return;
