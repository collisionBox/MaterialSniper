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
	//�b����������
	fxMillTime = 0;
	//���������p���Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
	if (millTime == GraFxInfinity)
	{
		fxMillTimeMax = GraFxInfinity;
	}
	else
	{
		fxMillTimeMax = (millTime / 1000.0f) * deltaTime;
	}
	//�Ԋu�̏�����
	fxInterMillTime = 0;
	fxInterMillTimeMax = (millInterval / 1000.0f) * deltaTime;
	//��ނ�ݒ�
	Fx = fx;
	return;
