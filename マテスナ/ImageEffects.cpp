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
	//•b”‚ğ‰Šú‰»
	fxMillTime = 0;
	//‚à‚µ–³ŒÀŒp‘±‚È‚çAÀÛ‚ÌMAXŠÔ‚ğŒvZ‚³‚¹‚È‚¢
	if (millTime == GraFxInfinity)
	{
		fxMillTimeMax = GraFxInfinity;
	}
	else
	{
		fxMillTimeMax = (millTime / 1000.0f) * deltaTime;
	}
	//ŠÔŠu‚Ì‰Šú‰»
	fxInterMillTime = 0;
	fxInterMillTimeMax = (millInterval / 1000.0f) * deltaTime;
	//í—Ş‚ğİ’è
	Fx = fx;
	return;
